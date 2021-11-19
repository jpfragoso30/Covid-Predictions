#ifndef FILES_H
#define FILES_H

#include "Libs.h"
#include "Memory.h"


#define READ "r"
#define WRITE "w"
#define READ_AND_WRITE "r+"
#define APPENDING "a"
#define READ_AND_APPENDING "a+"


//FUNCIONES PRINCIPALES

FILE* newFile(char* nameFile, char* mode);
FILE* closeFile(FILE* fileToClose);
char*** readCsvFile(FILE* csvFile, char*** matrixData, size_t* rows, size_t* rowsWithData, size_t* columns, size_t* columnsWithData);
FILE* writeCsvFile(FILE* csvFile, char*** data, size_t rowsWithData, size_t columnsWithData);
void formatString(char* string, char charToClean);
FILE* createConfigFile(FILE* configFile);
FILE* editConfigFile(FILE* configFile, int width, int height, int color, int menuType);


#endif
