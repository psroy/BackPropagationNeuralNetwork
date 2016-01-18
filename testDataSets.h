/* 
 * File:   testDataSets.h
 * Author: Pranab Singha Roy
 *
 */

#ifndef TESTDATASETS_H
#define TESTDATASETS_H

void loadXORData(int *numInputNeurons, int *numOutputNeurons, int *numTrainingPatterns, double **inputsData);
void loadIrisData(int *numInputNeurons, int *numOutputNeurons, int *numTrainingPatterns, double **inputsData);
void loadVowelData(int *numInputNeurons, int *numOutputNeurons, int *numTrainingPatterns, double **inputsData);

#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* TESTDATASETS_H */

