#include "../libs/Config.h"

ERRORS_CODE static setConfigurations(Config configApp);
static ERRORS_CODE checkConfig(Config configApp);
static ERRORS_CODE checkDirs(Config configApp);
<<<<<<< HEAD
static char* createDynamicPath(char* fileOrDir, char* userPath);
=======
<<<<<<< HEAD

struct _Config
{
=======
static char* createDynamicPath(char* fileOrDir, char* userPath);
>>>>>>> 2d4d84f7217a6f6e7a9bbe694beef065ea9463dc
>>>>>>> main

    uint8_t width;
    uint8_t height;
    uint8_t numColor;
    uint8_t typeMenu;
<<<<<<< HEAD
=======
<<<<<<< HEAD
    const char *dirPloters;
    const char *dirCsvsResults;
    const char *dirsCsvEntrenamiento;
};

Config initConfig(void)
{
=======
>>>>>>> main
    char* dirPloters;
    char* dirCsvsResults;
    char* dirsCsvEntrenamiento;
    char* configFile;

};


Config initConfig(char* userPath){
<<<<<<< HEAD
=======
>>>>>>> 2d4d84f7217a6f6e7a9bbe694beef065ea9463dc
>>>>>>> main

    Config newConfig = NULL;
    newConfig = malloc(sizeof(struct _Config));

    if (!newConfig)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, MEM_ERROR);
        exit(MEM_ERROR);
    }

    newConfig->width = -1;
    newConfig->height = -1;
    newConfig->typeMenu = 0;
<<<<<<< HEAD
=======
<<<<<<< HEAD
    newConfig->dirPloters = "./Covid-Predictions/PlotersResult";
    newConfig->dirCsvsResults = "./Covid-Predictions/CsvResults";
    newConfig->dirsCsvEntrenamiento = "./Covid-Predictions/CsvEntr";
=======
>>>>>>> main
    newConfig->dirPloters = createStrignSpace(newConfig->dirPloters, createDynamicPath("PlotersResult", userPath));
    newConfig->dirPloters = strdup(createDynamicPath("PlotersResult", userPath));

    newConfig->dirCsvsResults = createStrignSpace(newConfig->dirCsvsResults, createDynamicPath("CsvResults", userPath));
    newConfig->dirCsvsResults = strdup(createDynamicPath("CsvResults", userPath));

    newConfig->dirsCsvEntrenamiento = createStrignSpace(newConfig->dirsCsvEntrenamiento, createDynamicPath("CsvEntr", userPath));
    newConfig->dirsCsvEntrenamiento = strdup(createDynamicPath("CsvEntr", userPath));

    newConfig->configFile = createStrignSpace(newConfig->configFile, createDynamicPath("config.ini", userPath));
    newConfig->configFile = strdup(createDynamicPath("config.ini", userPath));
<<<<<<< HEAD
=======
>>>>>>> 2d4d84f7217a6f6e7a9bbe694beef065ea9463dc
>>>>>>> main

    return newConfig;
}

Config freeConfig(Config configToFree)
{

#if DEBUG_MODE
    puts("free Config Struct");
#endif

    free(configToFree->dirCsvsResults);
    configToFree->dirCsvsResults = NULL;

    free(configToFree->configFile);
    configToFree->configFile = NULL;

    free(configToFree->dirPloters);
    configToFree->dirPloters = NULL;

    free(configToFree->dirsCsvEntrenamiento);
    configToFree->dirsCsvEntrenamiento = NULL;

    free(configToFree->dirCsvsResults);
    configToFree->dirCsvsResults = NULL;

    free(configToFree->configFile);
    configToFree->configFile = NULL;

    free(configToFree->dirPloters);
    configToFree->dirPloters = NULL;

    free(configToFree->dirsCsvEntrenamiento);
    configToFree->dirsCsvEntrenamiento = NULL;

    free(configToFree);
    configToFree = NULL;

    return configToFree;
}

ERRORS_CODE configureApp(Config configApp)
{

#if DEBUG_MODE
    puts("Config APP!");
#endif

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    if (setConfigurations(configApp) != ERROR_OK)
        return CONFIG_ERROR;

    return ERROR_OK;
}

ERRORS_CODE static setConfigurations(Config configApp)
{

    ini_t *configIni = NULL;

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

<<<<<<< HEAD
    configIni = ini_load("./Covid-Predictions/config.ini");
    if (configIni == NULL)
=======
    
    configIni = ini_load(configApp->configFile);
    if(configIni == NULL)
>>>>>>> 2d4d84f7217a6f6e7a9bbe694beef065ea9463dc
        return CONFIG_FILE_NOT_FOUND;

    ini_sget(configIni, "app", "menu", "%hhu", &configApp->typeMenu);
    ini_sget(configIni, "app", "width", "%hhu", &configApp->width);
    ini_sget(configIni, "app", "height", "%hhu", &configApp->height);
    ini_sget(configIni, "app", "color", "%hhu", &configApp->numColor);

    if (checkConfig(configApp) == CONFIG_ERROR)
    {
        ini_free(configIni);
        return CONFIG_ERROR;
    }

    ini_free(configIni);
    setColor(configApp);
    configCommandSize(configApp);

    checkDirs(configApp);
    return ERROR_OK;
}

ERRORS_CODE createConfigFile(void)
{

<<<<<<< HEAD
=======
<<<<<<< HEAD
    FILE *configFile = openFile("./Covid-Predictions/config.ini", WRITE);
    struct stat attrib;
    char date[20];

    stat("../config.ini", &attrib);
=======
>>>>>>> main
ERRORS_CODE createConfigFile(char* configFilePath){
    
    FILE* configFile = openFile(configFilePath, WRITE);
    struct stat attrib;
    char date[20];   
    
    stat(configFilePath, &attrib);
<<<<<<< HEAD
=======
>>>>>>> 2d4d84f7217a6f6e7a9bbe694beef065ea9463dc
>>>>>>> main
    strftime(date, 20, "%d-%m-%y %H:%M:%S", localtime(&(attrib.st_ctime)));

    fprintf(configFile, "#CREATED AT: %s\n\n", date);
    fprintf(configFile, "[app]\n");
    fprintf(configFile, "menu=1\n");
    fprintf(configFile, "%s\n", "width=42");
    fprintf(configFile, "%s\n", "height=100");
    fprintf(configFile, "%s\n", "color=1");

    closeFile(configFile);

    return ERROR_OK;
}

ERRORS_CODE reconfigureConfigFile(Config configApp)
{

<<<<<<< HEAD
    FILE *configFile = openFile("./Covid-Predictions/config.ini", WRITE);
    struct stat attrib;
    char date[20];

<<<<<<< HEAD
=======
    stat("../config.ini", &attrib);
=======
>>>>>>> main
    FILE* configFile = openFile(configApp->configFile, WRITE);
    struct stat attrib;
    char date[20];   
    
    stat(configApp->configFile, &attrib);
<<<<<<< HEAD
=======
>>>>>>> 2d4d84f7217a6f6e7a9bbe694beef065ea9463dc
>>>>>>> main
    strftime(date, 20, "%d-%m-%y %H:%M:%S", localtime(&(attrib.st_ctime)));

    fprintf(configFile, "#CHANGE AT: %s\n\n", date);
    fprintf(configFile, "[app]\n");
    fprintf(configFile, "menu=%d\n", configApp->typeMenu);
    fprintf(configFile, "width=%d\n", configApp->width);
    fprintf(configFile, "height=%d\n", configApp->height);
    fprintf(configFile, "color=%hhu\n", configApp->numColor);

    closeFile(configFile);

    return ERROR_OK;
}

ERRORS_CODE configCommandSize(Config configApp)
{

    char command[BUFSIZ];

    sprintf(command, "resize -s %d %d", configApp->height, configApp->width);
    system(command);

    return ERROR_OK;
}

char *getColor(Config configApp)
{

    const char *configListColors[] = {WHITE, RED, GREEN, CYAN};

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return strdup(configListColors[configApp->numColor]);
}

char *getColorSelection(Config configApp)
{

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    switch (configApp->numColor)
    {

    case 0:
        return RED;
        break;

<<<<<<< HEAD
    case 1:
        return WHITE;
        break;

    case 2:
        return CYAN;
        break;
=======
// GETTERS
>>>>>>> 2d4d84f7217a6f6e7a9bbe694beef065ea9463dc

    case 3:
        return GREEN;
        break;

    default:
        return CYAN;
        break;
    }
}

uint8_t getTypeMenu(Config configApp)
{

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return configApp->typeMenu;
}



char* getCsvResutlsDir(Config configApp){

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return configApp->dirCsvsResults;
}


char* getPloterResutlsDir(Config configApp){

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return configApp->dirPloters;
}

<<<<<<< HEAD
// GETTERS
=======

char* getPathCsvEntrDir(Config configApp){

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }
>>>>>>> main

    return configApp->dirsCsvEntrenamiento;
}

char* getConfigFilePath(Config configApp){

     if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return configApp->configFile;
}



char* getCsvResutlsDir(Config configApp){

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return configApp->dirCsvsResults;
}


char* getPloterResutlsDir(Config configApp){

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return configApp->dirPloters;
}


char* getPathCsvEntrDir(Config configApp){

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return configApp->dirsCsvEntrenamiento;
}

char* getConfigFilePath(Config configApp){

     if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return configApp->configFile;
}

// SETTERS

ERRORS_CODE setColor(Config configApp)
{

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    puts(getColor(configApp));

    return ERROR_OK;
}

ERRORS_CODE setWidht(Config configApp)
{

    char line[256];
    uint8_t temp;

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    puts("Enter a new Width for the window");
    while (TRUE)
    {
        if (fgets(line, sizeof(line), stdin))
        {
            if (1 == sscanf(line, "%" SCNu8, &(temp)))
            {
                configApp->width = temp;
                return ERROR_OK;
            }
        }
    }
}

ERRORS_CODE setHeight(Config configApp)
{

    char line[256];
    uint8_t temp;

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    puts("Enter a new Height for the window");
    while (TRUE)
    {
        if (fgets(line, sizeof(line), stdin))
        {
            if (1 == sscanf(line, "%" SCNu8, &(temp)))
            {
                configApp->height = temp;
                return ERROR_OK;
            }
        }
    }
}

ERRORS_CODE setTypeMenu(Config configApp)
{

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    if (configApp->typeMenu)
        configApp->typeMenu = 0;
    else
        configApp->typeMenu = 1;

    return ERROR_OK;
}

static ERRORS_CODE checkDirs(Config configApp)
{

    DIR *dirs = NULL;

    dirs = openConfigDir(configApp->dirCsvsResults);
    if (exisistConfigDir(dirs) != ERROR_OK)
    {
        createDir(configApp->dirCsvsResults);
    }
    else
        closedir(dirs);

    dirs = openConfigDir(configApp->dirPloters);
    if (exisistConfigDir(dirs) != ERROR_OK)
    {
        createDir(configApp->dirPloters);
    }
    else
        closedir(dirs);

    dirs = openConfigDir(configApp->dirsCsvEntrenamiento);
    if (exisistConfigDir(dirs) != ERROR_OK)
    {
        createDir(configApp->dirsCsvEntrenamiento);
    }
    else
        closedir(dirs);

    return ERROR_OK;
}

ERRORS_CODE setNumColor(Config configApp, uint8_t newColor)
{

    if (!configApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    configApp->numColor = newColor;

    return ERROR_OK;
}

//STATICS

static ERRORS_CODE checkConfig(Config configApp)
{

    if (configApp->numColor < 0 || configApp->height < 0 || configApp->width < 0 || configApp->typeMenu < 0)
        return CONFIG_ERROR;

    if (configApp->typeMenu > 1)
        configApp->typeMenu = 1;

    if (configApp->numColor > 3)
        configApp->numColor = 3;

    return ERROR_OK;
}
<<<<<<< HEAD
=======


static char* createDynamicPath(char* fileOrDir, char* userPath){

    char newPath[BUFSIZ];
    uint8_t numSlashes = 0;

    for(uint8_t i = 0; i < strlen(userPath); i++){
        if(userPath[i] == '/')
            numSlashes++;
    }

<<<<<<< HEAD
static char* createDynamicPath(char* fileOrDir, char* userPath){

    char newPath[BUFSIZ];
    uint8_t numSlashes = 0;

    for(uint8_t i = 0; i < strlen(userPath); i++){
        if(userPath[i] == '/')
            numSlashes++;
    }

=======
>>>>>>> main
    if(numSlashes == 1) 
        sprintf(newPath, "../%s", fileOrDir);

    else if(numSlashes == 2)
        return fileOrDir;

    else
        sprintf(newPath, "./Covid-Predictions/%s", fileOrDir);
        
    puts(newPath);
    puts(userPath);
    return strdup(newPath);
<<<<<<< HEAD
}
=======
}
>>>>>>> 2d4d84f7217a6f6e7a9bbe694beef065ea9463dc
>>>>>>> main
