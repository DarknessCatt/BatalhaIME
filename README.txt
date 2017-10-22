Relatório - Projeto Fase 2
MAC0216 - Professor Marcos Dimas Gubitoso

Eduardo Nascimento - NºUSP 10267070
Gabriel Sarti Massukado - NºUSP 10824177
Matheus Lima Cunha - NºUSP 10297755

Para a implementação da segunda parte do projeto, criamos um arquivo arena.c, modificamos o montador, modificamos os arquivos maq.c e pilha.c e também criamos um Makefile que gera nossos programas de teste. Logicamente, criamos uma nova interface arena.h e atualizamos as interfaces maq.h, pilha.h e instr.h.

Primeiramente, definimos um novo tipo "Celula", que é utilizado para indicar as propriedades de cada espaço da arena. Além disso, modificamos os operandos da máquina virtual, para que pudessem ser - além de ints - ações, variáveis ou células. Consequentemente, modificamos a pilha para que os operandos novos funcionassem corretamente.

Com os novos operandos, tornou-se necessário alterar a maioria das instruções da máquina, fazendo com que elas se certificassem que o seu operando fosse compatível com a operação executada. Ademais, criamos 4 novas instruções que correspondem às operações do sistema: MOV, SCH, GRB, DRP. Suas funções são, respectivamente, mover um robô na arena, empilhar a célula alvo na pilha de dados, recolher um cristal do espaço alvo e depositar um cristal no espaço alvo. Cada uma delas empilha seu argumento (que indica a célula-alvo da ação) e chama a função "Sistema" de arena.c, que faz com que o robô execute a ação necessária (no caso de MOV, também ocorre uma verificação para garantir que o robô possa se mover para o espaço desejado). Devido a essas instruções, não implementamos uma instrução SIS para chamar o Sistema diretamente, pois acreditamos que dessa forma seria mais coerente com o enunciado e também mais simples.
Também criamos a instrução ATR, que idealmente, deve ser usada imediatamente após SCH, pois verifica um atributo da célula empilhada. O argumento de ATR é um inteiro entre 0 e 3 que determina a informação desejada sobre a célula, sendo 0 = tipo de terreno, 1 = número de cristais, 2 = ocupação e 3 = base.
Cada uma das operações do sistema é indicada por um inteiro entre 0 e 4, na seguinte ordem: ATR, MOV, SCH, GRB, DRP.

Na arena.c, criamos uma matriz bidimensional com uma função Vizinhos, que implementa o comportamento da matriz hexagonal. Além disso, criamos a função Sistema já mencionada, que gerencia as novas instruções das máquinas virtuais. Também há uma função Atualiza(), responsável por conter o escalonador.

Modificamos sucintamente o montador para que as instruções com o novo tipo de operando fossem geradas corretamente.

Finalmente, criamos um Makefile novo que constrói o executável contendo todos os nossos programas de teste. Para utilizá-lo, use
$ make progteste

Tivemos algumas dificuldades em modularizar nossos arquivos de modo coerente com o que foi requisitado.

Para facilitar a correção e o entendimento da execução do código, deixamos diversos prints que indicam o tipo de instrução sendo executada e se ela foi realizada corretamente. 

Além disso, é importante notar que nosso arena.c executa as máquinas com 50 ciclos de instrução, como foi pedido. Entretanto, alguns de nossos testes requerem mais do que isso para funcionar corretamente, então é recomendável alterar o valor "50" da função "exec_maquina", na linha 40 de arena.c, para "200".