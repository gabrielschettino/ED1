#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix.h"

SparseMatrix *createMatrix(int rows, int cols)
{
    SparseMatrix *matrix = (SparseMatrix *)malloc(sizeof(SparseMatrix));
    matrix->rows = rows;
    matrix->cols = cols;

    matrix->rowHeads = (Node **)malloc(rows * sizeof(Node *));
    matrix->colHeads = (Node **)malloc(cols * sizeof(Node *));

    for (int i = 0; i < rows; i++)
    {
        matrix->rowHeads[i] = NULL;
    }
    for (int j = 0; j < cols; j++)
    {
        matrix->colHeads[j] = NULL;
    }

    return matrix;
}

void destroyMatrix(SparseMatrix *matrix)
{
    // limpando cada elemento nao igual a zero
    for (int i = 0; i < matrix->rows; i++)
    {
        Node *current = matrix->rowHeads[i];
        while (current != NULL)
        {
            Node *temp = current;
            current = current->next_row;
            free(temp);
        }
    }

    free(matrix->rowHeads);
    free(matrix->colHeads);

    free(matrix);
}

void assignValue(SparseMatrix *matrix, int row, int col, float value)
{
    // criando novo node para o valor
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next_row = NULL;
    newNode->next_col = NULL;

    // atualizando a cadeia de linhas
    if (matrix->rowHeads[row] == NULL)
    {
        matrix->rowHeads[row] = newNode;
    }
    else
    {
        Node *current = matrix->rowHeads[row];
        while (current->next_row != NULL)
        {
            current = current->next_row;
        }
        current->next_row = newNode;
    }

    // atualizando colunas
    if (matrix->colHeads[col] == NULL)
    {
        matrix->colHeads[col] = newNode;
    }
    else
    {
        Node *current = matrix->colHeads[col];
        while (current->next_col != NULL)
        {
            current = current->next_col;
        }
        current->next_col = newNode;
    }
}

float readValue(const SparseMatrix *matrix, int row, int col)
{
    // Check if the cell is within the matrix bounds
    if (row < 0 || row >= matrix->rows || col < 0 || col >= matrix->cols)
    {
        printf("A celula esta fora dos limites da matriz\n");
        return 0;
    }

    Node *current = matrix->rowHeads[row];
    while (current != NULL)
    {
        if (current->col == col)
        {
            return current->value;
        }
        current = current->next_row;
    }

    // celula nao encontrada, entao o valor vai ser 0
    return 0;
}

SparseMatrix *addMatrices(const SparseMatrix *matrix1, const SparseMatrix *matrix2)
{
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols)
    {
        printf("As matrizes nao tem dimensões iguais\n");
        return NULL;
    }

    SparseMatrix *result = createMatrix(matrix1->rows, matrix1->cols);

    for (int i = 0; i < matrix1->rows; i++)
    {
        Node *current = matrix1->rowHeads[i];
        while (current != NULL)
        {
            int row = current->row;
            int col = current->col;
            float value = current->value + readValue(matrix2, row, col);
            assignValue(result, row, col, value);
            current = current->next_row;
        }
    }

    return result;
}

SparseMatrix *multiplyByScalar(const SparseMatrix *matrix, float scalar)
{
    SparseMatrix *result = createMatrix(matrix->rows, matrix->cols);

    // loop pelos elementos da matriz
    for (int i = 0; i < matrix->rows; i++)
    {
        Node *current = matrix->rowHeads[i];
        while (current != NULL)
        {
            int row = current->row;
            int col = current->col;
            float value = current->value * scalar;
            assignValue(result, row, col, value);
            current = current->next_row;
        }
    }

    return result;
}

SparseMatrix *multiplyMatrices(const SparseMatrix *matrix1, const SparseMatrix *matrix2)
{
    // checando se podem ser multiplicadas
    if (matrix1->cols != matrix2->rows)
    {
        printf("As matrizes nao podem ser multiplicadas!\n");
        return NULL;
    }

    SparseMatrix *result = createMatrix(matrix1->rows, matrix2->cols);

    // loop pelas colunas
    for (int i = 0; i < matrix1->rows; i++)
    {
        Node *currentRow1 = matrix1->rowHeads[i];

        // loop pelas linhas da segunda
        for (int j = 0; j < matrix2->cols; j++)
        {
            Node *currentCol2 = matrix2->colHeads[j];
            float value = 0;

            // multiplicacao do valor linha x coluna
            while (currentRow1 != NULL && currentCol2 != NULL)
            {
                if (currentRow1->col == currentCol2->row)
                {
                    value += currentRow1->value * currentCol2->value;
                    currentRow1 = currentRow1->next_row;
                    currentCol2 = currentCol2->next_col;
                }
                else if (currentRow1->col < currentCol2->row)
                {
                    currentRow1 = currentRow1->next_row;
                }
                else
                {
                    currentCol2 = currentCol2->next_col;
                }
            }

            // setando a celula na matriz resultante
            assignValue(result, i, j, value);
        }
    }

    return result;
}

SparseMatrix *pointToPointMultiply(const SparseMatrix *matrix1, const SparseMatrix *matrix2)
{
    // checando se as matrizes tem dimensões compatíveis
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols)
    {
        printf("matrizes tem dimensões diferentes.\n");
        return NULL;
    }

    SparseMatrix *result = createMatrix(matrix1->rows, matrix1->cols);

    // loop pelas linhas da matriz1
    for (int i = 0; i < matrix1->rows; i++)
    {
        Node *currentRow1 = matrix1->rowHeads[i];
        Node *currentRow2 = matrix2->rowHeads[i];

        // percorrendo as células da linha atual
        while (currentRow1 != NULL && currentRow2 != NULL)
        {
            int col1 = currentRow1->col;
            int col2 = currentRow2->col;

            if (col1 == col2)
            {
                float value = currentRow1->value * currentRow2->value;
                assignValue(result, i, col1, value);
                currentRow1 = currentRow1->next_row;
                currentRow2 = currentRow2->next_row;
            }
            else if (col1 < col2)
            {
                currentRow1 = currentRow1->next_row;
            }
            else
            {
                currentRow2 = currentRow2->next_row;
            }
        }
    }

    return result;
}

SparseMatrix *swapRows(const SparseMatrix *matrix, int row1, int row2)
{
    SparseMatrix *result = createMatrix(matrix->rows, matrix->cols);

    // copia os valores da matriz original para a matriz resultante
    for (int i = 0; i < matrix->rows; i++)
    {
        Node *current = matrix->rowHeads[i];
        while (current != NULL)
        {
            int row = current->row;
            int col = current->col;
            float value = current->value;
            if (row == row1)
            {
                row = row2;
            }
            else if (row == row2)
            {
                row = row1;
            }
            assignValue(result, row, col, value);
            current = current->next_row;
        }
    }

    return result;
}

SparseMatrix *sliceMatrix(const SparseMatrix *matrix, int startRow, int startCol, int endRow, int endCol)
{
    if (startRow < 0 || startCol < 0 || endRow >= matrix->rows || endCol >= matrix->cols || startRow > endRow || startCol > endCol)
    {
        printf("Coordenadas de slice inválidas.\n");
        return NULL;
    }

    int numRows = endRow - startRow + 1;
    int numCols = endCol - startCol + 1;

    SparseMatrix *result = createMatrix(numRows, numCols);

    // copia as células relevantes da matriz original para a matriz resultante
    for (int i = startRow; i <= endRow; i++)
    {
        Node *current = matrix->rowHeads[i];
        while (current != NULL)
        {
            int row = current->row;
            int col = current->col;
            float value = current->value;
            if (row >= startRow && row <= endRow && col >= startCol && col <= endCol)
            {
                int slicedRow = row - startRow;
                int slicedCol = col - startCol;
                assignValue(result, slicedRow, slicedCol, value);
            }
            current = current->next_row;
        }
    }

    return result;
}

SparseMatrix *transposeMatrix(const SparseMatrix *matrix)
{
    SparseMatrix *result = createMatrix(matrix->cols, matrix->rows);

    for (int i = 0; i < matrix->rows; i++)
    {
        Node *current = matrix->rowHeads[i];
        while (current != NULL)
        {
            int row = current->col; // trocando os indices
            int col = current->row;
            float value = current->value;
            assignValue(result, row, col, value);
            current = current->next_row;
        }
    }

    return result;
}

void displaySparseMatrix(const SparseMatrix *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        Node *current = matrix->rowHeads[i];
        while (current != NULL)
        {
            int row = i;
            int col = current->col;
            float value = current->value;
            printf("(%d, %d) -> %.2f\n", row, col, value);
            current = current->next_row;
        }
    }
}

void displayDenseMatrix(const SparseMatrix *matrix)
{
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            float value = readValue(matrix, i, j);
            printf("%.2f ", value);
        }
        printf("\n");
    }
}

SparseMatrix *convolution(const SparseMatrix *matrix, const SparseMatrix *kernel)
{
    int matrixRows = matrix->rows;
    int matrixCols = matrix->cols;
    int kernelRows = kernel->rows;
    int kernelCols = kernel->cols;

    SparseMatrix *result = createMatrix(matrixRows, matrixCols);

    for (int i = 0; i < matrixRows; i++)
    {
        for (int j = 0; j < matrixCols; j++)
        {
            float sum = 0;

            for (int k = 0; k < kernelRows; k++)
            {
                for (int l = 0; l < kernelCols; l++)
                {
                    int row = i - kernelRows / 2 + k;
                    int col = j - kernelCols / 2 + l;

                    float kernelValue = readValue(kernel, k, l);
                    float matrixValue = 0;

                    if (row >= 0 && row < matrixRows && col >= 0 && col < matrixCols)
                    {
                        matrixValue = readValue(matrix, row, col);
                    }

                    // stackando a soma pra cada termo do kernel
                    sum += kernelValue * matrixValue;
                }
            }

            assignValue(result, i, j, sum);
        }
    }

    return result;
}

void saveSparseMatrix(const SparseMatrix *matrix, const char *filename)
{
    FILE *file = fopen(filename, "wb");

    if (file == NULL)
    {
        printf("Erro ao abrir arquivo \n");
        return;
    }

    int rows = matrix->rows;
    int cols = matrix->cols;

    fwrite(&rows, sizeof(int), 1, file);
    fwrite(&cols, sizeof(int), 1, file);

    // escrevendo os valores nao nulos
    for (int i = 0; i < rows; i++)
    {
        Node *node = matrix->rowHeads[i];

        while (node != NULL)
        {
            int row = node->row;
            int col = node->col;
            float value = node->value;

            fwrite(&row, sizeof(int), 1, file);
            fwrite(&col, sizeof(int), 1, file);
            fwrite(&value, sizeof(float), 1, file);

            node = node->next_col;
        }
    }

    fclose(file);
}

SparseMatrix *readSparseMatrix(const char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        printf("Erro ao abrir arquivo \n");
        return NULL;
    }

    int rows, cols;

    // lendo as dimensões da matriz
    fread(&rows, sizeof(int), 1, file);
    fread(&cols, sizeof(int), 1, file);

    SparseMatrix *matrix = createMatrix(rows, cols);

    int row, col;
    float value;

    // Lendo os valores nao nulos, na forma esparsa
    while (fread(&row, sizeof(int), 1, file) == 1 &&
           fread(&col, sizeof(int), 1, file) == 1 &&
           fread(&value, sizeof(float), 1, file) == 1)
    {
        assignValue(matrix, row, col, value);
    }

    fclose(file);

    return matrix;
}
