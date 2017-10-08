#include <stdio.h>

#define GRID 11

static Celula[][] *init_arena() {
	Celula arena[GRID][GRID];
	int i,j;
	for(i=1;i<GRID;i++) {
		for(j=1; j<GRID; j++) {
			arena[i][j].terreno = rand() % 4;
			arena[i][j].cristais = rand() % 5;
		}
	}
	return arena;
}

int main() {
	Arena campo;
	campo->arena = init_arena();
	campo->time = 0;
}