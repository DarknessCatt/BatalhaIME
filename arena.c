#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#define GRID 21

INSTR programa[] = {
  {PUSH, 3},
  {PUSH, 6},
  {CALL, 5},
  {PRN,  0},
  {END,  0},
  {ADD,  0},
  {RET,  0}
};

Arena *init_arena() {
	Arena *arena = (Arena*)malloc(sizeof(Arena));
	nmaquinas = 0;
	robonow = 0;
	nexercitos = 0;
	int i,j;
	for(i=1;i<GRID;i++) {
		for(j=1; j<GRID; j++) {
			arena->cell[i][j].terreno = rand() % 4;
			arena->cell[i][j].cristais = rand() % 5;
			arena->cell[i][j].ocup = 0;
			arena->cell[i][j].base = 0;
			//printf("%d",arena->cell[i][j].cristais);
		}
	}
	return arena;
}

void Escalonador(int rodadas) {
	/*for(int j = 0; j< rodadas; j++) {
		for(int i = 0; i < nexercitos; i++) {
			for(int k = 0; k < nmaquinas; k++) {
					exec_maquina(exercito[i].maquinas[k], 50);
				}
			}
		}
	}*/
}

void InsereExercito(Exercito exercito) {
	exercito[nexercitos] = exercito;
	for(int i =0; i < 5; i++) {
		maquinas[nexercitos*5 + i] = exercito.robos[i];
	}
	nexercitos++;
}
int main() {
	Arena *arena = init_arena();
	Maquina *maq = cria_maquina(programa);
	printf("%d",arena->cell[1][1].cristais);
}