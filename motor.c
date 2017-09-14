#include <stdio.h>
#include "maq.h"

INSTR programa[] = {
  {PUSH, 3},
  {PUSH, 6},
  {CALL, 5},
  {PRN,  0},
  {END,  0},
  {ADD,  0},
  {RET,  0}
};

INSTR fibonacci[] =  {
  /* inicializa variáveis */
  {PUSH,  1},  /*  0 */
  {DUP,   0},  /*  1 */
  {STO,   0},  /*  2 x */
  {STO,   1},  /*  3 y */

  /* for i = 10 */
  {PUSH, 10},  /*  4 */
  {STO,   2},  /*  5 i*/

  /* início do laço */
  {RCL,   0},  /*  6 */
  {RCL,   1},  /*  7 y */
  {DUP,   0},  /*  8 */
  {STO,   0},  /*  9 x' = y */
  {ADD,   0},  /* 10 x+y */
  {DUP,   0},  /* 11 */
  {STO,   1},  /* 12 y = x+y */
  {PRN,   0},  /* 13 (x+y) */
  {RCL,   2},  /* 14 i */
  {PUSH,  1},  /* 15 */
  {SUB,   0},  /* 16 */
  {DUP,   0},  /* 17 */
  {STO,   2},  /* 18 i = i - 1 */
  {PUSH,  0},  /* 19 */
  {EQ,    0},  /* 20 i == 0 ?*/
  {JIF,   6},  /* 21 (LOOP) */
  {END,   0},  /* 22 */

};

int main(int ac, char **av) {
  Maquina *maq = cria_maquina(programa);
  Maquina *maq2 = cria_maquina(fibonacci);
  exec_maquina(maq, 3);
  exec_maquina(maq2, 40);
  puts("---");
  exec_maquina(maq, 10);
  puts("---");
  exec_maquina(maq2, 10000);
  destroi_maquina(maq);
  destroi_maquina(maq2);
  return 0;
}
