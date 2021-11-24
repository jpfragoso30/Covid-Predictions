#include "../libs/Ploter.h"

static char *createCommandPlot(const char *nameFile, uint8_t typeCommand);

ERRORS_CODE plotResults(char *plotFileName, char *csvFileName, float *x, float *y, uint8_t rows)
{

    FILE *ploterFile = openPloterFile();

    fprintf(ploterFile, "%s", createCommandPlot(NULL, 0));
    fprintf(ploterFile, "%s", createCommandPlot(plotFileName, 1));
    fprintf(ploterFile, "%s", createCommandPlot(csvFileName, 2));
    fprintf(ploterFile, "%s", createCommandPlot(NULL, 3));

    ploterFile = closePloterFile(ploterFile);

    return ERROR_OK;
}

static char *createCommandPlot(const char *nameFile, uint8_t typeCommand)
{

    char commands[BUFSIZ];

    switch (typeCommand)
    {

    case 0:
        sprintf(commands, "set term pdfcairo enhanced font 'Helvetica,20'\n");
        break;

    case 1:
        sprintf(commands, "set output '%s'\n", nameFile);
        break;

    case 2:
        sprintf(commands, "plot '%s'\n", nameFile);
        break;

    case 3:
        sprintf(commands, "set title aa\n");
        break;

    default:
        break;
    }

    return strdup(commands);
}