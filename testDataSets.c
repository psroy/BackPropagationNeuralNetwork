/* 
 * File:   
 * Author: Pranab Singha Roy
 *
 */

#include "testDataSets.h"
#include "sequentialMatrixOperations.h"

void loadXORData(int *numInputNeurons, int *numOutputNeurons, int *numTrainingPatterns, double **data) {

    double *loadData;
    int i, j;

    *numInputNeurons = 2;
    *numOutputNeurons = 1;
    *numTrainingPatterns = 4;

    //Normalization
    double maxVal[*numInputNeurons + *numOutputNeurons];
    double minVal[*numInputNeurons + *numOutputNeurons];
    double diff[*numInputNeurons + *numOutputNeurons];

    *data = createMatrixAs1DArray(*numTrainingPatterns, *numInputNeurons + *numOutputNeurons);

    loadData = *data;

    //Load Normalized XOR data in the range -1.0 to 1.0
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

    loadData = *data;
    minVal[0] = maxVal[0] = *loadData++; //input
    minVal[1] = maxVal[1] = *loadData++;
    minVal[2] = maxVal[2] = *loadData++;
    minVal[3] = maxVal[3] = *loadData; //output
    loadData = *data;

    for (i = 0; i < *numTrainingPatterns; i++) {
        for (j = 0; j < *numInputNeurons + *numOutputNeurons; j++) {
            if (maxVal[j] < *loadData) {
                maxVal[j] = *loadData;
            }
            if (minVal[j] > *loadData) {
                minVal[j] = *loadData;
            }
            loadData++;
        }
    }

    for (j = 0; j < *numInputNeurons + *numOutputNeurons; j++) {
        printf("Max: %f Min:%f\n", maxVal[j], minVal[j]);
        diff[j] = maxVal[j] - minVal[j];
    }

    loadData = *data;
    for (i = 0; i < *numTrainingPatterns; ++i) {
        for (j = 0; j < *numInputNeurons + *numOutputNeurons; ++j) {
            //Normalization
            *loadData = ((*loadData - minVal[j]) / diff[j]);
            loadData++;
        }
    }

    /*
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
     */

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

    //Normalization
    double maxVal[*numInputNeurons + *numOutputNeurons];
    double minVal[*numInputNeurons + *numOutputNeurons];
    double diff[*numInputNeurons + *numOutputNeurons];

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

    loadData = *data;
    minVal[0] = maxVal[0] = *loadData++; //input
    minVal[1] = maxVal[1] = *loadData++;
    minVal[2] = maxVal[2] = *loadData++;
    minVal[3] = maxVal[3] = *loadData; //output
    loadData = *data;

    for (i = 0; i < *numTrainingPatterns; i++) {
        for (j = 0; j < *numInputNeurons + *numOutputNeurons; j++) {
            if (maxVal[j] < *loadData) {
                maxVal[j] = *loadData;
            }
            if (minVal[j] > *loadData) {
                minVal[j] = *loadData;
            }
            loadData++;
        }
    }

    for (j = 0; j < *numInputNeurons + *numOutputNeurons; j++) {
        printf("Max: %f Min:%f\n", maxVal[j], minVal[j]);
        diff[j] = maxVal[j] - minVal[j];
    }

    loadData = *data;
    for (i = 0; i < *numTrainingPatterns; ++i) {
        for (j = 0; j < *numInputNeurons + *numOutputNeurons; ++j) {
            //Normalization
            *loadData = ((*loadData - minVal[j]) / diff[j]);
            loadData++;
        }
    }

    printf("Exit loading Vowel Data...\n");

}

void loadIrisData(int *numInputNeurons, int *numOutputNeurons, int *numTrainingPatterns, double **data) {

    FILE *input = NULL;
    int i, j;
    double *loadData;

    *numInputNeurons = 4;
    *numOutputNeurons = 1;
    *numTrainingPatterns = 150;

    *data = createMatrixAs1DArray(*numTrainingPatterns, *numInputNeurons + *numOutputNeurons);

    loadData = *data;

    input = fopen("iris.data", "r");

    float val = 0.0;
    char ch;
    char name[50];

    //Normalization
    double maxVal[*numInputNeurons];
    double minVal[*numInputNeurons];
    double diff[*numInputNeurons];

    for (i = 0; i < *numTrainingPatterns; i++) {

        for (j = 0; j < *numInputNeurons; j++) {
            fscanf(input, "%f", &val);
            *loadData++ = val;
            //Normalization
            //*loadData++ = ((val - minVal) / (maxVal - minVal))*(0.99 - 0.01) + 0.01;
            fscanf(input, "%c", &ch); // remove comma character
        }

        fscanf(input, "%s", name);
        //printf("%s\n", name);
        if (strcmp(name, "Iris-setosa") == 0)
            *loadData++ = 0.0;
        else if (strcmp(name, "Iris-versicolor") == 0)
            *loadData++ = 0.5;
        else if (strcmp(name, "Iris-virginica") == 0)
            *loadData++ = 1.0;
        /*
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
         */
    }

    fclose(input);

    loadData = *data;
    minVal[0] = maxVal[0] = *loadData++; //input
    minVal[1] = maxVal[1] = *loadData++;
    minVal[2] = maxVal[2] = *loadData++;
    minVal[3] = maxVal[3] = *loadData;

    loadData = *data;

    for (i = 0; i < *numTrainingPatterns; i++) {
        for (j = 0; j < *numInputNeurons; j++) {
            if (maxVal[j] < *loadData) {
                maxVal[j] = *loadData;
            }
            if (minVal[j] > *loadData) {
                minVal[j] = *loadData;
            }
            loadData++;
        }

        for (j = 0; j < *numOutputNeurons; j++) {
            loadData++;
        }
    }

    for (j = 0; j < *numInputNeurons; j++) {
        printf("Max: %f Min:%f\n", maxVal[j], minVal[j]);
        diff[j] = maxVal[j] - minVal[j];
    }

    loadData = *data;
    for (i = 0; i < *numTrainingPatterns; ++i) {
        for (j = 0; j < *numInputNeurons; ++j) {
            //Normalization
            *loadData = ((*loadData - minVal[j]) / diff[j]);
            loadData++;
        }
        for (j = 0; j < *numOutputNeurons; ++j) {
            loadData++;
        }
    }

    printf("Exit loading Iris Data...\n");
}