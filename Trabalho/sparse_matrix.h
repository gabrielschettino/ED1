#include "node.h"

typedef struct SparseMatrix
{
    int rows;
    int cols;
    Node **rowHeads; // Array de ponteiros para a cabeça de cada linha
    Node **colHeads; // Array de ponteiros para a cabeça de cada coluna
} SparseMatrix;
/*Modelo de matrizes esparsas, em que são definidas as quantidades de linhas, colunas, e os ponteiros para a cabeça de cada linha/coluna*/

SparseMatrix *createMatrix(int num_rows, int num_cols);
/*Complexidade O(n), pois alocar memória para os arrays rowHeads e colHeads tem uma complexidade de tempo de O(rows) e O(cols), respectivamente*/

void destroyMatrix(SparseMatrix *matrix);
/*Complexidade O(n), pois a função tem que iterar sobre cada linha da matriz, resultando numa complexidade de O(n-linhas * elementos nao zero)*/

void assignValue(SparseMatrix *matrix, int row, int col, float value);
/*Complexidade O(n), pois no pior caso, a função vai ter que iterar sobre elementos que já existem numa linha ou coluna, e preencher os valores, então O(n-elementoss na linha) ou O(n-elementoss na coluna)  */

float readValue(const SparseMatrix *matrix, int row, int col);
/*No pior caso, a função de leitura vai iterar sobre todos os valores de uma linha preenchida, resultando na complexidade de O(k), sendo k o numero de elementos nao nulos na linha*/

SparseMatrix *addMatrices(const SparseMatrix *matrix1, const SparseMatrix *matrix2);
/*Complexidade O(n), pois após checado os tamanhos, a operação mais longa vai depender do tamanho de elementos não nulos da matriz 1*/

SparseMatrix *multiplyByScalar(const SparseMatrix *matrix, float scalar);
/*O(n) novamente, pois necessariamente a função vai iterar por todos os elementos nao nulos*/

SparseMatrix *multiplyMatrices(const SparseMatrix *matrix1, const SparseMatrix *matrix2);
/*Comlpexidade O(n*m), sendo "n" o numero de linhas da matriz 1 e m o numero de colunas da matriz 2, sendo que no pior cenario, o loop interno da função vai iterar por todos valores das 2 matrizes*/

SparseMatrix *pointToPointMultiply(const SparseMatrix *matrix1, const SparseMatrix *matrix2);
/*Complexidade O(n*k), sendo n o numero de linhas da matriz 1, e k o numero de valores nao nulos na matriz 2*/

SparseMatrix *swapRows(const SparseMatrix *matrix, int row1, int row2);
/*A complexidade da função implementada está na ordem de O(n*k), como na função de multiplicação ponto a ponto*/

SparseMatrix *sliceMatrix(const SparseMatrix *matrix, int startRow, int startCol, int endRow, int endCol);
/*Complexidade O(n*k), snedo n o numero de linhas na matriz resultante e k é o valor de valores nao nulos da matriz original*/

SparseMatrix *transposeMatrix(const SparseMatrix *matrix);
/*Complexidade O(n*k), sendo n o numero de linhas da matriz original e k o numero de valores nao nulos da matriz original*/

void displaySparseMatrix(const SparseMatrix *matrix);
/*O(n), por simples loop pelos elementos nao nulos da matriz*/

void displayDenseMatrix(const SparseMatrix *matrix);
/*O(n*m), pois necessariamente vai printar todos os valores*/

SparseMatrix *convolution(const SparseMatrix *matrix, const SparseMatrix *kernel);
/*Presumo que seja O(n, m, p, q), em que "n" e "m" são referidos as dimensões da primeira matriz, e "p" e "q" sejam do kernel, e no pior caso, serem matrizes que tenham essas mesmas dimensões, com nenhum elemento sendo igual a zero*/

void saveSparseMatrix(const SparseMatrix *matrix, const char *filename);
/*considerando que percorrer a lista encadeada tem complexidade linear, a complexidade pra salvar em um arquivo será de O(m*n*k), no pior caso onde todas as celulas são diferentes de zero*/

SparseMatrix *readSparseMatrix(const char *filename);
/*Complexidade O(n), pois basicamente a função vai iterar por todos os elementos nao nulos da matriz*/