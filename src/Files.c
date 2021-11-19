#include "../libs/Files.h"
static int searchEmptyString(char* word);

static ERROR_CODE fileExist(FILE* fileToCheck);

//FUNCIONES PRINCIPALES

FILE* newFile(char* nameFile, char* mode){

    FILE* file = NULL;

    file = fopen(nameFile, mode);
    
    fileExist(file);

    return file;
}



FILE* closeFile(FILE* fileToClose){
    fclose(fileToClose);
    fileToClose = NULL;

    return fileToClose;
}




char*** readCsvFile(FILE* csvFile, char*** matrixData, size_t* rows, size_t* rowsWithData, size_t* columns, size_t* columnsWithData){
    
    size_t fileRows = 0, fileColumns = 0;
    char buffer[BUFSIZ];
    char *value;

    while(fgets(buffer, BUFSIZ, csvFile) != NULL){
        
        fileColumns = 0;
        value = strtok(buffer, ",");
        
        while(value != NULL){

            if(fileColumns == *columns){
                matrixData[fileRows] = setMoreColumns(matrixData[fileRows], *columns);
                *columns *= 2;
            }

            formatString(value, 9);
            if(searchEmptyString(value))
                value = "EMPTY";

            matrixData[fileRows][fileColumns] = setSizeColumn(matrixData[fileRows][fileColumns], value);
            matrixData[fileRows][fileColumns] = strdup(value);



            value = strtok(NULL, ",");

            fileColumns++;
        }

	    formatString(matrixData[fileRows][fileColumns - 1], 13);
	    formatString(matrixData[fileRows][fileColumns - 1], 10);
        fileRows++; 

        if(fileRows == *rows){
            matrixData = setMoreRows(matrixData, *rows, *columns);
            *rows *= 2;
        }
        


    }
    
    *columnsWithData = fileColumns;   
    *rowsWithData = fileRows;
    return matrixData;
}




FILE* writeCsvFile(FILE* csvFile, char*** data, size_t rowsWithData, size_t columnsWithData){
    
    for(size_t i = 0; i < rowsWithData; i++){
        
        for(size_t j = 0; j < columnsWithData; j++){

			if(j == columnsWithData - 1)
				fprintf(csvFile, "%s", data[i][j]);
			else
                fprintf(csvFile, "%s,", data[i][j]);
        }

            fprintf(csvFile, "\n");
    }
    
    return csvFile;
}



FILE* createConfigFile(FILE* configFile){

    struct stat attrib;
    char date[10];   
    
    stat("config.ini", &attrib);
    strftime(date, 10, "%d-%m-%y", localtime(&(attrib.st_ctime)));

    fprintf(configFile, "#CREATED AT: %s\n\n", date);
	fprintf(configFile, "[app]\n");
	fprintf(configFile, "menu=1\n");
    fprintf(configFile, "%s\n", "width=42");
    fprintf(configFile, "%s\n", "height=100");
    fprintf(configFile, "%s\n", "color=1");

    return configFile;
}


FILE* editConfigFile(FILE* configFile, int width, int height, int color, int menuType){

    struct stat attrib;
    char date[10];   
    
    stat("config.ini", &attrib);
    strftime(date, 10, "%d-%m-%y", localtime(&(attrib.st_ctime)));

    fprintf(configFile, "#CHANGE AT: %s\n\n", date);
	fprintf(configFile, "[app]\n");
	fprintf(configFile, "menu=%d\n", menuType);
    fprintf(configFile, "width=%d\n", width);
    fprintf(configFile, "height=%d\n", height);
    fprintf(configFile, "color=%d\n", color);

    return configFile;       

}

//STATICS
static ERROR_CODE fileExist(FILE* fileToCheck){

    if(fileToCheck == NULL){
        perror("ERROR::");
        return FILE_NOT_FOUND;
    }


    return ERROR_OK;
}


void formatString(char* string, char charToClean){

	char *ptr = strchr(string, charToClean);
	if (ptr)
		*ptr  = '\0';

}

static int searchEmptyString(char* word) {

    if(strcmp(word, " ") == 0)
        return 1;
    else 
        return 0;
}
