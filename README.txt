Relatório - Projeto Fase 3
MAC0216 - Professor Marcos Dimas Gubitoso

Eduardo Nascimento - NºUSP 10267070
Gabriel Sarti Massukado - NºUSP 10824177
Matheus Lima Cunha - NºUSP 10297755

Para a terceira fase do projeto, primeiramente criamos sprites para nossos robôs, cristais e bases. Optamos por não criar sprites para os diferentes tipos de terreno pois acreditamos que a visualização seria mais simples e intuitiva utilizando apenas cores para representar os terrenos, visto que a baixa resolução dos sprites poderiam criar imagens confusas pela sobreposição dos robôs/cristais sobre os terrenos. Para identificação dos times, utilizamos sprites iguais mas com diferenças de coloração (vermelha, azul, verde e amarela).

Além disso, alteramos nosso arena.c para que ele abrisse um pipe e executasse o programa "apres", responsável por implementar a parte gráfica do projeto. É importante notar que o pipe que criamos é criado da seguinte forma (linha 9 de arena.c):

display = popen("python apres", "w");

Logo, dependendo da sua versão de Python, talvez seja necessário alterar ess linha para:

display = popen("python3 apres", "w");

Ademais, adicionamos em nossas funções InsereExercito e Cristais comandos que imprimem as informações necessárias para que elas imprimam o texto que "apres" necessita para desenhar os robôs e os cristais.