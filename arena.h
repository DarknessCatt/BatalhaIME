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

Maquina exercito[100];
int maquinas;

Arena *init_arena();
void Atualiza();
void InsereExercito();
void RemoveExercito();
void Sistema(int op);