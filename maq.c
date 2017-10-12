#include <stdio.h>
#include <stdlib.h>
#include "maq.h"

//#define DEBUG 

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
  "PRN",
  "RCE",
  "STL",
  "ALC",
  "FRE",
  "ATR"
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
  m->rbp = 0;
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
		if (op.t == NUM) { 
			empilha(pil, arg); 
			break;
		}
		else Fatal("Operando incompatível", 9);
	case POP:
	  desempilha(pil);
	  break;
	case DUP:
	  tmp = desempilha(pil);
	  empilha(pil, tmp);
	  empilha(pil, tmp);
	  break;
	case ADD:
	  Operando op1 = desempilha(pil);
	  Operando op2 = desempilha(pil);
	  if (op1.t == NUM && op2.t == NUM) {
	  	Operando op3;
	  	op3.t = op1.t;
	  	op3.n = op1.n + op2.n;
	  	empilha(pil, op3);
	  	break;
	  }
	  else Fatal("Operando incompatível", 9);
	case SUB:
	  Operando op1 = desempilha(pil);
	  Operando op2 = desempilha(pil);
	  if (op1.t == NUM && op2.t == NUM) {
	  	Operando op3;
	  	op3.t = op1.t;
	  	op3.n = op2.n - op1.n;
	  	empilha(pil, op3);
	  	break;
	  }
	  else Fatal("Operando incompatível", 9);
	case MUL:
	  Operando op1 = desempilha(pil);
	  Operando op2 = desempilha(pil);
	  if (op1.t == NUM && op2.t == NUM) {
	  	Operando op3;
	  	op3.t = op1.t;
	  	op3.n = op1.n * op2.n;
	  	empilha(pil, op3);
	  	break;
	  }
	  else Fatal("Operando incompatível", 9);
	case DIV:
	  Operando op1 = desempilha(pil);
	  Operando op2 = desempilha(pil);
	  if (op1.t == NUM && op2.t == NUM) {
	  	Operando op3;
	  	op3.t = op1.t;
	  	op3.n = op2.n / op1.n;
	  	empilha(pil, op3);
	  	break;
	  }
	  else Fatal("Operando incompatível", 9);
	case JMP:
	  ip = arg.n;
	  continue;
	case JIT:
	  Operando op = desempilha(pil);
	  if (op.t == NUM) {
	  	if (op.n != 0) {
			ip = arg.n;
			continue;
		}
		break;
	  }
	  else Fatal("Operando incompatível", 9);
	case JIF:
	  Operando op = desempilha(pil);
	  if (op.t == NUM) {
	  	if (op.n == 0) {
			ip = arg.n;
			continue;
		}
		break;
	  }
	  else Fatal("Operando incompatível", 9); 
	case CALL:
	  Operando opip;
	  opip.t = NUM;
	  opip.n = ip;
	  Operando oprbp;
	  oprbp.t = NUM;
	  oprbp.n = m->rbp;
	  empilha(exec, opip);
	  empilha(exec, oprbp); //armazena o rbp para voltar depois no RET
	  D(imprime(exec,5));
	  D(printf("\n     ")); 
	  ip = arg.n;
	  continue;
	case RET:
	  Operando oprbp = desempilha(exec);
	  if (oprbp.t == NUM) m->rbp = oprbp.n;
	  else Fatal("Operando incompatível", 9);
	  
	  Operando opip = desempilha(exec);
	  if (opip.t == NUM) ip = opip.n;
	  else Fatal("Operando incompatível", 9); 

	  break;                     
	case EQ:
	  Operando op;
	  op.t = NUM;
	  Operando opA = desempilha(pil);
	  Operando opB = desempilha(pil);
	  if (opA.t == NUM && opB.t == NUM) {
	  if (opA.n == opB.n) {
		op.n = 1;
		empilha(pil, op);
	  }
	  else {
	  	op.n = 0;
		empilha(pil, op);
	  }
	  break;
	  }
	  else Fatal("Operando incompatível", 9); 
	case GT:
	  Operando op;
	  op.t = NUM;
	  Operando opA = desempilha(pil);
	  Operando opB = desempilha(pil);
	  if (opA.t == NUM && opB.t == NUM) {
	  if (opA.n < opB.n) {
		op.n = 1;
		empilha(pil, op);
	  }
	  else {
	  	op.n = 0;
		empilha(pil, op);
	  }
	  break;
	  }
	  else Fatal("Operando incompatível", 9);
	case GE:
	  Operando op;
	  op.t = NUM;
	  Operando opA = desempilha(pil);
	  Operando opB = desempilha(pil);
	  if (opA.t == NUM && opB.t == NUM) {
	  if (opA.n <= opB.n) {
		op.n = 1;
		empilha(pil, op);
	  }
	  else {
	  	op.n = 0;
		empilha(pil, op);
	  }
	  break;
	  }
	  else Fatal("Operando incompatível", 9);
	case LT:
	  Operando op;
	  op.t = NUM;
	  Operando opA = desempilha(pil);
	  Operando opB = desempilha(pil);
	  if (opA.t == NUM && opB.t == NUM) {
	  if (opA.n > opB.n) {
		op.n = 1;
		empilha(pil, op);
	  }
	  else {
	  	op.n = 0;
		empilha(pil, op);
	  }
	  break;
	  }
	  else Fatal("Operando incompatível", 9);
	case LE:
	  Operando op;
	  op.t = NUM;
	  Operando opA = desempilha(pil);
	  Operando opB = desempilha(pil);
	  if (opA.t == NUM && opB.t == NUM) {
	  if (opA.n >= opB.n) {
		op.n = 1;
		empilha(pil, op);
	  }
	  else {
	  	op.n = 0;
		empilha(pil, op);
	  }
	  break;
	  }
	  else Fatal("Operando incompatível", 9);
	case NE:
	  Operando op;
	  op.t = NUM;
	  Operando opA = desempilha(pil);
	  Operando opB = desempilha(pil);
	  if (opA.t == NUM && opB.t == NUM) {
	  if (opA.n != opB.n) {
		op.n = 1;
		empilha(pil, op);
	  }
	  else {
	  	op.n = 0;
		empilha(pil, op);
	  }
	  break;
	  }
	  else Fatal("Operando incompatível", 9); 
	case STO:
	  Operando op;
	  op.t = NUM;
	  op.n = desempilha(pil);
	  m->Mem[arg.n] = op.n;
	  break;
	case RCL:
	  Operando op;
	  op.t = NUM;
	  op.n = m->Mem[arg.n];
	  empilha(pil, op);
	  break;
	case END:
	  return;                   
	case PRN:
	  printf("%d\n", desempilha(pil)); //fazer depois LEIA-ME! ISSO! VC MESMO! ~~~~~~~~~~~~~~~~~X~~~~~~~~~~~~~~~
	  break;
	case RCE:
	  empilha(pil,exec->val[arg + m->rbp ]); //Empilha em pil o valor de pilha exec[arg + base]
	  break;
	case STL:
	  exec->val[m->rbp+arg] = desempilha(pil); //Desempilha da pilha de dados e coloca na de execucao na posição do arg mais rbp
	  break;      //até aqui parece certo RM ME LATER PLIS PLIS ----------------X-----------------------
	case ALC:
	  m->rbp = exec->topo-1; // Aponta a base para o inicio das variaveis locais (aponta para o valor de rbp antigo)
	  exec->topo = exec->topo + arg; //Soma arg no topo da pilha de exec
	  break;
	case FRE:
	  exec->topo = m->rbp+1; //Volta o topo para sua posicao original
	  break;
	case ATR: //change me plis plis
	  empilha(pil,arg);
	  empilha(Sistema(0)); // vamos supor que o 0 é para ele retornar o valor do atributo.
	  break;
	}
	D(imprime(pil,5));
	D(printf("\n     "));
	D(imprime(exec,20));
	D(puts("\n"));

	ip++;
  }
}
