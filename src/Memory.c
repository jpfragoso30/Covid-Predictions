#include "../libs/Memory.h"

static ERROR_CODE checkMatrixStringCR(char ***matrixString);
static ERROR_CODE checkListStringCR(char **listStirng);
static ERROR_CODE checkColumnData(char* columnData);




char*** createMatrixString(char*** matrixString, size_t rows, size_t columns){
    
    matrixString = calloc(rows, sizeof(char**));
    checkMatrixStringCR(matrixString);

    for(size_t i = 0; i < columns; i++){
        matrixString[i] = calloc(columns, sizeof(matrixString[i]));
        checkListStringCR(matrixString[i]);
    }

   return matrixString;
}




char** createListString(char** listStirng, size_t columns){
    
    listStirng = calloc(columns, sizeof(char*));
    checkListStringCR(listStirng);


    return listStirng;
} 




char*** freeMatrixString(char*** matrixString, size_t rows){
    
    for(int i = 0; i < rows; i++){

        free(matrixString[i]);
        matrixString[i] = NULL;
    }

    free(matrixString);
    matrixString = NULL;
    
    return matrixString;
}




char** freeListString(char** listStirng){
    
    free(listStirng);
    listStirng = NULL;

    return NULL;
}




char*** setMoreRows(char*** matrixString, size_t rows, size_t columns){

	char*** tempPtr;
	tempPtr = realloc(matrixString, sizeof(matrixString) * rows * 2);
    checkMatrixStringCR(tempPtr);

	for(size_t i = 0; i < rows * 2; i++){
		tempPtr[rows + i] = createListString(tempPtr[rows + i], columns);
		checkListStringCR(tempPtr[rows + i]);
	}

	matrixString = tempPtr;

    return matrixString;
    
}




char** setMoreColumns(char** listString, size_t columns){
    
    listString = realloc(listString, sizeof(char*) * columns * 2);
    checkListStringCR(listString);

    return listString;
}


char* setSizeColumn(char* columnData, char* word){
    
    columnData = realloc(columnData, sizeof(char) * strlen(word));
    checkColumnData(columnData);
    
    return columnData;
}




static ERROR_CODE checkMatrixStringCR(char ***matrixString){

    if(matrixString == NULL){
        perror("ERROR::");
        exit(MEM_ERROR);
    }

    return ERROR_OK;
}




static ERROR_CODE checkListStringCR(char **listStirng){

    if(listStirng == NULL){
        perror("ERROR::");
        exit(MEM_ERROR);
    }
    return ERROR_OK;
}



static ERROR_CODE checkColumnData(char* columnData){
    
    if(columnData == NULL){
        perror("ERROR::");
        exit(MEM_ERROR);
    }
    return ERROR_OK;
}
