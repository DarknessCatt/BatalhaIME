#include <stdio.h>

typedef struct {
int terreno;
int cristais;
int ocup;
int base;
} Celula;

int main()
{
	Celula arena[1][1];
	arena[0][0].terreno = 0;
	arena[0][0].cristais = 0;
	arena[0][0].ocup = 1;
	int i;
	for (i = 0; i < 10; i++)
    {
           /* gerando valores aleatórios entre zero e 100 */
           printf("%d ", rand() % 4);
    }
}