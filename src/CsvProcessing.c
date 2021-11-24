#include "../libs/CsvProcessing.h"

struct _CsvProcessing
{

    //!float** data; --> EN caso de usarse floats solos

    char ***data;
    uint8_t rows;
    uint8_t columns;
    uint8_t columnsWithData;
    uint8_t rowsWithData;
    char *fileName;
};

CsvProcessing initCsvProccessing(void)
{

    CsvProcessing newCsv = NULL;
    newCsv = malloc(sizeof(struct _CsvProcessing));

    if (!newCsv)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, MEM_ERROR);
        exit(MEM_ERROR);
    }

    newCsv->columns = 10;
    newCsv->rows = 10;
    newCsv->rowsWithData = 0;
    //!newCsv->data = createMatrix(newCsv->data, newCsv->rows, newCsv->columns);
    newCsv->data = createStringMatrix(newCsv->data, newCsv->rows, newCsv->columns);
    newCsv->columnsWithData = 0;
    return newCsv;
}

CsvProcessing freeCsvProcessing(CsvProcessing csvProcessingToFree)
{

#if DEBUG_MODE
    puts("free CsvProcessing");
#endif
    if (!csvProcessingToFree)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    //!csvProcessingToFree->data = freeMatrix(csvProcessingToFree->data, csvProcessingToFree->rows);
    csvProcessingToFree->data = freeMatrixString(csvProcessingToFree->data, csvProcessingToFree->rows);

    free(csvProcessingToFree);
    csvProcessingToFree = NULL;

    return csvProcessingToFree;
}

ERRORS_CODE restarCsvProcessing(CsvProcessing csvToRestart)
{

#if DEBUG_MODE
    puts("free restarting csv struct");
#endif

    if (!csvToRestart)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    csvToRestart->data = freeMatrixString(csvToRestart->data, csvToRestart->rows);

    csvToRestart->columns = 10;
    csvToRestart->rows = 10;
    csvToRestart->rowsWithData = 0;
    csvToRestart->columnsWithData = 0;

    csvToRestart->data = createStringMatrix(csvToRestart->data, csvToRestart->rows, csvToRestart->columns);
    return ERROR_OK;
}

/*
ERRORS_CODE readCsvForPrint(CsvProcessing csvData, char* fileName){


    FILE *csvFile = openFile(fileName, READ);

    char buffer[BUFSIZ];
    char* value;
    uint8_t fileRows = 0, fileColumns = 0;
    float tempData;
    

    while (fgets(buffer, BUFSIZ, csvFile) != NULL){
        
        value = strtok(buffer, ",");
        while (value != NULL){
            
            if(fileColumns >= csvData->columns){
                csvData->data[fileRows] = setMoreColumns(csvData->data[fileRows], csvData->columns);
                csvData->columns *= 2;
            }

            if(sscanf(value, "%f", tempData)){
                csvData->data[fileRows][fileColumns] = tempData;
                fileColumns++;
            }

           value = strtok(NULL, ",\t");    
        }
        
        fileRows++;
        if(fileRows >= csvData->rows){
            csvData->data = setMoreRows(csvData->data, csvData->rows);
            csvData->rows *= 2;
        }

    }

    csvData->rowsWithData = fileRows;
    csvFile = closeFile(csvFile);
    return ERROR_OK;    
}
*/

ERRORS_CODE readCsv(CsvProcessing csvData, char *fileName)
{

    FILE *csvFile = openFile(fileName, READ);

    char buffer[BUFSIZ];
    char *value;
    uint8_t fileRows = 0, fileColumns = 0;

    while (fgets(buffer, BUFSIZ, csvFile) != NULL)
    {

        value = strtok(buffer, ",\t");
        fileColumns = 0;
        while (value != NULL)
        {

            if (fileColumns >= csvData->columns)
            {
                csvData->data[fileRows] = setMoreColumnsString(csvData->data[fileRows], csvData->columns);
                csvData->columns *= 2;
            }

            formatString(value, '\n');
            csvData->data[fileRows][fileColumns] = createStrignSpace(csvData->data[fileRows][fileColumns], value);
            csvData->data[fileRows][fileColumns] = strdup(value);

            value = strtok(NULL, ",\t");
            fileColumns++;
        }

        fileRows++;
        if (fileRows >= csvData->rows)
        {
            csvData->data = setMoreRowsString(csvData->data, csvData->rows, csvData->columns);
            csvData->rows *= 2;
        }
    }

    csvData->columnsWithData = fileColumns;
    csvData->rowsWithData = fileRows;

    csvFile = closeFile(csvFile);
    return ERROR_OK;
}

ERRORS_CODE writeCsv(char *fileName, float *x, float *y, uint8_t rows)
{

    FILE *csvFile = openFile(fileName, WRITE);

    fputs("#X,\tY\n", csvFile);
    for (uint8_t i = 0; i < rows; i++)
        fprintf(csvFile, "%f,\t%f\n", x[i], y[i]);

    csvFile = closeFile(csvFile);
    return ERROR_OK;
}

void formatString(char *string, char charToClean)
{

    char *ptr = strchr(string, charToClean);
    if (ptr)
        *ptr = '\0';
}

// GETTERS

uint8_t getRowsWithData(CsvProcessing csv)
{

    if (!csv)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return csv->rowsWithData;
}

char **getRowDataForPrinting(CsvProcessing csv, uint8_t index)
{

    if (!csv)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return csv->data[index];
}

uint8_t getColumnsWithData(CsvProcessing csv)
{

    if (!csv)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return csv->columnsWithData;
}

void printResultData(CsvProcessing csv, char *fileName)
{

    ft_table_t *table = ft_create_table();
    ft_set_border_style(table, FT_DOUBLE2_STYLE);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    readCsv(csv, fileName);

    puts("\n\n");
    for (uint8_t row = 0; row < csv->rowsWithData; row++)
    {

        ft_row_write_ln(table, csv->columnsWithData, (const char **)csv->data[row]);
        ft_set_cell_prop(table, FT_ANY_ROW, row, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    }

    printf("%s", ft_to_string(table));

    ft_destroy_table(table);
    printf("\n\n");
}