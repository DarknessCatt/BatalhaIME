compila: compila.tab.o symrec.o arena.o maq.o pilha.o motor.o lex.yy.o acertos.o 
	gcc symrec.o arena.o maq.o pilha.o motor.o lex.yy.o compila.tab.o acertos.o -o compila -lm -lfl

compila.tab.o: compila.y
	bison -d compila.y
	gcc -c compila.tab.c

lex.yy.o: compila.l
	flex compila.l
	gcc -c lex.yy.c

progteste: maq.o pilha.o arena.o progteste.o

clean:
	rm -f progteste *.o lex.yy.c compila.tab.c compila.tab.h compila

