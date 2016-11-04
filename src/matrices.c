/*
   ITCR - Investigación de Operaciones

   Multiplicacion de matrices
   Licencia GNU Free Documentation License 1.2 


   referencias:
    manejar estructuras en listas:
    http://fresh2refresh.com/c-programming/c-array-of-structures/

*/
#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


//-------------------variables -----------------------
//global - estaticas
int MAX_INPUT_MATRIX_SIZE = 20;

//variables especificas de este algoritmo

typedef struct {
    int n;
    int m;
} matriz;
char *nodeNames[20] = {"M1","M2","M3","M4","M5","M6","M7","M8","M9","M10","M11","M12","M13","M14","M15","M16","M17","M18","M19","M20"};
char stringRespuesta[100];

matriz inputValues[20] = {{1,2},{2,3},{3,2},{2,7}};
int inputValuesTransform[40];
int cantidadMatrices = 9;

int resultMatrixM[20][20];
int resultMatrixP[20][20];

//variables de todos los problemas

GtkWidget *textInputsMatrix[21][4];
GtkWidget *window;
GtkWidget *resultMatrixMLabels[21][21];
GtkWidget *resultMatrixPLabels[21][21];
GtkWidget *resultadoString0;
GtkWidget *resultadoString1 ; ///aca se tiene que poner el resultado
GtkWidget *resultadoString6 ;
GtkWidget *resultadoString7 ;
GtkWidget *resultadoStringWarning;

GtkWidget *resultScreen;
GtkWidget *inputScreen;
GtkWidget *button;
GtkWidget *cantidadMatricesComboBox;
GtkWidget *labelCantidad;
GtkWidget *resultMatrixMLabelsWidget;
GtkWidget *resultMatrixPLabelsWidget;
GtkGrid    *inputsGrid;



//declaraciones de funcion .h
static void displayAnswer();
static void getTextInputValues();
static void displayAnswer();
static void transformInput();



//---funciones del problema----------------
void resolver ()
{
    //sow screen
    gtk_widget_show(resultadoString0);
    gtk_widget_show(resultadoString1);

    gtk_widget_show(resultMatrixMLabelsWidget);
    gtk_widget_show(resultMatrixPLabelsWidget);
    gtk_widget_show(resultadoString6);
    gtk_widget_show(resultadoString7);
    
    gtk_widget_hide(inputsGrid);
    gtk_widget_hide(inputScreen);
    gtk_widget_hide(labelCantidad);
    gtk_widget_hide(cantidadMatricesComboBox);
    
    //get values
    getTextInputValues();
    transformInput();

    //TODO insert problem functions



    //update answer with values
    displayAnswer();


}

void transformInput ()
{
  for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
  { 
      int referenceIndex =  i * 2; 
      inputValuesTransform[referenceIndex] = inputValues[i].n;
      inputValuesTransform[referenceIndex + 1] = inputValues[i].m;
  }
  for (int i = 0; i < 40; ++i)
  {
      printf(" %d  \n",  inputValuesTransform[i]);
  }

       
}

//----------------funciones de interfaz--------------
void cleanInput()
{
    gtk_widget_hide(resultadoString0);
    gtk_widget_hide(resultadoString1);
    gtk_widget_hide(resultadoStringWarning);

    gtk_widget_hide(resultMatrixMLabelsWidget);
    gtk_widget_hide(resultMatrixPLabelsWidget);
    gtk_widget_hide(resultadoString6);
    gtk_widget_hide(resultadoString7);
    
    
    gtk_widget_show(inputScreen);
    gtk_widget_show(inputsGrid);
    gtk_widget_show(labelCantidad);
    gtk_widget_show(cantidadMatricesComboBox);

}

void setTextInputValues()
{
    
    gtk_combo_box_set_active(GTK_COMBO_BOX(cantidadMatricesComboBox),cantidadMatrices - 1 );
    for (int i = 0; i < cantidadMatrices; ++i)
    { 
        

        char setValueN[10];
        snprintf(setValueN, 10, "%d",  inputValues[i].n);
        char setValueM[10];
        snprintf(setValueM, 10, "%d",  inputValues[i].m);
        gtk_entry_set_text (GTK_ENTRY (textInputsMatrix[i][1]),  setValueN);
        gtk_entry_set_text (GTK_ENTRY (textInputsMatrix[i][3]),  setValueM);; 
      }
      updateInput();
        
}
void showSaveFile(){

  //getTextInputValues();
  
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

      fichero = fopen(filename,"w+");

      if (fichero == NULL) {
        printf( "No se puede crear el fichero.\n" );
      }

      /** Proceso para guardar datos en archivo **/
      char *numeroLlaves =calloc(10, sizeof(char));
      
      //Conversion de tipos para guardar primera linea
      sprintf(numeroLlaves,"%d",cantidadMatrices); // ***********CAMBIAR NUMERO POR plazoProyecto
      //printf("%s \n",numeroLlaves);


      
      char *primerLinea =calloc(20, sizeof(char));

      strcat(primerLinea, numeroLlaves);
      strcat(primerLinea,"\n");

      printf("String:%s\n", primerLinea);
      fputs(primerLinea, fichero); // Escribe primera linea en archivo
      strcpy(primerLinea,"");

      for (int i = 0; i < cantidadMatrices; i++) 
      {
        char *dato =calloc(100, sizeof(char));
        char *valueN =calloc(50, sizeof(char));
        char *valueM =calloc(50, sizeof(char));

        sprintf(valueN, "%d",inputValues[i].n);
        strcat(dato, valueN);
        strcat(dato, " ");
        sprintf(valueM, "%d",inputValues[i].m);
        strcat(dato, valueM);
        strcat(dato, "\n");

        fputs(dato, fichero); // Escribe primera linea en archivo

        strcpy(dato,"");
        strcpy(valueN,"");
        strcpy(valueM,"");
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
   
    char buff[500];
    
    char primeraLinea[50];
    

    //Leer hasta que no hay lineas
      
      fgets(buff, 500, (FILE*)infile);


      //Lee primera Linea 
       strcpy(primeraLinea, buff);
    
        /***************************************************************/
        
        /** Inicializa variables**/
        cantidadMatrices = atoi(primeraLinea);

        //gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox),indiceComboObjetos );
        printf("Llaves: %d\n", cantidadMatrices);
          
      
      
    /********************** Proceso para leer y guardar matriz ******************************/      
    // Lee resto de líneas
    int indiceFilas = 0;
    char line[100];
    
    
    while (fgets(buff, 500, (FILE*)infile)){
            char *st =calloc(200, sizeof(char));
            strcpy(st, buff);
            char *ch =calloc(100, sizeof(char));
            //printf("Split \"%s\"\n", st);
            ch = strtok(st, " ");

            inputValues[indiceFilas].n = atoi(ch);
            while (ch != NULL) {
              inputValues[indiceFilas].m = atoi(ch);
              ch = strtok(NULL, " ,");

            }


            indiceFilas++;
      
    }
    /*for (int i = 0; i < tamDatos; ++i)
    {
      printf("%s %f\n", datos[i].name, datos[i].value); 
    }*/
    /*****************************************************************************************/
    
    // Cerrar Archivo
    fclose(infile);
    }
    gtk_widget_destroy(dialog);
  
  setTextInputValues();
  
}

//this function replaces the textInputsMatrix with curret values
void getTextInputValues()
{
    cantidadMatrices = gtk_combo_box_get_active (GTK_COMBO_BOX(cantidadMatricesComboBox));
    cantidadMatrices = cantidadMatrices + 1;
    printf(" %d \n ",  cantidadMatrices);     
    gtk_widget_hide(resultadoStringWarning);
    for (int i = 0; i < cantidadMatrices; ++i)
    {
        
            gchar *currentNValue;
            currentNValue = gtk_entry_get_text(GTK_ENTRY(textInputsMatrix[i][1]));
            gchar *currentMValue;
            currentMValue = gtk_entry_get_text(GTK_ENTRY(textInputsMatrix[i][3]));

            int newValueN = atoi(currentNValue);
            int newValueM = atoi(currentMValue);
            
            inputValues[i].n = newValueN;
            inputValues[i].m = newValueM;
            if( i > 0)
            {
              if(inputValues[i].n != inputValues[i -1].m)
              {
                  inputValues[i].n = inputValues[i -1].m;
                  gtk_widget_show(resultadoStringWarning);
              }
            }      
        
    }
    for (int i = 0; i < cantidadMatrices; ++i)
    {
        printf(" %d  x   %d  \n",  inputValues[i].n , inputValues[i].m);
    }

}

void displayAnswer()
{
    strcat(stringRespuesta, "Place holder text"); //TODO replace with anwers, comment this
    gtk_label_set_text(resultadoString1, stringRespuesta);


    for (int i = 1; i < 21; ++i)
    {
        for (int j = 1; j < 21; ++j)
        { 
            char tempStringDisplayM[10];
            snprintf(tempStringDisplayM, 10, "%d",resultMatrixM[i-1][j-1]);   
            gtk_label_set_text(GTK_LABEL(resultMatrixMLabels[i][j]), tempStringDisplayM);

            char tempStringDisplayP[10];
            snprintf(tempStringDisplayP, 10, "%d",resultMatrixP[i-1][j-1]);   
            gtk_label_set_text(GTK_LABEL(resultMatrixPLabels[i][j]), tempStringDisplayP);
              
        }
    }
    
    for (int iClean = 0; iClean < 21; ++iClean)
    {
        for (int jClean = 0; jClean < 21; ++jClean)
        { 
             
          if(iClean > cantidadMatrices  || jClean > cantidadMatrices )
          {
            gtk_widget_hide (resultMatrixMLabels[iClean][jClean]);
            gtk_widget_hide (resultMatrixPLabels[iClean][jClean]);
          }
          else
          {
              gtk_widget_show (resultMatrixMLabels[iClean][jClean]);
              gtk_widget_show (resultMatrixPLabels[iClean][jClean]);
            }
           
        }
    }
        
}
//Esta funcion esconde los inputs para cambiar tamaño de matriz
void updateInput()
{
    cantidadMatrices = gtk_combo_box_get_active (GTK_COMBO_BOX(cantidadMatricesComboBox));
    cantidadMatrices = cantidadMatrices + 1;

    for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
           if(i <= cantidadMatrices -1)
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



void closeWindow()
{
    gtk_main_quit();
}


///-------------------------------main-----------------
int main(int argc, char *argv[])
{
    
    
    GtkBuilder      *builder;
    GtkGrid    *inputsGrid;
    


    gtk_init(&argc, &argv);

    
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "src/matrices.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "matricesWindow"));
    gtk_builder_connect_signals(builder, NULL);


    cantidadMatricesComboBox = GTK_WIDGET(gtk_builder_get_object(builder, "comboboxtext4"));
    cantidadMatrices = gtk_combo_box_get_active (GTK_COMBO_BOX(cantidadMatricesComboBox));
    labelCantidad = GTK_WIDGET(gtk_builder_get_object(builder, "box9"));

    
    inputsGrid =  GTK_GRID(gtk_builder_get_object(builder, "gridInput2"));

    inputScreen =  GTK_WIDGET(gtk_builder_get_object(builder, "boxInput2"));
    resultScreen =  GTK_WIDGET(gtk_builder_get_object(builder, "boxResult"));

    resultadoString0 =  GTK_WIDGET(gtk_builder_get_object(builder, "labelRespuestaMate1"));
    resultadoString1 =  GTK_WIDGET(gtk_builder_get_object(builder, "labelRespuestaMate2"));
    resultadoString6 =  GTK_WIDGET(gtk_builder_get_object(builder, "label6"));
    resultadoString7 =  GTK_WIDGET(gtk_builder_get_object(builder, "label7"));
    resultadoStringWarning =  GTK_WIDGET(gtk_builder_get_object(builder, "labelRespuestaMate3"));
    
    resultMatrixMLabelsWidget  =  GTK_WIDGET(gtk_builder_get_object(builder, "respuestaM"));
    resultMatrixPLabelsWidget  =  GTK_WIDGET(gtk_builder_get_object(builder, "respuestaP"));

    //assign  save and load buttons callback
    //TODO uncomment
    button = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));

    button = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
    g_signal_connect(button, "clicked", G_CALLBACK(showOpenFile), window);


    for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
        {
            for (int j = 0; j < 4; ++j)
            { 
                if(j == 2 )
                {
                  textInputsMatrix[i][j] = gtk_label_new ("  x  " );

                }
                else if(j  ==0 )
                {
                  textInputsMatrix[i][j] = gtk_label_new (nodeNames[i]);
                }
                else
                {
                    

                  textInputsMatrix[i][j] = gtk_entry_new ();
                  gtk_entry_set_max_length (GTK_ENTRY (textInputsMatrix[i][j]),4);
                  gtk_entry_set_text (GTK_ENTRY (textInputsMatrix[i][j]), "1");
                  
                  gtk_entry_set_max_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 4);
                  gtk_entry_set_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 4);
                  
                }
                gtk_widget_show (textInputsMatrix[i][j]);
                gtk_grid_attach (inputsGrid,textInputsMatrix[i][j],j,i + 1,1,1);
                //GtkWidget *entry;
                //add one input and store reference
                
               
            }
        }


    for (int i = 0; i < 21; ++i)
    {
        for (int j = 0; j < 21; ++j)
        { 
            char tempString[10];
               
            if(i==0 && j==0)
            {
               resultMatrixMLabels[i][j] = gtk_label_new ("  ");
            }
            else if(i==0)
            {
                
                snprintf(tempString, 10, "%d", j );
                resultMatrixMLabels[i][j] = gtk_label_new (tempString);
            }
            else if(j==0)
            {
                snprintf(tempString, 10, "%d", i );
                resultMatrixMLabels[i][j] = gtk_label_new (tempString);
            }
            else
            {
                resultMatrixMLabels[i][j] = gtk_label_new (" - " );
                
            }
            gtk_widget_show (resultMatrixMLabels[i][j]);
            gtk_grid_attach (resultMatrixMLabelsWidget,resultMatrixMLabels[i][j],i,j,1,1);
            
          
           
        }
    }

    for (int i = 0; i < 21; ++i)
    {
        for (int j = 0; j < 21; ++j)
        { 
            char tempString[10];
               
            if(i==0 && j==0)
            {
               resultMatrixPLabels[i][j] = gtk_label_new ("  ");
            }
            else if(i==0)
            {
                
                snprintf(tempString, 10, "%d", j );
                resultMatrixPLabels[i][j] = gtk_label_new (tempString);
            }
            else if(j==0)
            {
                snprintf(tempString, 10, "%d", i );
                resultMatrixPLabels[i][j] = gtk_label_new (tempString);
            }
            else
            {
                resultMatrixPLabels[i][j] = gtk_label_new (" - " );
                
            }
            gtk_widget_show (resultMatrixPLabels[i][j]);
            gtk_grid_attach (resultMatrixPLabelsWidget,resultMatrixPLabels[i][j],i,j,1,1);
            
          
           
        }
    }



    //hide answer
    gtk_widget_hide(resultadoString0);
    gtk_widget_hide(resultadoString1);
    gtk_widget_hide(resultadoStringWarning);
    gtk_widget_hide(resultMatrixMLabelsWidget);
    gtk_widget_hide(resultMatrixPLabelsWidget);
    gtk_widget_hide(resultadoString6);
    gtk_widget_hide(resultadoString7);
    
    gtk_widget_hide(inputsGrid);
    gtk_widget_show(inputsGrid);
    gtk_widget_show(labelCantidad);
    gtk_widget_show(cantidadMatricesComboBox);

    //gtk_widget_show(inputScreen);
    //gtk_widget_show(resultScreen);
    


    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

  gtk_window_set_title(GTK_WINDOW(window), "CSS Window");
  g_signal_connect(G_OBJECT (window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

/*---------------- CSS ----------------------------------------------------------------------------------------------------*/
  provider = gtk_css_provider_new ();
  display = gdk_display_get_default ();
  screen = gdk_display_get_default_screen (display);
  gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  gsize bytes_written, bytes_read;

  const gchar* ccsContent = "src/mochila.css";  

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


