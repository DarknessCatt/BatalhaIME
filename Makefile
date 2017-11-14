.PHONY: edit

edit:
	subl arena.c arena.h instr.h maq.c maq.h pilha.c pilha.h

progteste: maq.o pilha.o arena.o progteste.o

drawteste: maq.o pilha.o arenaDRAW.o drawteste.o

clean:
	rm -f progteste *.o

