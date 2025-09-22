#!/bin/bash

PROG=./cub3d
FAILED=0

# Função para rodar um teste
# $1 = nome do teste
# $2 = argumento (arquivo)
# $3 = exit code esperado
run_test() {
    name=$1
    arg=$2
    expected_code=$3

    echo -n "[TEST] $name... "

    output=$(valgrind --quiet --leak-check=full --show-leak-kinds=all \
    --errors-for-leak-kinds=all --error-exitcode=42 $PROG "$arg" 2>&1)
    status=$?

    if [ $status -eq 42 ]; then
        echo "❌ FAILED (Memory leaks detectados)"
        FAILED=$((FAILED+1))
        return
    fi

    if [ $status -eq $expected_code ]; then
        echo "✅ PASSED (exit=$status)"
    else
        echo "❌ FAILED"
        echo "   Esperado: exit=$expected_code"
        echo "   Recebido: exit=$status"
        echo "   Saída:    $output"
        FAILED=$((FAILED+1))
    fi
}

# -------- TESTES -------- #

# 0 → sucesso
#run_test "Mapa válido simples" "assets/maps/tests/valid1.cub" 0
#run_test "Mapa válido complexo" "assets/maps/tests/valid2.cub" 0
#run_test "Linhas em branco entre configs e mapa" "assets/maps/tests/blank_lines.cub" 0

# 1 → erro de input
run_test "Extensão inválida" "assets/maps/tests/invalid_extension.txt" 1

# 2 → erro de leitura
run_test "Arquivo inexistente" "nao_existe.cub" 2
run_test "Arquivo vazio" "assets/maps/tests/empty.cub" 2

# 4 → erro de mapa/configurações
run_test "Mapa com quebra de linha ' '" "assets/maps/tests/empty_line_space.cub" 4
run_test "Mapa com quebra de linha \n" "assets/maps/tests/invalid_newline.cub" 4
run_test "Mapa não fechado" "assets/maps/tests/invalid_open.cub" 4
run_test "Caracter inválido" "assets/maps/tests/invalid_char.cub" 4
run_test "Arquivo apenas com configs" "assets/maps/tests/only_config.cub" 4
run_test "Mapa sem jogador" "assets/maps/tests/no_player.cub" 4
run_test "Mapa com mais de um jogador" "assets/maps/tests/multiple_players.cub" 4
run_test "Mapa com espaço no meio" "assets/maps/tests/invalid_blank_spot.cub" 4
run_test "Mapa agregação aberta" "assets/maps/tests/open_room.cub" 4
run_test "Mapa aberto em cima" "assets/maps/tests/im_tired.cub" 4


# 5 - erro ralacionado as configs
run_test "Configuração ausente" "assets/maps/tests/invalid_config.cub" 5
run_test "Configuração duplicada" "assets/maps/tests/invalid_duplicate.cub" 5
run_test "Textura inexistente" "assets/maps/tests/xpm_missing_no.cub" 5
run_test "Textura SO não XPM" "assets/maps/tests/xpm_invalid_so.cub" 5
run_test "Faltando extensão '.xpm'" "assets/maps/tests/missing_xpm_extension.cub" 5
run_test "Extensão xpm errada (.txt)" "assets/maps/tests/invalid_xpm_extension.cub" 5

# Resultado final
echo
if [ $FAILED -eq 0 ]; then
    echo "🎉 Todos os testes passaram sem leaks!"
else
    echo "⚠️ $FAILED testes falharam"
fi

exit $FAILED
