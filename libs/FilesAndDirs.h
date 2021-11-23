#ifndef FILESANDDIRS_H
#define FILESANDDIRS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "Errors.h"



#define READ "r"
#define WRITE "w"
#define APPEND "a"


FILE* openFile(char* fileName, const char* format);
FILE* closeFile(FILE* csvFile);
ERRORS_CODE fileExists(FILE* csvFile);

FILE* openPloterFile();
FILE* closePloterFile(FILE* plotFile);

DIR* openConfigDir(const char* dirName);
ERRORS_CODE exisistConfigDir(DIR* dir);
ERRORS_CODE createDir(const char* dirName);
DIR* openNormalDir(const char* dirName);

#endif