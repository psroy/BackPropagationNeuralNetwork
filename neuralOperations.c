#include "neuralOperations.h"
#include "sequentialMatrixOperations.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

double getRand(void) {
    return ((double) rand()) / (double) RAND_MAX;
}

void initializeWeights(int numRows, int numCols, double * matrix) {
    int i, j;
    srand(time(NULL));

    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            *matrix++ = (getRand() - 0.5) / 5;
        }
    }
}

void appendBiasColumn(int numRows, int numCols, double *matrix, double *appendedMatrix) {
    int i, j;

    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            *appendedMatrix++ = *matrix++;
        }
        *appendedMatrix++ = 1.0;
    }
}

void sigmoid(int numRows, int numCols, double *matrix, double *matrixPrime) {
    int i, j;

    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numCols; j++) {
            *matrix = 1.0 / (1.0 + exp(-*matrix)); // return from sigmoid function
            *matrixPrime = *matrix * (1 - *matrix); // return from sigmoid prime function => sigmoid(z)*(1 - sigmoid(z))
            matrix++;
            matrixPrime++;
        }
    }
}

void generateTrainingValidationTestData(int numTrainingPatterns, int numFeatures, int numLabels, int trainingRows, int testRows, double **data, double **inputTrainData, double **outputTrainData, double **inputTestData, double **outputTestData) {

    int crossValidationRows = numTrainingPatterns - trainingRows - testRows;
    int i, j;

    double *loadData;
    double *loadInputTrainData, *loadOutputTrainData;
    double *loadInputTestData, *loadOutputTestData;

    *inputTrainData = createMatrixAs1DArray(trainingRows, numFeatures);
    *outputTrainData = createMatrixAs1DArray(trainingRows, numLabels);

    *inputTestData = createMatrixAs1DArray(testRows, numFeatures);
    *outputTestData = createMatrixAs1DArray(testRows, numLabels);

    loadInputTrainData = *inputTrainData;
    loadOutputTrainData = *outputTrainData;
    loadInputTestData = *inputTestData;
    loadOutputTestData = *outputTestData;
    loadData = *data;

    for (i = 0; i < trainingRows; i++) {
        for (j = 0; j < numFeatures; j++) {
            *loadInputTrainData++ = *loadData++;
        }
        for (j = 0; j < numLabels; j++) {
            *loadOutputTrainData++ = *loadData++;
        }
    }

    for (i = 0; i < testRows; i++) {
        for (j = 0; j < numFeatures; j++) {
            *loadInputTestData++ = *loadData++;
        }
        for (j = 0; j < numLabels; j++) {
            *loadOutputTestData++ = *loadData++;
        }
    }
}

void printChosenActivation(int activationFunction) {
    switch (activationFunction) {
        case 1:
            printf("Chosen Sigmoid Activation function...\n");
            break;
        case 2:
            printf("Chosen Tanh Activation function...\n");
            break;
        default:
            printf("Unknown Activation function...\n");
            break;
    }
}