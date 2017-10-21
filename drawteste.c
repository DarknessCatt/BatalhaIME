#include <stdio.h>
#include "arenaDRAW.h"

INSTR tested[] = {
  {PUSH,{NUM, 1}},
  {PUSH,{NUM, 10}},
  {MOV, {NUM, 3}},
  {SCH, {NUM, 4}},
  {ATR, {NUM, 1}},
  {GRB, {NUM, 4}},
  {DRP, {NUM, 5}},
  {END,{NUM ,0}},
};

int main(int ac, char **av) {
  srand( 1 );
  init_arena();
  Exercito exercito;
  exercito.robos[0] = cria_maquina(tested);
  exercito.robos[1] = cria_maquina(tested);
  exercito.robos[2] = cria_maquina(tested);
  exercito.robos[3] = cria_maquina(tested);
  exercito.robos[4] = cria_maquina(tested);
  InsereExercito(exercito);
  Escalonador(2);
  //RemoveExercito(0);
  //destroi_maquina(exercito.robos[0]);
  return(0);
}
