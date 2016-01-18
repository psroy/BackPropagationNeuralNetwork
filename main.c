/* 
 * File:   main.c
 * Author: Pranab Singha Roy
 *
 */

#include "sequentialMatrixOperations.h"
#include "testDataSets.h"
#include "neuralOperations.h"

#define TRUE    1
#define FALSE   0
#define BIAS    1

/*
 * 
 */
int main(int argc, char** argv) {

    double *inputData;
    inputData = NULL;

    double *trainingFeatures, *trainingLabels;
    double *crossValidationFeatures, *crossValidationLabels;
    double *testFeatures, *testLabels;
    trainingFeatures = trainingLabels = NULL;
    crossValidationFeatures = crossValidationLabels = NULL;
    testFeatures = testLabels = NULL;

    int numInputNeurons, numOutputNeurons, numPatterns;
    int numLayers;
    int *numNeuronsAtLayer;

    double learningRate, momentum;
    int maxEpochs;
    double trainingRatio, crossValidationRatio, testRatio;
    int trainingRows, crossValidationRows, testRows;

    double *outputBiased;
    double *error, *errorSquare;
    double mse = 1.0;
    double mseLimit = 0.00001;
    double *transposeMatrix, *weightMatrixMinusBias;
    double *tempWeightDelta, *tempWeightMomentum;

    typedef struct {
        int numNeurons;
        double *weights;
        double *weightsPrevious;
        double *deltaWeights;
        double *error;
        double *errorDelta;
        double *output;
        double *outputPrime;
        double *outputBiased;
        int activationFunction;
    } LAYER;

    int i, count;
    int showRows;
    char choice;

    printf("******************** Back Propagation Neural Network *********************\n");
    printf("==========================================================================\n");
    printf("Network Initialization and Configurations\n");
    printf("==========================================================================\n");

    do {
        printf("Select your choice from following Test Data Sets:\n");
        printf("Press 1 for XOR Test Data Sets.\n");
        printf("Press 2 for IRIS Test Data Sets.\n");
        printf("Press 3 for VOWEL Test Data Sets.\n");
        choice = getchar();
        switch (choice) {
            case '1':
                printf("Loading Test Data Sets for XOR function...\n");
                loadXORData(&numInputNeurons, &numOutputNeurons, &numPatterns, &inputData);
                showRows = numPatterns;
                printf("Showing Features and Labels from %d number of rows at XOR Data Set\n", showRows);
                display1DArrayAsMatrix(numPatterns, numInputNeurons + numOutputNeurons, inputData, showRows);
                break;
            case '2':
                printf("Loading Test Data Sets from Iris Data...\n");
                loadIrisData(&numInputNeurons, &numOutputNeurons, &numPatterns, &inputData);
                showRows = 10;
                printf("Showing Features and Labels from %d number of rows at IRIS Data Set\n", showRows);
                display1DArrayAsMatrix(numPatterns, numInputNeurons + numOutputNeurons, inputData, showRows);
                break;
            case '3':
                printf("Loading Test Data Sets from VOWEL Data...\n");
                loadVowelData(&numInputNeurons, &numOutputNeurons, &numPatterns, &inputData);
                showRows = 10;
                printf("Showing Features and Labels from %d number of rows at VOWEL Data Set\n", showRows);
                display1DArrayAsMatrix(numPatterns, numInputNeurons + numOutputNeurons, inputData, showRows);
                break;
            default:
                printf("Not a valid choice for Test Data Sets %c\n", choice);
                break;
        }
    } while (choice != '1' && choice != '2' && choice != '3');

    numLayers = 3;
    /*
        do {
            printf("Enter the number of Layers in this Neural Network (including input and output layers): ");
            scanf("%d", &numLayers);
        } while (numLayers < 3);
     */

    /*
        printf("Enter Learning Rate: ");
        scanf("%lf", &learningRate);
        printf("Enter Momentum: ");    
        scanf("%lf", &momentum);
        printf("Enter Max Epochs: ");
        scanf("%d", &maxEpochs);
     */
    learningRate = 0.05;
    momentum = 0.01;
    maxEpochs = 1000;
    printf("Learning Rate: %f, Momentum: %f, Max Epochs: %d\n", learningRate, momentum, maxEpochs);

    trainingRatio = 1.0;
    testRatio = 0.0;

    printf("==========================================================================\n");
    printf("Preparing Learning Data\n");
    printf("==========================================================================\n");

    trainingRows = numPatterns * trainingRatio;
    testRows = numPatterns - trainingRows;

    shuffleMatrix(numPatterns, numInputNeurons + numOutputNeurons, inputData);
    printf("Shuffled Data Matrix:\n");
    showRows = numPatterns;
    display1DArrayAsMatrix(numPatterns, numInputNeurons + numOutputNeurons, inputData, showRows);

    generateTrainingValidationTestData(numPatterns, numInputNeurons, numOutputNeurons, trainingRows, testRows, &inputData, &trainingFeatures, &trainingLabels, &testFeatures, &testLabels);

    printf("Training Data Matrix (selected %d number of rows from total of %d):\n", trainingRows, numPatterns);
    displayFeaturesLabelsAsMatrix(numInputNeurons, trainingFeatures, numOutputNeurons, trainingLabels, trainingRows);

    printf("Test Data Matrix (selected %d number of rows from total of %d):\n", testRows, numPatterns);
    displayFeaturesLabelsAsMatrix(numInputNeurons, testFeatures, numOutputNeurons, testLabels, testRows);

    LAYER *layer = calloc(numLayers, sizeof (LAYER));
    layer[0].numNeurons = numInputNeurons;
    printf("The number of neurons at Layer No. 0: %d\n", layer[0].numNeurons);
    layer[0].output = trainingFeatures;

    for (i = 1; i < numLayers; i++) {
        if (i == numLayers - 1) {
            layer[i].numNeurons = numOutputNeurons;
        } else {
            printf("Enter the number of neurons at Layer No. %d: ", i);
            scanf("%d", &layer[i].numNeurons);
        }
        printf("The number of neurons at Layer No. %d: %d\n", i, layer[i].numNeurons);

        // Weights emerges from layer i - 1 to layer i 
        layer[i - 1].weights = createMatrixAs1DArray(layer[i - 1].numNeurons + 1, layer[i].numNeurons); // last row corresponds to the connection of Bias node
        initializeWeights(layer[i - 1].numNeurons + 1, layer[i].numNeurons, layer[i - 1].weights);
        printf("Weight matrix between layer %d & %d:\n", i - 1, i);
        display1DArrayAsMatrix(layer[i - 1].numNeurons + 1, layer[i].numNeurons, layer[i - 1].weights, layer[i - 1].numNeurons + 1);

        layer[i - 1].weightsPrevious = createMatrixAs1DArray(layer[i - 1].numNeurons + 1, layer[i].numNeurons);

        //layer[i - 1].deltaWeights = createMatrixAs1DArray(layer[i - 1].numNeurons + 1, layer[i].numNeurons);
        //display1DArrayAsMatrix(layer[i - 1].numNeurons + 1, layer[i].numNeurons, layer[i - 1].deltaWeights, layer[i - 1].numNeurons + 1);

        layer[i].output = createMatrixAs1DArray(trainingRows, layer[i].numNeurons);
        layer[i].outputPrime = createMatrixAs1DArray(trainingRows, layer[i].numNeurons);

        layer[i - 1].outputBiased = createMatrixAs1DArray(trainingRows, layer[i - 1].numNeurons + 1); // Biased Matrix has one more column

        layer[i].error = createMatrixAs1DArray(trainingRows, layer[i].numNeurons);
        layer[i].errorDelta = createMatrixAs1DArray(trainingRows, layer[i].numNeurons);

        printf("Enter the Activation Function (1 for Sigmoid, 2 for tanh) at Layer No. %d: ", i);
        scanf("%d", &layer[i].activationFunction);
        printChosenActivation(layer[i].activationFunction);
    }

    count = 0;
    while ((count++ < maxEpochs) && (mse > mseLimit)) {
        /*
                printf("==========================================================================\n");
                printf("Starting Forward Propagation\n");
                printf("==========================================================================\n");
         */

        for (i = 1; i < numLayers; i++) {
            //printf("Incoming Matrix from Layer: %d\n", i - 1);
            //display1DArrayAsMatrix(trainingRows, layer[i - 1].numNeurons, layer[i - 1].output, trainingRows);

            appendBiasColumn(trainingRows, layer[i - 1].numNeurons, layer[i - 1].output, layer[i - 1].outputBiased);
            //printf("Biased Incoming Matrix from Layer: %d\n", i - 1);
            //display1DArrayAsMatrix(trainingRows, layer[i - 1].numNeurons + 1, layer[i - 1].outputBiased, trainingRows);

            multiplicationOfMatrices(trainingRows, layer[i - 1].numNeurons + 1, layer[i - 1].outputBiased, layer[i - 1].numNeurons + 1, layer[i].numNeurons, layer[i - 1].weights, layer[i].output);
            //printf("Output Matrix before activation from Layer: %d\n", i);
            //display1DArrayAsMatrix(trainingRows, layer[i].numNeurons, layer[i].output, trainingRows);
            sigmoid(trainingRows, layer[i].numNeurons, layer[i].output, layer[i].outputPrime);
            /*
                        printf("Output Matrix from Layer: %d\n", i);
                        display1DArrayAsMatrix(trainingRows, layer[i].numNeurons, layer[i].output, trainingRows);
             */

        }

        /*
            trainingRows= 4;
            layer[numLayers - 1].numNeurons = 5;
            error = createMatrixAs1DArray(trainingRows, layer[numLayers - 1].numNeurons);
            initializeWeights(trainingRows, layer[numLayers - 1].numNeurons, error);
         */

        error = createMatrixAs1DArray(trainingRows, layer[numLayers - 1].numNeurons);
        differenceOfMatrices(trainingRows, layer[numLayers - 1].numNeurons, trainingLabels, layer[numLayers - 1].output, error);
        //printf("Error\n");
        //display1DArrayAsMatrix(trainingRows, layer[numLayers - 1].numNeurons, error, trainingRows);

        errorSquare = createMatrixAs1DArray(trainingRows, layer[numLayers - 1].numNeurons);
        squareOfMatrixComponents(trainingRows, layer[numLayers - 1].numNeurons, error, errorSquare);
        //display1DArrayAsMatrix(trainingRows, layer[numLayers - 1].numNeurons, errorSquare, trainingRows);
        //printf("Sum of all components of squared of error matrix: %f\n", sumOfMatrixComponents(trainingRows, layer[numLayers - 1].numNeurons, errorSquare));
        mse = sumOfMatrixComponents(trainingRows, layer[numLayers - 1].numNeurons, errorSquare) / (trainingRows * layer[numLayers - 1].numNeurons);
        //mse = mse;
        //printf("MSE: %f-%f-%d\n", mse, sumOfMatrixComponents(trainingRows, layer[numLayers - 1].numNeurons, errorSquare), (trainingRows * layer[numLayers - 1].numNeurons));
        printf("Iteration: %d, MSE: %f\n", count, mse);

        if (count == maxEpochs - 1 || mse < mseLimit) {
            printf("Input Matrix :\n");
            displayFeaturesLabelsAsMatrix(numInputNeurons, trainingFeatures, numOutputNeurons, trainingLabels, trainingRows);
            printf("Predicted Matrix :\n");
            displayFeaturesLabelsAsMatrix(numInputNeurons, trainingFeatures, numOutputNeurons, layer[2].output, trainingRows);
        }
        /*
                printf("==========================================================================\n");
                printf("Starting Backward Propagation\n");
                printf("==========================================================================\n");
         */

        for (i = numLayers - 1; i >= 1; i--) {
            if (i == numLayers - 1) {
                differenceOfMatrices(trainingRows, layer[i].numNeurons, trainingLabels, layer[i].output, layer[i].error);
            } else {
                transposeMatrix = createMatrixAs1DArray(layer[i + 1].numNeurons, layer[i].numNeurons);
                matrixTranspose(layer[i].numNeurons, layer[i + 1].numNeurons, layer[i].weights, transposeMatrix);
                multiplicationOfMatrices(trainingRows, layer[i + 1].numNeurons, layer[i + 1].error, layer[i + 1].numNeurons, layer[i].numNeurons, transposeMatrix, layer[i].error);
            }
            productOfMatricesComponents(trainingRows, layer[i].numNeurons, layer[i].outputPrime, layer[i].error, layer[i].errorDelta);
            /*
                        printf("Delta error matrix from layer %d :\n", i);
                        display1DArrayAsMatrix(trainingRows, layer[i].numNeurons, layer[i].errorDelta, trainingRows);
             */
        }

        for (i = numLayers - 1; i >= 1; i--) {

            tempWeightDelta = createMatrixAs1DArray(layer[i - 1].numNeurons + 1, layer[i].numNeurons);

            transposeMatrix = createMatrixAs1DArray(layer[i - 1].numNeurons + 1, trainingRows);
            matrixTranspose(trainingRows, layer[i - 1].numNeurons + 1, layer[i - 1].outputBiased, transposeMatrix);

            //computing delta weight matrix
            multiplicationOfMatrices(layer[i - 1].numNeurons + 1, trainingRows, transposeMatrix, trainingRows, layer[i].numNeurons, layer[i].errorDelta, tempWeightDelta);

            /*
                        printf("Weight matrix previous between layer %d & %d:\n", i - 1, i);
                        display1DArrayAsMatrix(layer[i - 1].numNeurons + 1, layer[i].numNeurons, layer[i - 1].weightsPrevious, layer[i - 1].numNeurons + 1);
                        printf("Weight matrix between layer %d & %d:\n", i - 1, i);
                        display1DArrayAsMatrix(layer[i - 1].numNeurons + 1, layer[i].numNeurons, layer[i - 1].weights, layer[i - 1].numNeurons + 1);
             */

            // computing contribution from learning rate
            scalarProductOfMatrix(layer[i - 1].numNeurons + 1, layer[i].numNeurons, learningRate, tempWeightDelta);

            // getting the previous weight component
            tempWeightMomentum = createMatrixAs1DArray(layer[i - 1].numNeurons + 1, layer[i].numNeurons);
            copyDataFromOneMatrixToAnother(layer[i - 1].numNeurons + 1, layer[i].numNeurons, layer[i - 1].weightsPrevious, tempWeightMomentum);
            // computing how much contribution (momentum) from previous weight component should be incorporated
            scalarProductOfMatrix(layer[i - 1].numNeurons + 1, layer[i].numNeurons, momentum, tempWeightMomentum);

            // computing current delta weight matrix by which current weight matrix needs to be updated
            additionOfMatrix(layer[i - 1].numNeurons + 1, layer[i].numNeurons, tempWeightDelta, tempWeightMomentum);

            // copy current weight matrix (t) to previous weight matrix (t-1)
            copyDataFromOneMatrixToAnother(layer[i - 1].numNeurons + 1, layer[i].numNeurons, layer[i - 1].weights, layer[i - 1].weightsPrevious);

            // computing updated weights
            additionOfMatrix(layer[i - 1].numNeurons + 1, layer[i].numNeurons, layer[i - 1].weights, tempWeightDelta);


            //printf("Weight matrix after update between layer %d & %d:\n", i - 1, i);
            //display1DArrayAsMatrix(layer[i - 1].numNeurons + 1, layer[i].numNeurons, layer[i - 1].weights, layer[i - 1].numNeurons + 1);
        }
    }

    return (EXIT_SUCCESS);

}