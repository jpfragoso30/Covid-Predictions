#include "../libs/FilesAndDirs.h"

static ERRORS_CODE exisistDir(DIR* dir);




FILE* openFile(char* fileName, const char* format){

    FILE* csvFile = NULL;

    csvFile = fopen(fileName, format);

    fileExists(csvFile);

    return csvFile;
}



FILE* closeFile(FILE* csvFile){

    fclose(csvFile);
    csvFile = NULL;

    return csvFile;
}



ERRORS_CODE fileExists(FILE* csvFile){

    if(!csvFile){

        csvFile = closeFile(csvFile);
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, INVALID_FILE);
        exit(INVALID_FILE);
    }

    return ERROR_OK;
}





DIR* openNormalDir(const char* dirName){

    DIR* newDir = NULL;
    newDir = opendir(dirName);

    exisistDir(newDir);

    return newDir;
}



DIR* openConfigDir(const char* dirName){

    DIR* newDir = NULL;
    newDir = opendir(dirName);

    return newDir;
}



ERRORS_CODE exisistConfigDir(DIR* dir){

    if(!dir)
        return INVALID_DIR;
    

    return ERROR_OK;
}


ERRORS_CODE createDir(const char* dirName){

    if(mkdir(dirName, 0777) == -1){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, ERROR_CREATING_DIR);
        return ERROR_CREATING_DIR;
    }

    return ERROR_OK;
}



FILE* openPloterFile(void){

    FILE* plotFile = NULL;
    plotFile = popen("gnuplot -persistent", WRITE);

    if(!plotFile){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, ERROR_PLOTING);
        exit(ERROR_PLOTING);
    }

    return plotFile;
}


FILE* closePloterFile(FILE* plotFile){

    pclose(plotFile);
    plotFile = NULL;

    return plotFile;
}

static ERRORS_CODE exisistDir(DIR* dir){
    
    if(!dir){
        closedir(dir);
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, INVALID_DIR);
        exit(INVALID_DIR);
    }

    return ERROR_OK;
}





