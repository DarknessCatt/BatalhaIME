#include "maq.h"


typedef struct {
	Celula cell[21][21];
	int time;
} Arena;

typedef struct {
	Maquina *robos[5];
} Exercito;

Maquina *maquinas[100];
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