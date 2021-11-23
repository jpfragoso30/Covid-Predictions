#include "../libs/PF.h"

//static void clearBuffer(void);
static ERRORS_CODE setFileNameFromMenuOptions(PF pf, char* newFileName);
static ERRORS_CODE ploterExistingFileState(PF pf);
static ERRORS_CODE ploterState(PF pf);
static ERRORS_CODE exitState(PF pf);
static ERRORS_CODE changeConfigurationsState(PF pf);
static ERRORS_CODE backToMainMenuState(PF pf);
static ERRORS_CODE backToMainMenuState(PF pf);
static ERRORS_CODE chanegSizeWindow(PF pf);
static ERRORS_CODE chanegColor(PF pf);
static ERRORS_CODE changeTypeMenu(PF pf);
static ERRORS_CODE menuPrincipalState(PF pf);
static ERRORS_CODE restartPF(PF pf);
static ERRORS_CODE replotState(PF pf);
static ERRORS_CODE reprintData(PF pf);
static ERRORS_CODE ploterExistingFileStateMenu(PF pf);
static ERRORS_CODE replotingExistingFileStateMenu(PF pf);

struct _PF{
    
    float* tiempo;
    float* y; 
    uint8_t endValue;
    float width;
    char* fileNamePlot;
    char* fileNameCsv;

    STATES nextState;
    uint8_t seleccion;

    ERRORS_CODE(*functionByProcess[5][5])(PF pf);

    CsvProcessing csv;
    Menu menu;
    Config configApp;
};



PF initPF(uint8_t endValue, float width){

    PF newPF = NULL;
    newPF = malloc(sizeof(struct _PF));

    if(!newPF){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, MEM_ERROR);
        exit(MEM_ERROR);
    }

    
    newPF->endValue = endValue;
    newPF->width = width;

    newPF->tiempo = createArray(newPF->tiempo, newPF->endValue);
    newPF->y = createArray(newPF->y, newPF->endValue);

    newPF->fileNameCsv = "\0";
    newPF->fileNamePlot = "\0";

    newPF->nextState = MENU_P;

    newPF->csv = initCsvProccessing();
    newPF->menu = initMenu();
    newPF->configApp = initConfig();
    
    newPF->seleccion = 0;

    newPF->functionByProcess[MENU_P][0] = &menuPrincipalState;
    newPF->functionByProcess[MENU_P][1] = &ploterState;
    newPF->functionByProcess[MENU_P][2] = &ploterExistingFileStateMenu;
    newPF->functionByProcess[MENU_P][3] = &changeConfigurationsState;
    newPF->functionByProcess[MENU_P][4] = &exitState;

    newPF->functionByProcess[PREDICCION][0] = &replotState;
    newPF->functionByProcess[PREDICCION][1] = &backToMainMenuState;
    newPF->functionByProcess[PREDICCION][2] = &exitState;


    newPF->functionByProcess[PLOTER][0] = &replotingExistingFileStateMenu;
    newPF->functionByProcess[PLOTER][1] = &backToMainMenuState;
    newPF->functionByProcess[PLOTER][2] = &exitState;

    newPF->functionByProcess[CONFIGURACIONES][0] = &chanegSizeWindow;
    newPF->functionByProcess[CONFIGURACIONES][1] = &chanegColor;
    newPF->functionByProcess[CONFIGURACIONES][2] = &changeTypeMenu;
    newPF->functionByProcess[CONFIGURACIONES][3] = &backToMainMenuState;
    newPF->functionByProcess[CONFIGURACIONES][4] = &exitState;

    newPF->functionByProcess[PLOTER_SELECT_FILE][0] = &ploterExistingFileState;

    return newPF;
}



PF freePF(PF PfToFree){

    if(!PfToFree){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    PfToFree->csv = freeCsvProcessing(PfToFree->csv);
    PfToFree->menu = freeMenu(PfToFree->menu);
    PfToFree->configApp = freeConfig(PfToFree->configApp);
    
    #if DEBUG_MODE
        puts("free PF");
    #endif

    PfToFree->tiempo = freeArray(PfToFree->tiempo);
    PfToFree->y = freeArray(PfToFree->y);

    if(PfToFree->fileNameCsv[0] != '\0'){
        free(PfToFree->fileNameCsv);
        PfToFree->fileNameCsv = NULL;
    }

    if(PfToFree->fileNamePlot[0] != '\0'){
        free(PfToFree->fileNamePlot);
        PfToFree->fileNamePlot = NULL;
    }

    free(PfToFree);
    PfToFree = NULL;

    return PfToFree;
}


static ERRORS_CODE restartPF(PF pf){

#if DEBUG_MODE
puts("restar PF STRCUT");    
#endif

    pf->width = .100;
    pf->endValue = 10;
    
    free(pf->fileNameCsv);
    pf->fileNameCsv = "\0";

    free(pf->fileNamePlot);
    pf->fileNamePlot = "\0";

    pf->tiempo = freeArray(pf->tiempo);
    pf->tiempo = createArray(pf->tiempo, pf->endValue);
    
    pf->y = freeArray(pf->y);
    pf->y = createArray(pf->y, pf->endValue);

    pf->tiempo[0] = 0;
    pf->y[0] = 1;

    return ERROR_OK;
}


//SETTERS
ERRORS_CODE setValueInTiempo(PF pf, float newValue, uint8_t index){

    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }


    pf->tiempo[index] = newValue;

    return ERROR_OK;
}


ERRORS_CODE setTiempoCero(PF pf, float xCero){

    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    pf->tiempo[0] = xCero;

    return ERROR_OK;
}


ERRORS_CODE setValueInY(PF pf, float newValue, uint8_t index){

    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    pf->y[index] = newValue;

    return ERROR_OK;
}


ERRORS_CODE setYCero(PF pf, float yCero){

    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    pf->y[0] = yCero;

    return ERROR_OK;
}

ERRORS_CODE setNextState(PF pf, STATES newProcess){

    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    pf->nextState = newProcess;

    return ERROR_OK; 
}



ERRORS_CODE setOptionFromState(PF pf){

    char line[256];
    uint8_t temp;
    
    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }
    if(pf->seleccion == 10){
        pf->seleccion = 0;
        return ERROR_OK;
    }
        
    
    if (fgets(line, sizeof(line), stdin)) {
        if (1 == sscanf(line, "%" SCNu8, &(temp))) 
            pf->seleccion = temp;
        else
            pf->seleccion = -1;    
    }

    //scanf("%" SCNu8, &(pf->seleccion));
    //clearBuffer();
    return ERROR_OK; 
}


ERRORS_CODE setFileName(PF pf){

    char newFileNameCsv[BUFSIZ];
    char newFileName[BUFSIZ];
    char newFileNamePloter[BUFSIZ];

    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    puts("INTRODUCE EL NOMBRE UN NOMBRE PARA EL ARHCIVO PLOTER Y CSV (No introduzca ninguna ruta Y/O extención):");
    fgets(newFileName, BUFSIZ, stdin);

    formatString(newFileName, '\n');
    sprintf(newFileNameCsv, "CsvResults/%s.csv", newFileName);
    pf->fileNameCsv = createStrignSpace(pf->fileNameCsv, newFileNameCsv);
    pf->fileNameCsv = strdup(newFileNameCsv);

   
    sprintf(newFileNamePloter, "PlotersResult/%s.pdf", newFileName);
    pf->fileNamePlot = createStrignSpace(pf->fileNamePlot, newFileNamePloter);
    pf->fileNamePlot = strdup(newFileNamePloter);

    return ERROR_OK; 
}


static ERRORS_CODE setFileNameFromMenuOptions(PF pf, char* newFileName){

    char newFileNameCsv[BUFSIZ];
    char newFileNamePloter[BUFSIZ];

    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    sprintf(newFileNameCsv, "CsvResults/%s", newFileName);
    pf->fileNameCsv = createStrignSpace(pf->fileNameCsv, newFileNameCsv);
    pf->fileNameCsv = strdup(newFileNameCsv);

    formatString(newFileName, '.');

    sprintf(newFileNamePloter, "PlotersResult/%s.pdf", newFileName);
    pf->fileNamePlot = createStrignSpace(pf->fileNamePlot, newFileNamePloter);
    pf->fileNamePlot = strdup(newFileNamePloter);

    return ERROR_OK;
}

//GETTERS
float* getTiempo(PF pf){

    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return pf->tiempo;
}


float getTiempoValue(PF pf, uint8_t index){

    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return pf->tiempo[index];
}


float* getY(PF pf){

    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return pf->y;
}


float getYValue(PF pf, uint8_t index){

    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return pf->y[index];
}


float getEndValue(PF pf){

    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return pf->endValue;
}


float getWidth(PF pf){

    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return pf->width;
}




Menu getMenuStruct(PF pf){

    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return pf->menu;
}


CsvProcessing getCsvProcessingStruct(PF pf){
    
    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return pf->csv;
}

Config getConfigStruct(PF pf){
    
    if(!pf){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return pf->configApp;
}





//CONTROLADOR

ERRORS_CODE controlador(PF pf){


    switch (pf->nextState){
        case MENU_P:
            if(pf->seleccion >= 0 && pf->seleccion < 5)
                pf->functionByProcess[MENU_P][pf->seleccion](pf);
            else
                pf->functionByProcess[MENU_P][0](pf);
            break;
        
        case PREDICCION:
            if(pf->seleccion > 0 && pf->seleccion < 4)
                pf->functionByProcess[PREDICCION][pf->seleccion - 1](pf);
            else 
                reprintData(pf);
            break;

        case PLOTER:
            if(pf->seleccion > 0 && pf->seleccion < 4)
                pf->functionByProcess[PLOTER][pf->seleccion - 1](pf);
            else
                reprintData(pf);
            break;    

        case CONFIGURACIONES:
            pf->functionByProcess[CONFIGURACIONES][pf->seleccion - 1](pf);
            break;

        case PLOTER_SELECT_FILE:
            if(pf->seleccion > 0 && pf->seleccion <= getNumOptions(pf->menu))
                pf->functionByProcess[PLOTER_SELECT_FILE][0](pf);
            else
                pf->functionByProcess[MENU_P][2](pf);

            break; 
            
        default:
            pf->functionByProcess[MENU_P][0](pf);
            break;
    }

    return ERROR_OK;
}




// REINICIA APP
void restartApp(PF pf){

    createConfigFile();
    freePF(pf);
    
    puts("THE APP NEEDS TO RESTART\n PLEASE PRESS ENTER");
    getchar();

    system("./myapp.out");
    exit(CONFIG_FILE_NOT_FOUND);
}


// STATICS

static ERRORS_CODE menuPrincipalState(PF pf){
    
    printHeader();
    printMenu(pf->menu);

    return ERROR_OK;
}


static ERRORS_CODE ploterState(PF pf){


    euler_method(getTiempo(pf), getY(pf), getWidth(pf), getEndValue(pf));
    setFileName(pf);
    writeCsv(pf->fileNameCsv, pf->tiempo, pf->y, pf->endValue);
    plotResults(pf->fileNamePlot, pf->fileNameCsv, pf->tiempo, pf->y, pf->endValue);

    printHeader();
    
    printResultData(pf->csv, pf->fileNameCsv);
    
    
    setNextState(pf, PREDICCION);
    setMenuOptions(pf->menu, MENU_PLOTER);
    printMenu(pf->menu);

    return ERROR_OK;
}


static ERRORS_CODE replotingExistingFileStateMenu(PF pf){

    restarCsvProcessing(pf->csv);
    ploterExistingFileStateMenu(pf);

    return ERROR_OK;
}

static ERRORS_CODE replotState(PF pf){

    restartPF(pf);
    restarCsvProcessing(pf->csv);

    euler_method(getTiempo(pf), getY(pf), getWidth(pf), getEndValue(pf));
    setFileName(pf);
    writeCsv(pf->fileNameCsv, pf->tiempo, pf->y, pf->endValue);
    plotResults(pf->fileNamePlot, pf->fileNameCsv, pf->tiempo, pf->y, pf->endValue);

    printHeader();
    
    printResultData(pf->csv, pf->fileNameCsv);
    
    
    setNextState(pf, PREDICCION);
    setMenuOptions(pf->menu, MENU_PLOTER);
    printMenu(pf->menu);

    return ERROR_OK;
}


static ERRORS_CODE reprintData(PF pf){

    printHeader();
    printResultData(pf->csv, pf->fileNameCsv);
    printMenu(pf->menu);

    return ERROR_OK;
}

static ERRORS_CODE exitState(PF pf){
    
    freePF(pf);
    exit(ERROR_OK);
}



static ERRORS_CODE ploterExistingFileState(PF pf){

    if(pf->seleccion <= getNumOptions(pf->menu) && pf->seleccion > 0){
        setFileNameFromMenuOptions(pf, getFileNameOfMenuOptions(pf->menu, pf->seleccion - 1));
        plotResults(pf->fileNamePlot, pf->fileNameCsv, pf->tiempo, pf->y, pf->endValue);;
    }

    printHeader();
    puts(pf->fileNameCsv);
    printResultData(pf->csv, pf->fileNameCsv);

    setMenuOptions(pf->menu, MENU_PLOTER);
    setNextState(pf, PLOTER);
    printMenu(pf->menu);   
    

    return ERROR_OK;
}


static ERRORS_CODE ploterExistingFileStateMenu(PF pf){

    printHeader();
    setMenuOptions(pf->menu, MENU_REPLOT_FILE);
    printMenu(pf->menu);

    setNextState(pf, PLOTER_SELECT_FILE);
    return ERROR_OK;
}

static ERRORS_CODE changeConfigurationsState(PF pf){

    puts("change Configurations");
    return ERROR_OK;
}


static ERRORS_CODE backToMainMenuState(PF pf){

   
    restartPF(pf);
    restarCsvProcessing(pf->csv);

    setNextState(pf, MENU_P);
    pf->seleccion = 10;
    
    setMenuOptions(pf->menu, MENU_PRINCIPAL);
    return ERROR_OK;
}

static ERRORS_CODE chanegSizeWindow(PF pf){
    
    puts("change size window");
    return ERROR_OK;
}

static ERRORS_CODE chanegColor(PF pf){

    puts("change color");
    return ERROR_OK;
}


static ERRORS_CODE changeTypeMenu(PF pf){

    puts("change type Menu");
    return ERROR_OK;
}


/*static void clearBuffer(void){

	char input;
	while((input = getchar()) != '\n');
}*/
