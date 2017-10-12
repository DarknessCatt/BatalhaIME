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

	for(i=0;i<GRID;i++){
		arena->cell[i][0].ocup = 1;
		arena->cell[i][20].ocup = 1;
	}

	for(i=0;i<GRID;i++){
		arena->cell[0][i].ocup = 1;
		arena->cell[20][i].ocup = 1;
	}

	return arena;
}

void Escalonador(int rodadas) {
	for(int k = 0; k < nmaquinas; k++) {
		escalonador = k;
		exec_maquina(maquinas[k], 50);	
	}
}

void InsereExercito(Exercito exercito) {
	exercito[nexercitos] = exercito;
	for(int i =0; i < 5; i++) {
		maquinas[nexercitos*5 + i] = exercito.robos[i];
	}
	nexercitos++;
}

void Sistema(int op) {
	switch (op) {
		case 0: // Chamada do ATR
			Operando op = desempilha(maquinas[escalonador].pil);
			Operando atr;
			atr.t = NUM;
			Operando cel = desempilha(maquinas[escalonador].pil);
			if(cel.t == CELULA) {
				switch (op.n) {
					case 0:
						atr.n = cel.cel.terreno;
						break;
					case 1:
						atr.n = cel.cel.cristais;
						break;
					case 2:
						atr.n = cel.cel.ocup;
						break;
					case 3:
						atr.n = cel.cel.base;
						break;
				}
			}
			empilha(maquinas[escalonador].pil,atr);
			break;
		case 1: // MOV
			Operando mov;
			mov.t = NUM;
			mov.n = Mover();
			empilha(maquinas[escalonador].pil,mov);
			break;
		case 2: // SRC
			break;
		case 3: // GRB
			break;
		case 4: // DRP
			break;
	}

}

//Tenta mover o robo, e retorna 1 se conseguiu e 0 se não pode mover ele ( ou ele andou para a parede ou
// a casa já está ocupada)
int Mover(){
	Operando op =  desempilha(maquinas[escalonador].pil);
	int x = maquinas[escalonador].x;
	int y = maquinas[escalonador].y;
	int nx = x, ny = y;

	if(x%2){
		switch(op.n){
			case 0: // Mover Para N (x,y+1)
				ny++;
				if(!arena->cell[nx][ny].ocupada){				
					maquinas[escalonador].y = ny;
					arena->cell[x][y].ocupada = 0;
					arena->cell[nx][ny].ocupada = 1;
					return 1;				
				}
				return 0;
				break;
			case 1: // Mover para NE (x+1,y+1)
				nx++;
				ny++;
				if(!arena->cell[nx][ny].ocupada){
					maquinas[escalonador].x = nx;
					maquinas[escalonador].y = ny;
					arena->cell[x][y].ocupada = 0;
					arena->cell[nx][ny].ocupada = 1;
					return 1;
				}
				return 0;
				break;
			case 2: // Mover para SE (x+1,y)
				nx++;
				if(!arena->cell[nx][ny].ocupada){
					maquinas[escalonador].x = nx;
					arena->cell[x][y].ocupada = 0;
					arena->cell[nx][ny].ocupada = 1;
					return 1;
				}
				return 0;
				break;
			case 3: // Mover para S (x,y-1)
				ny--;
				if(!arena->cell[nx][ny].ocupada){
					maquinas[escalonador].y = ny;
					arena->cell[x][y].ocupada = 0;
					arena->cell[nx][ny].ocupada = 1;
					return 1;
				}
				return 0;
				break;
			case 4: // Mover para SW (x-1,y)
				nx--;
				if(!arena->cell[nx][ny].ocupada){
					maquinas[escalonador].x = nx;
					arena->cell[x][y].ocupada = 0;
					arena->cell[nx][ny].ocupada = 1;
					return 1;
				}
				return 0;
				break;
			case 5: //Mover para NW (x-1,y+1)
				nx--;
				ny++;
				if(!arena->cell[nx][ny].ocupada){
					maquinas[escalonador].x = nx;
					maquinas[escalonador].y = ny;
					arena->cell[x][y].ocupada = 0;
					arena->cell[nx][ny].ocupada = 1;
					return 1;
				}
				return 0;
				break;
		}
	}
	else{
		switch(op.n){
			case 0: // Mover Para N (x,y+1)
				ny++;
				if(!arena->cell[nx][ny].ocupada){				
					maquinas[escalonador].y = ny;
					arena->cell[x][y].ocupada = 0;
					arena->cell[nx][ny].ocupada = 1;
					return 1;				
				}
				return 0;
				break;
			case 1: // Mover para NE (x+1,y)
				nx++;
				if(!arena->cell[nx][ny].ocupada){
					maquinas[escalonador].x = nx;
					arena->cell[x][y].ocupada = 0;
					arena->cell[nx][ny].ocupada = 1;
					return 1;
				}
				return 0;
				break;
			case 2: // Mover para SE (x+1,y-1)
				nx++;
				ny--;
				if(!arena->cell[nx][ny].ocupada){
					maquinas[escalonador].x = nx;
					maquinas[escalonador].y = ny;
					arena->cell[x][y].ocupada = 0;
					arena->cell[nx][ny].ocupada = 1;
					return 1;
				}
				return 0;
				break;
			case 3: // Mover para S (x,y-1)
				ny--;
				if(!arena->cell[nx][ny].ocupada){
					maquinas[escalonador].y = ny;
					arena->cell[x][y].ocupada = 0;
					arena->cell[nx][ny].ocupada = 1;
					return 1;
				}
				return 0;
				break;
			case 4: // Mover para SW (x-1,y-1)
				nx--;
				ny--;
				if(!arena->cell[nx][ny].ocupada){
					maquinas[escalonador].x = nx;
					maquinas[escalonador].y = ny;
					arena->cell[x][y].ocupada = 0;
					arena->cell[nx][ny].ocupada = 1;
					return 1;
				}
				return 0;
				break;
			case 5: //Mover para NW (x-1,y)
				nx--;
				if(!arena->cell[nx][ny].ocupada){
					maquinas[escalonador].x = nx;
					arena->cell[x][y].ocupada = 0;
					arena->cell[nx][ny].ocupada = 1;
					return 1;
				}
				return 0;
				break;
		}
	}
}

int main() {
	Arena *arena = init_arena();
	Maquina *maq = cria_maquina(programa);
	printf("%d",arena->cell[1][1].cristais);
}