#include <stdio.h>
#include <stdlib.h>
#include "arena.h"

#define GRID 21
#define RoboPerExerc 5

void *init_arena() {
	arena.nexercitos = 0;
	int i,j;
	for(i=1;i<GRID;i++) {
		for(j=1; j<GRID; j++) {
			arena.cell[i][j].terreno = rand() % 4;
			arena.cell[i][j].cristais = rand() % 5;
			arena.cell[i][j].ocup = 0;
			arena.cell[i][j].base = 0;
			//printf("%d",arena->cell[i][j].cristais);
		}
	}

	for(i=0;i<GRID;i++){
		arena.cell[i][0].ocup = 1;
		arena.cell[i][GRID-1].ocup = 1;	
	}

	for(i=0;i<GRID;i++){
		arena.cell[0][i].ocup = 1;
		arena.cell[GRID-1][i].ocup = 1;
	}
}

void Escalonador(int rodadas) {
	for(int r = 0; r < rodadas; r++) {
		for(int i = 0; i < RoboPerExerc; i++) {
			arena.robonow = i;
			for(int j = 0; j < arena.nexercitos; j++) {
				if(arena.exercitos[j].jogando) {
					arena.exercitonow = j;
					printf("Executando robo %d e exercito %d \n",i,j);
					exec_maquina(arena.exercitos[j].robos[i],50);
				}	
			}
		}
	}
}

void InsereExercito(Exercito exct) {
	
	arena.exercitos[arena.nexercitos] = exct;
	arena.nexercitos++;
}

void RemoveExercito(int base) {
	arena.exercitos[base].jogando = 0;
	for(int i = 0; i < 5; i++) {
		int x = arena.exercitos[base].robos[i]->x;
		int y = arena.exercitos[base].robos[i]->y;
		arena.cell[x][y].ocup = 0;
		destroi_maquina(arena.exercitos[base].robos[i]);
	}
}

// Localiza a coordenada pedida pelo robo e tenta executar a ação baseada na coordenada.
// Caso SRC, retorna a celula. Para os outros casos, retorna 1 caso tenha conseguido executar a ação.
// M:
// 0 = Mover
// 1 = Olhar espaço
// 2 = Pegar Cristal
// 3 = Soltar Cristal
OPERANDO Vizinhos(int M) {
	Maquina *maq = arena.exercitos[arena.exercitonow].robos[arena.robonow];
	OPERANDO op =  desempilha(&maq->pil);
	int x = maq->x;
	int y = maq->y;
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
			r.n = Mover(nx,ny,maq);
			break;

		case 1:
			r.t = CELULA;
			r.cel = arena.cell[nx][ny];
		 	break;

		 case 2:
		 	r.t = NUM;
		 	r.n = Cristal(nx,ny,1,maq);
		 	break;

		 case 3:
		 	r.t = NUM;
		 	r.n = Cristal(nx,ny,0,maq);
		 	break;
	}
	return r;
}

int Mover(int nx, int ny, Maquina *maq) {

	int x = maq->x;
	int y = maq->y;

	if(!arena.cell[nx][ny].ocup){
		maq->x = nx;
		maq->y = ny;
		arena.cell[x][y].ocup = 0;
		arena.cell[nx][ny].ocup = 1;
		return 1;
	}
	return 0;
}

int Cristal(int nx, int ny, int c, Maquina *maq) {

	if(c) {
		if(arena.cell[nx][ny].cristais) {
			maq->cristais++;
			arena.cell[nx][ny].cristais--;
			return 1;
		}
		else
			return 0;
	}
	else {
		if(maq->cristais) {
			maq->cristais--;
			arena.cell[nx][ny].cristais++;
			if(arena.cell[nx][ny].base && arena.cell[nx][ny].cristais >= 5) {
				RemoveExercito(arena.cell[nx][ny].base - 1);
			}
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
		Maquina *maq = arena.exercitos[arena.exercitonow].robos[arena.robonow];
		case 0: // Chamada do ATR
			opr = desempilha(&maq->pil);
			atr.t = NUM;
			cel = desempilha(&maq->pil);
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
			empilha(&maq->pil,atr);
			break;
		case 1: // MOV
			empilha(&maq->pil,Vizinhos(0));
			break;
		case 2: // SRC
			empilha(&maq->pil,Vizinhos(1));
			break;
		case 3: // GRB
			empilha(&maq->pil,Vizinhos(2));
			break;
		case 4: // DRP
			empilha(&maq->pil,Vizinhos(3));
			break;
	}

}