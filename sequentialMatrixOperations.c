/* 
 * File:   
 * Author: Pranab Singha Roy
 *
 */

#include "sequentialMatrixOperations.h"
#include <time.h>
#include <malloc.h>

double * createMatrixAs1DArray(int numRows, int numCols) {
    double * matrix;
    int i;
    matrix = (double *) calloc(numRows * numCols, sizeof (double));
    if (matrix == NULL)
        perror("Memory allocation for matrix");
    return matrix;
}

void display1DArrayAsMatrix(int numRows, int numCols, double * matrix, int showRows) {
    int i, j;
    for (i = 0; i < numRows && i < showRows; i++) {
        for (j = 0; j < numCols; j++) {
            printf("%f\t", *matrix++);
        }
        printf("\n");
    }
}

void displayFeaturesLabelsAsMatrix(int inputNumCols, double * input1DMatrix, int outputNumCols, double * output1DMatrix, int showRows) {
    int i, j;
    //show header
    printf("Inputs:");
    for (j = 0; j < inputNumCols; j++) {
        printf("\t\t");
    }
    printf("|\tOutputs:\n");

    for (i = 0; i < showRows; i++) {
        for (j = 0; j < inputNumCols; j++) {
            printf("%f\t", *input1DMatrix++);
        }
        printf("|\t");
        for (j = 0; j < outputNumCols; j++) {
            printf("%f\t", *output1DMatrix++);
        }
        printf("\n");
    }
}

void initializeRandoms() {
    srand(time(NULL));
}

int RandomEqualINT(int Low, int High) {
    return rand() % (High - Low + 1) + Low;
}

double RandomEqualREAL(double Low, double High) {
    return ((double) rand() / RAND_MAX) * (High - Low) + Low;
}

void shuffleMatrix(int numRows, int numCols, double * matrix) {
    int i, j, temp;
    int rowToSwap;
    srand(time(NULL));
    for (i = 0; i < numRows; i++) {
        rowToSwap = rand() % numRows;
        for (j = 0; j < numCols; j++) {
            temp = *(matrix + i * numCols + j);
            *(matrix + i * numCols + j) = *(matrix + rowToSwap * numCols + j);
            *(matrix + rowToSwap * numCols + j) = temp;
        }
    }
}

double *appendMatricesHorizontally(int numCols1, double *matrix1, int numCols2, double *matrix2, int numRows) {
    int i, j;
    double *matrix;
    matrix = (double*) calloc((numCols1 + numCols2) * numRows, sizeof (double));
    if (matrix == NULL)
        perror("Memory allocation for matrix");

    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols1; j++) {
            *matrix++ = *matrix1++;
        }
        for (j = 0; j < numCols2; j++) {
            *matrix++ = *matrix2++;
        }
    }
    return matrix;
}

void differenceOfMatrices(int numRows, int numCols, double *matrixA, double *matrixB, double *resultMatrix) {
    int i, j;

    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            //printf("%f %f ", *matrixA, *matrixB);
            //*(resultMatrix + numCols * i + j) = *matrixA++ - *matrixB++; 
            *resultMatrix++ = *matrixA++ - *matrixB++;
        }
        //printf("\n");
    }
}

void deleteLastRowFromMatrix(int numRows, int numCols, double *matrix, double *resultMatrix) {
    int i, j;

    for (i = 0; i < numRows - 1; i++) {
        for (j = 0; j < numCols; j++) {
            *resultMatrix++ = *matrix++;
        }
    }
}

void squareOfMatrixComponents(int numRows, int numCols, double *matrix, double *resultMatrix) {
    int i, j;

    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            *resultMatrix++ = *matrix * *matrix++;
        }
    }
}

void productOfMatricesComponents(int numRows, int numCols, double *matrixA, double*matrixB, double *resultMatrix) {
    int i, j;

    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            *resultMatrix++ = *matrixA++ * *matrixB++;
        }
    }
}

void matrixTranspose(int numRows, int numCols, double *matrix, double *transposeMatrix) {
    int i, j;
    for (i = 0; i < numCols; i++) {
        for (j = 0; j < numRows; j++) {
            *transposeMatrix++ = *(matrix + numCols * j + i);
        }
    }
}

double sumOfMatrixComponents(int numRows, int numCols, double *matrix) {
    int i, j;
    float sum = 0.0;
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            sum += *matrix++;
        }
    }
    //printf("Sum: %f\n", sum);
    return sum;
}

void multiplicationOfMatrices(int numRowsA, int numColsA, double *matrixA, int numRowsB, int numColsB, double *matrixB, double *matrixProduct) {
    int i, j, k;
    if (numColsA != numRowsB)
        perror("Rows are not equal for matrix");

    for (i = 0; i < numRowsA; i++) {
        for (j = 0; j < numColsB; j++) {
            for (k = 0; k < numRowsB; k++) {
                //matrixProduct[i][j] += matrix1[i][k] * matrix2[k][i];
                matrixProduct[i * numColsB + j] += matrixA[i * numColsA + k] * matrixB[k * numColsB + j];
            }
        }
    }
}

void scalarProductOfMatrix(int numRows, int numCols, double scalar, double *matrix) {
    int i, j;
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            *matrix = scalar * (*matrix);
            matrix++;
        }
    }
}

void copyDataFromOneMatrixToAnother(int numRows, int numCols, double *srcMatrix, double *desMatrix) {
    int i, j;
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            *desMatrix++ = *srcMatrix++;
        }
    }
}

void additionOfMatrix(int numRows, int numCols, double *matrix1, double *matrix2) {
    int i, j;
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            *matrix1 = *matrix1 + *matrix2;
            matrix1++;
            matrix2++;
        }
    }
}