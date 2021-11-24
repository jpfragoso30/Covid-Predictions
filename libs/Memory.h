#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "Errors.h"

//MATRIX
float **createMatrix(float **matrix, uint8_t rows, uint8_t columns);
float **freeMatrix(float **matrix, uint8_t rows);

//ARRAY
float *createArray(float *array, uint8_t columns);
float *freeArray(float *array);

//MATRIX STRING
char ***createStringMatrix(char ***stringMatrix, uint8_t rows, uint8_t columns);
char ***freeMatrixString(char ***matrixString, uint8_t rows);

//STRING ARRAY
char **createStringArray(char **stringArray, uint8_t columns);
char **freeStringArray(char **stringArray);

//STRING
char *createStrignSpace(char *string, const char *word);

// SETTERS
float **setMoreRows(float **matrix, uint8_t rows);
float *setMoreColumns(float *array, uint8_t columns);
char ***setMoreRowsString(char ***stringMatrix, uint8_t rows, uint8_t columns);
char **setMoreColumnsString(char **stringArray, uint8_t columns);

#endif