#include "maq.h"

#define GRID 21
#define RoboPerExerc 5

typedef struct {
	Maquina *robos[RoboPerExerc];
	int jogando;
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
void RemoveExercito(int base);
OPERANDO Vizinhos(int M);
int Mover(int nx, int ny);
int Cristal(int nx, int ny, int c);
void Sistema(int op);