#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <inttypes.h>
#include "ini.h"
#include "Errors.h"
#include "FilesAndDirs.h"


#define WHITE "\x1B[0m" 
#define RED "\x1B[31m" 
#define GREEN "\x1B[32m" 
#define CYAN "\033[36m"


typedef struct _Config* Config;

Config initConfig(void);

Config freeConfig(Config configToFree);

ERRORS_CODE configureApp(Config configApp);
ERRORS_CODE configCommandSize(Config configApp);

ERRORS_CODE createConfigFile(void);
ERRORS_CODE reconfigureConfigFile(Config configApp);

char* getColor(Config configApp);


ERRORS_CODE setColor(Config configApp);
ERRORS_CODE setWidht(Config configApp);
ERRORS_CODE setHeight(Config configApp);
ERRORS_CODE setNumColor(Config configApp, uint8_t newColor);
ERRORS_CODE setTypeMenu(Config configApp);
#endif