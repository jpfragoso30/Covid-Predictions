#ifndef LIBS_H
#define LIBS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdbool.h>


#define CLEAN "clear"

typedef enum{

    MEM_ERROR, 
    ERROR_OK,
    FILE_NOT_FOUND,
    CONFIG_FILE_NOT_FOUND,
    CONFIG_ERROR

}ERROR_CODE;







#endif
