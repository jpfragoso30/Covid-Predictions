#include "../libs/Config.h"

ERRORS_CODE static setConfigurations(Config configApp);
static ERRORS_CODE checkConfig(Config configApp);
static ERRORS_CODE checkDirs(Config configApp);


struct _Config{
    
    uint8_t width, height;
    uint8_t numColor;
    uint8_t typeMenu;
    const char* dirPloters;
    const char* dirCsvsResults;
    const char* dirsCsvEntrenamiento;

};


Config initConfig(void){

    Config newConfig = NULL;
    newConfig = malloc(sizeof(struct _Config));

    if(!newConfig){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, MEM_ERROR);
        exit(MEM_ERROR);
    }

    newConfig->width = -1;
    newConfig->height = -1;
    newConfig->typeMenu = 0;
    newConfig->dirPloters = "PlotersResult";
    newConfig->dirCsvsResults = "CsvResults";
    newConfig->dirsCsvEntrenamiento = "CsvEntr";

    return newConfig;
}


Config freeConfig(Config configToFree){

    #if DEBUG_MODE
    puts("free Config Struct");
    #endif

    free(configToFree);
    configToFree = NULL;

    return configToFree;
}


ERRORS_CODE configureApp(Config configApp){
    
    #if DEBUG_MODE
    puts("Config APP!");
    #endif


    if(!configApp){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    if(setConfigurations(configApp) != ERROR_OK)
        return CONFIG_ERROR;

    
    return ERROR_OK;
}


ERRORS_CODE static setConfigurations(Config configApp){

    ini_t* configIni = NULL;
    
    if(!configApp){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    
    configIni = ini_load("config.ini");
    if(configIni == NULL)
        return CONFIG_FILE_NOT_FOUND;

	ini_sget(configIni, "app", "menu", "%d", &configApp->typeMenu);
    ini_sget(configIni, "app", "width", "%d", &configApp->width);
    ini_sget(configIni, "app", "height", "%d", &configApp->height);
    ini_sget(configIni, "app", "color", "%d", &configApp->numColor);



    if(checkConfig(configApp) == CONFIG_ERROR){       
        ini_free(configIni);
        return CONFIG_ERROR;
    }

    ini_free(configIni);
    setColor(configApp);

    checkDirs(configApp);
    return ERROR_OK;
}



char* createConfigCommandSize(Config configApp){
    
    char command[BUFSIZ];
    
    sprintf(command, "resize -s %d %d", configApp->width, configApp->height);
    return strdup(command);
}




char* getColor(Config configApp){
    
    const char* configListColors[] = {WHITE,  RED, GREEN, CYAN};
    
    if(!configApp){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }
        
        
    return strdup(configListColors[configApp->numColor]);   
}



ERRORS_CODE setColor(Config configApp){
    
    if(!configApp){
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    
    puts(getColor(configApp));
    

    return ERROR_OK;
}

static ERRORS_CODE checkDirs(Config configApp){

    DIR* dirs = NULL;

    dirs = openConfigDir(configApp->dirCsvsResults);
    if(exisistConfigDir(dirs) != ERROR_OK){
        createDir(configApp->dirCsvsResults);
    }else
        closedir(dirs);


    dirs = openConfigDir(configApp->dirPloters);
    if(exisistConfigDir(dirs) != ERROR_OK){
        createDir(configApp->dirPloters);
    }else
        closedir(dirs);
    

    dirs = openConfigDir(configApp->dirsCsvEntrenamiento);
    if(exisistConfigDir(dirs) != ERROR_OK){
        createDir(configApp->dirsCsvEntrenamiento);
    }else
        closedir(dirs);

    return ERROR_OK;
}




static ERRORS_CODE checkConfig(Config configApp){

    if(configApp->numColor < 0 || configApp->height < 0 || configApp->width < 0 || configApp->typeMenu < 0)
        return CONFIG_ERROR;

	if(configApp->typeMenu > 1)
		configApp->typeMenu = 1;

    return ERROR_OK;
}


ERRORS_CODE createConfigFile(void){
    
    FILE* configFile = openFile("config.ini", WRITE);
    struct stat attrib;
    char date[10];   
    
    stat("config.ini", &attrib);
    strftime(date, 10, "%d-%m-%y", localtime(&(attrib.st_ctime)));

    fprintf(configFile, "#CREATED AT: %s\n\n", date);
	fprintf(configFile, "[app]\n");
	fprintf(configFile, "menu=1\n");
    fprintf(configFile, "%s\n", "width=42");
    fprintf(configFile, "%s\n", "height=100");
    fprintf(configFile, "%s\n", "color=1");

    closeFile(configFile);

    return ERROR_OK;
}