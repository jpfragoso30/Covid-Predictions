#include <stdio.h>
#include <stdlib.h>
#include "../libs/PF.h"



int main(int argc, char* argv[]){

    PF pf = initPF(10, .100);


    setMenuOptions(getMenuStruct(pf), MENU_PRINCIPAL);

    

    setTiempoCero(pf, 0);
    setYCero(pf, 1);
    

    if(configureApp(getConfigStruct(pf)) != ERROR_OK)
        restartApp(pf, argv[0]);
    
    
    while (TRUE){

        controlador(pf);
        if(getTypeMenu(getConfigStruct(pf)) == TRUE)
            setOptionFromState(pf);
    }
    
    

    return ERROR_OK;   
}