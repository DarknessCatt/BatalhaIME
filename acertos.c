static int Pilha[20];
static int top = 0;

int salva_end(int ip) {
  if (top < 19) {
	Pilha[++top] = ip;
	return 1;
  }
  return 0;
}

int pega_end() {
  if (top >0)
	return Pilha[top--];
  return -1;
}

int pega_atu() {
  return top;
}
