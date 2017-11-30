#include <stdio.h>
#include "compila.tab.h"
#include "maq.h"

INSTR p1[2000];

int compilador(FILE *, INSTR *);

int main(int ac, char **av) {
  FILE *p = stdin;
  int res;
  ac --; av++;
  if (ac>0)
	p = fopen(*av,"r");

  res = compilador(p, p1);
  if (res) return 1;
  
  Maquina *maq = cria_maquina(p1);
  exec_maquina(maq, 1000);
  destroi_maquina(maq);
  return 0;
}
