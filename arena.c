#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arena.h"

#define maqnow (arena.exercitos[arena.exercitonow].robos[arena.robonow])

void *init_arena() {
	display = popen("python apres", "w");
    arena.nexercitos = 0;
    int i,j,r,g,b;
    for(i=1;i<GRID;i++) {
        for(j=1; j<GRID; j++) {

            arena.cell[i][j].terreno = rand() % 4;
            arena.cell[i][j].cristais = rand() % 5;
            arena.cell[i][j].ocup = 0;
            arena.cell[i][j].base = 0;

            switch (arena.cell[i][j].terreno){
            	case 0:
            		r = 255;
            		g = 0;
            		b = 0;
            		break;
            	case 1:
            		r = 255;
            		g = 255;
            		b = 0;
            		break;
            	case 2:
            		r = 255;
            		g = 0;
            		b = 255;
            		break;
            	case 3:
            		r = 0;
            		g = 255;
            		b = 0;
            		break;
            }

            fprintf(display, "cell %d %d %d %d %d\n",i,j,r,g,b);
            fprintf(display, "cristais %d %d %d\n",arena.cell[i][j].cristais,i,j);
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
					printf("O robo %d do exercito %d esta jogando agora!\n",i,j);
					exec_maquina(arena.exercitos[j].robos[i],50);
				}	
			}
		}
	}
}

void InsereExercito(Exercito exct) {
	//dando uma posicao aleatoria para cada robo
	arena.exercitos[arena.nexercitos] = exct;
	arena.exercitos[arena.nexercitos].jogando = 1;
	for(int i = 0; i< RoboPerExerc; i++) {
		int x = 1 + rand() % 19;
		int y = 1 + rand() % 19;
		while(arena.cell[x][y].ocup) {
			x = 1 + rand() % 19;
		    y = 1 + rand() % 19;
		}
		arena.exercitos[arena.nexercitos].robos[i]->x = x;
		arena.exercitos[arena.nexercitos].robos[i]->y = y;
		arena.cell[x][y].ocup = 1;
		printf("Robo:%d, pos[%d][%d]\n",i,arena.exercitos[arena.nexercitos].robos[i]->x,arena.exercitos[arena.nexercitos].robos[i]->y);
		fprintf(display, "rob crystal.png %d %d\n",x,y);
	}
	int v = 1 + rand() % 19;
	int w = 1 + rand() % 19;
	arena.cell[v][w].base = arena.nexercitos + 1;
	arena.cell[v][w].cristais = 0;
	printf("A base do exercito %d esta em [%d][%d].\n",arena.nexercitos,v,w);
	fprintf(display, "base tower_a.png %d %d\n",v,w);
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
	printf("O Exercito %d foi destruido!",base);
}

// Localiza a coordenada pedida pelo robo e tenta executar a ação baseada na coordenada.
// Caso SCH, retorna a celula. Para os outros casos, retorna 1 caso tenha conseguido executar a ação.
// M:
// 0 = Mover
// 1 = Olhar espaço
// 2 = Pegar Cristal
// 3 = Soltar Cristal

OPERANDO Vizinhos(int M) {
	OPERANDO op =  desempilha(&maqnow->pil);
	int x = maqnow->x;
	int y = maqnow->y;
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
			r.cel = arena.cell[nx][ny];
			printf("Olhando para a cel[%d][%d].\n",nx,ny);
		 	break;

		 case 2:
		 	r.t = NUM;
		 	r.n = Cristal(nx,ny,1);
		 	break;

		 case 3:
		 	r.t = NUM;
		 	r.n = Cristal(nx,ny,0);
		 	break;
	}
	return r;
}

int Mover(int nx, int ny) {
	printf("Tentando mover...\n");
	printf("De [%d][%d] para [%d][%d]\n",maqnow->x,maqnow->y,nx,ny );
	int x = maqnow->x;
	int y = maqnow->y;

	if(!arena.cell[nx][ny].ocup){
		maqnow->x = nx;
		maqnow->y = ny;
		arena.cell[x][y].ocup = 0;
		arena.cell[nx][ny].ocup = 1;
		printf("Movido com sucesso\n");
		fprintf(display, "%d %d %d %d %d\n", arena.exercitonow*5 + arena.robonow, x, y, nx, ny);
		return 1;
	}
	printf("Nao foi possivel se mover, a celula [%d][%d] ja esta ocupada\n",nx,ny);
	return 0;
}

int Cristal(int nx, int ny, int c) {

	if(c) {
	printf("Tentando pegar cristais...\n");
		if(arena.cell[nx][ny].cristais) {
			printf("Sucesso! O Robo %d tinha %d cristais agora tem ",arena.robonow, maqnow->cristais);
			maqnow->cristais++;
			printf("%d.\n",maqnow->cristais);
			arena.cell[nx][ny].cristais--;
			fprintf(display, "cristais %d %d %d\n",arena.cell[nx][ny].cristais,nx,ny);
			return 1;
		}
		else {
			printf("Nao ha cristais.\n");
			return 0;
		}
	}
	else {
		if(maqnow->cristais) {
			printf("O Robo %d depositou um cristal na celula[%d][%d],", arena.robonow,nx,ny);
			if(arena.cell[nx][ny].base)
				printf("a celula continha uma base do exercito %d .\n",arena.cell[nx][ny].base - 1);
			else
				printf("nao havia nenhuma base na celula.\n");
			maqnow->cristais--;
			arena.cell[nx][ny].cristais++;
			fprintf(display, "cristais %d %d %d\n",arena.cell[nx][ny].cristais,nx,ny);
			if(arena.cell[nx][ny].base && arena.cell[nx][ny].cristais >= 5) {
				RemoveExercito(arena.cell[nx][ny].base - 1);
				arena.cell[nx][ny].base  = 0;
				arena.cell[nx][ny].cristais  = 0;
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
		case 0: // Chamada do ATR
			opr = desempilha(&maqnow->pil);
			atr.t = NUM;
			cel = desempilha(&maqnow->pil);
			if(cel.t == CELULA) {
				switch (opr.n) {
					case 0:
						atr.n = cel.cel.terreno;
						break;
					case 1:
						atr.n = cel.cel.cristais;
						printf("Tem %d cristais na celula.\n",atr.n);
						break;
					case 2:
						atr.n = cel.cel.ocup;
						if(atr.n)
							printf("A celula esta ocupada.\n");
						else
							printf("A celula nao esta ocupada.\n");
						break;
					case 3:
						atr.n = cel.cel.base;
						if(atr.n)
							printf("Eh uma base do exercito %d.\n", atr.n - 1);
						else
							printf("A celula nao esta ocupada por nenhum exercito.");
						break;
				}
			}
			empilha(&maqnow->pil,atr);
			break;
		case 1: // MOV
			empilha(&maqnow->pil,Vizinhos(0));
			break;
		case 2: // SEARCH (SCH)
			empilha(&maqnow->pil,Vizinhos(1));
			break;
		case 3: // GRB
			empilha(&maqnow->pil,Vizinhos(2));
			break;
		case 4: // DRP
			empilha(&maqnow->pil,Vizinhos(3));
			break;
	}

}