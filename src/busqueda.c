/*
   ITCR - Investigación de Operaciones

   Arboles de busqueda
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

typedef struct {
    char *name;
    float value;
} Item;

float answerMatrixA[20][20] = {{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0}};//TODO cambiar, datos de prueb
int answerMatrixR[20][20] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};//TODO cambiar, datos de prueb
//Item datos[20] = {{"Harrison", 0.18},{"Lennon" ,0.32},{"McCartney", 0.39},{"Starr", 0.11}};
Item datos[20] = {{"Carpenter", 0.05},{"Cash" ,0.07},{"Cabain", 0.01},{"Harrison", 0.35},{"Hendrix", 0.09},
          {"Joplin" ,0.23},{"Lennon", 0.15},{"Morrison", 0.04},{"Presley", 0.01}};
int tamDatos = 9;
int columnaInicial = 2;

char linea[300];

//variables de todos los problemas
int MAX_INPUT_MATRIX_SIZE = 29;
GtkWidget *textInputsMatrix[20][2];
GtkWidget   *window;
GtkWidget *resultLabelsMatrixA[29][29];//utiliza estas dos para las respuestas
GtkWidget *resultLabelsMatrixR[29][29];

//variables de interfaz

GtkWidget *resultScreen;
GtkWidget *inputScreen;
GtkWidget *button;
GtkWidget *comboBoxNumero;
GtkGrid    *inputsGrid;
GtkWidget *labelInput;
GtkGrid *resultGridA;
GtkGrid *resultGridR;
//variables especificas de este algoritmo
int numeroLlaves = 9;


//declaraciones de funcion .h
bool verificarDatos();
bool estaOrdenada();
void ordenarDatos();
void setTablaInicial();
float calcularCasilla(int row, int col);
void calcularValoresTabla();
float sumarProbabilidades(int row,int col);
float ordenar(float*valores, int largo, int row, int col);
int getIndex(float number, float* array, int largo);
float sumaValores();
void calcularProbabilidades();
void imprimirA();
void imprimirR();
void formarString();

static void displayAnswer();
static void getTextInputValues();
static void displayAnswer();






//---funciones del problema----------------

// FUNCION PRINCIPAL DE LA LOGICA
void busquedaArboles(){
  if(verificarDatos() == false){
    printf("%s\n", "La suma de probabilidades es diferente de 1");
    calcularProbabilidades();
  }
  if(estaOrdenada() == false){
    printf("%s\n", "LOs datos no estan ordenados");
    ordenarDatos();
  }
  setTablaInicial();
  calcularValoresTabla();
  imprimirA();
  imprimirR();
  columnaInicial = 2;
}

// Inicializa las tablas A y R
void setTablaInicial(){
  for (int i = 0; i < tamDatos+1; i++)
  {
    for (int j = 0; j < tamDatos+1; j++)
    {
      if(i==j){
        answerMatrixA[i][j] = 0.0;
        answerMatrixR[i][j] = 0;
      }
      else if(i== j-1){
        answerMatrixA[i][j] = datos[i].value;
        answerMatrixR[i][j] = j;  
      }
      else{
        answerMatrixA[i][j] = 0.0;  
        answerMatrixR[i][j] = 0;  
      }
    }
  }
}

// Calcula la tabla A de los costos minimos, junto con la tabla R
void calcularValoresTabla(){
  int contadorFila = 0;
    for (int i = 0; i < tamDatos+1; ++i)
    {
      for (int j = columnaInicial; j < tamDatos+1; ++j)
      {
        answerMatrixA[contadorFila][j] = calcularCasilla(contadorFila,j);
        contadorFila++;
      }
      contadorFila=0;
      columnaInicial++;
    }
  
}

// Realiza el metodo PUM PUM para calcular el costo minimo.
float calcularCasilla(int row, int col){ //  0,  2
  float numeros[col-row];
  int contaFilas = 0;
  for (int j = row; j < col; ++j)
  {
    numeros[contaFilas] = answerMatrixA[row][j];
    contaFilas++;
    //printf("%f\n",  answerMatrixA[row][j]);
  }
  contaFilas = 0;
  for (int i = row; i < col; ++i)
  {
    
    //printf("%d %d\n",i+1, col );
    //printf("%f\n", numeros[contaFilas]);
    //printf("%f\n",  answerMatrixA[i+1][col]);
    numeros[contaFilas] = numeros[contaFilas] + answerMatrixA[i+1][col];
    contaFilas++;
//    printf("SUma: %f\n", numeros[i]);
  }
  //for (int i = 0; i < col-row; i++)
  //{
    //printf("%f\n", numeros[i]);
  //}
  
  return ordenar(numeros,col-row, row, col) + sumarProbabilidades(row,col);
  
}

// Ordena los costos (sin probabilidades sumadas) para obtener el menor de ellos para el metodo PUM PUM
// Ademas construye la tabla R con el k ganador
float ordenar(float*valores, int largo, int row, int col){
  float aux;
  float auxiliar[largo];
  memcpy(auxiliar,valores,sizeof(auxiliar)); 

  /*for (int i = 0; i < largo; ++i)
  {
    printf("%f\n", valores[i]);
  }*/

  for (int i = 0; i < largo-1; i++)
  {
    for (int j = i+1; j < largo; j++)
    {
      if(valores[j] < valores[i]){
        aux = valores[j];
        valores[j] = valores[i];
        valores[i] = aux;
      }
    }
  }
/*
  for (int i = 0; i < largo; ++i)
  {
    printf("%f ", auxiliar[i]);
  }
  printf("\n");
  printf("%d %d: %d \n",row,col, getIndex(valores[0], auxiliar, largo) +row);*/
  answerMatrixR[row][col] = getIndex(valores[0], auxiliar, largo)+row+1;
  return valores[0];

}

// Ordena los datos de menor a mayor
void ordenarDatos(){
  Item aux;
  for (int i = 0; i < tamDatos-1; i++)
  {
    for (int j = i+1; j < tamDatos; j++)
    {
      if(strcmp(datos[j].name,datos[i].name) < 0){
        aux = datos[j];
        datos[j] = datos[i];
        datos[i] = aux;
      }
    }
  }
}

// Verifica si la lista de datos esta ordenada
bool estaOrdenada(){
  char* ref = datos[0].name;
  for (int i = 1; i < tamDatos-1; ++i)
  {
    if(strcmp(ref,datos[i].name) > 0){
      return false;
    }
  }
  return true;

}

// Suma las probabilidades dependiendo de la casilla donde se encuentre
float sumarProbabilidades(int row,int col){
  float suma = 0;
  for (int i = row; i < col; ++i)
  {
    suma = suma + datos[i].value;
  }
  return suma;
}

// Obtiene el indice de un numero , que es equivalente al k ganador para construir la tabla R
int getIndex(float number, float* array, int largo){
  for (int i = 0; i < largo; ++i)
  {
    if(number == array[i]){return i;}
  }
}


// Indica si los datos son probabilidades o no
bool verificarDatos(){
  float suma = 0;
  for (int i = 0; i < tamDatos; i++)
  {
    suma += datos[i].value;
  }
  printf("%f\n", suma);
  if(suma == 1.0f){ 
    return true;
  }
  else{ 
    return false;
  }
}

void calcularProbabilidades(){
  float total = sumaValores();

  for (int i = 0; i < tamDatos; ++i)
  {
    datos[i].value = datos[i].value / total;
    //printf("%f\n", datos[i].value);
  }
}

float sumaValores(){
  float suma = 0;

  for (int i = 0; i < tamDatos; ++i)
  {
    suma = suma + datos[i].value;
  }
  return suma;
}

void imprimirA(){
  for (int i = 0; i < tamDatos+1; ++i)
  {
    for (int j = 0; j < tamDatos+1; ++j)
    {
      printf("%0.3f\t", answerMatrixA[i][j]);
    }
    printf("\n");
  }

  
}

void imprimirR(){
  for (int i = 0; i < tamDatos+1; ++i)
  {
    for (int j = 0; j < tamDatos+1; ++j)
    {
      printf("%d\t", answerMatrixR[i][j]);
    }
    printf("\n");
  }
}

void formarString(){
      char* stringDatos =calloc(3000, sizeof(char));
      char *value =calloc(50, sizeof(char));
      char *llave =calloc(50, sizeof(char));

      for (int i = 0; i < tamDatos; ++i)
      {
        strcat(stringDatos, "Key");
        sprintf(llave, "%d ",i);
        strcat(stringDatos, llave);
        strcat(stringDatos, datos[i].name);
        sprintf(value, "%f",datos[i].value);
        strcat(stringDatos,"\t");
        strcat(stringDatos, value);
        strcat(stringDatos,"\n");
        strcat(value,"");
      }
      //printf("%s\n", stringDatos);
    }

//---funciones de interfaz----------------
//llamada a todas las funciones para resolver el problema
void resolver (GtkWidget* button, gpointer window)
{
    
    gtk_widget_show(resultScreen);
    //gtk_widget_hide(inputScreen); //TODO comment
    //TODO uncomment
    gtk_widget_hide(labelInput);
    gtk_widget_hide(comboBoxNumero);
    gtk_widget_hide(inputsGrid);
    getTextInputValues();
    
    busquedaArboles();

    //cleanLabels();
    displayAnswer();
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
      sprintf(numeroLlaves,"%d",tamDatos); // ***********CAMBIAR NUMERO POR plazoProyecto
      //printf("%s \n",numeroLlaves);


      
      char *primerLinea =calloc(20, sizeof(char));

      strcat(primerLinea, numeroLlaves);
      strcat(primerLinea,"\n");

      printf("String:%s\n", primerLinea);
      fputs(primerLinea, fichero); // Escribe primera linea en archivo
      strcpy(primerLinea,"");

      for (int i = 0; i < tamDatos; i++) 
      {
        char *dato =calloc(100, sizeof(char));
        char *value =calloc(50, sizeof(char));

        strcat(dato, datos[i].name);
        strcat(dato, " ");
        sprintf(value, "%f",datos[i].value);
        strcat(dato, value);
        strcat(dato, "\n");

        fputs(dato, fichero); // Escribe primera linea en archivo

        strcpy(dato,"");
        strcpy(value,"");
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
        tamDatos = atoi(primeraLinea);

        //gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox),indiceComboObjetos );
        printf("Llaves: %d\n", tamDatos);
          
      
      
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
            datos[indiceFilas].name = ch;
            while (ch != NULL) {
              printf("%s\n", ch);
              datos[indiceFilas].value = atof(ch);
              ch = strtok(NULL, " ,");

            }


            indiceFilas++;
      
    }
    /*for (int i = 0; i < tamDatos; ++i)
    {
      printf("%s %f\n", datos[i].name, datos[i].value); 
    }*/
    /*****************************************************************************************/
    numeroLlaves = tamDatos;
    // Cerrar Archivo
    fclose(infile);
    }
    gtk_widget_destroy(dialog);
  
  setTextInputValues();
  
}

//this function replaces the textInputsMatrix with curret values
void getTextInputValues()
{
    numeroLlaves = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxNumero));
    numeroLlaves = numeroLlaves + 1;
    printf(" %d \n ",  numeroLlaves);     
    for (int i = 0; i < numeroLlaves; ++i)
    {
        
            gchar *currentTextInputTextName;
            currentTextInputTextName = gtk_entry_get_text(GTK_ENTRY(textInputsMatrix[i][0]));
            gchar *currentTextInputTextValue;
            currentTextInputTextValue = gtk_entry_get_text(GTK_ENTRY(textInputsMatrix[i][1]));

            float newValue = atof(currentTextInputTextValue);
            
            datos[i].name = currentTextInputTextName;
            datos[i].value = newValue;      
        
    }
    for (int i = 0; i < numeroLlaves; ++i)
    {
        printf(" %s  ",  datos[i].name);
        printf(" %f  \n",  datos[i].value);
    }

}
void displayAnswer()
{   
     //for a
    printf(" %d \n ",  numeroLlaves);
    for (int i = 1; i < numeroLlaves + 2; ++i)
    {
        for (int j = 1; j < numeroLlaves + 2; ++j)
        { 
            
              char tempStringDisplay[10];
              snprintf(tempStringDisplay, 10, "%0.3f",answerMatrixA[i-1][j-1]);   
              gtk_label_set_text(GTK_LABEL(resultLabelsMatrixA[i][j]), tempStringDisplay);
              gtk_widget_show (resultLabelsMatrixA[j][i]);
             
        }
    }
    //for R
    
    for (int i = 1; i < numeroLlaves + 2; ++i)
    {
        for (int j = 1; j < numeroLlaves + 2; ++j)
        { 
            
              char tempStringDisplay[10];
              snprintf(tempStringDisplay, 10, "%d",answerMatrixR[i-1][j-1]);   
              gtk_label_set_text(GTK_LABEL(resultLabelsMatrixR[i][j]), tempStringDisplay);
              gtk_widget_show (resultLabelsMatrixR[j][i]);
             
        }
    }
    
    for (int iClean = 0; iClean < MAX_INPUT_MATRIX_SIZE; ++iClean)
    {
        for (int jClean = 0; jClean < MAX_INPUT_MATRIX_SIZE; ++jClean)
        { 
             
          if( jClean > numeroLlaves + 1||  iClean > numeroLlaves + 1 )
          {
            gtk_widget_hide (resultLabelsMatrixA[iClean][jClean]);
             gtk_widget_hide (resultLabelsMatrixR[iClean][jClean]);
          }
          else
          {
              gtk_widget_show (resultLabelsMatrixA[iClean][jClean]);
              gtk_widget_show (resultLabelsMatrixR[iClean][jClean]);
            }
           }
    }
    
    
}


//Esta funcion esconde los inputs para cambiar tamaño de matriz
void updateInput()
{
    numeroLlaves = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxNumero));
    numeroLlaves = numeroLlaves + 1;
    printf(" %d \n ",  numeroLlaves);

    for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
           if(i <= numeroLlaves -1)
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
void cleanInput()
{
    gtk_widget_hide(resultScreen);
   // gtk_widget_show(inputScreen);//TODO comment

    //TODO uncomment
    gtk_widget_show(inputsGrid);
    gtk_widget_show(labelInput);
    gtk_widget_show(comboBoxNumero);

}
void closeWindow()
{
    gtk_main_quit();
}

void setTextInputValues()
{
    
    gtk_combo_box_set_active(GTK_COMBO_BOX(comboBoxNumero),numeroLlaves - 1 );
    for (int i = 0; i < numeroLlaves; ++i)
    { 
        gtk_entry_set_text (GTK_ENTRY (textInputsMatrix[i][0]),  datos[i].name);

        char setValue[10];
        snprintf(setValue, 10, "%0.3f",  datos[i].value);
        gtk_entry_set_text (GTK_ENTRY (textInputsMatrix[i][1]), setValue);
        gtk_widget_show(GTK_WIDGET (textInputsMatrix[i][0]));
        gtk_widget_show(GTK_WIDGET (textInputsMatrix[i][1])); 
      }
        
}

//------MAIN--------------------------------------------------------------------
int main(int argc, char *argv[])
{
    
    
    GtkBuilder      *builder;
    
    


    gtk_init(&argc, &argv);

    
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "src/busqueda.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "mochilaWindow"));
    gtk_builder_connect_signals(builder, NULL);


    comboBoxNumero = GTK_WIDGET(gtk_builder_get_object(builder, "comboCantidad"));
    numeroLlaves = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxNumero));
    numeroLlaves = numeroLlaves + 1;

    
    button = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
    //g_signal_connect(button, "clicked", G_CALLBACK(resolver), window);

    button = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
    g_signal_connect(button, "clicked", G_CALLBACK(showOpenFile), window);
    
    labelInput =  GTK_WIDGET(gtk_builder_get_object(builder, "Label2"));
    
    inputsGrid =  GTK_GRID(gtk_builder_get_object(builder, "gridInput"));
    resultGridA =  GTK_GRID(gtk_builder_get_object(builder, "gridA"));
    resultGridR =  GTK_GRID(gtk_builder_get_object(builder, "gridR"));
    

    inputScreen =  GTK_WIDGET(gtk_builder_get_object(builder, "box8"));
    resultScreen =  GTK_WIDGET(gtk_builder_get_object(builder, "boxResult"));


    gtk_widget_hide(resultScreen);
    //gtk_widget_show(inputScreen);//TODO comment
    //TODO uncomment
    gtk_widget_show(inputsGrid);
    
 
   

    for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < 2; ++j)
        { 
          textInputsMatrix[i][j] = gtk_entry_new ();
          gtk_entry_set_max_length (GTK_ENTRY (textInputsMatrix[i][j]),6);
          if(j == 0)
          {
            gtk_entry_set_text (GTK_ENTRY (textInputsMatrix[i][j]), "Identificador");

            gtk_entry_set_max_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 20);
            gtk_entry_set_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 20);
            gtk_entry_set_max_length (GTK_ENTRY (textInputsMatrix[i][j]),20);
          }
          else
          {
            gtk_entry_set_text (GTK_ENTRY (textInputsMatrix[i][j]), "1.0");
            gtk_entry_set_max_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 10);
            gtk_entry_set_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 10);
            gtk_entry_set_max_length (GTK_ENTRY (textInputsMatrix[i][j]),10);
          }
         
          gtk_widget_show (textInputsMatrix[i][j]);
          gtk_grid_attach (inputsGrid,textInputsMatrix[i][j],j,i + 1,1,1);
            
        }  
    }
    //for a
   for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MAX_INPUT_MATRIX_SIZE; ++j)
        { 
                char tempString[10];
               
            if(i==0 && j==0)
            {
               resultLabelsMatrixA[i][j] = gtk_label_new (" - ");
            }
            else if(i==0)
            {
                
                snprintf(tempString, 10, "%d", j - 1 );
                resultLabelsMatrixA[i][j] = gtk_label_new (tempString);
            }
            else if(j==0)
            {
                snprintf(tempString, 10, "%d", i );
                resultLabelsMatrixA[i][j] = gtk_label_new (tempString);
            }
            else
            {
                resultLabelsMatrixA[i][j] = gtk_label_new ("0.001" );
                
            }
            gtk_widget_show (resultLabelsMatrixA[i][j]);
            gtk_grid_attach (resultGridA,resultLabelsMatrixA[i][j],j,i,1,1);
                    
        }
    }


    //for R 
   
   for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MAX_INPUT_MATRIX_SIZE; ++j)
        { 
                char tempString[10];
               
            if(i==0 && j==0)
            {
               resultLabelsMatrixR[i][j] = gtk_label_new (" - ");
            }
            else if(i==0)
            {
                
                snprintf(tempString, 10, "%d", j - 1 );
                resultLabelsMatrixR[i][j] = gtk_label_new (tempString);
            }
            else if(j==0)
            {
                snprintf(tempString, 10, "%d", i );
                resultLabelsMatrixR[i][j] = gtk_label_new (tempString);
            }
            else
            {
                resultLabelsMatrixR[i][j] = gtk_label_new ("0.001" );
                
            }
            gtk_widget_show (resultLabelsMatrixR[i][j]);
            gtk_grid_attach (resultGridR,resultLabelsMatrixR[i][j],j,i,1,1);
                    
        }
    }
    

    updateInput();


    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

     gtk_window_set_title(GTK_WINDOW(window), "Árboles Binarios de Búsqueda Óptimos");
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