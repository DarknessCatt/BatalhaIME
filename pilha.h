#include "instr.h"

#define PILMAX 99

typedef struct {
  int topo;
  OPERANDO val[PILMAX+1];
} Pilha;

Pilha *cria_pilha();
void destroi_pilha(Pilha *p);
void empilha(Pilha *p, OPERANDO op);
OPERANDO desempilha(Pilha *p);
void imprime(Pilha *p, int n);
