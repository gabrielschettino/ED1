#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix.h"

SparseMatrix *create_matrix(int rows, int cols)
{
    SparseMatrix *matrix = (SparseMatrix *)malloc(sizeof(SparseMatrix));
    matrix->rows = rows;
    matrix->cols = cols;

    // Allocate memory for the row and column heads arrays
    matrix->rowHeads = (Node **)malloc(rows * sizeof(Node *));
    matrix->colHeads = (Node **)malloc(cols * sizeof(Node *));

    // Initialize all row and column heads to NULL
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

// Function to destroy a sparse matrix and free the allocated memory
void destroy_matrix(SparseMatrix *matrix)
{
    // Free the memory for each non-zero element
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

    // Free the memory for the row and column heads arrays
    free(matrix->rowHeads);
    free(matrix->colHeads);

    // Free the memory for the sparse matrix structure
    free(matrix);
}

void assignValue(SparseMatrix *matrix, int row, int col, float value)
{
    // Create a new node for the cell
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next_row = NULL;
    newNode->next_col = NULL;

    // Update the row chain
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

    // Update the column chain
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
        printf("Error: Cell (%d, %d) is out of bounds.\n", row, col);
        return 0.0;
    }

    // Traverse the row chain to find the cell
    Node *current = matrix->rowHeads[row];
    while (current != NULL)
    {
        if (current->col == col)
        {
            return current->value;
        }
        current = current->next_row;
    }

    // Cell not found, it is zero
    return 0.0;
}

SparseMatrix *addMatrices(const SparseMatrix *matrix1, const SparseMatrix *matrix2)
{
    // Check if the matrices have compatible dimensions
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols)
    {
        printf("Error: Matrices have incompatible dimensions.\n");
        return NULL;
    }

    // Create a new sparse matrix to store the result
    SparseMatrix *result = create_matrix(matrix1->rows, matrix1->cols);

    // Loop through the cells of matrix1 and add the corresponding cells from matrix2
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
    // Create a new sparse matrix to store the result
    SparseMatrix *result = create_matrix(matrix->rows, matrix->cols);

    // Loop through the cells of the matrix and multiply each value by the scalar
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
    // Check if the matrices have compatible dimensions
    if (matrix1->cols != matrix2->rows)
    {
        printf("Error: Matrices have incompatible dimensions.\n");
        return NULL;
    }

    // Create a new sparse matrix to store the result
    SparseMatrix *result = create_matrix(matrix1->rows, matrix2->cols);

    // Loop through the rows of matrix1
    for (int i = 0; i < matrix1->rows; i++)
    {
        Node *currentRow1 = matrix1->rowHeads[i];

        // Loop through the columns of matrix2
        for (int j = 0; j < matrix2->cols; j++)
        {
            Node *currentCol2 = matrix2->colHeads[j];
            float value = 0.0;

            // Multiply corresponding cells and accumulate the result
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

            // Assign the computed value to the result matrix
            assignValue(result, i, j, value);
        }
    }

    return result;
}

SparseMatrix *pointToPointMultiply(const SparseMatrix *matrix1, const SparseMatrix *matrix2)
{
    // Check if the matrices have the same dimensions
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols)
    {
        printf("Error: Matrices have different dimensions.\n");
        return NULL;
    }

    // Create a new sparse matrix to store the result
    SparseMatrix *result = create_matrix(matrix1->rows, matrix1->cols);

    // Loop through the cells of matrix1
    for (int i = 0; i < matrix1->rows; i++)
    {
        Node *currentRow1 = matrix1->rowHeads[i];
        Node *currentRow2 = matrix2->rowHeads[i];

        // Loop through the cells of the current row
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
    // Create a new sparse matrix with the same dimensions as the input matrix
    SparseMatrix *result = create_matrix(matrix->rows, matrix->cols);

    // Copy the values from the input matrix to the result matrix
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
        printf("Error: Invalid slice coordinates.\n");
        return NULL;
    }

    int numRows = endRow - startRow + 1;
    int numCols = endCol - startCol + 1;

    // Create a new sparse matrix for the sliced submatrix
    SparseMatrix *result = create_matrix(numRows, numCols);

    // Traverse the cells of the original matrix and copy the relevant cells to the result matrix
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
    // Create a new sparse matrix with swapped dimensions
    SparseMatrix *result = create_matrix(matrix->cols, matrix->rows);

    // Traverse the cells of the original matrix and assign them to the transposed matrix
    for (int i = 0; i < matrix->rows; i++)
    {
        Node *current = matrix->rowHeads[i];
        while (current != NULL)
        {
            int row = current->col; // Swap row and column indices
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

    // Create a new matrix for the output
    SparseMatrix *result = create_matrix(matrixRows, matrixCols);

    for (int i = 0; i < matrixRows; i++)
    {
        for (int j = 0; j < matrixCols; j++)
        {
            float sum = 0.0;

            for (int k = 0; k < kernelRows; k++)
            {
                for (int l = 0; l < kernelCols; l++)
                {
                    int row = i - kernelRows / 2 + k;
                    int col = j - kernelCols / 2 + l;

                    float kernelValue = readValue(kernel, k, l);
                    float matrixValue = 0.0;

                    if (row >= 0 && row < matrixRows && col >= 0 && col < matrixCols)
                    {
                        matrixValue = readValue(matrix, row, col);
                    }

                    sum += kernelValue * matrixValue;
                }
            }

            assignValue(result, i, j, sum);
        }
    }

    return result;
}
