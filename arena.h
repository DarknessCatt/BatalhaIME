
typedef struct {
int terreno;
int cristais;
int ocup;
int base;
} Celula;

typedef struct {
	Celula[][] arena;
} Arena;

Arena *init_arena();
void Atualiza();
void InsereExercito();
void RemoveExercito();
void Sistema(int op);