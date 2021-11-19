#ifndef CONFIG_H
#define CONFIG_H

#include "Libs.h"
#include "Files.h"
#include "ini.h"

typedef struct _Config* Config;


//Constructor
Config initConfig(void);


//Destructors
Config freeConfig(Config configToFree);



//FUNCIONES PRINCIPALES
void configureApp(Config configApp);
char* createConfigCommandSize(Config configApp);

//SETTERS
ERROR_CODE setColor(Config configApp);
ERROR_CODE setNumColor(Config confingApp, int newNumColor);
ERROR_CODE setWidth(Config configApp, int newWidth);
ERROR_CODE setHeight(Config configApp, int newHeight);
ERROR_CODE setMenuType(Config configApp);

//GETTERS
int getWidth(Config configApp);
int getHeight(Config configApp);
int getNumColor(Config configApp);
char* getColor(Config configApp);
int getTypeMenu(Config configApp);
char* getColorSelection(Config configApp);
#endif
