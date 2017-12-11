Relatório - Projeto Fase 4
MAC0216 - Professor Marcos Dimas Gubitoso

Eduardo Nascimento - NºUSP 10267070
Gabriel Sarti Massukado - NºUSP 10284177
Matheus Lima Cunha - NºUSP 10297755

Em primeiro lugar, mantivemos o pipe criado pelo arena.c utilizando a versão 1 de python. Caso o corretor utilize uma versão mais recente, é necessária a seguinte alteração (linha 9 de arena.c):

display = popen("python apres", "w");

Logo, dependendo da sua versão de Python, talvez seja necessário alterar ess linha para:

display = popen("python3 apres", "w");

Para a quarta fase de nosso projeto, trabalhamos principalmente sobre os arquivos disponibilizados pelo professor responsáveis pelo compilador, ou seja, compila.l e compila.y. Antes de começarmos, alteramos nosso makefile para que compilasse os arquivos de byson e flex, assim como o makefile dos arquivos em "Anexos para a quarta fase". Simplesmente executar "make" compila o nosso compilador e gera o executável "compila".

No arquivo "compila.l", criamos novas palavras reservadas para a linguagem: mov, sch, grb, drp e atk, que são indicadoras das ações que os robôs podem executar - se mover, examinar seus arredores, pegar um cristal, soltar seus cristais e atacar, respectivamente. Logicamente, tambéma adicionamos a interpretação dessas palavras registradas como comandos no arquivo "compila.y". 

Implementamos também o loop com a palavra reservada "for", que recebe uma variável, uma condição de parada e uma condição que se repete no final do loop (como incrementar a variável, por exemplo). É importante notar que nossa linguagem não possui formas simplificadas para representar incrementos, decrementos e outras operações similares. 

Finalmente, implementamos o condicional com a palavra reservada "else". Para isso, utilizamos uma definição recursiva na gramática, evitando assim o conflito reduce/reduce que possuíamos anteriormente.

Tivemos algumas dificuldades na implementação do "for", devido ao modo como organizávamos nossos valores na pilha. Entretanto, todas foram solucionadas.