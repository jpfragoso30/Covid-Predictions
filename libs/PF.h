#ifndef PF_H
#define PF_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include "Menu.h"
#include "Errors.h"
#include "CsvProcessing.h"
#include "Memory.h"
#include "Euler.h"
#include "Config.h"
#include "Ploter.h"

typedef struct _PF *PF;

typedef enum states
{

    MENU_P,
    PREDICCION,
    PLOTER,
    CONFIGURACIONES,
    SUBMENUS,
    PLOTER_SELECT_FILE,
    CONFIG_MENU,
    COLORS_MENU,

} STATES;

// Constructor
PF initPF(uint8_t endValue, float width);

// Destructor
PF freePF(PF PfToFree);


// SETTERS
ERRORS_CODE setValueInTiempo(PF pf, float newValue, uint8_t index);
ERRORS_CODE setValueInY(PF pf, float newValue, uint8_t index);
ERRORS_CODE setTiempoCero(PF pf, float xCero);
ERRORS_CODE setYCero(PF pf, float yCero);
ERRORS_CODE setNextState(PF pf, STATES newProcess);
ERRORS_CODE setOptionFromState(PF pf);


// GETTERS
float *getTiempo(PF pf);
float *getY(PF pf);
float getEndValue(PF pf);
float getWidth(PF pf);
float getTiempoValue(PF pf, uint8_t index);
float getYValue(PF pf, uint8_t index);
Menu getMenuStruct(PF pf);
CsvProcessing getCsvProcessingStruct(PF pf);
Config getConfigStruct(PF pf);

// CONTROLADOR
ERRORS_CODE controlador(PF pf);

//REINICIA LA APP
void restartApp(PF pf, char* nameExecutable);
#endif
