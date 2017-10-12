#include "maq.h"
#include "pilha.h"

typedef struct {
int terreno;
int cristais;
int ocup;
int base;
} Celula;

typedef struct {
	Celula cell[21][21];
	int time;
} Arena;

Maquina maquinas[100];
Exercito exercito[20];
int nmaquinas;
int nexercitos;
int robonow;
int escalonador;

Arena *init_arena();
void Atualiza();
void InsereExercito();
void RemoveExercito();
void Sistema(int op);