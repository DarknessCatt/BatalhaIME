Arena *init_arena() {
	Celula arena[11][11];
	int i,j;
	for(i=1;i<11;i++) {
		for(j=1; j<11; j++) {
			arena[i][j].terreno = rand() % 4;
			arena[i][j].cristais = rand() % 5;
		}
	}
}