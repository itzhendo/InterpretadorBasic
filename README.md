# InterpretadorBasic
 Interpretador Basic simples de comandos que lê instruções de um arquivo e executa operações básicas, como atribuições, impressão de variáveis e controle de fluxo
 
 LET: Atribui um valor a uma variável.
 PRINT: Imprime o valor de uma expressão.
 GOTO: Salta para uma linha especificada no arquivo.
 HALT: Encerra a execução do interpretador.


 Exemplo:
 Criar um arquivo de entrada: Crie um arquivo (.bas) com as instruções no seguinte formato:
 //=================
 10 LET A = 23
 20 LET B = 8
 30 PRINT B
 40 LET C = A - B
 50 PRINT C
 60 GOTO 80
 70 PRINT A
 80 HALT
 //=================

 Compile no terminal com o comando:
 g++ -o main main.cpp
 ./main [SeuArquivo].txt

 Com esse exemplo terá a saída:
 8
 15


