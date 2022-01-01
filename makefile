INCLUDE=./include
SRC=./src
OBJ=./obj
BIN=./bin
SRC_FLEX=./Programa_FLEX


all: $(BIN)/series $(BIN)/extractorurls $(BIN)/pagina_principal

$(BIN)/pagina_principal: $(OBJ)/pagina_principal.o $(OBJ)/conjunto.o
	g++ -o $@ $^

$(BIN)/series: $(OBJ)/series.o
	gcc -o $@ $^ -lfl -DECHO

$(BIN)/extractorurls: $(OBJ)/extractorurls.o
	gcc -o $@ $^ -lfl -DECHO

$(OBJ)/series.o: $(SRC_FLEX)/practica2.l
	flex -o $(OBJ)/lex.yy.c $^
	gcc -c -o $@ $(OBJ)/lex.yy.c -lfl -DECHO

$(OBJ)/extractorurls.o: $(SRC_FLEX)/extractorurls.l
	flex -o $(OBJ)/lex2.yy.c $^
	gcc -c -o $@ obj/lex2.yy.c -lfl -DECHO

$(OBJ)/pagina_principal.o: $(SRC)/pagina_principal.cpp $(INCLUDE)/conjunto.h
	g++ -c -o $@ $< -I$(INCLUDE)

$(OBJ)/conjunto.o: $(SRC)/conjunto.cpp $(INCLUDE)/conjunto.h
	g++ -c -o $@ $< -I$(INCLUDE)

clean:
	rm obj/*

full-clean:
	rm obj/* bin/*