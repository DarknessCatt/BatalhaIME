#include <stdio.h>
#include "arena.h"

INSTR fatorial[] = {
    {PUSH,{NUM, 8}},  // 0
    {CALL,{NUM, 4}},  // 1
    {PRN,{NUM, 0}},  // 2
    {END,{NUM, 0}},  // 3

    // FAT
    {ALC,{NUM, 1}},  // 4
    {DUP,{NUM, 0}},  // 5
    {STL,{NUM, 1}},  // 6 n
    {PUSH,{NUM, 1}},  // 7
    {EQ,  {NUM, 0}},  // 8 n == 1 ?
    {JIF, {NUM, 13}},  // 9
    {PUSH,{NUM, 1}},  // 10
    {FRE,{NUM, 1}},  // 11
    {RET,{NUM, 0}},  // 12
    {RCE,{NUM, 1}},  // 13 n
    {PUSH,{NUM, 1}},  // 14
    {SUB,{NUM, 0}},  // 15 n-1
    {CALL,{NUM, 4}},  // 16 fat(n-1)
    {RCE,{NUM, 1}},  // 17 n
    {MUL,{NUM, 0}}, // 18 n * fat(n-1)
    {FRE,{NUM, 1}}, // 19
    {RET,{NUM, 0}}, // 20
};

INSTR fibonacci[] = {
  {PUSH,{NUM, 1}},
  {DUP, {NUM, 0}},
  {STO, {NUM, 0}},
  {STO, {NUM, 1}},

  {PUSH,{NUM, 10}},
  {STO, {NUM, 2}},

  {RCL,{NUM, 0}},
  {RCL,{NUM ,1}},
  {DUP,{NUM ,0}},
  {STO,{NUM ,0}},
  {ADD,{NUM ,0}},
  {DUP,{NUM ,0}},
  {STO,{NUM ,1}},
  {PRN,{NUM ,0}},
  {RCL,{NUM ,2}},
  {PUSH,{NUM ,1}},
  {SUB,{NUM ,0}},
  {DUP,{NUM ,0}},
  {STO,{NUM ,2}},
  {PUSH,{NUM ,0}},
  {EQ,{NUM ,0}},
  {JIF,{NUM ,6}},

  {END,{NUM ,0}},
};

INSTR teste[] = {
  {PUSH,{NUM, 1}},
  {DUP, {NUM, 0}},
  {STO, {NUM, 0}},
  {STO, {NUM, 1}},

  {PUSH,{NUM, 10}},
  {STO, {NUM, 2}},

  {RCL,{NUM, 0}},
  {RCL,{NUM ,1}},
  {DUP,{NUM ,0}},
  {STO,{NUM ,0}},
  {ADD,{NUM ,0}},
  {DUP,{NUM ,0}},
  {STO,{NUM ,1}},
  {PRN,{NUM ,0}},
  {RCL,{NUM ,2}},
  {PUSH,{NUM ,1}},
  {SUB,{NUM ,0}},
  {DUP,{NUM ,0}},
  {STO,{NUM ,2}},
  {PUSH,{NUM ,0}},
  {EQ,{NUM ,0}},
  {JIF,{NUM ,6}},

  {END,{NUM ,0}},
};

INSTR programa[] = {
  {PUSH,{NUM, 3}},
  {PUSH,{NUM, 23}},
  {CALL,{NUM,5}},
  {PRN, {NUM,0}},
  {END, {NUM,0}},
  {ADD, {NUM,0}},
  {RET, {NUM, 0}}
};

int main(int ac, char **av) {
  init_arena();
  Exercito exercito;
  exercito.robos[0] = cria_maquina(fatorial);
  exercito.robos[1] = cria_maquina(fibonacci);
  exercito.robos[2] = cria_maquina(programa);
  exercito.robos[3] = cria_maquina(teste);
  exercito.robos[4] = cria_maquina(fibonacci);
  InsereExercito(exercito);
  Escalonador(2);
  //destroi_maquina(exercito.robos[0]);
}