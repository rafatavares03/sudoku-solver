# Projeto e Análise de Algoritmos - Trabalho Prático 2

**Alunos:** Hugo Alves Azevedo de Souza e Rafael Moisés de Sá Tavares

## Execução

Para compilar o programa, use o comando no terminal:

```
make build
```

Esse comando irá compilar todos os arquivos necessários em arquivo objeto e salvá-los na pasta `objeto`.

Para executar o programa, utilize o comando:

```
./sudoku.exe arquivo1.txt arquivo2.txt
```

Onde `arquivo1` é o arquivo que contém as entradas, e `arquivo2` é o arquivo onde serão escritas as soluções.

Outra forma de executar o programa é com o comando:

```
make run
```

Esse comando usará a entrada do arquivo `sudoku.txt` e armazenará os resultados no arquivo `solucoes.txt`.

## Entrada

O formato da entrada segue as especificações do PDF do trabalho prático, com sudokus diferentes sendo separados por duas linhas vazias.

## Saída

No terminal, será impresso o tempo gasto com:

- Leitura
- Resolução de todos os sudokus com a heurística
- Resolução de todos os sudokus com backtracking comum
- Escritas no arquivo

A saída do arquivo conterá primeiramente as soluções obtidas com a heurística, seguidas pelas soluções obtidas com o backtracking comum. Exemplo de saída:

```
heuristica: 1
 4 5 6  7 8 1  2 9 3
 7 9 8  5 3 2  6 4 1
 2 1 3  6 9 4  8 5 7

 9 6 2  4 1 7  5 3 8
 5 8 1  2 6 3  4 7 9
 3 4 7  8 5 9  1 2 6

 8 7 5  3 4 6  9 1 2
 6 3 9  1 2 5  7 8 4
 1 2 4  9 7 8  3 6 5

heuristica: 2
 6 3 2  9 4 5  7 8 1
 5 7 9  8 1 6  4 2 3
 1 8 4  3 2 7  6 9 5

 2 6 8  5 9 3  1 4 7
 9 5 1  7 8 4  2 3 6
 7 4 3  1 6 2  9 5 8

 8 2 7  4 5 1  3 6 9
 4 1 5  6 3 9  8 7 2
 3 9 6  2 7 8  5 1 4

forca bruta: 1
 4 5 6  7 8 1  2 9 3
 7 9 8  5 3 2  6 4 1
 2 1 3  6 9 4  8 5 7

 9 6 2  4 1 7  5 3 8
 5 8 1  2 6 3  4 7 9
 3 4 7  8 5 9  1 2 6

 8 7 5  3 4 6  9 1 2
 6 3 9  1 2 5  7 8 4
 1 2 4  9 7 8  3 6 5

forca bruta: 2
 6 3 2  9 4 5  7 8 1
 5 7 9  8 1 6  4 2 3
 1 8 4  3 2 7  6 9 5

 2 6 8  5 9 3  1 4 7
 9 5 1  7 8 4  2 3 6
 7 4 3  1 6 2  9 5 8

 8 2 7  4 5 1  3 6 9
 4 1 5  6 3 9  8 7 2
 3 9 6  2 7 8  5 1 4
```
