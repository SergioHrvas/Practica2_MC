

all: bin/series bin/extractorurls bin/pagina_principal

bin/series: Programa_FLEX/practica2.l
	flex -o obj/lex.yy.c Programa_FLEX/practica2.l
	gcc -o $@ obj/lex.yy.c -lfl -DECHO

bin/extractorurls: Programa_FLEX/extractorurls.l
	flex -o obj/lex2.yy.c Programa_FLEX/extractorurls.l
	gcc -o $@ obj/lex2.yy.c -lfl -DECHO

bin/pagina_principal: src/pagina_principal.cpp src/conjunto.h src/conjunto.cpp
	g++ -o $@ src/pagina_principal.cpp src/conjunto.cpp

clean:
	rm bin/*
	rm obj/*