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
  "ATR",
  "MOV",
  "SRC",
  "GRB",
  "DRP"
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
	  OPERANDO op1;
	  OPERANDO op2;
	  OPERANDO op3;
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
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);
	  if (op1.t == NUM && op2.t == NUM) {
	  	op3.t = op1.t;
	  	op3.n = op1.n + op2.n;
	  	empilha(pil, op3);
	  }
	  else Fatal("Operando incompatível", 9);
	  break;
	case SUB:
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);
	  if (op1.t == NUM && op2.t == NUM) {
	  	op3;
	  	op3.t = op1.t;
	  	op3.n = op2.n - op1.n;
	  	empilha(pil, op3);
	  }
	  else Fatal("Operando incompatível", 9);
	  break;
	case MUL:
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);
	  if (op1.t == NUM && op2.t == NUM) {
	  	op3.t = op1.t;
	  	op3.n = op1.n * op2.n;
	  	empilha(pil, op3);
	  }
	  else Fatal("Operando incompatível", 9);
	  break;
	case DIV:
	  op1 = desempilha(pil);
	  op2 = desempilha(pil);
	  if (op1.t == NUM && op2.t == NUM) {
	  	op3.t = op1.t;
	  	op3.n = op2.n / op1.n;
	  	empilha(pil, op3);
	  }
	  else Fatal("Operando incompatível", 9);
	  break;
	case JMP:
	  ip = arg.n;
	  continue;
	case JIT:
	  op1 = desempilha(pil);
	  if (op1.t == NUM) {
	  	if (op1.n != 0) {
			ip = arg.n;
			continue;
		}
	  }
	  else Fatal("Operando incompatível", 9);
	  break;
	case JIF:
	  op1 = desempilha(pil);
	  if (op1.t == NUM) {
	  	if (op1.n == 0) {
			ip = arg.n;
			continue;
		}
	  }
	  else Fatal("Operando incompatível", 9); 
	  break;
	case CALL:
	  op1.t = NUM;
	  op1.n = ip;
	  op2.t = NUM;
	  op2.n = m->rbp;
	  empilha(exec, op1);
	  empilha(exec, op2); //armazena o rbp para voltar depois no RET
	  D(imprime(exec,5));
	  D(printf("\n     ")); 
	  ip = arg.n;
	  continue;
	case RET:
	  op2 = desempilha(exec);
	  if (op2.t == NUM) m->rbp = op2.n;
	  else Fatal("OPERANDO incompatível", 9);
	  
	  op1 = desempilha(exec);
	  if (op1.t == NUM) ip = op1.n;
	  else Fatal("OPERANDO incompatível", 9); 
	  break;                     
	case EQ:
	  op1.t = NUM;
	  op2 = desempilha(pil);
	  op3 = desempilha(pil);
	  if (op2.t == NUM && op3.t == NUM) {
	 	 if (op2.n == op3.n) {
			op1.n = 1;
			empilha(pil, op1);
	 	 }
	 	 else {
	  		op1.n = 0;
			empilha(pil, op1);
	  	}
	  }
	  else Fatal("Operando incompatível", 9); 
	  break;
	case GT:
	  op1.t = NUM;
	  op2 = desempilha(pil);
	  op3 = desempilha(pil);
	  if (op2.t == NUM && op3.t == NUM) {
	 	 if (op2.n < op3.n) {
			op1.n = 1;
			empilha(pil, op1);
	  	}
	  	else {
	  		op1.n = 0;
			empilha(pil, op1);
	  	}
	  }
	  else Fatal("Operando incompatível", 9);
	  break;
	case GE:
	  op1.t = NUM;
	  op2 = desempilha(pil);
	  op3 = desempilha(pil);
	  if (op2.t == NUM && op3.t == NUM) {
	 	 if (op2.n <= op3.n) {
			op1.n = 1;
			empilha(pil, op1);
	  	}
	 	 else {
	  		op1.n = 0;
			empilha(pil, op1);
	  	}
	  }
	  else Fatal("Operando incompatível", 9);
	  break;
	case LT:
	  op1.t = NUM;
	  op2 = desempilha(pil);
	  op3 = desempilha(pil);
	  if (op2.t == NUM && op3.t == NUM) {
	  	if (op3.n > op3.n) {
			op1.n = 1;
			empilha(pil, op1);
	  	}
	  	else {
	  		op1.n = 0;
			empilha(pil, op1);
	  	}
	  }
	  else Fatal("Operando incompatível", 9);
	  break;
	case LE:
	  op1.t = NUM;
	  op2 = desempilha(pil);
	  op3 = desempilha(pil);
	  if (op2.t == NUM && op3.t == NUM) {
	  	if (op2.n >= op3.n) {
			op1.n = 1;
			empilha(pil, op1);
	 	 }
	 	else {
	  		op1.n = 0;
			empilha(pil, op1);
	  	}
	  }
	  else Fatal("Operando incompatível", 9);
	  break;
	case NE:
	  op1.t = NUM;
	  op2 = desempilha(pil);
	  op3 = desempilha(pil);
	  if (op2.t == NUM && op2.t == NUM) {
	  if (op2.n != op3.n) {
		op1.n = 1;
		empilha(pil, op1);
	  }
	  else {
	  	op1.n = 0;
		empilha(pil, op1);
	  }
	  }
	  else Fatal("Operando incompatível", 9); 
	  break;
	case STO:
	  op1 = desempilha(pil);
	  m->Mem[arg.n] = op1;
	  break;
	case RCL:
	  op1 = m->Mem[arg.n];
	  empilha(pil, op1);
	  break;
	case END:
	  return;                   
	case PRN:
	  op1 = desempilha(pil);
	  printf("%d\n", op1.n); 
	  break;
	case RCE:
	  empilha(pil,exec->val[arg.n + m->rbp ]); //Empilha em pil o valor de pilha exec[arg + base]
	  break;
	case STL:
	  exec->val[m->rbp + arg.n] = desempilha(pil); //Desempilha da pilha de dados e coloca na de execucao na posição do arg mais rbp
	  break;
	case ALC:
	  if (arg.t == NUM) {
	  m->rbp = exec->topo-1; // Aponta a base para o inicio das variaveis locais (aponta para o valor de rbp antigo)
	  exec->topo = exec->topo + arg.n; //Soma arg no topo da pilha de exec
	  }
	  else Fatal("Operando incompatível", 9); 
	  break;
	case FRE:
	  exec->topo = m->rbp+1; //Volta o topo para sua posicao original
	  break;
	case ATR:
	  empilha(pil,arg);
	  Sistema(0); // vamos supor que o 0 é para ele retornar o valor do atributo.
	  break;
	case MOV:
	  if(arg.t == NUM){
	    empilha(pil,arg);
	  	Sistema(1);
	  }
	  else Fatal("Operando incompatível", 9); 
	  break;
	case SRC:
	   if(arg.t == NUM){
	   	empilha(pil,arg);
	  	Sistema(2);
	   }
	   else Fatal("Operando incompatível", 9);
	   break;
	case GRB:
	  if(arg.t == NUM){
	    empilha(pil,arg);
	  	Sistema(2);
	  }
	  else Fatal("Operando incompatível", 9);
	  break;
	case DRP:
	  if(arg.t == NUM){
	    empilha(pil,arg);
	  	Sistema(3);
	  }
	  else Fatal("Operando incompatível", 9);
	  break;
	}

	D(imprime(pil,5));
	D(printf("\n     "));
	D(imprime(exec,20));
	D(puts("\n"));

	ip++;
  }
}
