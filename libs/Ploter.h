#ifndef PLOTER_H
#define PLOTER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "Errors.h"
#include "FilesAndDirs.h"

ERRORS_CODE plotResults(char *plotFileName, char *csvFileName, float *x, float *y, uint8_t rows);

#endif