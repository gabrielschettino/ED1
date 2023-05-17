#include "node.h"

typedef struct SparseMatrix
{
    int rows;
    int cols;
    Node **rowHeads; // Array of pointers to the head of each row
    Node **colHeads; // Array of pointers to the head of each column
} SparseMatrix;

SparseMatrix *create_matrix(int num_rows, int num_cols);

void destroy_matrix(SparseMatrix *matrix);

void assignValue(SparseMatrix *matrix, int row, int col, float value);

float readValue(const SparseMatrix *matrix, int row, int col);

SparseMatrix *addMatrices(const SparseMatrix *matrix1, const SparseMatrix *matrix2);

SparseMatrix *multiplyByScalar(const SparseMatrix *matrix, float scalar);

SparseMatrix *multiplyMatrices(const SparseMatrix *matrix1, const SparseMatrix *matrix2);

SparseMatrix *pointToPointMultiply(const SparseMatrix *matrix1, const SparseMatrix *matrix2);

SparseMatrix *swapRows(const SparseMatrix *matrix, int row1, int row2);

SparseMatrix *sliceMatrix(const SparseMatrix *matrix, int startRow, int startCol, int endRow, int endCol);

SparseMatrix *transposeMatrix(const SparseMatrix *matrix);

void displaySparseMatrix(const SparseMatrix *matrix);

void displayDenseMatrix(const SparseMatrix *matrix);

SparseMatrix *convolution(const SparseMatrix *matrix, const SparseMatrix *kernel);