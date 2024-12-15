estrutura-de-dados =  ./estrutura-de-dados/lista.o ./estrutura-de-dados/filaSu.o

run: 
	./sudoku su-do-ku.txt ku-do-su.txt

build: ./main.o leitura.o saida.o sudoku.o heuristica.o cronometro.o backtracking.o $(estrutura-de-dados)
	gcc main.c leitura.o saida.o sudoku.o heuristica.o cronometro.o backtracking.o $(estrutura-de-dados) -o ./sudoku

main.o: ./main.c ./leitura.h  ./heuristica.h ./sudoku.h ./saida.h
	gcc -c main.c -o main.o

leitura.o: ./leitura.c ./leitura.h
	gcc -c leitura.c -o leitura.o

filaSu.o: ./estrutura-de-dados/filaSu.c ./estrutura-de-dados/filaSu.h
	gcc -c ./estrutura-de-dados/filaSu.c -o ./estrutura-de-dados/filaSu.o

saida.o: ./saida.c ./saida.h
	gcc -c saida.c -o saida.o

sudoku.o: ./sudoku.c ./sudoku.h
	gcc -c sudoku.c -o sudoku.o

backtracking.o: ./backtracking.c ./backtracking.h 
	gcc -c backtracking.c -o backtracking.o

cronometro.o: ./cronometro.c cronometro.h
	gcc -c cronometro.c -o cronometro.o

heuristica.o: ./heuristica.c ./heuristica.h
	gcc -c heuristica.c -o heuristica.o

lista.o: ./estrutura-de-dados/lista.c ./estrutura-de-dados/lista.h
	gcc -c ./estrutura-de-dados/lista.c -o ./estrutura-de-dados/lista.o

clean: 
	rm *.o 
	rm ./estrutura-de-dados/*.o
	rm sudoku