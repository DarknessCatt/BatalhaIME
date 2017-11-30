#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "symrec.h"

typedef struct {
  int base;
  symrec * syms;
} Cabec;

/* symrec *SymStack[SYM_STACK_SIZE] = {(symrec* )0,}; */
Cabec SymStack[SYM_STACK_SIZE];
int topss = 0;					/* top = first free */


/* Inclui um símbolo na tabela corrente */
symrec *putsym (char *sym_name)
{
  symrec *ptr;
  symrec *table = SymStack[topss].syms;

  ptr = (symrec *) malloc (sizeof (symrec));
  
  ptr->name = (char *) malloc (strlen (sym_name) + 1);
  strcpy (ptr->name,sym_name);

  ptr->val = SymStack[topss].base++;
  ptr->next = table;

  /* printf("Inclui: %2d: %s, %d\n", topss, ptr->name, ptr->val); */
  SymStack[topss].syms = ptr;
  return ptr;
}

/* Busca na tabela indicada */
static symrec *getsym_i(int t, char *sym_name) {
  symrec *ptr;
  symrec *table = SymStack[t].syms;

  for (ptr = table; ptr != (symrec *) 0;
	   ptr = (symrec *)ptr->next)
	if (strcmp (ptr->name,sym_name) == 0) {
	  /* printf("Achei: %2d: %s, %d\n", t, ptr->name, ptr->val); */
	  return ptr;
	}
  return 0;
}

/* Busca na tabela corrente */
symrec *getsymcur(char *sym_name) {
  return getsym_i(topss, sym_name);
}

/* Busca em todas as tabelas */
symrec *getsym(char *sym_name)
{
  symrec *ptr;
  for (int t = topss; t >= 0; t--)
	if ((ptr = getsym_i(t, sym_name)) != NULL)
	  return ptr;
  return 0;
}


int isglobal() { return !topss;}

symrec *newtab(int b) {
  if (topss < SYM_STACK_SIZE-1) {
	SymStack[++topss] = (Cabec) {b,0};
	return SymStack[topss].syms;
  }
  else
	fprintf(stderr,
			"Programa muito complexo:"
			"número de contextos encaixados muito grande\n");
  return NULL;
}

static void delsymtab(Cabec c) {
  symrec *ptr, *prox;
  symrec *s = c.syms;
  if (!s)
	return;				/* já está vazia */
  prox = s->next;
  
  for (ptr = s; ptr != NULL; ptr = prox) {
	prox = ptr->next;
	free(ptr->name);
	free(ptr);
  }
}

symrec *deltab() {
  if (topss ==0) return SymStack[0].syms;

  delsymtab(SymStack[topss]);
  return SymStack[--topss].syms;
}


int lastval() {
  return SymStack[topss].base;
}
