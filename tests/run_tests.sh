#!/bin/bash

PROG=./cub3d
FAILED=0

# --- Função para testar arquivos de extensão / erros simples ---
run_test_extensao() {
    name=$1
    argumento=$2
    esperado=$3
    esperado_code=$4

    echo "Rodando: $name '$argumento'"

    saida=$($PROG "$argumento" 2>&1)
    code=$?

    if [[ "$saida" == *"$esperado"* && $code -eq $esperado_code ]]; then
        echo "✅"
    else
        echo "❌ Falha: $name"
        echo "   Esperado: '$esperado' Code $esperado_code"
        echo "   Obtido: '$saida' Code $code"
        FAILED=$((FAILED+1))
    fi
}

# --- Função para testar o conteúdo completo de um .cub ---
run_test_cub() {
    name=$1
    arquivo=$2
    expected_output=("${!3}")

    echo "Rodando teste: $name '$arquivo'"

    saida=$($PROG "$arquivo" 2>&1)
    code=$?

    for linha in "${expected_output[@]}"; do
        echo "$saida" | grep -qF "$linha"
        if [ $? -ne 0 ]; then
            echo "❌ Falha no teste: linha não encontrada -> '$linha'"
            FAILED=$((FAILED+1))
        fi
    done

    if [ $code -ne 0 ]; then
        echo "❌ Código de saída inesperado: $code"
        FAILED=$((FAILED+1))
    fi
}

# --- Lista de testes de extensão / argumentos ---
run_test_extensao "Extensão correta" "./maps/test.cub" "" 0
run_test_extensao "Extensão errada" "mapa.txt" "Invalid termination" 1
run_test_extensao "Sem argumento" "" "Error" 1
run_test_extensao "Extensão quase válida" "mapa..cu" "Invalid termination" 1

# --- Saída esperada do teste completo ---
expected_output_test=(
"NO texture: ./path_to_the_north_texture"
"SO texture: ./path_to_the_south_texture"
"WE texture: ./path_to_the_west_texture"
"EA texture: ./path_to_the_east_texture"
"Floor color: 220,100,0"
"Ceiling color: 225,30,0"
"Map width: 6, height: 5"
"Map:"
"111111"
"100001"
"10N001"
"100001"
"111111"
)

# --- Teste do mapa e configurações ---
run_test_cub "Teste completo do .cub" "./maps/test.cub" expected_output_test[@]

# --- Relatório final ---
if [ $FAILED -eq 0 ]; then
    echo "🎉 Todos os testes passaram!"
else
    echo "❌ $FAILED teste(s) falharam"
fi

exit $FAILED
