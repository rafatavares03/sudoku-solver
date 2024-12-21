<!DOCTYPE html>
<html lang="pt-BR">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Projeto e Análise de Algoritmos - Trabalho Prático 2</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 20px;
        }
        h1, h2 {
            color: #333;
        }
        code {
            background-color: #f4f4f4;
            padding: 2px 4px;
            border-radius: 4px;
            font-family: monospace;
        }
        pre {
            background-color: #f4f4f4;
            padding: 10px;
            border-radius: 4px;
            overflow-x: auto;
        }
    </style>
</head>
<body>
    <h1>Projeto e Análise de Algoritmos - Trabalho Prático 2</h1>
    <p><strong>Alunos:</strong> Hugo Alves Azevedo de Souza e Rafael Moisés de Sá Tavares</p>

    <h2>Execução</h2>
    <p>Para compilar o programa, use o comando no terminal:</p>
    <pre><code>make build</code></pre>
    <p>Esse comando irá compilar todos os arquivos necessários em arquivo objeto e salvá-los na pasta <code>objeto</code>.</p>
    <p>Para executar o programa, utilize o comando:</p>
    <pre><code>./sudoku.exe arquivo1.txt arquivo2.txt</code></pre>
    <p>Onde <code>arquivo1</code> é o arquivo que contém as entradas, e <code>arquivo2</code> é o arquivo onde serão escritas as soluções.</p>
    <p>Outra forma de executar o programa é com o comando:</p>
    <pre><code>make run</code></pre>
    <p>Esse comando usará a entrada do arquivo <code>sudoku.txt</code> e armazenará os resultados no arquivo <code>solucoes.txt</code>.</p>

    <h2>Entrada</h2>
    <p>O formato da entrada segue as especificações do PDF do trabalho prático, com sudokus diferentes sendo separados por duas linhas vazias.</p>

    <h2>Saída</h2>
    <p>No terminal, será impresso o tempo gasto com:</p>
    <ul>
        <li>Leitura</li>
        <li>Resolução de todos os sudokus com a heurística</li>
        <li>Resolução de todos os sudokus com backtracking comum</li>
        <li>Escritas no arquivo</li>
    </ul>
    <p>A saída do arquivo conterá primeiramente as soluções obtidas com a heurística, seguidas pelas soluções obtidas com o backtracking comum. Exemplo de saída:</p>

    <pre><code>heuristica: 1
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
</code></pre>
</body>
</html>
