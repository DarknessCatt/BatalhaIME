#include "maq.h"

#define GRID 21

typedef struct {
	Celula cell[GRID][GRID];
	int time;
} Arena;

typedef struct {
	Maquina *robos[5];
} Exercito;

Maquina *maquinas[100];
Exercito exercito[4];
int nexercitos;
int escalonador;

Arena *init_arena();
void Atualiza();
void InsereExercito();
void RemoveExercito();
void Sistema(int op);