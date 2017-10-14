#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

#define GRID 21
#define RoboPerExerc 5

INSTR programa[] = {
  {PUSH,{NUM, 3}},
  {PUSH,{NUM, 6}},
  {CALL,{NUM,5}},
  {PRN, {NUM,0}},
  {END, {NUM,0}},
  {ADD, {NUM,0}},
  {RET, {NUM, 0}}
};

Arena *init_arena() {
	Arena *arena = (Arena*)malloc(sizeof(Arena));
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
		arena->cell[i][GRID-1].ocup = 1;
	}

	for(i=0;i<GRID;i++){
		arena->cell[0][i].ocup = 1;
		arena->cell[GRID-1][i].ocup = 1;
	}

	return arena;
}

void Escalonador(int rodadas) {
	for(int i = 0; i < RoboPerExerc; i++) {
		for(int j = 0; j < nexercitos; j++){
			escalonador = j*5+i;
			exec_maquina(exercito[j]->robos[i],50);	
		}
	}
}

void InsereExercito(Exercito exct) {
	exercito[nexercitos] = exct;
	for(int i =0; i < 5; i++) {
		maquinas[nexercitos*5 + i] = exercito->robos[i];
	}
	nexercitos++;
}

// Localiza a coordenada pedida pelo robo e tenta executar a ação baseada na coordenada.
// Caso SRC, retorna a celula. Para os outros casos, retorna 1 caso tenha conseguido executar a ação.
// M:
// 0 = Mover
// 1 = Olhar espaço
// 2 = Pegar Cristal
// 3 = Soltar Cristal
OPERANDO Vizinhos(int M) {

	OPERANDO op =  desempilha(&maquinas[escalonador]->pil);
	int x = maquinas[escalonador]->x;
	int y = maquinas[escalonador]->y;
	int nx = x, ny = y;

	if(x%2) { //impar
		switch(op.n) {
			case 0: // N (x,y+1)
				ny++;
				break;
			case 1: // NE (x+1,y+1)
				nx++;
				ny++;
				break;
			case 2: // SE (x+1,y)
				nx++;
				break;
			case 3: // S (x,y-1)
				ny--;
				break;
			case 4: // SW (x-1,y)
				nx--;
				break;
			case 5: // NW (x-1,y+1)
				nx--;
				ny++;
				break;
		}
	}
	else { //par
		switch(op.n) {
			case 0: // N (x,y+1)
				ny++;
				break;
			case 1: // NE (x+1,y)
				nx++;
				break;
			case 2: // SE (x+1,y-1)
				nx++;
				ny--;
				break;
			case 3: // S (x,y-1)
				ny--;
				break;
			case 4: // SW (x-1,y-1)
				nx--;
				ny--;
				break;
			case 5: // NW (x-1,y)
				nx--;
				break;
		}
	}

	OPERANDO r;

	switch (M) {
		case 0:
			r.t = NUM;
			r.n = Mover(nx,ny);
			break;

		case 1:
			r.t = CELULA;
			r.cel = arena->cell[nx][ny];
		 	break;

		 case 2:
		 	r.t = NUM;
		 	r.n = Cristal(nx,ny,1);
		 	break;

		 case 3:
		 	r.t = NUM;
		 	r.n = Cristal(nx,ny,0);;
		 	break;
	}
	return r;
}

int Mover(int nx, int ny) {

	int x = maquinas[escalonador]->x;
	int y = maquinas[escalonador]->y;

	if(!arena->cell[nx][ny].ocupada){
		maquinas[escalonador]->x = nx;
		maquinas[escalonador]->y = ny;
		arena->cell[x][y].ocupada = 0;
		arena->cell[nx][ny].ocupada = 1;
		return 1;
	}
	return 0;
}

int Cristal(int nx, int ny, int c) {

	if(c) {
		if(arena->cell[nx][ny].cristais){
			maquinas[escalonador]->cristais++;
			arena->cell[nx][ny].cristais--;
			return 1;
		}
		else
			return 0;
	}
	else {
		if(maquinas[escalonador]->cristais){
			maquinas[escalonador]->cristais--;
			arena->cell[nx][ny].cristais++;
			return 1;
		}
		else
			return 0;
	}

}

void Sistema(int op) {
	switch (op) {
		OPERANDO atr;
		OPERANDO opr;
		OPERANDO cel;
		case 0: // Chamada do ATR
			opr = desempilha(&maquinas[escalonador]->pil);
			atr.t = NUM;
			cel = desempilha(&maquinas[escalonador]->pil);
			if(cel.t == CELULA) {
				switch (opr.n) {
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
			empilha(&maquinas[escalonador]->pil,atr);
			break;
		case 1: // MOV
			empilha(&maquinas[escalonador]->pil,Vizinhos(0));
			break;
		case 2: // SRC
			empilha(&maquinas[escalonador]->pil,Vizinhos(1));
			break;
		case 3: // GRB
			empilha(&maquinas[escalonador]->pil,Vizinhos(2));
			break;
		case 4: // DRP
			empilha(&maquinas[escalonador]->pil,Vizinhos(3));
			break;
	}

}

int main() {
	Arena *arena = init_arena();
	Maquina *maq = cria_maquina(programa);
	printf("%d",arena->cell[1][1].cristais);
}