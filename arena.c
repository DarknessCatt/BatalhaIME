#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#define GRID 21

/*INSTR programa[] = {
  {PUSH, 3},
  {PUSH, 6},
  {CALL, 5},
  {PRN,  0},
  {END,  0},
  {ADD,  0},
  {RET,  0}
};*/

Arena* init_arena() {
	Arena *arena = (Arena*)malloc(sizeof(Arena));
	maquinas = 0;
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
void registro(Maquina *maq) {
	exercito[maquinas] = *maq;
	maquinas++;
	/*printf("Maquinas:%d\n",maquinas);
	exercito[0].cristais = 217;
	printf("%d",exercito[0].cristais);*/
}


int main() {
	Arena *arena = init_arena();
	Maquina *maq = cria_maquina(programa);
	registro(maq);
	printf("%d",arena->cell[1][1].cristais);
}