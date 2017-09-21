#include <stdio.h>
#include "maq.h"
INSTR prog[] = {
  {PUSH, 1},
  {DUP, 0},
  {STO, 0},
  {STO, 1},

  {PUSH, 10},
  {STO, 2},

  {RCL, 0},
  {RCL, 1},
  {DUP, 0},
  {STO, 0},
  {ADD, 0},
  {DUP, 0},
  {STO, 1},
  {PRN, 0},
  {RCL, 2},
  {PUSH, 1},
  {SUB, 0},
  {DUP, 0},
  {STO, 2},
  {PUSH, 0},
  {EQ, 0},
  {JIF, 6},

  {END, 0},
};
int main(int ac, char **av) {
Maquina *maq = cria_maquina(prog);
exec_maquina(maq,  1000 );
destroi_maquina(maq);
}
