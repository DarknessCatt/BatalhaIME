#include <stdio.h>
#include "arenaDRAW.h"

INSTR robo1[] = {
  {MOV, {NUM, 3}},
  {GRB, {NUM, 2}},
  {DRP, {NUM, 1}},
  {END, {NUM, 0}}
};

INSTR robo2[] = {
  {MOV, {NUM, 5}},
  {MOV, {NUM, 4}},
  {MOV, {NUM, 5}},
  {MOV, {NUM, 4}},
  {MOV, {NUM, 5}},
  {MOV, {NUM, 4}},
  {MOV, {NUM, 3}},
  {MOV, {NUM, 3}},
  {MOV, {NUM, 3}},
  {MOV, {NUM, 5}},
  {MOV, {NUM, 0}},
  {MOV, {NUM, 2}},
  {MOV, {NUM, 3}},
  {MOV, {NUM, 4}},
  {MOV, {NUM, 4}},
  {END, {NUM, 0}}
};

INSTR robo8[] = {
  {MOV, {NUM, 3}},
  {MOV, {NUM, 3}},
  {GRB, {NUM, 1}},
  {GRB, {NUM, 2}},
  {GRB, {NUM, 3}},
  {MOV, {NUM, 3}},
  {GRB, {NUM, 2}},
  {MOV, {NUM, 2}},
  {GRB, {NUM, 2}},
  {DRP, {NUM, 3}},
  {DRP, {NUM, 3}},
  {DRP, {NUM, 3}},
  {DRP, {NUM, 3}},
  {DRP, {NUM, 3}},
  {END, {NUM, 0}}
};

INSTR tested[] = {
  {PUSH,{NUM, 1}},
  {PUSH,{NUM, 10}},
  {MOV, {NUM, 3}},
  {SCH, {NUM, 4}},
  {ATR, {NUM, 1}},
  {GRB, {NUM, 4}},
  {DRP, {NUM, 5}},
  {END,{NUM ,0}}
};

INSTR chill[] = {
  {END,{NUM,0}}
};

int main(int ac, char **av) {
  srand( 100 );
  init_arena();
  Exercito exercito;
  exercito.robos[0] = cria_maquina(robo1);
  exercito.robos[1] = cria_maquina(tested);
  exercito.robos[2] = cria_maquina(chill);
  exercito.robos[3] = cria_maquina(chill);
  exercito.robos[4] = cria_maquina(chill);
  InsereExercito(exercito);
  Exercito exercito2;
  exercito2.robos[0] = cria_maquina(robo2);
  exercito2.robos[1] = cria_maquina(tested);
  exercito2.robos[2] = cria_maquina(chill);
  exercito2.robos[3] = cria_maquina(robo8);
  exercito2.robos[4] = cria_maquina(chill);
  InsereExercito(exercito2);
  Escalonador(1);
  //RemoveExercito(0);
  //destroi_maquina(exercito.robos[0]);
  return(0);
}
