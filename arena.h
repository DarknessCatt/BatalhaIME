#include "maq.h"

#define GRID 12
#define RoboPerExerc 5

//define a estrutura do exercito
typedef struct {
	Maquina *robos[RoboPerExerc];
	int jogando;
} Exercito;

//define a estrutura da arena
typedef struct {
	Celula cell[GRID][GRID];
	int time;
	Exercito exercitos[4];
	int nexercitos;
	int robonow;
	int exercitonow;
} Arena;

//Arena Global
Arena arena;
FILE *display;

//Gera a arena aleatoriamente, colocando o terreno e os cristais
void init_arena();

//Executa todos os robos N rodadas, alterando entre os robos de cada time
void Escalonador(int rodadas);

//insere um exercito e posiciona aleatoriamente uma base e os robos do exercito
void InsereExercito(Exercito exct);

//Destroi as maquinas, remove os robos e a base do mapa
void RemoveExercito(int base,int x, int y);

//Usado para achar as casas vizinhas ao robo, e ou retorna a celula ou chama Mover() ou Cristal()
OPERANDO Vizinhos(int M);

//Verifica se a casa desejada está vazia, e move o robo para lá ( se puder )
int Mover(int nx, int ny);

//quando c = 0, o robo deposita um cristal, quando c != 0, coleta o cristal de uma casa vizinha
int Cristal(int nx, int ny, int c);

//O robo na posição nx, ny ( se houver ) perde 1 de HP e demaia se ela chegar a 0
int Atacar(int nx, int ny);

//A chamada do sistema, chamando Vizinhos() no caso de MOV, SRC, DRP, GRB, ou retorna o atributo da celula quando ATR 
void Sistema(int op);