#include "pilha.h"

#define MAXMEM 100
#define MAXFRM 30

typedef struct {
  Pilha pil;
  Pilha exec;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  int ip;
  int rbp;
  int bp[MAXFRM];
  int ib;
  int x;
  int y;
  int cristais;
  int contador;
  int HP;
  int rest;
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);

int new_frame(Maquina *m, int pos);

int del_frame(Maquina *m);
