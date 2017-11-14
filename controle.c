#include <stdio.h>

typedef struct {
  int pi, pj;
  int i, j;
  int vi, vj;
} Robot;

FILE *display;
Robot rb[2];


void anda(int ri) {
  Robot r = rb[ri];

  if (r.pi == 14) r.vi = -1;
  if (r.pi == 0)  r.vi =  1;

  if (r.pj == 14) r.vj = -1;
  if (r.pj == 0)  r.vj =  1;

  r.i = r.pi + r.vi;
  r.j = r.pj + r.vj;
  rb[ri] = r;
}

void atualiza(int ri) {
  Robot r = rb[ri];
  r.pi = r.i;
  r.pj = r.j;
  rb[ri] = r;
}


void mostra(int ri) {
  fprintf(display, "%d %d %d %d %d\n",
		  ri, rb[ri].pi, rb[ri].pj, rb[ri].i, rb[ri].j);
  atualiza(ri);
}

/* Programa simples para mostrar como controlar a arena */
int main() {
  int t; 						/* tempo */
  display = popen("./apres", "w");

  rb[0].pi =  6;
  rb[0].pj = 14;
  rb[0].vi = -1;
  rb[0].vj =  1;
  
  rb[1].pi = 10;
  rb[1].pj = 11;
  rb[1].vi =  1;
  rb[1].vj = -1;

  if (display == NULL) {
	fprintf(stderr,"Não encontrei o programa de exibição\n");
	return 1;
  }
  
  /* cria dois robôs */
  fprintf(display, "rob GILEAD_A.png\nrob GILEAD_B.png\n");


  for (t=0; t < 100; t++) {
	anda(0);
	anda(1);
	mostra(0);
	mostra(1);
	fflush(display);
  }

  pclose(display);
}
