/* Compilador */

%{
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "symrec.h"
#include "acertos.h"
#include "instr.h"

int yylex();
void yyerror(char const *);
int compila(FILE *, INSTR *);
static int ip  = 0;					/* ponteiro de instruções */
static int jp  = 0;
static int mem = 6;					/* ponteiro da memória */
static INSTR *prog;
static INSTR paux[100];
static int parmcnt = 0;		/* contador de parâmetros */
static int dir = 0;

void push(){
	paux[jp++] = prog[--ip];
}

INSTR pop(){
    if(jp>0){
        return paux[--jp];
    }
    else {
        yyerror("ta dando pop no nada tio?");
    }
}

void AddInstr(OpCode op, int val) {
  prog[ip++] = (INSTR) {op,  {NUM, {val}}};
}
%}

/*  Declaracoes */
%union {
  double val;
  /* symrec *cod; */
  char cod[30];
}

/* %type  Expr */

%token <val>  NUMt
%token <cod> ID
%token ADDt SUBt MULt DIVt ASGN OPEN CLOSE RETt EOL
%token EQt NEt LTt LEt GTt GEt ABRE FECHA SEP
%token IF ELSE WHILE FOR FUNC PRINT MOVER SEARCH GRAB DROP ATKK

%right ASGN
%left ADDt SUBt
%left MULt DIVt
%left NEG
%right PWR
%left LTt GTt LEt GEt EQt NEt


/* Gramatica */
%%

Programa: Comando
       | Programa Comando
	   ;

Comando: Expr EOL
       | Cond
       | Loop
       | Func
	   | PRINT Expr EOL { AddInstr(PRN, 0);}
	   | MOVER Direcao EOL {AddInstr(MOV, dir);}
	   | SEARCH Direcao EOL {AddInstr(SCH, dir);}
       | GRAB Direcao EOL {AddInstr(GRB, dir);}
	   | DROP Direcao EOL {AddInstr(DRP, dir);}
       | ATKK Direcao EOL {AddInstr(ATK, dir);}
	   | RETt EOL {
		 	     AddInstr(LEAVE, 0);
			     AddInstr(RET, 0);
 			  }
	   | RETt OPEN  Expr CLOSE EOL {
		 	     AddInstr(LEAVE, 0);
			     AddInstr(RET,0);
 		      }
	   /* | EOL {printf("--> %d\n", ip);} */
;

Expr: NUMt {  AddInstr(PUSH, $1);}
    | ID   {
	         symrec *s = getsym($1);
			 if (s==0) s = putsym($1); /* não definida */
			 AddInstr(RCL, s->val);
	       }
	| ID ASGN Expr {
	         symrec *s = getsym($1);
			 if (s==0) s = putsym($1); /* não definida */
			 AddInstr(STO, s->val);
 		 }
	/* | ID PONTO NUMt  {  % v.4 */
	/*          symrec *s = getsym($1); */
	/* 		 if (s==0) s = putsym($1); /\* não definida *\/ */
	/* 		 AddInstr(PUSH, s->val); */
	/* 		 AddInstr(ATR, $3); */
 	/* 	 } */
	| Chamada 
    | Expr ADDt Expr { AddInstr(ADD,  0);}
	| Expr SUBt Expr { AddInstr(SUB,  0);}
	| Expr MULt Expr { AddInstr(MUL,  0);}
	| Expr DIVt Expr { AddInstr(DIV,  0);}
    | '-' Expr %prec NEG  { printf("  {CHS,  0},\n"); }
	| OPEN Expr CLOSE
	| Expr LTt Expr  { AddInstr(LT,   0);}
	| Expr GTt Expr  { AddInstr(GT,   0);}
	| Expr LEt Expr  { AddInstr(LE,   0);}
	| Expr GEt Expr  { AddInstr(GE,   0);}
	| Expr EQt Expr  { AddInstr(EQ,   0);}
	| Expr NEt Expr  { AddInstr(NE,   0);}
;

Cond: IF OPEN Expr {
  	  	 	   salva_end(ip);
			   AddInstr(JIF,  0);
 		 }
		 CLOSE Bloco {
		 	prog[pega_end()].op.n = ip+1;
		 	salva_end(ip);
		 	AddInstr(JMP,  ip+1);
		 }
	| Cond ELSE Bloco {
		   prog[pega_end()].op.n = ip;
	};

Loop: WHILE OPEN  {salva_end(ip);}
	  		Expr  { salva_end(ip); AddInstr(JIF,0); }
	  		CLOSE Bloco {
			  int ip2 = pega_end();
			  AddInstr(JMP, pega_end());
			  prog[ip2].op.n = ip;
			}
	| FOR OPEN Expr EOL { salva_end(ip);}
	  		Expr EOL { salva_end(ip);}
	  	    ID ASGN Expr {
	        	symrec *s = getsym($9);
				if (s==0) s = putsym($9); /* não definida */
				AddInstr(STO, s->val);
				int i = pega_end();
				int num = ip - i;
				while(ip>i) push();
				AddInstr(ADD, num); push(); // adiciona num na pilha
				salva_end(ip);
				AddInstr(JIF,0);
 		 	}
	  		CLOSE Bloco {
	  		  for( int j = (int) pop().op.n; j>0 ; j--) prog[ip++] = pop();
			  int ip2 = pega_end();
			  AddInstr(JMP, pega_end());
			  prog[ip2].op.n = ip;
			}; 

Bloco: ABRE Comandos FECHA ;

Comandos: Comando 
    | Comandos Comando
	;

Func: FUNC ID
	  {
		salva_end(ip);
		AddInstr(JMP,  0);
		symrec *s = getsym($2);
		if (s==0) s = putsym($2);
		else {
		  yyerror("Função definida duas vezes\n");
		  YYABORT;
		}
		s->val = ip;
	  } OPEN
	  {
		newtab(0);
	  }
	  Args CLOSE  Bloco
	  {
		AddInstr(LEAVE, 0);
		AddInstr(RET, 0);
		prog[pega_end()].op.n = ip;
		deltab();
	  }
	  ;

Args: 
	| ID {
	  	 putsym($1);
	  }
    | Args SEP ID {
	  	 putsym($3);
	  }
	;

Chamada: ID OPEN
		 {
			 parmcnt = 0;
			 /* posição da memória mais avançada */
		 }
		 ListParms
		 {
		   symrec *s = getsym($1);
		   if (s == 0) {
			 yyerror("Função não definida\n");
			 YYABORT;
		   }
		   AddInstr(ENTRY, lastval());
		   /* Cópia dos parâmetros */
		   while (parmcnt > 0) 
			 AddInstr( STO, --parmcnt);
		   AddInstr(CALL, s->val);
		 }
	  	 CLOSE ;

Direcao: OPEN ID CLOSE {
			char* string = $2;
	   			if      (strcmp(string, "NW") == 0) {dir = 0;}
	   			else if (strcmp(string, "NE") == 0) {dir = 1;}
	   			else if (strcmp(string, "E") == 0)  {dir = 2;}
	   			else if (strcmp(string, "SE") == 0) {dir = 3;}
	   			else if (strcmp(string, "SW") == 0) {dir = 4;}
	   			else if (strcmp(string, "W") == 0)  {dir = 5;}
	   			else {
	   				yyerror("Direção invalida!\n");
			 		YYABORT;
			 	}
			}
;

ListParms:
	| Expr { parmcnt++;}
	| Expr { parmcnt++;} SEP ListParms
;

%%
extern FILE *yyin;

void yyerror(char const *msg) {
  fprintf(stderr,"ERRO: %s",msg);
}

int compilador(FILE *cod, INSTR *dest) {
  int r;
  yyin = cod;
  prog = dest;
  cleartab();
  ip = 0;
  r = yyparse();
  AddInstr(END,0);
  return r;
}

/* int main(int ac, char **av) */
/* { */
/*   ac --; av++; */
/*   if (ac>0) */
/* 	yyin = fopen(*av,"r"); */

/*   yyparse(); */
/*   return 0; */
/* } */
