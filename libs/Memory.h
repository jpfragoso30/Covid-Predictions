#ifndef MEMORY_H
#define MEMORY_H

#include "Libs.h"


//CONSTRUCTORS
char*** createMatrixString(char*** matrixString, size_t rows, size_t columns);
char** createListString(char** listStirng, size_t columns);


//FREES
char*** freeMatrixString(char*** matrixString, size_t rows);
char** freeListString(char** listStirng);


//SETTERS
char*** setMoreRows(char*** matrixString, size_t rows, size_t columns);
char** setMoreColumns(char** listString, size_t columns);
char* setSizeColumn(char* columnData, char* word);



#endif 
