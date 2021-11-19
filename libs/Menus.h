#ifndef MENUS_H
#define MENUS_H

#include "Libs.h"
#include "Memory.h"
#include "Config.h"

typedef struct _Menu* Menu;

//Constructor
Menu initMenu(void);


//FUNCIONES PRINCIPALES
void menuController(Menu menuApp, int state);
void printMenu(Menu menuApp);
void printHeader(void);
void updateMenu(Menu menuApp, Config configApp);


//GETTERS
char** getMenuList(Menu menuApp);
int getOption(Menu menuApp);
int getNumOptions(Menu menuApp);

//SETTERS
void setMenuList(Menu menuApp, int state);
ERROR_CODE setOption(Menu menuApp, int newOption);
ERROR_CODE setDynamicOption(Menu menuApp, char newOption);


//Destructors
Menu freeMenu(Menu menuApp);
#endif
