#include <stdio.h>
#include "compila.tab.h"
#include "arena.h"

INSTR p1[2000];

int compilador(FILE *, INSTR *);
void srand(int num);
int main(int ac, char **av) {
  FILE *p = stdin;
  int res;
  ac --; av++;
  if (ac>0)
	p = fopen(*av,"r");

  res = compilador(p, p1);
  if (res) return 1;
  /*Maquina *maq = cria_maquina(p1);
  exec_maquina(maq, 1000);
  destroi_maquina(maq);*/
  srand(92);
  init_arena();
  Exercito exercito;
  exercito.robos[0] = cria_maquina(p1);
  exercito.robos[1] = cria_maquina(p1);
  exercito.robos[2] = cria_maquina(p1);
  exercito.robos[3] = cria_maquina(p1);
  exercito.robos[4] = cria_maquina(p1);
  InsereExercito(exercito);
  Escalonador(60);
  //RemoveExercito(0,1,2);
  //destroi_maquina(exercito.robos[0]);
  return 0;
}
