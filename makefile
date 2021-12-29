

all: programa

programa: prueba.l
	flex practica2.l
	gcc -o $@ lex.yy.c -lfl


clean:
	rm programa