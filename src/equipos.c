/*
   ITCR - Investigación de Operaciones

   Algoritmos 1/0, bounded , unbounded basados en ejemplos de codigo disponibles de la pagina https://rosettacode.org/wiki/Rosetta_Code,
   Licencia GNU Free Documentation License 1.2 
*/
#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>



//variables de todos los problemas
int MAX_INPUT_MATRIX_SIZE = 10;
GtkWidget *textInputsMatrix[20][4];
GtkWidget   *window;
GtkWidget *resultInputsMatrix[20][20];

//variables de interfaz
GtkGrid    *resultGrid;
GtkWidget *resultScreen;
GtkWidget *inputScreen;


//variables especificas de este programa
int tipo;//0=0/1, 1= bounded, 2= unbounded

double inflacion;
int plazoProyecto;
int vidaUtil;
int matrizValores[20][4];
int tablaCalculos[20][4];
char *nombreObjetos[20] = {"A1", "A2", "A3", "A4", "A5", "A6","A7","A8", "A9", "A10", "11","12","13","14","15","16" ,"17", "18", "19", "20"};
char *listaProximos[30] = {"1,3", "2,4" , "5", "4", "5"};
char stringNombres[100];
int costosPorTiempo[30] = {640,510,380,260,130,0};
int contaNombres = 0;
int comboSelect ;
int comboBoxPlazoSelected ;
int comboBoxVidaUtilSelect ;
GtkWidget *button;
GtkWidget *comboBox;
GtkWidget *comboBoxPlazo;
GtkWidget *comboBoxVidaUtil;
GtkWidget *dialog;


//delcaraciones de funciones
int max(int a, int b);
void separarColumnas(int fila);
static void getTextInputValues();
static void setTextInputValues();
static void cleanLabels();
static void displayAnswer();
void resolver (GtkWidget* button, gpointer window);
static void showOpenFile(GtkWidget* button, gpointer window);


char stringInicial[100];
char stringSujeto[100];

char linea[100];



//name_object nombres[] = {{"A1"}, {"A2"}, {"A3"}, {"A4"}, {"A5"}, {"A6"},{"A7"},{"A8"}, {"A9"}};

 

 
//--------------------------------------------------------Switch ComboBox
void resolver (GtkWidget* button, gpointer window)
{
    gtk_widget_hide(inputScreen);
    gtk_widget_show(resultScreen);

    //getTextInputValues();
    









    cleanLabels();
    displayAnswer();
}

/** Save file **/
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
      void getTextInputValues();  // Actualiza para obtener los ultimos datos ingresados por el usuario

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
      char cantMaxChar[5];
      char tipoChar[5];
      char cantObjChar[5];

      //itoa(plazoProyecto,cantMaxChar,10); 
      //itoa(tipo,tipoChar,10); 
      //itoa(vidaUtil,cantObjChar,10); 
      //Conversion de tipos para guardar primera linea
      sprintf(cantMaxChar,"%d",plazoProyecto); // ***********CAMBIAR NUMERO POR plazoProyecto
      sprintf(tipoChar, "%d",tipo); // **************CAMBIAR NUMERO POR tipo
      sprintf(cantObjChar, "%d",vidaUtil); //*********** CAMBIAR NUMERO POR vidaUtil
      printf("%s %s %s\n",cantMaxChar,tipoChar,cantObjChar );


      char primerLinea[20];
      strcat(primerLinea, cantMaxChar);
      strcat(primerLinea," ");
      strcat(primerLinea, tipoChar);
      strcat(primerLinea," ");
      strcat(primerLinea, cantObjChar);
      strcat(primerLinea,"\n");

      printf("String:%s\n", primerLinea);
      fputs(primerLinea, fichero); // Escribe primera linea en archivo
      strcpy(primerLinea,"");

      for (int i = 0; i < vidaUtil; i++) // ***** Cambiar 5 por vidaUtil
      {
        for (int j = 0; j < 4; j++)
        {
          char valor[10];
          sprintf(valor, "%d", matrizValores[i][j]);

          //printf("%d\n", matrizValores[i][j]);
          strcat(texto, valor);
          strcpy(valor,"");
          if (j<3)
          {
            strcat(texto," ");
          }
        }
        strcat(texto, "\n");
        fputs(texto, fichero);
        strcpy(texto,"");
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
    char *token;
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
          plazoProyecto = atoi(primeraLinea[0]);
          tipo = atoi(primeraLinea[1]);
          vidaUtil = atoi(primeraLinea[2]);
          int indiceComboObjetos = tipo - 1;
          if(indiceComboObjetos == -1)
          {
            indiceComboObjetos = 2;
          }
          gtk_combo_box_set_active(GTK_COMBO_BOX(comboBoxVidaUtil),vidaUtil - 1 );
          gtk_combo_box_set_active(GTK_COMBO_BOX(comboBoxPlazo),plazoProyecto - 1 );
          //gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox),indiceComboObjetos );
          printf("Cantidad máxima: %d\n", plazoProyecto);
          printf("Tipo algortimo: %d\n", tipo);
          printf("Cantidad objetos: %d\n", vidaUtil);
          
    /********************** Proceso para leer y guardar matriz ******************************/      
    int indiceFilas = 0;
    strcpy(linea,"");

    // Lee resto de líneas
		while (fgets(buff, 255, (FILE*)infile)){

            strcpy(linea, buff);
            //printf("Linea: %s\n", buff);
            if(indiceFilas < vidaUtil){
            separarColumnas(indiceFilas); 
            //printf("Objeto: %s\n",  nombres[0].name); 
            }

            indiceFilas++;
            strcpy(linea,"");
			
		}
    /*****************************************************************************************/

    /** Imprime matriz  **/
    printf("Matriz\n");

    for(int i=0;i<vidaUtil;i++){
         for(int j=0;j<4;j++){
          //printf("%d %d\n", i,j);
        printf("%d ", matrizValores[i][j]); 
      }
      printf("\n");
    }

    /******* Inicia proceso de split línea para obtener datos ******/
          char* nombre;
          nombre = strtok (stringNombres," ");
          int indice = 0;

          /** Obtiene datos de primera linea y la guarda en un array **/
          while (nombre != NULL)
          {
              if(indice <4){
                nombreObjetos[indice] = nombre;  
              }
              nombre = strtok (NULL, " ");
              indice++;
          }

    /****************************/
		// Cerrar Archivo
		fclose(infile);
		}
	  gtk_widget_destroy(dialog);
  
  setTextInputValues();
	
}

void separarColumnas(int fila){
  
  char *token;
  int indiceColumnas =0;
  /**Agarra el primer token separado por espacio**/
  token = strtok (linea," ");  
  
  while (token != NULL )
  {
    /***Guarda el token en la matriz****/
    if(indiceColumnas==0){
      // agarra los nombres de los objetos para guardarlos en la lista
        strcat(stringNombres,token);
        strcat(stringNombres," ");
        //printf("String: %s\n", stringNombres);
    }
    int valor = atoi(token);
    matrizValores[fila][indiceColumnas] = valor;
    indiceColumnas++;
    token = strtok (NULL, " ");
      
    
  }
   
}

//Esta funcion esconde los inputs para cambiar tamaño de matriz
void updateInput()
{
    comboBoxVidaUtilSelect = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxVidaUtil));
    g_print("%d",comboBoxVidaUtilSelect);
    for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
           if(i <= comboBoxVidaUtilSelect)
            {
               gtk_widget_show(GTK_WIDGET (textInputsMatrix[i][j]));
            }
            else
            {
                 gtk_widget_hide(GTK_WIDGET (textInputsMatrix[i][j])); 
            }    
        }
    }

}

//this function replaces the textInputsMatrix with curret values
void getTextInputValues()
{
    comboBoxVidaUtilSelect = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxVidaUtil));
    vidaUtil = comboBoxVidaUtilSelect + 1;
    comboBoxPlazoSelected = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxPlazo));
    plazoProyecto = comboBoxPlazoSelected + 1;
     printf("objetos: %d\n", vidaUtil);
      printf("pesio: %d\n", plazoProyecto);
    for (int i = 0; i < vidaUtil; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if(j == 0)
            {
               matrizValores[i][j] = 0;
            }
            else
            {
              gchar *currentTextInputText;
              currentTextInputText = gtk_entry_get_text(GTK_ENTRY(textInputsMatrix[i][j]));
              int newValue = atoi(currentTextInputText);
              matrizValores[i][j] = newValue;

              if(i <= comboBoxVidaUtilSelect)
              {
                 gtk_widget_show(GTK_WIDGET (textInputsMatrix[i][j]));
              }
              else
              {
                   gtk_widget_hide(GTK_WIDGET (textInputsMatrix[i][j])); 
              }
            }        
        }
    }
}
void setTextInputValues()
{

    for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
    {
        for (int j = 1; j < 4; ++j)
        { 
            if(i < vidaUtil)
              {
                 char newChar[4];
                  snprintf(newChar, 4, "%d", matrizValores[i][j]);
                  gtk_entry_set_text (GTK_ENTRY (textInputsMatrix[i][j]), newChar);
                 gtk_widget_show(GTK_WIDGET (textInputsMatrix[i][j]));
              }
              else
              {
                   gtk_widget_hide(GTK_WIDGET (textInputsMatrix[i][j])); 
              }
        }
         
    }
    for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
    {
       
         if(i < vidaUtil)
        {
             gtk_widget_show(GTK_WIDGET (textInputsMatrix[i][0]));
              gtk_button_set_label (GTK_BUTTON (textInputsMatrix[i][0]), nombreObjetos[i]);
        }
        else
        {
             gtk_widget_hide(GTK_WIDGET (textInputsMatrix[i][0])); 
        }
    }
    strcpy(stringNombres,"");
}
void cleanLabels()
{
    for (int i = 1; i < 20; ++i)
    {
        for (int j = 0; j < 20; ++j)
        { 
          gtk_label_set_text(GTK_LABEL(resultInputsMatrix[i][j])," - ");
             gtk_widget_show(resultInputsMatrix[i][j]);
        }
    }
}
void cleanInput()
{
    gtk_widget_hide(resultScreen);
    gtk_widget_show(inputScreen);

}
void closeWindow()
{
    gtk_main_quit();
}
void displayAnswer()
{   
    vidaUtil = 5;//comentar esta linea para que concuerde con el valor de la interfaz
    for (int i = 0; i <= vidaUtil; i++) 
    {
        char costoTiempo[20] = "";
        snprintf(costoTiempo, 50, "%d", costosPorTiempo[i]);
        char tiempo[20] = "";
        snprintf(tiempo, 50, "%d", i);
        gtk_label_set_text(GTK_LABEL(resultInputsMatrix[0][i + 1]), tiempo);
        gtk_label_set_text(GTK_LABEL(resultInputsMatrix[1][i + 1]), costoTiempo);
        gtk_label_set_text(GTK_LABEL(resultInputsMatrix[2][i + 1]), listaProximos[i]);

    }
    for (int iClean = 0; iClean < 20; ++iClean)
    {
        for (int jClean = 0; jClean < 20; ++jClean)
        { 
             
          if(iClean > 2 || jClean > vidaUtil + 1)
          {
            gtk_widget_hide (resultInputsMatrix[iClean][jClean]);
          }
          else if (iClean > 1)
          {
              gtk_widget_show (resultInputsMatrix[iClean][jClean]);
            }
           
        }
    }
    
}
//--------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    
    
    GtkBuilder      *builder;
    GtkGrid    *inputsGrid;
    


    gtk_init(&argc, &argv);

    
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "src/equipos.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "mochilaWindow"));
    gtk_builder_connect_signals(builder, NULL);


    comboBoxPlazo = GTK_WIDGET(gtk_builder_get_object(builder, "comboboxtext1"));
    comboBoxPlazoSelected = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxPlazo));

    comboBoxVidaUtil = GTK_WIDGET(gtk_builder_get_object(builder, "comboboxtext4"));
    comboBoxVidaUtilSelect = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxVidaUtil));
    
    button = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
    g_signal_connect(button, "clicked", G_CALLBACK(resolver), window);

    button = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
    g_signal_connect(button, "clicked", G_CALLBACK(showOpenFile), window);
  
    
    inputsGrid =  GTK_GRID(gtk_builder_get_object(builder, "grid2"));
    resultGrid =  GTK_GRID(gtk_builder_get_object(builder, "gridRespuesta"));
    gtk_widget_set_name (GTK_WIDGET(resultGrid), "gridRespuesta");

    inputScreen =  GTK_WIDGET(gtk_builder_get_object(builder, "boxInput"));
    resultScreen =  GTK_WIDGET(gtk_builder_get_object(builder, "boxResult"));


    gtk_widget_hide(resultScreen);
    gtk_widget_show(inputScreen);
    
 
   

    for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < 3; ++j)
        { 
            if(j == 0)
            {
                char indexString[10];
                snprintf(indexString, 10, "%d",  i +1 );
                
                
                textInputsMatrix[i][j] =  gtk_label_new ("");
                gtk_label_set_text(GTK_LABEL(textInputsMatrix[i][j]), indexString);
                gtk_button_set_label (GTK_BUTTON (textInputsMatrix[i][j]), nombreObjetos[i]);
                gtk_widget_show (textInputsMatrix[i][j]);
                gtk_grid_attach (inputsGrid,textInputsMatrix[i][j],j,i + 1,1,1);

            }
            else
            {
              textInputsMatrix[i][j] = gtk_entry_new ();
              gtk_entry_set_max_length (GTK_ENTRY (textInputsMatrix[i][j]),4);
              gtk_entry_set_text (GTK_ENTRY (textInputsMatrix[i][j]), "1");
              gtk_widget_show (textInputsMatrix[i][j]);
              gtk_entry_set_max_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 4);
              gtk_entry_set_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 4);
              gtk_grid_attach (inputsGrid,textInputsMatrix[i][j],j,i + 1,1,1);
            }
            
           
        }
    }

    for (int i = 1; i < 20; ++i)
    {
        for (int j = 0; j < 20; ++j)
        { 
             
          resultInputsMatrix[i][j] = gtk_label_new (" - " );
          gtk_widget_show (resultInputsMatrix[i][j]);
          gtk_grid_attach (resultGrid,resultInputsMatrix[i][j],i,j,1,1);
           
        }
    }

    



    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

     gtk_window_set_title(GTK_WINDOW(window), "Problema remplazo de equipos");
     g_signal_connect(G_OBJECT (window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

    /*---------------- CSS ----------------------------------------------------------------------------------------------------*/
  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gsize bytes_written, bytes_read;

  const gchar* ccsContent = "src/equipos.css";  

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

