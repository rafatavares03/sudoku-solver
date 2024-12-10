estrutura-de-dados = ./estrutura-de-dados/fila.o ./estrutura-de-dados/lista.o

build: ./main.c leitura.o saida.o sudoku.o $(estrutura-de-dados)
	gcc main.c leitura.o saida.o sudoku.o $(estrutura-de-dados) -o ./teste

main.o: ./main.c ./leitura.h ./sudoku.h ./saida.h
	gcc -c main.c -o main.o

leitura.o: ./leitura.c ./leitura.h
	gcc -c leitura.c -o leitura.o

saida.o: ./saida.c ./saida.h
	gcc -c saida.c -o saida.o

sudoku.o: ./sudoku.c ./sudoku.h
	gcc -c sudoku.c -o sudoku.o

fila.o: ./estrutura-de-dados/fila.c ./estrutura-de-dados/fila.h
	gcc -c ./estrutura-de-dados/fila.c -o ./estrutura-de-dados/fila.o

lista.o: ./estrutura-de-dados/lista.c ./estrutura-de-dados/lista.h
	gcc -c ./estrutura-de-dados/lista.c -o ./estrutura-de-dados/lista.o

clean: 
	rm ./*.o 
	rm ./estrutura-de-dados/*.o