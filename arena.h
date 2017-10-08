#include "maq.h"

typedef struct {
int terreno;
int cristais;
int ocup;
int base;
} Celula;

typedef struct {
	Celula arena[][];
	int time;
	Maquina exercito[100];
} Arena;

Arena *init_arena();
void Atualiza();
void InsereExercito();
void RemoveExercito();
void Sistema(int op);