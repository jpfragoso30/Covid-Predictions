#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0

// para debugear las liberaciones de memoria
#define DEBUG_MODE 1

typedef enum errors{
    MEM_ERROR,
    ERROR_OK,
    EMPTY_STRUCT,
    INVALID_FILE,
    INVALID_DIR,
    CONFIG_ERROR,
    CONFIG_FILE_NOT_FOUND,
    ERROR_CREATING_DIR,
    ERROR_PLOTING,
    EMPTY_DIR,
    
}ERRORS_CODE;


#endif
