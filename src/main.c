
#include "../libs/DataShell.h"

int main(void){
 

    DataShell app = NULL;
    Menu menuApp = NULL;
    Config configApp = NULL;

    configApp = initConfig();    
    app = initDataShell();
    menuApp = initMenu();

    configureApp(configApp);

    while(1){

	    setMenuList(menuApp, getState(app));
		if(getTypeMenu(configApp))
            selectOption2(app, menuApp, configApp);
		else
            selectOption(app, menuApp);
		clearBuffer();
        dynamicController(app, menuApp, configApp);
    }

      
}
