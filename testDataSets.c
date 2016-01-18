/* 
 * File:   
 * Author: Pranab Singha Roy
 *
 */

#include "testDataSets.h"
#include "sequentialMatrixOperations.h"

void loadXORData(int *numInputNeurons, int *numOutputNeurons, int *numTrainingPatterns, double **data) {

    double *loadData;

    *numInputNeurons = 2;
    *numOutputNeurons = 1;
    *numTrainingPatterns = 4;

    *data = createMatrixAs1DArray(*numTrainingPatterns, *numInputNeurons + *numOutputNeurons);

    loadData = *data;

    /*
        //Load Normalized XOR data in the range -1.0 to 1.0 for tanh
     *loadData++ = 1.0;
     *loadData++ = -1.0;
     *loadData++ = 1.0;

     *loadData++ = -1.0;
     *loadData++ = 1.0;
     *loadData++ = 1.0;

     *loadData++ = 1.0;
     *loadData++ = 1.0;
     *loadData++ = -1.0;

     *loadData++ = -1.0;
     *loadData++ = -1.0;
     *loadData++ = -1.0;
     */

    *loadData++ = 1.0;
    *loadData++ = 0.0;
    *loadData++ = 1.0;

    *loadData++ = 0.0;
    *loadData++ = 1.0;
    *loadData++ = 1.0;

    *loadData++ = 1.0;
    *loadData++ = 1.0;
    *loadData++ = 0.0;

    *loadData++ = 0.0;
    *loadData++ = 0.0;
    *loadData++ = 0.0;

    printf("Finished loading XOR Data...\n");
}

void loadVowelData(int *numInputNeurons, int *numOutputNeurons, int *numTrainingPatterns, double **data) {

    FILE *input = NULL;
    int i, j, k = 0;
    double *loadData;
    int currentRowLabel = 0;

    *numInputNeurons = 3;
    *numOutputNeurons = 1;
    *numTrainingPatterns = 871;

    *data = createMatrixAs1DArray(*numTrainingPatterns, *numInputNeurons + *numOutputNeurons);

    loadData = *data;

    input = fopen("vowel.dat", "r"); // Put check if File exist in the current directory

    for (i = 0; i < *numTrainingPatterns; i++) {
        //output
        fscanf(input, "%d", &currentRowLabel);

        //inputs
        for (j = 0; j < *numInputNeurons; j++) {
            fscanf(input, "%d", &k);
            *loadData++ = (double) k;
        }

        *loadData++ = (double) currentRowLabel;
    }

    fclose(input);

    printf("Exit loading Vowel Data...\n");

}

void loadIrisData(int *numInputNeurons, int *numOutputNeurons, int *numTrainingPatterns, double **data) {

    FILE *input = NULL;
    int i, j;
    double *loadData;

    *numInputNeurons = 4;
    *numOutputNeurons = 3;
    *numTrainingPatterns = 150;

    *data = createMatrixAs1DArray(*numTrainingPatterns, *numInputNeurons + *numOutputNeurons);

    loadData = *data;

    input = fopen("iris.data", "r");

    float val = 0.0;
    char ch;
    char name[50];

    for (i = 0; i < *numTrainingPatterns; ++i) {

        for (j = 0; j < *numInputNeurons; ++j) {
            fscanf(input, "%f", &val);
            *loadData++ = val;
            fscanf(input, "%c", &ch); // remove comma character
            //printf("%f\t", trainingInputs[i][j]);
        }
        //printf("\n");
        //trainingInputs[i][j] = 1.0;

        fscanf(input, "%s", name);
        //printf("%s\n", name);
        if (strcmp(name, "Iris-setosa") == 0)
            *loadData++ = 1.0;
        else
            *loadData++ = 0.0;
        if (strcmp(name, "Iris-versicolor") == 0)
            *loadData++ = 1.0;
        else
            *loadData++ = 0.0;
        if (strcmp(name, "Iris-virginica") == 0)
            *loadData++ = 1.0;
        else
            *loadData++ = 0.0;
    }

    fclose(input);
    printf("Exit loading Iris Data...\n");
}