#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#define GRID 21

Arena* init_arena() {
	printf("teste");
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
}

int main() {
	Arena *arena = init_arena();
	printf("%d",arena->cell[1][1].cristais);
}