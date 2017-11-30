/* Data type for links in the chain of symbols.      */
struct symrec
{
  char *name;  /* name of symbol                     */
  int val;
  struct symrec *next;    /* link field              */
};

typedef struct symrec symrec;

/* Stack size of sym tables */
#define SYM_STACK_SIZE 20


/* The symbol table: a chain of `struct symrec'.     */
extern symrec *sym_table;

symrec *putsym (char*);
symrec *getsym (char*);
symrec *getsymcur (char*);

int isglobal(void);

symrec *newtab(int);
symrec *deltab(void);
int lastval(void);
