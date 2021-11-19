#include "../libs/Config.h"


static ERROR_CODE setInitConfiguratinosApp(Config configApp);
static void restartApp(Config configApp);
static ERROR_CODE checkConfig(Config configApp);


struct _Config{
    
    int width;
    int height;
	int numColor;
	char* hexColor;
	int typeMenu;
    char* dirName;

};


//Constructors
Config initConfig(void){
    
    Config config = NULL;
    config = malloc(sizeof(struct _Config));

    if(config == NULL){
        perror("ERROR::");
        exit(MEM_ERROR);
    }

    config->width = -1;
    config->height = -1;
	config->numColor = -1;
	config->typeMenu = -1;
    return config;
}


//Destructors
Config freeConfig(Config configToFree){
    
    free(configToFree);
    configToFree = NULL;

    return configToFree;
}


//FUNCIONES PRINCIPALES

void configureApp(Config configApp){

    if(setInitConfiguratinosApp(configApp) != ERROR_OK)
        restartApp(configApp);

    system(CLEAN);
    system(createConfigCommandSize(configApp));
    printf("%s", configApp->hexColor);
    
}



//STATICS
static ERROR_CODE setInitConfiguratinosApp(Config configApp){
    ini_t* config = NULL;
    
    config = ini_load("config.ini");
    if(config == NULL)
        return CONFIG_FILE_NOT_FOUND;

	ini_sget(config, "app", "menu", "%d", &configApp->typeMenu);
    ini_sget(config, "app", "width", "%d", &configApp->width);
    ini_sget(config, "app", "height", "%d", &configApp->height);
    ini_sget(config, "app", "color", "%d", &configApp->numColor);



    if(checkConfig(configApp) == CONFIG_ERROR){       
        ini_free(config);
        return CONFIG_ERROR;
    }

    ini_free(config);
    setColor(configApp);

    return ERROR_OK;
}


static void restartApp(Config configApp){
    
    FILE* configFile = NULL;
    configFile = newFile("config.ini", WRITE);

    configApp = freeConfig(configApp);
    configFile = createConfigFile(configFile);
    closeFile(configFile);
    
    puts("THE APP NEEDS TO RESTART\n PLEASE PRESS ENTER");
    getchar();

    system("./myapp.out");
    exit(CONFIG_FILE_NOT_FOUND);
}


static ERROR_CODE checkConfig(Config configApp){

    if(configApp->numColor < 0 || configApp->height < 0 || configApp->width < 0 || configApp->typeMenu < 0)
        return CONFIG_ERROR;

	if(configApp->typeMenu > 1)
		configApp->typeMenu = 1;

    return ERROR_OK;
}


char* createConfigCommandSize(Config configApp){
    
    char command[BUFSIZ] = "resize -s ";
    char number[20];
    
    sprintf(number, "%d ", configApp->width);
    strcat(command, number);
    
	sprintf(number, "%d ", configApp->height);
    strcat(command, number);

    return strdup(command);
}



//SETTERS

ERROR_CODE setNumColor(Config confingApp, int newNumColor){
    
    if(confingApp != NULL)
        confingApp->numColor = newNumColor;

    return ERROR_OK;
}

ERROR_CODE setColor(Config configApp){
    
    
    const char* configListColors[] = { "\x1B[0m",  "\x1B[31m", "\x1B[32m", "\033[36m"};
    
    if(configApp != NULL)
        configApp->hexColor = strdup(configListColors[configApp->numColor]);
    
    return ERROR_OK;  
}


ERROR_CODE setWidth(Config configApp, int newWidth){
    
    if(newWidth  < 0)
        newWidth = 0;

    if(configApp != NULL)
        configApp->width = newWidth;

    return ERROR_OK;
}



ERROR_CODE setHeight(Config configApp, int newHeight){
    
    if(newHeight  < 0)
        newHeight = 0;

    if(configApp != NULL)
        configApp->height = newHeight;

    return ERROR_OK;
}


ERROR_CODE setMenuType(Config configApp){
	if(configApp != NULL){
		if(configApp->typeMenu == 1)
			configApp->typeMenu = 0;
		else if(configApp->typeMenu == 0)
			configApp->typeMenu = 1;
	}

	return ERROR_OK;
}



//GETTERS
int getWidth(Config configApp){
    return configApp->width;
}

int getHeight(Config configApp){
    return configApp->height;
}

int getNumColor(Config configApp){
    return configApp->numColor;
}

char* getColor(Config configApp){
    return configApp->hexColor;
}

int getTypeMenu(Config configApp){
	return configApp->typeMenu;
}

char* getColorSelection(Config configApp){
	const char* configListColors[] = { "\x1B[0m",  "\x1B[31m", "\x1B[32m", "\033[36m"};

	switch (configApp->numColor) {
		case 0:
			return strdup(configListColors[1]);
		case 1:
			return strdup(configListColors[0]);
		case 2:
			return strdup(configListColors[3]);
		case 3:
			return strdup(configListColors[2]);
	}

	return strdup(configListColors[0]);
}



