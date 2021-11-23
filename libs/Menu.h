#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>
#include "Errors.h"
#include "Memory.h"


typedef struct _Menu* Menu;

typedef enum menu{

    MENU_PRINCIPAL,
    MENU_PLOTER,
    MENU_REPLOT_FILE,

}TYPEMENU;


Menu initMenu(void);
Menu freeMenu(Menu menuToFree);

// VISTAS
void printHeader(void);
void printMenu(Menu menuApp);

// SETTERS
ERRORS_CODE setMenuOptions(Menu menu, TYPEMENU typemenu);

// GETTERS
uint8_t getNumOptions(Menu menuApp);
char* getFileNameOfMenuOptions(Menu menuApp, uint8_t optionsSelected);

#endif
