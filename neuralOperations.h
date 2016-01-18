/* 
 * File:   neuralOperations.h
 * Author: Pranab Singha Roy
 *
 */

#ifndef NEURALOPERATIONS_H
#define NEURALOPERATIONS_H

void initializeWeights(int numRows, int numCols, double * matrix);
void appendBiasColumn(int numRows, int numCols, double *matrix, double *appendedMatrix);
void sigmoid(int numRows, int numCols, double *matrix, double *matrixPrime);
void generateTrainingValidationTestData(int numRows, int numFeatures, int numLabels, int trainRows, int testRows, double **data, double **inputTrainData, double **outputTrainData, double **inputTestData, double **outputTestData);
void printChosenActivation(int activationFunction);

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* NEURALOPERATIONS_H */

