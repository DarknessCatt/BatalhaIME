#include "maq.h"

#define GRID 21

typedef struct {
	Maquina *robos[5];
} Exercito;

typedef struct {
	Celula cell[GRID][GRID];
	int time;
	Exercito exercitos[4];
	int nexercitos;
	int robonow;
	int exercitonow;
} Arena;

Arena arena;
void *init_arena();
void Atualiza();
void InsereExercito();
void RemoveExercito();
void Sistema(int op);