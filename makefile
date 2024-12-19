OBJ_DIR = ./pontoOh
SRC_DIR = ./estrutura-de-dados

estrutura-de-dados = $(OBJ_DIR)/fila.o

run: 
	clear
	./sudoku.exe su-do-ku.txt ku-do-su.txt

leak:
	valgrind --leak-check=full --show-leak-kinds=all ./sudoku.exe su-do-ku.txt ku-do-su.txt

build: $(OBJ_DIR)/main.o $(OBJ_DIR)/leitura.o $(OBJ_DIR)/saida.o $(OBJ_DIR)/sudoku.o $(OBJ_DIR)/heuristica.o $(OBJ_DIR)/cronometro.o $(OBJ_DIR)/backtracking.o $(estrutura-de-dados)
	gcc $(OBJ_DIR)/main.o $(OBJ_DIR)/leitura.o $(OBJ_DIR)/saida.o $(OBJ_DIR)/sudoku.o $(OBJ_DIR)/heuristica.o $(OBJ_DIR)/cronometro.o $(OBJ_DIR)/backtracking.o $(estrutura-de-dados) -o ./sudoku.exe

$(OBJ_DIR)/main.o: ./main.c ./leitura.h ./heuristica.h ./sudoku.h ./saida.h | $(OBJ_DIR)
	gcc -c main.c -o $(OBJ_DIR)/main.o

$(OBJ_DIR)/leitura.o: ./leitura.c ./leitura.h | $(OBJ_DIR)
	gcc -c leitura.c -o $(OBJ_DIR)/leitura.o

$(OBJ_DIR)/fila.o: $(SRC_DIR)/fila.c $(SRC_DIR)/fila.h | $(OBJ_DIR)
	gcc -c $(SRC_DIR)/fila.c -o $(OBJ_DIR)/fila.o

$(OBJ_DIR)/saida.o: ./saida.c ./saida.h | $(OBJ_DIR)
	gcc -c saida.c -o $(OBJ_DIR)/saida.o

$(OBJ_DIR)/sudoku.o: ./sudoku.c ./sudoku.h | $(OBJ_DIR)
	gcc -c sudoku.c -o $(OBJ_DIR)/sudoku.o

$(OBJ_DIR)/backtracking.o: ./backtracking.c ./backtracking.h | $(OBJ_DIR)
	gcc -c backtracking.c -o $(OBJ_DIR)/backtracking.o

$(OBJ_DIR)/cronometro.o: ./cronometro.c cronometro.h | $(OBJ_DIR)
	gcc -c cronometro.c -o $(OBJ_DIR)/cronometro.o

$(OBJ_DIR)/heuristica.o: ./heuristica.c ./heuristica.h | $(OBJ_DIR)
	gcc -c heuristica.c -o $(OBJ_DIR)/heuristica.o

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean: 
	rm  $(OBJ_DIR)/*.o
	rm  sudoku.exe
