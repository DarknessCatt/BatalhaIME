#include "maq.h"

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

typedef struct {
	Maquina maquinas[5];
} Exercito;

Exercito exercito[20];
int nmaquinas;
int nexercitos;

Arena *init_arena();
void Atualiza();
void InsereExercito();
void RemoveExercito();
void Sistema(int op);