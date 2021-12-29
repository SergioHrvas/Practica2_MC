

all: bin/series bin/extractorurls

bin/series: Programa_FLEX/practica2.l
	flex -o obj/lex.yy.c Programa_FLEX/practica2.l
	gcc -o $@ obj/lex.yy.c -lfl -DECHO

bin/extractorurls: Programa_FLEX/extractorurls.l
	flex -o obj/lex2.yy.c Programa_FLEX/extractorurls.l
	gcc -o $@ obj/lex2.yy.c -lfl -DECHO

clean:
	rm bin/*
	rm obj/*