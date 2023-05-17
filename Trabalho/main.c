#include <stdio.h>
#include "sparse_matrix.h"

int main()
{
    // Create input matrix
    SparseMatrix *matrix = create_matrix(3, 3);
    assignValue(matrix, 0, 0, 1.0);
    assignValue(matrix, 1, 1, 1.0);
    assignValue(matrix, 2, 2, 1.0);
    assignValue(matrix, 0, 1, -1.0);
    assignValue(matrix, 0, 2, -1.0);
    assignValue(matrix, 1, 0, -1.0);
    assignValue(matrix, 1, 2, -1.0);
    assignValue(matrix, 2, 0, -1.0);
    assignValue(matrix, 2, 1, -1.0);

    // Create kernel
    SparseMatrix *kernel = create_matrix(3, 3);
    assignValue(kernel, 0, 0, 1.0);
    assignValue(kernel, 1, 1, 1.0);
    assignValue(kernel, 2, 2, 1.0);
    assignValue(kernel, 0, 1, -1.0);
    assignValue(kernel, 0, 2, -1.0);
    assignValue(kernel, 1, 0, -1.0);
    assignValue(kernel, 1, 2, -1.0);
    assignValue(kernel, 2, 0, -1.0);
    assignValue(kernel, 2, 1, -1.0);

    displayDenseMatrix(matrix);
    displayDenseMatrix(kernel);

    // Perform convolution
    SparseMatrix *result = convolution(matrix, kernel);

    // Display the result
    printf("Resulting Matrix:\n");
    displayDenseMatrix(result);

    // Free the memory
    destroy_matrix(matrix);
    destroy_matrix(kernel);
    destroy_matrix(result);

    return 0;
}
