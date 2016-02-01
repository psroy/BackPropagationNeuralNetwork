/* 
 * File:   sequentialMatrixOperations.h
 * Author: Pranab Singha Roy
 *
 */


#ifndef SEQUENTIALMATRIXOPERATIONS_H
#define SEQUENTIALMATRIXOPERATIONS_H

#include <stdio.h>
#include <stdlib.h>

double * createMatrixAs1DArray(int numRows, int numCols);
void display1DArrayAsMatrix(int numRows, int numCols, double *matrix, int showRows);
void displayFeaturesLabelsAsMatrix(int inputNumCols, double * input1DMatrix, int outputNumCols, double * output1DMatrix, int showRows);
void shuffleMatrix(int numRows, int numCols, double * matrix);
double *appendMatricesHorizontally(int numCols1, double *matrix1, int numCols2, double *matrix2, int numRows);
void scalarProductOfMatrix(int numRows, int numCols, double scalar, double *matrix);
void additionOfMatrix(int numRows, int numCols, double *matrix1, double *matrix2);
void multiplicationOfMatrices(int numRows1, int numCols1, double *matrix1, int numRows2, int numCols2, double *matrix2, double *matrixProduct);
void differenceOfMatrices(int numRows, int numCols, double *matrixA, double *matrixB, double *resultMatrix);
void squareOfMatrixComponents(int numRows, int numCols, double *matrix, double *resultMatrix);
void productOfMatricesComponents(int numRows, int numCols, double *matrixA, double*matrixB, double *resultMatrix);
double sumOfMatrixComponents(int numRows, int numCols, double *matrix);
double matrixTranspose(int numRows, int numCols, double *matrix, double *transposeMatrix);
void deleteLastRowFromMatrix(int numRows, int numCols, double *matrix, double *resultMatrix);

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* SEQUENTIALMATRIXOPERATIONS_H */