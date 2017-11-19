#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arena.h"

#define maqnow (arena.exercitos[arena.exercitonow].robos[arena.robonow])
#define ID (arena.exercitonow*5 + arena.robonow)

// Função que inicializa a arena com uma quantidade aleatória de cristais em células aleatórias.
// Também são definidas as bordas da arena.
void init_arena() {
	display = popen("python apres", "w");
    arena.nexercitos = 0;
    int i,j,r,g,b;
    for(i=1;i<GRID-1;i++) {
        for(j=1; j<GRID-1; j++) {

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

// Função responsável por administrar o jogo, deixando apenas um robo por vez executar um determinado ciclo de instruções.
void Escalonador(int rodadas) {
	for(int r = 0; r < rodadas; r++) {
		for(int i = 0; i < RoboPerExerc; i++) {
			arena.robonow = i;
			for(int j = 0; j < arena.nexercitos; j++) {
				if(arena.exercitos[j].jogando) {
					if(arena.exercitos[j].robos[i]->rest){
						printf("O robo %d está desmaiado!\n",ID);						
						arena.exercitos[j].robos[i]->HP++;
						if(arena.exercitos[j].robos[i]->HP>4){
							printf("O robo se recuperou!\n");
							fprintf(display, "rest bot%d.png %d %d %d\n",j, 5*j + i,arena.exercitos[j].robos[i]->x,arena.exercitos[j].robos[i]->y);
							arena.exercitos[j].robos[i]->rest = 0;
						}
					}
					else if(arena.exercitos[j].robos[i]->contador > 0){
						printf("O robo %d está atrasado!\n",ID);						
						arena.exercitos[j].robos[i]->contador--;
					}
					else {
						arena.exercitonow = j;
						//printf("O robo %d esta jogando agora!\n",ID);
						exec_maquina(arena.exercitos[j].robos[i],1);
					}
				}	
			}
		}
	}
}

//Função que insere um exercito na arena, definindo posições aleatórias para os robôs e sua base. 
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
		printf("Robo:%d, pos[%d][%d]\n",ID,arena.exercitos[arena.nexercitos].robos[i]->x,arena.exercitos[arena.nexercitos].robos[i]->y);
		fprintf(display, "rob bot%d.png %d %d\n",arena.nexercitos,x,y);
		arena.robonow++;
	}
	int v = 1 + rand() % (GRID-2);
	int w = 1 + rand() % (GRID-2);
	while(arena.cell[v][w].base) {
		v = 1 + rand() % (GRID-2);
		w = 1 + rand() % (GRID-2);
	}
	arena.cell[v][w].base = arena.nexercitos + 1;
	arena.cell[v][w].cristais = 0;
	arena.cell[v][w].ocup = 21+arena.exercitonow;
	printf("A base do exercito %d esta em [%d][%d].\n",arena.nexercitos,v,w);
	fprintf(display, "cristais 0 %d %d\n",v,w);
	fprintf(display, "base tower%d.png %d %d\n",arena.nexercitos,v,w);
	arena.robonow = 0;
	arena.nexercitos++;
	arena.exercitonow++;
}

//Função chamada quando são depositados 5 ou mais cristais em uma base, remove o exercito do jogo e destroi sua base.
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
			printf("O robo %d está olhando para a cel[%d][%d].\n",ID,nx,ny);
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

// Função que iplementa a movimentação do robo da célula x,y para nx,ny.
int Mover(int nx, int ny) {
	printf("O robo %d quer se mover ",ID);
	printf("de [%d][%d] para [%d][%d]! ",maqnow->x,maqnow->y,nx,ny );
	int x = maqnow->x;
	int y = maqnow->y;

	if(!arena.cell[nx][ny].ocup){
		maqnow->x = nx;
		maqnow->y = ny;
		arena.cell[x][y].ocup = 0;
		arena.cell[nx][ny].ocup = arena.exercitonow*5+arena.robonow+1;
		maqnow->contador = arena.cell[nx][ny].terreno;
		printf("Ele conseguiu!\n");
		fprintf(display, "%d %d %d %d %d\n", arena.exercitonow*5 + arena.robonow, x, y, nx, ny);
		return 1;
	}
	printf("Não foi possivel se mover, a celula [%d][%d] já esta ocupada!\n",nx,ny);
	return 0;
}

// Função que implementa pegar/depositar cristais na direção passada como argumento.
int Cristal(int nx, int ny, int c) {

	if(c) {
	printf("O robo %d vai pegar alguns cristais! ",ID);
		if(arena.cell[nx][ny].cristais) {
			printf("Sucesso! O Robo %d tinha %d cristais agora tem ",ID, maqnow->cristais);
			maqnow->cristais++;
			printf("%d.\n",maqnow->cristais);
			arena.cell[nx][ny].cristais--;
			fprintf(display, "cristais %d %d %d\n",arena.cell[nx][ny].cristais,nx,ny);
			return 1;
		}
		else {
			printf("Mas não há cristal algum naquele espaço!\n");
			return 0;
		}
	}
	else {
		if(maqnow->cristais) {
			if(nx == 0 || nx == (GRID-1) || ny == 0 || ny == (GRID-1)) {
				printf("O robo %d tentou depositar em [%d][%d], mas não é possivel depositar cristais na borda!\n",ID,nx,ny);
				return 0;
			}
			else {
				maqnow->cristais--;
				arena.cell[nx][ny].cristais++;
				printf("O Robo %d depositou um cristal na celula[%d][%d], ",ID,nx,ny);
				if(arena.cell[nx][ny].base)
					printf("a celula continha uma base do exercito %d.\n",arena.cell[nx][ny].base - 1);
				else
					printf("não havia nenhuma base na celula.\n");
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

// Função que implementa o ataque do robo na posição da célula passada como argumento.
int Atacar(int nx, int ny){
	printf("O robo %d vai atacar a posição [%d][%d]! ",ID,nx,ny);
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
				printf("O robo acertou um soco em cheio na cara do robo %d! ",arena.cell[nx][ny].ocup-1);
				break;
			case 1:
				printf("O robo deu uma cabeçada no robo %d com força! ",arena.cell[nx][ny].ocup-1);
				break;
			case 2:
				printf("O robo atropelou o robo %d! ",arena.cell[nx][ny].ocup-1);
				break;
			case 3:
				printf("O robo mordeu o braço do robo %d! ",arena.cell[nx][ny].ocup-1);
				break;
			case 4:
				printf("O robo deu uma voadora nas costas do robo %d! ",arena.cell[nx][ny].ocup-1);
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

/* Função chamada pelo robô requisitando executar uma determinada ação, onde op:
0 = ATR, olha atributo da célulala vizinha empilhada
1 = Mover
2 = Olhar espaço
3 = Pegar Cristal
4 = Soltar Cristal
5 = Atacar
*/
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
						printf("O robo %d nota que existem %d cristais na celula.\n",ID,atr.n);
						break;
					case 2:
						atr.n = cel.cel.ocup;
						if(atr.n)
							printf("O robo %d percebeu que a celula esta ocupada.\n",ID);
						else
							printf("O robo %d percebeu que a celula nao esta ocupada.\n",ID);
						break;
					case 3:
						atr.n = cel.cel.base;
						if(atr.n)
							printf("O robo %d observa uma base do exercito %d.\n",ID,atr.n - 1);
						else
							printf("O robo %d observa que o espaço não ocupada por exercito algum.\n",ID);
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