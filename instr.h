/* Códigos das instruções */
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
  ATR,
  MOV,
  SRC,
  GRB,
  DRP
} OpCode;

/* Tipos dos operandos */
/* no momento, são todos inteiros */
typedef enum {
  NUM,
  ACAO,
  VAR,
  CELULA
} Tipo;

/* Operando */
typedef struct { 
  Tipo t; 
   union { 
  	int n; 
  	int ac; 
  	int v;
    Celula cel; 
  }; 
} OPERANDO;

/* Instrução */
typedef struct {
  OpCode instr;
  OPERANDO op;
} INSTR;
