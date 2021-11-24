#include "../libs/Menu.h"

static ERRORS_CODE validateFile(const char *fileName);
static ERRORS_CODE createMenuFiles(Menu menu);

struct _Menu
{

    char **menuOptions;
    uint8_t columns;
    uint8_t optionSelected;
    uint8_t numOptions;
};

Menu initMenu(void)
{

    Menu newMenu = NULL;
    newMenu = malloc(sizeof(struct _Menu));

    if (!newMenu)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, MEM_ERROR);
        exit(MEM_ERROR);
    }

    newMenu->numOptions = 0;
    newMenu->optionSelected = 0;

    newMenu->columns = 10;
    newMenu->menuOptions = createStringArray(newMenu->menuOptions, newMenu->columns);

    return newMenu;
}

Menu freeMenu(Menu menuToFree)
{

#if DEBUG_MODE
    puts("free freeMenu");
#endif

    if (!menuToFree)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    menuToFree->menuOptions = freeStringArray(menuToFree->menuOptions);

    free(menuToFree);
    menuToFree = NULL;

    return menuToFree;
}

// SETTERS

ERRORS_CODE setMenuOptions(Menu menu, TYPEMENU typemenu)
{

    const char *list[4][7] = {
        {"MAKE PREDICTION", "PLOTER", "CHANGE CONFIGURATIONS", "EXIT", NULL},
        {"REPLOT", "MAIN MENU", "EXIT", NULL},
        {"CHANGE COLOR", "CHANGE WIDOW SIZE", "CHANGE MENU TYPE", "RETURN TO MAIN MENU", "EXIT", NULL},
        {"WHITE", "RED", "GREEN", "CYAN", "RETURN TO MAIN MENU", "EXIT", NULL}};

    if (!menu)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    menu->numOptions = 0;

    if (typemenu == MENU_REPLOT_FILE)
        createMenuFiles(menu);
    else
    {

        for (uint8_t i = 0; list[typemenu][i] != (void *)0; i++, menu->numOptions++)
        {

            menu->menuOptions[i] = createStrignSpace(menu->menuOptions[i], list[typemenu][i]);
            menu->menuOptions[i] = strdup(list[typemenu][i]);
        }
    }

    menu->menuOptions[menu->numOptions] = NULL;

    if (menu->numOptions == 0)
        return EMPTY_DIR;

    return ERROR_OK;
}

ERRORS_CODE setMenuSelection(Menu menuApp, uint8_t newSelection)
{

    if (!menuApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    menuApp->optionSelected = newSelection;

    return ERROR_OK;
}

// GETTERS

uint8_t getNumOptions(Menu menuApp)
{

    if (!menuApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return menuApp->numOptions;
}

char *getFileNameOfMenuOptions(Menu menuApp, uint8_t optionsSelected)
{

    if (!menuApp)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    return menuApp->menuOptions[optionsSelected];
}

// VISTAS

void printMenu(Menu menuApp)
{

    puts("");

    for (uint8_t i = 0; menuApp->menuOptions[i] != (void *)0; i++)
        printf("\t\t\t[%d]%s\n", i + 1, menuApp->menuOptions[i]);
}

void updateMenu(Menu menuApp, char *color, char *colorSelection)
{

    puts("");
    for (uint8_t i = 0; menuApp->menuOptions[i] != (void *)0; i++)
    {

        if (menuApp->optionSelected == i)
            printf("\t\t\t%s[██] %s\n", colorSelection, menuApp->menuOptions[i]);
        else
            printf("\t\t\t%s[  ] %s\n", color, menuApp->menuOptions[i]);
    }

    printf("\n\n\n\n %sTO MOVE UP PRESS [W/w], TO MODE DOWN [S/s] AND TO SELECT OPTION PRESS [X/x]\n", colorSelection);
    puts(color);
}

void printHeader(void)
{

    system("clear");
    puts("░█████╗░░█████╗░██╗░░░██╗██╗██████╗░");
    puts("██╔══██╗██╔══██╗██║░░░██║██║██╔══██╗");
    puts("██║░░╚═╝██║░░██║╚██╗░██╔╝██║██║░░██║");
    puts("██║░░██╗██║░░██║░╚████╔╝░██║██║░░██║");
    puts("╚█████╔╝╚█████╔╝░░╚██╔╝░░██║██████╔╝");
    puts("░╚════╝░░╚════╝░░░░╚═╝░░░╚═╝╚═════╝░");

    puts("\t\t██████╗░██████╗░███████╗██████╗░██╗░█████╗░████████╗██╗░█████╗░███╗░░██╗░██████╗");
    puts("\t\t██╔══██╗██╔══██╗██╔════╝██╔══██╗██║██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║██╔════╝");
    puts("\t\t██████╔╝██████╔╝█████╗░░██║░░██║██║██║░░╚═╝░░░██║░░░██║██║░░██║██╔██╗██║╚█████╗░");
    puts("\t\t██╔═══╝░██╔══██╗██╔══╝░░██║░░██║██║██║░░██╗░░░██║░░░██║██║░░██║██║╚████║░╚═══██╗");
    puts("\t\t██║░░░░░██║░░██║███████╗██████╔╝██║╚█████╔╝░░░██║░░░██║╚█████╔╝██║░╚███║██████╔╝");
    puts("\t\t╚═╝░░░░░╚═╝░░╚═╝╚══════╝╚═════╝░╚═╝░╚════╝░░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░");
}

// STATICS

static ERRORS_CODE createMenuFiles(Menu menu)
{

    DIR *dr = NULL;
    struct dirent *en;

    if (!menu)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, EMPTY_STRUCT);
        exit(EMPTY_STRUCT);
    }

    dr = opendir("./Covid-Predictions/CsvResults/");

    if (dr == NULL)
    {
        fprintf(stderr, "ERROR: %s %d %d", __FILE__, __LINE__, INVALID_DIR);
        exit(INVALID_DIR);
    }

    while ((en = readdir(dr)) != NULL)
    {

        if (validateFile(en->d_name) == ERROR_OK)
        {

            if (menu->numOptions >= menu->columns)
            {
                menu->menuOptions = setMoreColumnsString(menu->menuOptions, menu->columns);
                menu->columns *= 2;
            }

            menu->menuOptions[menu->numOptions] = createStrignSpace(menu->menuOptions[menu->numOptions], en->d_name);
            menu->menuOptions[menu->numOptions] = strdup(en->d_name);
            menu->numOptions++;
        }
    }

    closedir(dr);
    return ERROR_OK;
}

static ERRORS_CODE validateFile(const char *fileName)
{

    const char *coincidence = strstr(fileName, ".csv");

    if (!coincidence)
        return INVALID_FILE;
    if (strcmp(".csv", coincidence) == 0 || strcmp(".CSV", coincidence) == 0)
        return ERROR_OK;

    return INVALID_FILE;
}
