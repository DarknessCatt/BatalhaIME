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
void Escalonador(int rodadas);
void InsereExercito(Exercito exct);
void RemoveExercito();
OPERANDO Vizinhos(int M);
int Mover(int nx, int ny, Maquina *maq);
int Cristal(int nx, int ny, int c, Maquina *maq);
void Sistema(int op);