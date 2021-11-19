#include "../libs/Menus.h"



struct _Menu{
    
    char* menuOptions[BUFSIZ]; 
    int option;
    int numOptions;
};




//Constructor
Menu initMenu(void){

    Menu menuApp = NULL; 
    
    menuApp= malloc(sizeof(struct _Menu));
    if(menuApp == NULL){
        perror("ERROR::");
        exit(MEM_ERROR);
    }

    menuApp->option = 0;
    menuApp->numOptions = 0;
    return menuApp;
}



//Destructors
Menu freeMenu(Menu menuApp){
    free(menuApp);

    menuApp = NULL;
    return menuApp;
}




//GETTERS
char** getMenuList(Menu menuApp){
    return menuApp->menuOptions;
}



int getOption(Menu menuApp){
    return menuApp->option;
}

int getNumOptions(Menu menuApp){
    return menuApp->numOptions;
}


//SETTER
void setMenuList(Menu menuApp, int state){

	int i;
	menuApp->numOptions = 0;
    const char* list[5][7] = { 
                            {"SHOW CSV FILE", "CHANGE CONFIGURATIONS","EXIT", NULL},
                            {"CHANGE COLOR", "CHANGE WIDOW SIZE", "CHANGE MENU TYPE", "RETURN TO MAIN MENU", "EXIT", NULL},
                            {"ADD COLUMN", "RETURN TO MAIN MENU", "EXIT", NULL},
                            {"WHITE", "RED", "GREEN", "CYAN", "RETURN TO MAIN MENU", "EXIT", NULL}
                        };


    for(i = 0; list[state][i] != (void*)0; i++){
        menuApp->menuOptions[i] = strdup(list[state][i]);
        menuApp->numOptions ++;
    }
	menuApp->menuOptions[i] = NULL;
}



ERROR_CODE setOption(Menu menuApp, int newOption){

    if(menuApp == NULL){
        perror("ERROR::");
        exit(MEM_ERROR);
    }

    menuApp->option = newOption;
    return ERROR_OK;
}


ERROR_CODE setDynamicOption(Menu menuApp, char newOption){

    newOption = tolower(newOption);
    
    if(newOption == 'w')
        menuApp->option --;
    else if(newOption == 's')
        menuApp->option ++;


    if(menuApp->option >= menuApp->numOptions)
        menuApp->option = 0;
    else if(menuApp->option < 0)
        menuApp->option = menuApp->numOptions - 1;

    return ERROR_OK;
}




void printMenu(Menu menuApp){

	puts("");
    for(int i = 0; menuApp->menuOptions[i] != (void*)0; i++)
        printf("\t\t\t[%d]%s\n", i, menuApp->menuOptions[i]);
}



void updateMenu(Menu menuApp, Config configApp){

	puts("");
    for(int i = 0; menuApp->menuOptions[i] != (void*)0; i++){
        
        if(menuApp->option == i)
            printf("\t\t\t%s[██] %s\n", getColorSelection(configApp), menuApp->menuOptions[i]);
        else 
            printf("\t\t\t%s[  ] %s\n", getColor(configApp), menuApp->menuOptions[i]);
    }

	printf("\n\n\n\n %sTO MOVE UP PRESS [W/w], TO MODE DOWN [S/s] AND TO SELECT OPTION PRESS [X/x]\n", getColorSelection(configApp));
	printf("%s", getColor(configApp));
}



void printHeader(void){


    system("clear");
	puts(" ░█████╗░██████╗░██╗░░░██╗███╗░░██╗░█████╗░██╗░░██╗");
	puts("░██╔══██╗██╔══██╗██║░░░██║████╗░██║██╔══██╗██║░░██║");
	puts(" ██║░░╚═╝██████╔╝██║░░░██║██╔██╗██║██║░░╚═╝███████║");
	puts(" ██║░░██╗██╔══██╗██║░░░██║██║╚████║██║░░██╗██╔══██║");
	puts(" ╚█████╔╝██║░░██║╚██████╔╝██║░╚███║╚█████╔╝██║░░██║");
	puts( "░╚════╝░╚═╝░░╚═╝░╚═════╝░╚═╝░░╚══╝░╚═══╝░ ╚═╝░░ ╚╝");
	puts("");
	puts("			██████╗░░█████╗░████████╗░█████╗░░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░");
	puts("			██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗██╔════╝██║░░██║██╔════╝██║░░░░░██║░░░░░");
	puts("			██║░░██║███████║░░░██║░░░███████║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░");
	puts("			██║░░██║██╔══██║░░░██║░░░██╔══██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░");
	puts("			██████╔╝██║░░██║░░░██║░░░██║░░██║██████╔╝██║░░██║███████╗███████╗███████╗");
	puts("			╚═════╝░╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝");
	printf("                                                                                               A.0.1\n");

}

