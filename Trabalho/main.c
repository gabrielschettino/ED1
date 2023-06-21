#include <stdio.h>
#include "sparse_matrix.h"

int main()
{
    // criando uma matriz esparsa
    SparseMatrix *matrix1 = createMatrix(3, 3);
    assignValue(matrix1, 0, 0, 1.0);
    assignValue(matrix1, 1, 1, 2.0);
    assignValue(matrix1, 2, 2, 3.0);

    // criando mais uma matriz esparsa
    SparseMatrix *matrix2 = createMatrix(3, 3);
    assignValue(matrix2, 0, 0, 4.0);
    assignValue(matrix2, 1, 1, 5.0);
    assignValue(matrix2, 2, 2, 6.0);

    // testando a função de exibição
    SparseMatrix *result;

    // mostrando matriz 1
    printf("matriz 1:\n");
    displayDenseMatrix(matrix1);
    printf("\n");
    // resultado esperado:
    // 1.00 0.00 0.00
    // 0.00 2.00 0.00
    // 0.00 0.00 3.00

    // mostrando matriz 2
    printf("matriz 2:\n");
    displayDenseMatrix(matrix2);
    printf("\n");
    // resultado esperado:
    // 4.00 0.00 0.00
    // 0.00 5.00 0.00
    // 0.00 0.00 6.00

    // Soma de matrizes
    printf("somando as matrizes 1 e 2:\n");
    result = addMatrices(matrix1, matrix2);
    displayDenseMatrix(result);
    printf("\n");
    // resultado esperado da soma:
    // 5.00 0.00 0.00
    // 0.00 7.00 0.00
    // 0.00 0.00 9.00
    destroyMatrix(result);

    // maultiplicando matriz 1 pelo escalar 2
    printf("multiplicando matriz 1 por escalar 2:\n");
    result = multiplyByScalar(matrix1, 2);
    displayDenseMatrix(result);
    printf("\n");
    // resultado esperado:
    // 2.00 0.00 0.00
    // 0.00 4.00 0.00
    // 0.00 0.00 6.00
    destroyMatrix(result);

    // multiplicação de matrizes
    printf("Multiplicando matriz 1 por matriz 2:\n");
    result = multiplyMatrices(matrix1, matrix2);
    displayDenseMatrix(result);
    printf("\n");
    // resultado esperado:
    // 4.00 0.00 0.00
    // 0.00 10.00 0.00
    // 0.00 0.00 18.00
    destroyMatrix(result);

    // multiplicação ponto a ponto
    printf("Multiplicação ponto a ponto da matriz 1 pela matriz 2:\n");
    result = pointToPointMultiply(matrix1, matrix2);
    displayDenseMatrix(result);
    printf("\n");
    // resultado esperado:
    // 4.00 0.00 0.00
    // 0.00 10.00 0.00
    // 0.00 0.00 18.00
    destroyMatrix(result);

    // trocando linhas
    printf("trocando lunha 1 pela linha 3 da matriz 1:\n");
    result = swapRows(matrix1, 0, 2);
    displayDenseMatrix(result);
    printf("\n");
    // resultado esperado:
    // 0.00 0.00 3.00
    // 0.00 2.00 0.00
    // 1.00 0.00 0.00
    destroyMatrix(result);

    // slice de matrizes
    printf("slice da parte esquerda superior 2x2 da matriz 1:\n");
    result = sliceMatrix(matrix1, 0, 0, 1, 1);
    displayDenseMatrix(result);
    printf("\n");
    // resultado esperado:
    // 1.00 0.00
    // 0.00 2.00
    destroyMatrix(result);

    // transposta da matriz
    printf("transpondo a matriz 1:\n");
    result = transposeMatrix(matrix1);
    displayDenseMatrix(result);
    printf("\n");
    // resultado esperado:
    // 1.00 0.00 0.00
    // 0.00 2.00 0.00
    // 0.00 0.00 3.00
    destroyMatrix(result);

    // convolução de matrizes
    printf("Resultado da convolução entre a matriz 1 e o kernel recém criado:\n");
    SparseMatrix *kernel = createMatrix(3, 3);
    assignValue(kernel, 0, 0, 1.0);
    assignValue(kernel, 1, 1, 2.0);
    assignValue(kernel, 2, 2, 1.0);
    result = convolution(matrix1, kernel);
    displayDenseMatrix(result);
    printf("\n");
    // resultado esperado:
    // 4.00 0.00 0.00
    // 0.00 8.00 0.00
    // 0.00 0.00 8.00
    destroyMatrix(kernel);
    destroyMatrix(result);

    // salvando a matriz em um arquivo
    saveSparseMatrix(matrix1, "matriz.bin");

    // lendo a matriz do arquivo, exibindo e destruindo em seguida
    SparseMatrix *readMatrix = readSparseMatrix("matriz.bin");
    if (readMatrix != NULL)
    {
        printf("matriz do arquivo:\n");
        displayDenseMatrix(readMatrix);
        printf("\n");
        destroyMatrix(readMatrix);
    }
    // resultado esperado (a propria matriz 1):
    // 1.00 0.00 0.00
    // 0.00 2.00 0.00
    // 0.00 0.00 3.00

    // limpando matrizes
    destroyMatrix(matrix1);
    destroyMatrix(matrix2);

    return 0;
}
