PROJETO E ANÁLISE DE ALGORITMOS - TRABALHO PRÁTICO 2
Alunos: Hugo Alves Azevedo de Souza e Rafael Moisés de Sá Tavares

Esse arquivo conta com instruções para execução do tp 2 e de informações sobre a entrada e saída do programa.

Execução:
  Para compilar o programa é necessário usar o comando no terminal "make build", tal comando irá compilar todos os arquivos necessários em arquivo objeto e salvar na pasta "objeto".
  Para executar o programa é necessário utilizar o comando "./sudoku.exe arquivo1.txt arquivo2.txt", sendo arquivo1 o arquivo que contém as entradas e arquivo2 o arquivo onde será escrito as soluções.
  Outra forma de executar o programa é com o comando make run, ele irá pegar a entrada que está no arquivo "sudoku.txt" e vai armazenar os resultados no arquivo "solucoes.txt".
Entrada:
  O formato da entrada é o mesmo especificado no pdf do tp com sudokus diferentes sendo separados por duas linhas vazias.
Saída: 
  É impresso no terminal o tempo gasto com a leitura, resolução de todos os sudokus com a heurística, resolução de todos os sudokus com backtracking comum e com as escritas no arquivo.
  Também 
  A saída é preenchida primeiramente com todas as soluções feitas com a heurística e depois todas as soluções com o backtracking comum. Um exemplo de saída:
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
