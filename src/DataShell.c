#include "../libs/DataShell.h"


static void exitApp(DataShell app, Menu menuApp, Config configApp);
static void returnMainMenu(DataShell app, Menu menuApp);
static ERROR_CODE showCSVFile(DataShell app, Menu menuApp);
static void reprintData(DataShell app);
static void printData(DataShell app);
static ERROR_CODE setFileName(DataShell app);
static ERROR_CODE addColumn(DataShell app);
static char* getNameNewColumn(void);
static int getInt(char input);
static void getSizeFromInput(Config configApp);
static void reconfigureApp(DataShell app, Menu menuApp, Config configApp, int isWindoSizeChange);



struct _DataShell{
    
    int state;
    size_t columns;
    size_t rows;
    size_t columnsWithData;
    size_t rowsWithData;
    char*** data;
    char fileName[BUFSIZ];

};


//Constructor
DataShell initDataShell(void){


    DataShell app = NULL;
    
    app = malloc(sizeof(struct _DataShell));
    if(app == NULL){
        perror("ERROR::");
        exit(MEM_ERROR);
    }

    app->state = 0;
    app->columns = 8;
    app->rows = 8;
    app->columnsWithData = 8;
    app->rowsWithData = 8;   
    app->data = createMatrixString(app->data, app->rows, app->columns);
    return app;
}


//Destructors
DataShell freeDataShell(DataShell app){
    
    free(app);
    app = NULL;

    return app;
}


//FUNCIONES PRINCIPALES
void selectOption(DataShell app, Menu menuApp){

    int input = -1;

	do {
    
        reprintData(app);
        printMenu(menuApp);
    }while((input =  getInt(getchar())) < 0 && input >= getNumOptions(menuApp) && input == EOF);

    setOption(menuApp, input);

}




void selectOption2(DataShell app, Menu menuApp, Config configApp){
    
    char input = '\0';
	int firstInput = 1;

    do{

        setDynamicOption(menuApp, input);
        reprintData(app);
        updateMenu(menuApp, configApp);

		if(firstInput)
			firstInput = 0;
		else
			clearBuffer();


    }while((input = getchar()) != 'x' && input != 'X' && input != EOF);

}


static int getInt(char input){
       

    if(isdigit(input) && input != '\0')
    {
        return input - '0';
    }
    
    return  -1;
}



//ESTADOS 
// 0 - MENU PRINCIPAL
//  0 - 0 SHOW_CSV_FILE
//  0 - 1 CONFIGURATIONS
//  0 - 2 EXIT
// 1 - MENU DE COLORES
//  1 - (0 - 3) OPCIONES DE COLORES
//  1 - 4 RETURN_TO_MAIN_MENU 
//  1 - 5 EXIT 
// 2 - SHOW_CSV_FILE
//  2 - 0 ADD_COLUMN
//  2 - 1 RETURN_TO_MAIN_MENU
//  2 - 2 EXIT
// 3 - CHANGE_COLOR
// 3 - 0 CHANGE_COLOR 


void dynamicController(DataShell app, Menu menuApp, Config configApp){

	switch(app->state){
      case 0:
          switch(getOption(menuApp)){
              case 0:
                  showCSVFile(app, menuApp);
                  break;
              case 1:
                  app->state = 1;
		          setOption(menuApp, 0);
                  break;
             case 2:
                  exitApp(app, menuApp, configApp);
                  break;
          }
		  break;
      case 1:
          switch(getOption(menuApp)){
              case 0:
                  app->state = 3;
                  break;
              case 1:
                  getSizeFromInput(configApp);
                  reconfigureApp(app, menuApp, configApp, 1);
				  app->state = 1;
				  break;
	          case 2:
		          setMenuType(configApp);
		          reconfigureApp(app, menuApp, configApp, 2);
				  app->state = 0;
		          setOption(menuApp, 0);
				  break;
              case 3:
                  returnMainMenu(app, menuApp);
                  break;
              case 4:
                  exitApp(app, menuApp, configApp);
		          break;
		  }
		  break;
      case 2:
          switch(getOption(menuApp)){
              case 0:
                  addColumn(app);
                  break;
              case 1:
                  returnMainMenu(app, menuApp);
                  break;
              case 2:
                  exitApp(app, menuApp, configApp);
                  break;
          }
		  break;
	  case 3:
		  switch (getOption(menuApp)) {
			  case 0: case 1: case 2: case 3:
				  setNumColor(configApp, getOption(menuApp));
				  reconfigureApp(app, menuApp, configApp, 0);
			      break;
			  case 4:
				  returnMainMenu(app, menuApp);
				  break;
			  case 5:
				  exitApp(app, menuApp, configApp);
				  break;
		  }
		  break;
    }
}










void clearBuffer(void){

	char input;
	while((input = getchar()) != '\n');
}


 






// GETTERS
char*** getMatrixData(DataShell app){
    return app->data;
}


char** getMatrixDataRow(DataShell app, size_t indexRow){

    return app->data[indexRow];
}


int getState(DataShell app){
    return app->state;
}




// SETTER
ERROR_CODE setMatrixData(DataShell app, size_t indexRow, size_t indexColumn, char* newData){

    if(app != NULL)
        app->data[indexRow][indexColumn] = strdup(newData);
    
    return ERROR_OK;

}










//STATICS
static ERROR_CODE showCSVFile(DataShell app, Menu menuApp){

    FILE* csvFile = NULL;
    
    setFileName(app);

    csvFile = newFile(app->fileName, READ);
    if(csvFile == NULL){
       
        csvFile = closeFile(csvFile);
        app->state = 0;
        puts("PRESS ENTER TO RETURN TO MAIN MENU\n");
        getchar();
        return FILE_NOT_FOUND;
    }

    app->data = readCsvFile(csvFile, app->data, &app->rows, &app->rowsWithData, &app->columns, &app->columnsWithData);
    csvFile = closeFile(csvFile);


    app->state = 2;
    return ERROR_OK;
}



static ERROR_CODE setFileName(DataShell app){
    
    
    if(app != NULL){

        puts("ENTER THE NAME OF THE FILE YOU WANT TO SEE\n");
        fgets(app->fileName, sizeof(app->fileName), stdin);
        app->fileName[strcspn(app->fileName, "\n")] = 0;
    }
    return ERROR_OK;
}



static ERROR_CODE addColumn(DataShell app){
    
    FILE* csvFile = NULL;
    
    csvFile = newFile(app->fileName, WRITE);
    if(csvFile == NULL){
        csvFile = closeFile(csvFile);
        app->state = 1;

        return FILE_NOT_FOUND;
    }

    for(size_t i = 0; i < app->rowsWithData; i++){
        
        if(i == 0)
            setMatrixData(app, i, app->columnsWithData, getNameNewColumn());
        else
            setMatrixData(app, i, app->columnsWithData, "NULL");
    }

    app->columnsWithData += 1;

    writeCsvFile(csvFile, app->data, app->rowsWithData, app->columnsWithData);

	csvFile = closeFile(csvFile);
    return ERROR_OK;    
}



static char* getNameNewColumn(void){

    char nameNewColumn[BUFSIZ];
	puts("ENTER THE NAME OF THE NEW COLUMN");
    fgets(nameNewColumn, BUFSIZ, stdin);

    nameNewColumn[strcspn(nameNewColumn, "\n")] = 0;

    return strdup(nameNewColumn);
}



static void returnMainMenu(DataShell app, Menu menuApp) {

	if (app->state == 2){
		app->data = freeMatrixString(app->data, app->rows);
		app->rows = 8;
		app->rowsWithData = 8;
		app->columns = 8;
		app->columnsWithData = 8;
		app->data = createMatrixString(app->data, app->rows, app->columns);
	}

	app->state = 0;
    setOption(menuApp, 0);

}



static void exitApp(DataShell app, Menu menuApp, Config configApp){
    puts("EXIT APP THANKS FOR COMMING =)");

    app->data = freeMatrixString(app->data, app->rows);

   
    menuApp = freeMenu(menuApp);
    app = freeDataShell(app);
    configApp = freeConfig(configApp);
    exit(ERROR_OK);
}



static void reprintData(DataShell app){

    if(app->state == 0 || app->state == 1 || app->state == 3)
        printHeader();
    else if(app->state == 2)
        printData(app);
}








static void printData(DataShell app){

	system("clear");
    printf("\t\t\t\t########%s#############\n\n",app->fileName);
   
    ft_table_t *table = ft_create_table();
	ft_set_border_style(table, FT_DOUBLE2_STYLE);
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    for(size_t rows = 0; rows < app->rowsWithData; rows++){
    
        ft_row_write_ln(table, app->columnsWithData, app->data[rows]);
        ft_set_cell_prop(table, FT_ANY_ROW, rows, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    }

    printf("%s\n", ft_to_string(table));

    ft_destroy_table(table);
    printf("\n\n\n");
}



static void reconfigureApp(DataShell app, Menu menuApp, Config configApp, int isWindoSizeChange){

    FILE* configFile = NULL;

    configFile = newFile("config.ini", WRITE);


    editConfigFile(configFile, getWidth(configApp), getHeight(configApp), getNumColor(configApp), getTypeMenu(configApp));
    configFile = closeFile(configFile);

	configFile = closeFile(configFile);


     
    if(isWindoSizeChange == 1)
        system(createConfigCommandSize(configApp));
	else if(isWindoSizeChange == 0){
	    setColor(configApp);
	    printf("%s", getColor(configApp));
	}


	setOption(menuApp, 0);

}



static void getSizeFromInput(Config configApp){

    char input[BUFSIZ];
    char* pEnd;

    printf("ENTER THE WIDTH SIZE: ");
    fgets(input, BUFSIZ, stdin);
    setWidth(configApp, strtol(input, &pEnd, 10));
    

    printf("ENTER THE HEIGHT SIZE: ");
    fgets(input, BUFSIZ, stdin);
    setHeight(configApp, strtol(input, &pEnd, 10));

}
