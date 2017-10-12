#include <stdio.h>

typedef struct {
int terreno;
int cristais;
int ocup;
int base;
} Celula;

typedef enum {
  PUSH,
  POP,
  DUP,
  ADD,
  SUB,
  MUL,
  DIV,
  JMP,
  JIT,
  JIF,
  CALL,
  RET,
  STS,
  RCS,
  EQ,
  GT,
  GE,
  LT,
  LE,
  NE,
  STO,
  RCL,
  END,
  PRN,
  RCE,
  STL,
  ALC,
  FRE,
  ATR
} OpCode;

typedef enum {
  NUM,
  ACAO,
  VAR,
  CELULA
} Tipo;

typedef struct { 
  Tipo t; 
   union { 
  	int n; 
  	int ac; 
  	int v; 
  	Celula c;
  }; 
} OPERANDO;

typedef struct {
  OpCode instr;
  OPERANDO op;
} INSTR;




INSTR programa[] = {
  {PUSH, 3},
  {PUSH, 6},
  {CALL, 5},
  {PRN,  0},
  {END,  0},
  {ADD,  0},
  {RET,  0}
};


int main()
{
	//OpCode   opc = programa[0].instr; //Linha ip do programa pegando o OpCode instr
	OPERANDO op;
	OPERANDO op1;
	op.t = CELULA;
	op1.t = NUM;
	op.n = 23;
	op1.n = 23;
	op.c.cristais = 22;
	printf("%d\n", op.c.cristais);
	/*
	OPERANDO op;
	op.t = NUM;
	op.n = 72;
	op.ac = 155;
	if(op.t == ACAO) printf("Acao");
	printf("%d",op.n);
	printf("%d",op.ac);
	Celula arena[1][1];
	arena[0][0].terreno = 0;
	arena[0][0].cristais = 0;
	arena[0][0].ocup = 1;
	int i;
	for (i = 0; i < 10; i++)
    {
           //printf("%d ", rand() % 4);
    }
	*/
}