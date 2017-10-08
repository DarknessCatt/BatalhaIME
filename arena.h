
typedef struct {
int terreno;
int cristais;
int ocup;
int base;
} Celula;

Arena *init_arena();
void Atualiza();
void InsereExercito();
void RemoveExercito();
void Sistema(int op);