#include "../libs/Memory.h"

static ERRORS_CODE checkColumns(float *array);
static ERRORS_CODE checkRows(float **matrix);
static ERRORS_CODE checkRowsString(char ***stringMatrix);
static ERRORS_CODE checkColumnsString(char **stringArray);
static ERRORS_CODE checkString(char *string);

float **createMatrix(float **matrix, uint8_t rows, uint8_t columns)
{

    matrix = (float **)calloc(rows, sizeof(float *));
    checkRows(matrix);

    for (uint8_t i = 0; i < rows; i++)
    {

        matrix[i] = (float *)calloc(columns, sizeof(float));
        checkColumns(matrix[i]);
    }

    return matrix;
}

float **freeMatrix(float **matrix, uint8_t rows)
{

    for (uint8_t i = 0; i <= rows; i++)
    {
        free(matrix[i]);
        matrix[i] = NULL;
    }

    free(matrix);
    matrix = NULL;

    return matrix;
}

float *createArray(float *array, uint8_t columns)
{

    array = (float *)calloc(columns, sizeof(float));
    checkColumns(array);

    return array;
}

float *freeArray(float *array)
{

    free(array);
    array = NULL;

    return array;
}

char ***createStringMatrix(char ***stringMatrix, uint8_t rows, uint8_t columns)
{

    stringMatrix = calloc(rows, sizeof(char **));
    checkRowsString(stringMatrix);

    for (uint8_t i = 0; i < rows; i++)
    {
        stringMatrix[i] = createStringArray(stringMatrix[i], columns);
        checkColumnsString(stringMatrix[i]);
    }

    return stringMatrix;
}

char **createStringArray(char **stringArray, uint8_t columns)
{

    stringArray = calloc(columns, sizeof(char *));
    checkColumnsString(stringArray);

    return stringArray;
}

char ***freeMatrixString(char ***matrixString, uint8_t rows)
{

    for (uint8_t i = 0; i < rows; i++)
    {

        free(matrixString[i]);
        matrixString[i] = NULL;
    }

    free(matrixString);
    matrixString = NULL;

    return matrixString;
}

char **freeStringArray(char **stringArray)
{

    free(stringArray);
    stringArray = NULL;

    return stringArray;
}

char *createStrignSpace(char *string, const char *word)
{

    string = calloc(strlen(word), sizeof(char));
    checkString(string);

    return string;
}

// Setters
float **setMoreRows(float **matrix, uint8_t rows)
{

    matrix = (float **)realloc(matrix, sizeof(float *) * (rows * 2));
    checkRows(matrix);

    return matrix;
}

char ***setMoreRowsString(char ***stringMatrix, uint8_t rows, uint8_t columns)
{

    stringMatrix = realloc(stringMatrix, sizeof(char *) * (columns * 2));
    checkRowsString(stringMatrix);

    for (uint8_t i = rows; i < rows * 2; i++)
    {

        stringMatrix[i] = createStringArray(stringMatrix[i], columns);
        checkColumnsString(stringMatrix[i]);
    }

    return stringMatrix;
}

float *setMoreColumns(float *array, uint8_t columns)
{

    array = realloc(array, sizeof(float) * (columns * 2));
    checkColumns(array);

    return array;
}

char **setMoreColumnsString(char **stringArray, uint8_t columns)
{

    stringArray = realloc(stringArray, sizeof(char *) * (columns * 2));
    checkColumnsString(stringArray);

    return stringArray;
}

//Statics

static ERRORS_CODE checkRows(float **matrix)
{

    if (!matrix)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, MEM_ERROR);
        exit(MEM_ERROR);
    }

    return ERROR_OK;
}

static ERRORS_CODE checkRowsString(char ***stringMatrix)
{

    if (!stringMatrix)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, MEM_ERROR);
        exit(MEM_ERROR);
    }

    return ERROR_OK;
}

static ERRORS_CODE checkColumns(float *array)
{

    if (!array)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, MEM_ERROR);
        exit(MEM_ERROR);
    }

    return ERROR_OK;
}

static ERRORS_CODE checkColumnsString(char **stringArray)
{

    if (!stringArray)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, MEM_ERROR);
        exit(MEM_ERROR);
    }

    return ERROR_OK;
}

static ERRORS_CODE checkString(char *string)
{

    if (!string)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, MEM_ERROR);
        exit(MEM_ERROR);
    }

    return ERROR_OK;
}