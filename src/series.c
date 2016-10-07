/*
   ITCR - Investigación de Operaciones

   Proyecto 4

   Adrian Chacon
   Genesis Salazar
*/
#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//------------variables del problema --------
float probGaneACasa = 0.57;//tomada de la interfaz
float probPerderACasa = 0;//calculado

float probGaneAVisita = 0.49;//tomada de la interfaz
float probPerderAVisita = 0;//calculado

float probGaneBCasa = 0.51;//calculado
float probPerderBCasa = 0;//calculado

float probGaneBVisita = 0.43;//calculado
float probPerderBVisita = 0;//calculado
//usar esta variable para los valores de la respuesta
float answerMatrix[20][20] = {{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0}};//TODO cambiar, datos de prueb

int totalJuegos = 4;//TODO cambiar, datos de prueb
//variables para la localidad de juego
char *lugarJuegos[30] = {"casa", "casa", "visita", "visita", "visita",
						"casa", "casa", "casa", "casa", "casa",
						"casa", "casa", "casa", "casa", "casa",
						"casa", "casa", "casa", "casa", "casa",
						"casa", "casa", "casa", "casa", "casa",
						"casa", "casa", "casa", "casa", "casa"};
char *comparingValue = "casa";
char *changeValue = "visita";

//----------Variables de interfaz -------

GtkWidget   *window;
GtkGrid   *resultGrid;
GtkWidget *resultScreen;
GtkWidget *inputScreen;
GtkWidget *button;

//intefaz con valores de variables
GtkWidget *comboJuegos;//numero de juegos
GtkWidget *probCasaInput;
GtkWidget *probVisitaInput;
GtkWidget *lugarJuegosButtons[30];
GtkWidget *lugarJuegosLabels[30];
GtkWidget *resultLabelsMatrix[20][20];


//functions reference

static void getTextInputValues();
static void displayAnswer();
void series();
void imprimir();
char* calcularLocalia();

void series(){

    for (int i = 0; i < totalJuegos + 2; i++)
    {
        for (int j = 0; j < totalJuegos + 2 ; j++)
        {
            if(i==0 && j==0){
                answerMatrix[i][j]=-0.0;
            }
            else{
                if(j==0){
                    answerMatrix[i][j]=1.0;       
                }
                else if(i==0){
                    answerMatrix[i][j]=0.0;
                }
                else{
                    if(calcularLocalia(i,j) == "casa"){
                        
                        answerMatrix[i][j]= probGaneBVisita * answerMatrix[i-1][j] +  probGaneACasa* answerMatrix[i][j-1];    
                    }
                    else{
                        answerMatrix[i][j]= probGaneBCasa  * answerMatrix[i-1][j] + probGaneAVisita* answerMatrix[i][j-1];   
                    }
                }
            }
        }
    }
    imprimir();
}

void imprimir(){
    for (int i = 0; i < totalJuegos+1; ++i)
    {
        for (int j = 0; j < totalJuegos+1; ++j)
        {
            printf("%0.3f\t", answerMatrix[i][j]);

        }
        printf("\n");
    }
}

char* calcularLocalia(int i, int j){
    return lugarJuegos[(totalJuegos-i + 1) + (totalJuegos-j + 1)];
}



void resolver (GtkWidget* button, gpointer window)
{
    gtk_widget_hide(inputScreen);
    gtk_widget_show(resultScreen);
    getTextInputValues();
    

    //TODO call funtion to solve problem
    
    series();

    //cleanLabels();
    displayAnswer();
}

void cleanInput()
{
    gtk_widget_hide(resultScreen);
    gtk_widget_show(inputScreen);
    void updateInput();

}
void updateInput()
{
    totalJuegos = gtk_combo_box_get_active (GTK_COMBO_BOX(comboJuegos));
    int calcularTotalJuegos = totalJuegos * 2;
    for (int i = 0; i < 30; ++i)
    {
        for (int j = 0; j < 30; ++j)
        {
           if(i <= calcularTotalJuegos)
            {
               gtk_widget_show(GTK_WIDGET (lugarJuegosButtons[i]));
               gtk_widget_show(GTK_WIDGET (lugarJuegosLabels[i]));
            }
            else
            {
                gtk_widget_hide(GTK_WIDGET (lugarJuegosButtons[i]));
                gtk_widget_hide(GTK_WIDGET (lugarJuegosLabels[i]));
                lugarJuegos[i] = comparingValue;
                gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[i]), lugarJuegos[i]); 
            }    
        }
    }

}
void displayAnswer()
{   
    for (int i = 1; i < 19; ++i)
    {
        for (int j = 1; j < 19; ++j)
        { 
            if(i==1 && j==1)
            {

            }
            else
            {
            	 char tempStringDisplay[10];
            	snprintf(tempStringDisplay, 10, "%0.3f",answerMatrix[i-1][j-1]);   
            	gtk_label_set_text(GTK_LABEL(resultLabelsMatrix[i][j]), tempStringDisplay);
            }  
        }
    }
    
    for (int iClean = 0; iClean < 20; ++iClean)
    {
        for (int jClean = 0; jClean < 20; ++jClean)
        { 
             
          if(iClean > totalJuegos + 2 || jClean > totalJuegos + 2)
          {
            gtk_widget_hide (resultLabelsMatrix[iClean][jClean]);
          }
          else
          {
              gtk_widget_show (resultLabelsMatrix[iClean][jClean]);
            }
           
        }
    } 
    
}

void showSaveFile(){

  getTextInputValues();
  
  GtkWidget *dialog;
  GtkFileChooser *chooser;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
  gint res;

  dialog = gtk_file_chooser_dialog_new ("Save File",
                                        window,
                                        action,
                                        ("_Cancel"),
                                        GTK_RESPONSE_CANCEL,
                                        ("_Save"),
                                        GTK_RESPONSE_ACCEPT,
                                        NULL);
  chooser = GTK_FILE_CHOOSER (dialog);

  gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

  res = gtk_dialog_run (GTK_DIALOG (dialog));

  if (res == GTK_RESPONSE_ACCEPT)
    {
      printf("ENtro if\n");

      char *filename = gtk_file_chooser_get_filename (chooser);

      FILE *fichero;
      //char stringSave[300];
      char* lineas[50];
      char texto[100];

      fichero = fopen(filename,"w+");

      if (fichero == NULL) {
        printf( "No se puede crear el fichero.\n" );
      }

      /** Proceso para guardar datos en archivo **/
      char *probAGanaCasa =calloc(10, sizeof(char));
      char *probAGanaVisita =calloc(10, sizeof(char));
      char *totalJuegosGanar =calloc(10, sizeof(char));
      
      //Conversion de tipos para guardar primera linea
      sprintf(probAGanaCasa,"%f",probGaneACasa); // ***********CAMBIAR NUMERO POR plazoProyecto
      sprintf(probAGanaVisita, "%f",probGaneAVisita); // **************CAMBIAR NUMERO POR tipo
      sprintf(totalJuegosGanar, "%d",totalJuegos); //*********** CAMBIAR NUMERO POR vidaUtil
      printf("%s %s %s\n",probAGanaCasa,probAGanaVisita,totalJuegosGanar );


      
      char *primerLinea =calloc(20, sizeof(char));

      strcat(primerLinea, probAGanaCasa);
      strcat(primerLinea," ");
      strcat(primerLinea, probAGanaVisita);
      strcat(primerLinea," ");
      strcat(primerLinea, totalJuegosGanar);
      strcat(primerLinea,"\n");

      printf("String:%s\n", primerLinea);
      fputs(primerLinea, fichero); // Escribe primera linea en archivo
      strcpy(primerLinea,"");

      for (int i = 0; i < totalJuegos*2-1; i++) 
      {
        fputs(lugarJuegos[i], fichero); // Escribe primera linea en archivo
        fputs("\n",fichero);
      }
      //printf("stringSave: %s\n", stringSave);
      //fputs(stringSave, fichero);
      if (fclose(fichero)!=0)
        printf( "Problemas al cerrar el fichero\n" );

      /** Fin proceso  **/
    
    }

    gtk_widget_destroy(dialog);
}

//Open File
static void showOpenFile(GtkWidget* button, gpointer window)
{
        //Contruccion Dialog

	GtkWidget *dialog;
	
  dialog = gtk_file_chooser_dialog_new("Chosse a file", GTK_WINDOW(window), 
				GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_OK, GTK_RESPONSE_OK, 
				GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);

	gtk_widget_show_all(dialog);

        //Localizar el directorio
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(dialog), g_get_home_dir());

        //Guarda la respuesta al hacer Ok/Cancel
	gint resp = gtk_dialog_run(GTK_DIALOG(dialog));

	if(resp == GTK_RESPONSE_OK)
		{
			
		FILE *infile;
		
		
		infile = fopen(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)), "r");
	 
		char buff[255];
        char *token ;
		char *primeraLinea[255];
    

		//Leer hasta que no hay lineas
		  
			fgets(buff, 255, (FILE*)infile);


			//Lee primera Linea	
			   strcpy(primeraLinea, buff);
			
         /******* Inicia proceso de split línea para obtener datos ******/
          token = strtok (buff," ");
          int index = 0;

          /** Obtiene datos de primera linea y la guarda en un array **/
          while (token != NULL)
          {
              if(index <3){
                primeraLinea[index] = token;  
              }
              token = strtok (NULL, " ");
              index++;
          }
          /***************************************************************/
          
          /** Inicializa variables**/
          probGaneACasa = atof(primeraLinea[0]);
          probGaneAVisita = atof(primeraLinea[1]);
          totalJuegos = atof(primeraLinea[2]);

          //gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox),indiceComboObjetos );
          printf("Prob casa: %f\n", probGaneACasa);
          printf("Prob visita: %f\n", probGaneAVisita);
          printf("Total Juegos: %d\n", totalJuegos);
          char *tempProbCasa[10];
          char *tempProbVisita[10];
          snprintf(tempProbCasa, 10, "%0.3f", probGaneACasa);
          snprintf(tempProbVisita, 10, "%0.3f", probGaneAVisita);

        gtk_entry_set_text (GTK_ENTRY (probCasaInput), tempProbCasa);
        gtk_entry_set_text (GTK_ENTRY (probVisitaInput), tempProbVisita);
   		gtk_combo_box_set_active(GTK_COMBO_BOX(comboJuegos),totalJuegos );
   		 for (int i = 0; i < 30; ++i)
    	{
        
    		gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[i]), lugarJuegos[i]);
    	}
    	updateInput();
          
    /********************** Proceso para leer y guardar matriz ******************************/      
    int indiceFilas = 0;
    

    // Lee resto de líneas
		while (fgets(buff, 255, (FILE*)infile)){

            lugarJuegos[indiceFilas] = buff;
            indiceFilas++;
            printf("Lugar: %s", buff);

			
		}
    /*****************************************************************************************/

		// Cerrar Archivo
		fclose(infile);
		}
	  gtk_widget_destroy(dialog);
  
  //setTextInputValues();
	
}


//this function replaces the textInputsMatrix with curret values
void getTextInputValues()
{
    totalJuegos = gtk_combo_box_get_active (GTK_COMBO_BOX(comboJuegos));
    gchar *inputValueACasaString = gtk_entry_get_text(GTK_ENTRY(probCasaInput));
    probGaneACasa = atof(inputValueACasaString);
    gchar *probGaneAVisitaString = gtk_entry_get_text(GTK_ENTRY(probVisitaInput));
    probGaneAVisita = atof(probGaneAVisitaString);
    

    //TODO remove this console lines
    printf("input values: \n Porcentajes: \n Casa %f  Visita %f  \n",probGaneACasa, probGaneAVisita);
    for (int i = 0; i < 20; ++i)
    {
        printf(" %s", lugarJuegos[i]);
    }
    printf("\n");
}
//--------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    
    
    GtkBuilder  *builder;
    GtkGrid    *inputsGrid;


    gtk_init(&argc, &argv);


    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "src/series.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "seriesWindow"));
    gtk_builder_connect_signals(builder, NULL);

    probCasaInput = GTK_WIDGET(gtk_builder_get_object(builder, "probACasaInput"));
    probVisitaInput = GTK_WIDGET(gtk_builder_get_object(builder, "probaAVisitaInput"));

    comboJuegos = GTK_WIDGET(gtk_builder_get_object(builder, "totalJuegosCombo"));
    totalJuegos = gtk_combo_box_get_active (GTK_COMBO_BOX(comboJuegos)); //TODO remove comment
  
    inputsGrid =  GTK_GRID(gtk_builder_get_object(builder, "gridInput"));
    resultGrid =  GTK_GRID(gtk_builder_get_object(builder, "gridRespuesta"));
    //gtk_widget_set_name (GTK_WIDGET(resultGrid), "gridRespuesta");

    inputScreen =  GTK_WIDGET(gtk_builder_get_object(builder, "boxInput"));
    resultScreen =  GTK_WIDGET(gtk_builder_get_object(builder, "boxResult"));

    button = GTK_WIDGET(gtk_builder_get_object(builder, "open_button"));
    g_signal_connect(button, "clicked", G_CALLBACK(showOpenFile), window);	

    gtk_widget_hide(resultScreen);
    gtk_widget_show(inputScreen);
    

    for (int i = 0; i < 30; ++i)
    {
        

    	lugarJuegosLabels[i] = gtk_grid_get_child_at(GTK_GRID(inputsGrid),1 ,i+2);
         lugarJuegosButtons[i] = gtk_grid_get_child_at(GTK_GRID(inputsGrid),0 ,i+2);
    }

    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 20; ++j)
        { 
                char tempString[10];
               
            if(i==0 && j==0)
            {
               resultLabelsMatrix[i][j] = gtk_label_new ("Tabla[i][j]");
            }
            else if(i==1 && j==1)
            {
               resultLabelsMatrix[i][j] = gtk_label_new ("Null");
            }
            else if(i==0)
            {
                
                snprintf(tempString, 10, "%d", j - 1);
                resultLabelsMatrix[i][j] = gtk_label_new (tempString);
            }
            else if(j==0)
            {
                snprintf(tempString, 10, "%d", i - 1);
                resultLabelsMatrix[i][j] = gtk_label_new (tempString);
            }
            else
            {
                resultLabelsMatrix[i][j] = gtk_label_new ("0.001" );
                
            }
            gtk_widget_show (resultLabelsMatrix[i][j]);
            gtk_grid_attach (resultGrid,resultLabelsMatrix[i][j],i,j,1,1);
            
          
           
        }
    }


    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

     gtk_window_set_title(GTK_WINDOW(window), "Series Deportivas");
     g_signal_connect(G_OBJECT (window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

    /*---------------- CSS ----------------------------------------------------------------------------------------------------*/
  	provider = gtk_css_provider_new ();
  	display = gdk_display_get_default ();
  	screen = gdk_display_get_default_screen (display);
  	gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  	gsize bytes_written, bytes_read;
  	const gchar* ccsContent = "src/series.css";  
  	GError *error = 0;
   	gtk_css_provider_load_from_path (provider,
                                      g_filename_to_utf8(ccsContent, strlen(ccsContent), &bytes_read, &bytes_written, &error),
                                 NULL);
  	



  	g_object_unref (provider);
    g_object_unref(builder);
    gtk_widget_show(window);                
    gtk_main();
    return 0;

}

void closeWindow()
{
    gtk_main_quit();
}

//function for binterface input buttons, used to change location value
void changePlace0(){
	//change value in array
	char *currentLabelValue = lugarJuegos[0];
	if(strcmp(comparingValue, currentLabelValue) == 0)
	{
		lugarJuegos[0] = changeValue;
	}
	else
	{
		lugarJuegos[0] = comparingValue;
	}
	//update string in interface
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[0]), lugarJuegos[0]);
}

void changePlace1(){
	char *currentLabelValue = lugarJuegos[1];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[1] = changeValue;
	}else{
		lugarJuegos[1] = comparingValue;
	}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[1]), lugarJuegos[1]);
}

void changePlace2(){
	char *currentLabelValue = lugarJuegos[2];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[2] = changeValue;
	}else{
		lugarJuegos[2] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[2]), lugarJuegos[2]);
}

void changePlace3(){
	char *currentLabelValue = lugarJuegos[3];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[3] = changeValue;
	}else{
		lugarJuegos[3] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[3]), lugarJuegos[3]);
}

void changePlace4(){
	char *currentLabelValue = lugarJuegos[4];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[4] = changeValue;
	}else{
		lugarJuegos[4] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[4]), lugarJuegos[4]);
}

void changePlace5(){
	char *currentLabelValue = lugarJuegos[5];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[5] = changeValue;
	}else{
		lugarJuegos[5] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[5]), lugarJuegos[5]);
}

void changePlace6(){
	char *currentLabelValue = lugarJuegos[6];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[6] = changeValue;
	}else{
		lugarJuegos[6] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[6]), lugarJuegos[6]);
}

void changePlace7(){
	char *currentLabelValue = lugarJuegos[7];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[7] = changeValue;
	}else{
		lugarJuegos[7] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[7]), lugarJuegos[7]);
}

void changePlace8(){
	char *currentLabelValue = lugarJuegos[8];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[8] = changeValue;
	}else{
		lugarJuegos[8] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[8]), lugarJuegos[8]);
}

void changePlace9(){
	char *currentLabelValue = lugarJuegos[9];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[9] = changeValue;
	}else{
		lugarJuegos[9] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[9]), lugarJuegos[9]);
}

void changePlace10(){
	char *currentLabelValue = lugarJuegos[10];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[10] = changeValue;
	}else{
		lugarJuegos[10] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[10]), lugarJuegos[10]);
}

void changePlace11(){
	char *currentLabelValue = lugarJuegos[11];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[11] = changeValue;
	}else{
		lugarJuegos[11] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[11]), lugarJuegos[11]);
}

void changePlace12(){
	char *currentLabelValue = lugarJuegos[12];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[12] = changeValue;
	}else{
		lugarJuegos[12] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[12]), lugarJuegos[12]);
}

void changePlace13(){
	char *currentLabelValue = lugarJuegos[13];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[13] = changeValue;
	}else{
		lugarJuegos[13] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[13]), lugarJuegos[13]);
}

void changePlace14(){
	char *currentLabelValue = lugarJuegos[14];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[14] = changeValue;
	}else{
		lugarJuegos[14] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[14]), lugarJuegos[14]);
}

void changePlace15(){
	char *currentLabelValue = lugarJuegos[15];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[15] = changeValue;
	}else{
		lugarJuegos[15] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[15]), lugarJuegos[15]);
}

void changePlace16(){
	char *currentLabelValue = lugarJuegos[16];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[16] = changeValue;
	}else{
		lugarJuegos[16] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[16]), lugarJuegos[16]);
}

void changePlace17(){
	char *currentLabelValue = lugarJuegos[17];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[17] = changeValue;
	}else{
		lugarJuegos[17] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[17]), lugarJuegos[17]);
}

void changePlace18(){
	char *currentLabelValue = lugarJuegos[18];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[18] = changeValue;
	}else{
		lugarJuegos[18] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[18]), lugarJuegos[18]);
}

void changePlace19(){
	char *currentLabelValue = lugarJuegos[19];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[19] = changeValue;
	}else{
		lugarJuegos[19] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[19]), lugarJuegos[19]);
}
void changePlace20(){
	char *currentLabelValue = lugarJuegos[20];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[20] = changeValue;
	}else{
		lugarJuegos[20] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[20]), lugarJuegos[20]);
}

void changePlace21(){
	char *currentLabelValue = lugarJuegos[21];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[21] = changeValue;
	}else{
		lugarJuegos[21] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[21]), lugarJuegos[21]);
}

void changePlace22(){
	char *currentLabelValue = lugarJuegos[22];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[22] = changeValue;
	}else{
		lugarJuegos[22] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[22]), lugarJuegos[22]);
}

void changePlace23(){
	char *currentLabelValue = lugarJuegos[23];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[23] = changeValue;
	}else{
		lugarJuegos[23] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[23]), lugarJuegos[23]);
}

void changePlace24(){
	char *currentLabelValue = lugarJuegos[24];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[24] = changeValue;
	}else{
		lugarJuegos[24] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[24]), lugarJuegos[24]);
}

void changePlace25(){
	char *currentLabelValue = lugarJuegos[25];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[25] = changeValue;
	}else{
		lugarJuegos[25] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[25]), lugarJuegos[25]);
}

void changePlace26(){
	char *currentLabelValue = lugarJuegos[26];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[26] = changeValue;
	}else{
		lugarJuegos[26] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[26]), lugarJuegos[26]);
}

void changePlace27(){
	char *currentLabelValue = lugarJuegos[27];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[27] = changeValue;
	}else{
		lugarJuegos[27] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[27]), lugarJuegos[27]);
}

void changePlace28(){
	char *currentLabelValue = lugarJuegos[28];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[28] = changeValue;
	}else{
		lugarJuegos[28] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[28]), lugarJuegos[28]);
}

void changePlace29(){
	char *currentLabelValue = lugarJuegos[29];
	if(strcmp(comparingValue, currentLabelValue) == 0){
		lugarJuegos[29] = changeValue;
	}else{
		lugarJuegos[29] = comparingValue;}
   	gtk_label_set_text (GTK_LABEL (lugarJuegosLabels[29]), lugarJuegos[29]);
}

