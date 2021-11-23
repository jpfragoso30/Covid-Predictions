#ifndef CSVPROCESSING_H
#define CSVPROCESSING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "Errors.h"
#include "Memory.h"
#include "FilesAndDirs.h"
#include "fort.h"



typedef struct _CsvProcessing* CsvProcessing;


CsvProcessing initCsvProccessing(void);
CsvProcessing freeCsvProcessing(CsvProcessing csvProcessingToFree);

ERRORS_CODE restarCsvProcessing(CsvProcessing csvToRestart);

///ERRORS_CODE readCsvForPrint(CsvProcessing csvData, char* fileName);
ERRORS_CODE readCsv(CsvProcessing csvData, char* fileName);
ERRORS_CODE writeCsv(char* fileName, float* x, float* y, uint8_t rows);
void formatString(char* string, char charToClean);

uint8_t getRowsWithData(CsvProcessing csv);
char** getRowDataForPrinting(CsvProcessing csv, uint8_t index);
uint8_t getColumnsWithData(CsvProcessing csv);


void printResultData(CsvProcessing csv, char* fileName);
#endif
