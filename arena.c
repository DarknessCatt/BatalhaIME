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
            if(rand()%10<3)
            	arena.cell[i][j].cristais = rand() % 5;
            else
            	arena.cell[i][j].cristais = 0;
            arena.cell[i][j].ocup = 0;
            arena.cell[i][j].base = 0;

            switch (arena.cell[i][j].terreno){
            	case 0:
            		r = 153;
            		g = 76;
            		b = 0;
            		break;
            	case 1:
            		r = 0;
            		g = 204;
            		b = 0;
            		break;
            	case 2:
            		r = 0;
            		g = 51;
            		b = 0;
            		break;
            	case 3:
            		r = 0;
            		g = 128;
            		b = 255;
            		break;
            }

            fprintf(display, "cell %d %d %d %d %d\n",i,j,r,g,b);
            fprintf(display, "cristais %d %d %d\n",arena.cell[i][j].cristais,i,j);
        }
    }

    for(i=0;i<GRID;i++){
        arena.cell[i][0].ocup = -1;
        arena.cell[i][GRID-1].ocup = -1;
    }

    for(i=0;i<GRID;i++){
        arena.cell[0][i].ocup = -1;
        arena.cell[GRID-1][i].ocup = -1;
    }

    arena.exercitonow = 0;
    arena.robonow = 0;
}

void Escalonador(int rodadas) {
	for(int r = 0; r < rodadas; r++) {
		for(int i = 0; i < RoboPerExerc; i++) {
			arena.robonow = i;
			for(int j = 0; j < arena.nexercitos; j++) {
				if(arena.exercitos[j].jogando) {
					if(arena.exercitos[j].robos[i]->rest){
						printf("O robo %d do exercito %d está desmaiado!\n",i,j);
						arena.exercitos[j].robos[i]->HP++;
						if(arena.exercitos[j].robos[i]->HP>4){
							printf("O robo se recuperou!\n");
							fprintf(display, "rest bot%d.png %d %d %d\n",arena.exercitonow,arena.cell[maqnow->x][maqnow->y].ocup-1,maqnow->x,maqnow->y);
							arena.exercitos[j].robos[i]->rest = 0;
						}
					}
					else if(arena.exercitos[j].robos[i]->contador > 0){
						printf("O robo %d do exercito %d está atrasado!\n",i,j);
						arena.exercitos[j].robos[i]->contador--;
					}
					else{
						arena.exercitonow = j;
						printf("O robo %d do exercito %d esta jogando agora!\n",i,j);
						exec_maquina(arena.exercitos[j].robos[i],2);
					}
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
		int x = 1 + rand() % (GRID-1);
		int y = 1 + rand() % (GRID-1);
		while(arena.cell[x][y].ocup) {
			x = 1 + rand() % (GRID-1);
		    y = 1 + rand() % (GRID-1);
		}
		arena.exercitos[arena.nexercitos].robos[i]->x = x;
		arena.exercitos[arena.nexercitos].robos[i]->y = y;
		arena.cell[x][y].ocup = arena.exercitonow*5+arena.robonow+1;
		printf("Robo:%d, pos[%d][%d]\n",i,arena.exercitos[arena.nexercitos].robos[i]->x,arena.exercitos[arena.nexercitos].robos[i]->y);
		fprintf(display, "rob bot%d.png %d %d\n",arena.nexercitos,x,y);
		arena.robonow++;
	}
	int v = 1 + rand() % (GRID-1);
	int w = 1 + rand() % (GRID-1);
	arena.cell[v][w].base = arena.nexercitos + 1;
	arena.cell[v][w].cristais = 0;
	arena.cell[v][w].ocup = 21+arena.exercitonow;
	printf("A base do exercito %d esta em [%d][%d].\n",arena.nexercitos,v,w);
	fprintf(display, "cristais 0 %d %d\n",v,w);
	fprintf(display, "base tower%d.png %d %d\n",arena.nexercitos,v,w);
	arena.nexercitos++;
	arena.exercitonow++;
}

void RemoveExercito(int base,int x, int y) {
	arena.exercitos[base].jogando = 0;
	for(int i = 0; i < 5; i++) {
		int x = arena.exercitos[base].robos[i]->x;
		int y = arena.exercitos[base].robos[i]->y;
		arena.cell[x][y].ocup = 0;
		destroi_maquina(arena.exercitos[base].robos[i]);
	}
	fprintf(display, "destroy tower-1.png %d %d %d\n",base,x,y);
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
			case 0: // NW (x,y+1)
				nx--;
				break;
			case 1: // NE (x+1,y+1)
				nx--;
				ny++;
				break;
			case 2: // E (x+1,y)
				ny++;
				break;
			case 3: // SE (x+1,y-1)
				nx++;
				ny++;
				break;
			case 4: // SW (x,y-1)
				nx++;
				break;
			case 5: // W (x-1,y+1)
				ny--;
				break;
		}
	}
	else { //par
		switch(op.n) {
			case 0: // NW (x-1,y+1)
				ny--;
				nx--;
				break;
			case 1: // NE (x,y+1)
				nx--;
				break;
			case 2: // E (x+1,y)
				ny++;
				break;
			case 3: // SE (x,y-1)
				nx++;
				break;
			case 4: // SW (x-1,y-1)
				nx++;
				ny--;
				break;
			case 5: // W (x-1,y)
				ny--;
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

		 case 4:
		 	r.t = NUM;
		 	r.n = Atacar(nx,ny);
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
		arena.cell[nx][ny].ocup = arena.exercitonow*5+arena.robonow+1;
		maqnow->contador = arena.cell[nx][ny].terreno;
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
			if(nx == 0 || nx == (GRID-1) || ny == 0 || ny == (GRID-1)) {
				printf("Nao e possivel depositar cristais na borda! Tentou depositar em [%d][%d].\n",nx,ny);
				return 0;
			}
			else {
				maqnow->cristais--;
				arena.cell[nx][ny].cristais++;
				printf("O Robo %d depositou um cristal na celula[%d][%d], ", arena.robonow,nx,ny);
				if(arena.cell[nx][ny].base)
					printf("a celula continha uma base do exercito %d.\n",arena.cell[nx][ny].base - 1);
				else
					printf("nao havia nenhuma base na celula.\n");
				fprintf(display, "cristais %d %d %d\n",arena.cell[nx][ny].cristais,nx,ny);
				if(arena.cell[nx][ny].base && arena.cell[nx][ny].cristais >= 5) {
					RemoveExercito(arena.cell[nx][ny].base - 1,nx,ny);
					arena.cell[nx][ny].base  = 0;
					arena.cell[nx][ny].cristais  = 0;
				}
				return 1;
			}
		}
		else
			return 0;
	}

}

int Atacar(int nx, int ny){
	printf("O robo %d do exercito %d vai atacar a posição [%d][%d]!\n",arena.robonow,arena.exercitonow,nx,ny);
	printf("arena.cell[nx][y].ocup = %d", arena.cell[nx][ny].ocup);
	fprintf(display, "atk botatk%d.png bot%d.png %d %d %d\n",arena.exercitonow,arena.exercitonow,arena.cell[maqnow->x][maqnow->y].ocup-1,maqnow->x,maqnow->y);
	if(arena.cell[nx][ny].ocup <= 0 || arena.cell[nx][ny].ocup>20){
		printf("Parece que não havia nada ali!\n");
		return 0;
	}
	else{
		int e = (arena.cell[nx][ny].ocup-1)/5;
		int r = (arena.cell[nx][ny].ocup-1)%5;
		int a = rand()%5;

		switch(a){

			case 0:
				printf("O robo acertou um soco em cheio na cara do robo %d do exercito %d! ",r,e);
				break;
			case 1:
				printf("O robo deu uma cabeçada no robo %d do exercito %d com força! ",r,e);
				break;
			case 2:
				printf("O robo atropelou o robo %d do exercito %d! ",r,e);
				break;
			case 3:
				printf("O robo mordeu o braço do robo %d do exercito %d! ",r,e);
				break;
			case 5:
				printf("O robo deu uma voadora nas costas do robo %d do exercito %d! ",r,e);
				break;

		}

		arena.exercitos[e].robos[r]->HP--;

		if(arena.exercitos[e].robos[r]->HP<1){
			arena.exercitos[e].robos[r]->rest=1;
			printf("Ele desmaiou!\n");
			fprintf(display, "rest brkbot%d.png %d %d %d\n",e,arena.cell[nx][ny].ocup-1,nx,ny);
		}
		else{
			printf("Ele ainda tem %d de HP!\n",arena.exercitos[e].robos[r]->HP);
		}

		return 1;
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
		case 5: //ATK
			empilha(&maqnow->pil,Vizinhos(4));
			break;
	}

}