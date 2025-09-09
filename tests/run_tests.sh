#!/bin/bash

# Caminho para o executável
PROG=./cub3d
FAILED=0

# Função para rodar um teste
run_test_extensao() {
    name=$1          # nome do teste
    argumento=$2     # arquivo passado como argumento
    esperado=$3      # parte do texto que esperamos
    esperado_code=$4 # código de saída esperado

    echo "Rodando: $name '$argumento'"

    # roda o programa, captura saída e código de retorno
    saida=$($PROG "$argumento" 2>&1)
    code=$?

    if [[ "$saida" == *"$esperado"* && $code -eq $esperado_code ]]; then
        echo "✅"
    else
        echo "❌"
        echo "   Esperado: '$esperado' Code $esperado_code"
		echo "   Exit code: '$code'"
		echo "   Obtido:   '$saida'"
        FAILED=$((FAILED+1))
    fi
}

# Lista de testes parsing
	# extensão do arquivo
	run_test_extensao "Extensão correta" "mapa.cub" "" 0
	run_test_extensao "Extensão errada" "mapa.txt" "Invalid termination" 1
	run_test_extensao "Sem argumento" "" "Error" 1
	run_test_extensao "Extensão quase válida" "mapa..cu" "Invalid termination" 1

if [ $FAILED -eq 0 ]; then
    echo "🎉 Todos os testes passaram!"
else
    echo "❌ $FAILED teste(s) falharam"
fi
    exit $FAILED

