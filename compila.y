/* Compilador */

%{
#include <stdio.h>
#include <math.h>
#include "symrec.h"
#include "acertos.h"
#include "instr.h"
  
int yylex();
void yyerror(char const *);
int compila(FILE *, INSTR *);
static int ip  = 0;					/* ponteiro de instruções */
static int mem = 6;					/* ponteiro da memória */
static INSTR *prog;
static int parmcnt = 0;		/* contador de parâmetros */

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
%token IF WHILE FUNC PRINT MOV

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
	   | MOV OPEN ID CLOSE EOL { int dir;
	   							switch($3){
	   								case "NW":
	   									dir = 0;
	   									break;
	   								case "NE":
	   									dir = 1;
	   									break;
	   								case "E":
	   									dir = 2;
	   									break;
	   								case "SE":
	   									dir = 3;
	   									break;
	   								case "SW":
	   									dir = 4;
	   									break;
	   								case "W":
	   									dir = 5;
	   									break;
	   								default:
	   									yyerror("Direção invalida!\n");
			 							YYABORT;
			 							break;
			 						}
			 					AddInstr(MOV, dir);
	   							}
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

Cond: IF OPEN  Expr {
  	  	 	   salva_end(ip);
			   AddInstr(JIF,  0);
 		 }
		 CLOSE  Bloco {
		   prog[pega_end()].op.n = ip;
		 };

Loop: WHILE OPEN  {salva_end(ip);}
	  		Expr  { salva_end(ip); AddInstr(JIF,0); }
	  		CLOSE Bloco {
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
