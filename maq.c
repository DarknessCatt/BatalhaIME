#include <stdio.h>
#include <stdlib.h>
#include "maq.h"

/* #define DEBUG */

#ifdef DEBUG
#  define D(X) X
char *CODES[] = {
  "PUSH",
  "POP",
  "DUP",
  "ADD",
  "SUB",
  "MUL",
  "DIV",
  "JMP",
  "JIT",
  "JIF",
  "CALL",
  "RET",
  "STS",
  "RCS",
  "EQ",
  "GT",
  "GE",
  "LT",
  "LE",
  "NE",
  "STO",
  "RCL",
  "END",
  "PRN"
};
#else
#  define D(X)
#endif

static void Erro(char *msg) {
  fprintf(stderr, "%s\n", msg);
}

static void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}

Maquina *cria_maquina(INSTR *p) {
  Maquina *m = (Maquina*)malloc(sizeof(Maquina));
  if (!m) Fatal("Memória insuficiente",4);
  m->ip = 0;
  m->prog = p;
  return m;
}

void destroi_maquina(Maquina *m) {
  free(m);
}

/* Alguns macros para facilitar a leitura do código */
#define ip (m->ip)
#define pil (&m->pil)
#define exec (&m->exec)
#define prg (m->prog)

void exec_maquina(Maquina *m, int n) {
  int i;

  for (i = 0; i < n; i++) {
	OpCode   opc = prg[ip].instr;
	OPERANDO arg = prg[ip].op;

	D(printf("%3d: %-4.4s %d\n     ", ip, CODES[opc], arg));

	switch (opc) {
	  OPERANDO tmp;
	case PUSH:
	  empilha(pil, arg);
	  break;
	case POP:
	  desempilha(pil);
	  break;
	case DUP:
	  tmp = desempilha(pil);
	  empilha(pil, tmp);
	  empilha(pil, tmp);
	  break;
	case ADD:
	  empilha(pil, desempilha(pil)+desempilha(pil));
	  break;
	case SUB:
	  tmp = desempilha(pil);
	  empilha(pil, desempilha(pil)-tmp);
	  break;
	case MUL:
	  empilha(pil, desempilha(pil)*desempilha(pil));
	  break;
	case DIV:
	  tmp = desempilha(pil);
	  empilha(pil, desempilha(pil)/tmp);
	  break;
	case JMP:
	  ip = arg;
	  continue;
	case JIT:
	  if (desempilha(pil) != 0) {
		ip = arg;
		continue;
	  }
	  break;
	case JIF:
	  if (desempilha(pil) == 0) {
		ip = arg;
		continue;
	  }
	  break;
	case CALL:
	  empilha(exec, ip);
	  ip = arg;
	  continue;
	case RET:
	  ip = desempilha(exec);
	  break;
	case EQ:
	  if (desempilha(pil) == desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case GT:
	  if (desempilha(pil) < desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case GE:
	  if (desempilha(pil) <= desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case LT:
	  if (desempilha(pil) > desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case LE:
	  if (desempilha(pil) >= desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case NE:
	  if (desempilha(pil) != desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case STO:
	  m->Mem[arg] = desempilha(pil);
	  break;
	case RCL:
	  empilha(pil,m->Mem[arg]);
	  break;
	case END:
	  return;
	case PRN:
	  printf("%d\n", desempilha(pil));
	  break;
	}
	D(imprime(pil,5));
	D(puts("\n"));

	ip++;
  }
}
