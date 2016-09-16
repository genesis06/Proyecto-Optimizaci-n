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
GtkWidget *textInputsMatrix[20][5];
GtkWidget   *window;
GtkWidget *resultInputsMatrix[20][32];

//variables de interfaz
GtkGrid    *resultGrid;
GtkWidget *resultScreen;
GtkWidget *inputScreen;
GtkWidget   *resultadoString1;


//variables especificas de este programa
int tipo;//0=0/1, 1= bounded, 2= unbounded

double inflacion;
int valorCompra = 500;
int plazoProyecto = 5; // CAMBIAR POR EL VALOR MAXIMO DE PLAZO
int vidaUtil= 3; // CAMBIAR POR EL VALOR MAXIMO DE VIDA UTIL
int matrizValores[30][2] = {{30,400},{40,300},{60,250}}; // CAMBIAR POR EL VALOR MAXIMO DE PLAZO
char *listaProximos[30] = {"", "" , "", "", ""}; // CAMBIAR POR EL VALOR MAXIMO DE PLAZO
int costosPorTiempo[30] = {0,0,0,0,0,0}; // CAMBIAR POR EL VALOR MAXIMO DE PLAZO
int costos[3] = {0,0,0}; // CAMBIAR POR EL VALOR MAXIMO DE VIDA UTIL
int cantidadProximos[30] = {0,0,0,0,0}; //lleva el conteo de cuantos proximos hay en cada tiempo
char stringReemplazoOptimo[100];
int costoInicial;


int tablaCalculos[20][2];
char stringNombres[100];
char *nombreObjetos[20] = {"A1", "A2", "A3", "A4", "A5", "A6","A7","A8", "A9", "A10", "11","12","13","14","15","16" ,"17", "18", "19", "20"};
int contaNombres = 0;
int comboSelect ;
int comboBoxPlazoSelected ;
int comboBoxVidaUtilSelect ;
GtkWidget *button;
GtkWidget *comboBox;
GtkWidget *comboBoxPlazo;
GtkWidget *comboBoxVidaUtil;
GtkWidget *dialog;

typedef struct {
    int valor;
    int proximo;
} G_prox;

//delcaraciones de funciones
void calcularCostos();
void calcularG(int t);
int calcularMantenimientos(int year);
G_prox* ordenar(G_prox*valores, int largo, int t);
int cantidadRepetidos(G_prox*valores, int largo);
void calcularReemplazoOptimo(int t);

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


// Funcion principal
void reemplazoEquipos(){
  calcularCostos();
  for (int i = plazoProyecto; i >= 0; i--)
  {
    calcularG(i);
  }
}

void calcularReemplazoOptimo(int t){
  char* string = calloc(100, sizeof(char));
  int largo = cantidadProximos[t];
  
  while(t!=plazoProyecto){
    if(largo>1){
      char *aux = listaProximos[t];   
      char *token = calloc(5, sizeof(char));
      token = strtok (aux,",");
      strcat(string,token);
      strcat(string, " ");

      t = atoi(token);
      
    }
    else{
      strcat(string,listaProximos[t]);
      strcat(string, " ");
      t = atoi(listaProximos[t]);
    }
    largo = cantidadProximos[t];
  }
  strcpy(stringReemplazoOptimo, string);
  printf("Reemplazo: %s\n", stringReemplazoOptimo);
  gtk_label_set_text(resultadoString1, stringReemplazoOptimo);
}


// Calcula los costos dependiendo de los valores de tx
void calcularCostos(){

  for (int i = 0; i < vidaUtil; i++)
  {
    costos[i] = valorCompra + calcularMantenimientos(i+1) - matrizValores[i][1];
  }
}

//Calcula los mantenimientos para cada año
int calcularMantenimientos(int year){
  int mante=0;
  for (int i = 0; i < year; i++)
  {
    mante += matrizValores[i][0];
  }
  return mante;
}


void calcularG(int t){
  if(t == plazoProyecto){
    printf("%d\n", 0);// 0;

  }
  else{
    int largoValores;
    if ((plazoProyecto - t) > vidaUtil)
    {
      largoValores = vidaUtil;
    }
    else{
      largoValores = plazoProyecto - t; 
    }
    
    int valores[largoValores];
    G_prox auxiliar[largoValores];

    int contaValores = 0;
    for (int i = t; i < plazoProyecto; i++)
    {
      auxiliar[contaValores].valor = costos[contaValores] + costosPorTiempo[t+1+contaValores];
      auxiliar[contaValores].proximo = (t + (contaValores + 1));
      contaValores++;
      if ((plazoProyecto - t) > vidaUtil && contaValores==vidaUtil)
      {
        break;
      }
    }
    if(t==(plazoProyecto-1)){
      char *num=calloc(5, sizeof(char));
      sprintf(num,"%d",  t+1);
      costosPorTiempo[t] = costos[0];
      listaProximos[t] = num;
    }
    else{
      
      memcpy(auxiliar,ordenar(auxiliar,largoValores, t),sizeof(auxiliar)); 
      
      char *num=calloc(5, sizeof(char));
      sprintf(num,"%d", auxiliar[0].proximo);
      costosPorTiempo[t] = auxiliar[0].valor;
      listaProximos[t] = num;

      int repetidos = cantidadRepetidos(auxiliar, largoValores);
      if (repetidos > 1)
      {
        char *proximos=calloc(10, sizeof(char));
        strcpy(proximos,listaProximos[t]);
        strcat(proximos,",");
        for (int i = 1; i < repetidos; i++)
        {
          char *num2=calloc(5, sizeof(char));
          sprintf(num2,"%d", auxiliar[i].proximo);
          strcat(proximos,num2);    
        }
        listaProximos[t]= proximos;
      }
    }

  }
}


G_prox* ordenar(G_prox*valores, int largo, int t){
  G_prox aux;
  for (int i = 0; i < largo-1; i++)
  {
    for (int j = i+1; j < largo; j++)
    {
      if(valores[j].valor < valores[i].valor){
        aux = valores[j];
        valores[j] = valores[i];
        valores[i] = aux;
      }
    }
  }
  return valores;

}

int cantidadRepetidos(G_prox*valores, int largo){
  int cantidad = 1;
  for (int i = 1; i < largo; i++)
  {
    if(valores[0].valor == valores[i].valor){
      cantidad++;
    }
  }
  //printf("Cantidad: %d\n", cantidad);
  return cantidad;
}

 
//--------------------------------------------------------Switch ComboBox
void resolver (GtkWidget* button, gpointer window)
{
    gtk_widget_hide(inputScreen);
    gtk_widget_show(resultScreen);

    getTextInputValues();
    

    reemplazoEquipos();







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

      for (int i = 0; i < vidaUtil; i++) 
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
    char *token = calloc(5, sizeof(char));
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
          costoInicial = atoi(primeraLinea[0]);
          vidaUtil = atoi(primeraLinea[1]);
          plazoProyecto = atoi(primeraLinea[2]);

          //gtk_combo_box_set_active(GTK_COMBO_BOX(comboBox),indiceComboObjetos );
          printf("Plazo: %d\n", plazoProyecto);
          printf("vida: %d\n", vidaUtil);
          printf("Compra: %d\n", costoInicial);
          
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
         for(int j=0;j<2;j++){
          //printf("%d %d\n", i,j);
        printf("%d ", matrizValores[i][j]); 
      }
      printf("\n");
    }

    /******* Inicia proceso de split línea para obtener datos ******/
          char* nombre = calloc(5, sizeof(char));
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
  
  char *token =calloc(5, sizeof(char));;
  int indiceColumnas =0;
  /**Agarra el primer token separado por espacio**/
  token = strtok (linea," ");  
  
  while (token != NULL )
  {
    /***Guarda el token en la matriz****/
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
    

    gchar *costoInicialString;           
    costoInicialString = gtk_entry_get_text(GTK_ENTRY(textInputsMatrix[0][4]));
    costoInicial = atoi(costoInicialString);
    printf("costo inicial: %d\n", costoInicial);
           
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
        for (int j = 1; j < 5; ++j)
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
        for (int j = 0; j < 32; ++j)
        { 
          gtk_label_set_text(GTK_LABEL(resultInputsMatrix[i][j]),"  ");
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
    for (int i = 1; i <= plazoProyecto; i++) 
    {
        char costoTiempo[20] = "";
        snprintf(costoTiempo, 20, "%d", costosPorTiempo[i]);
        char tiempo[20] = "";
        snprintf(tiempo, 20, "%d", i);
        //gtk_label_set_text(GTK_LABEL(resultInputsMatrix[0][i + 1]), tiempo);
        gtk_label_set_text(GTK_LABEL(resultInputsMatrix[1][i + 1]), costoTiempo);
        gtk_label_set_text(GTK_LABEL(resultInputsMatrix[2][i + 1]), listaProximos[i]);
        gtk_widget_show (resultInputsMatrix[0][i + 1]);
        gtk_widget_show (resultInputsMatrix[1][i + 1]);
        gtk_widget_show (resultInputsMatrix[2][i + 1]);

    }
    for (int iClean = 0; iClean < 20; ++iClean)
    {
        for (int jClean = 0; jClean < 32; ++jClean)
        { 
             
          if(iClean > 2 || jClean > vidaUtil + 1)
          {
            gtk_widget_hide (resultInputsMatrix[iClean][jClean]);
          }
          else
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

    resultadoString1 =  GTK_WIDGET(gtk_builder_get_object(builder, "stringConstruido"));

    gtk_widget_hide(resultScreen);
    gtk_widget_show(inputScreen);
    
 
   

    for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < 5; ++j)
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
              gtk_entry_set_text (GTK_ENTRY (textInputsMatrix[i][j]), "0");
              gtk_widget_show (textInputsMatrix[i][j]);
              gtk_entry_set_max_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 4);
              gtk_entry_set_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 4);
              gtk_grid_attach (inputsGrid,textInputsMatrix[i][j],j,i + 1,1,1);
            }
            

            if(j==4)
            {
                if(i!=0)
                {
                      gtk_widget_hide(textInputsMatrix[i][j]);
                }

            }
           
        }
    }

    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 32; ++j)
        { 
            if(i==0)
            {
               resultInputsMatrix[i][j] =  gtk_grid_get_child_at(resultGrid,i,j);
            }
            else
            {
                resultInputsMatrix[i][j] = gtk_label_new (" " );
                gtk_widget_show (resultInputsMatrix[i][j]);
                gtk_grid_attach (resultGrid,resultInputsMatrix[i][j],i,j,1,1);
            }
          
           
        }
    }

    
    updateInput();


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

void buttonAnswer1()
{
    calcularReemplazoOptimo(1);
}
void buttonAnswer2()
{
    calcularReemplazoOptimo(2);
}
void buttonAnswer3()
{
    calcularReemplazoOptimo(3);
}
void buttonAnswer4()
{
    calcularReemplazoOptimo(4);
}
void buttonAnswer5()
{
    calcularReemplazoOptimo(5);
}
void buttonAnswer6()
{
    calcularReemplazoOptimo(6);
}
void buttonAnswer7()
{
    calcularReemplazoOptimo(7);
}
void buttonAnswer8()
{
    calcularReemplazoOptimo(8);
}
void buttonAnswer9()
{
    calcularReemplazoOptimo(9);
}
void buttonAnswer10()
{
    calcularReemplazoOptimo(10);
}
void buttonAnswer11()
{
    calcularReemplazoOptimo(11);
}
void buttonAnswer12()
{
    calcularReemplazoOptimo(12);
}
void buttonAnswer13()
{
    calcularReemplazoOptimo(13);
}
void buttonAnswer14()
{
    calcularReemplazoOptimo(14);
}
void buttonAnswer15()
{
    calcularReemplazoOptimo(15);
}
void buttonAnswer16()
{
    calcularReemplazoOptimo(16);
}
void buttonAnswer17()
{
    calcularReemplazoOptimo(17);
}
void buttonAnswer18()
{
    calcularReemplazoOptimo(18);
}
void buttonAnswer19()
{
    calcularReemplazoOptimo(19);
}
void buttonAnswer20()
{
    calcularReemplazoOptimo(20);
}
void buttonAnswer21()
{
    calcularReemplazoOptimo(21);
}
void buttonAnswer22()
{
    calcularReemplazoOptimo(22);
}
void buttonAnswer23()
{
    calcularReemplazoOptimo(23);
}
void buttonAnswer24()
{
    calcularReemplazoOptimo(24);
}
void buttonAnswer25()
{
    calcularReemplazoOptimo(25);
}
void buttonAnswer26()
{
    calcularReemplazoOptimo(26);
}
void buttonAnswer27()
{
    calcularReemplazoOptimo(27);
}
void buttonAnswer28()
{
    calcularReemplazoOptimo(28);
}
void buttonAnswer29()
{
    calcularReemplazoOptimo(29);
}
void buttonAnswer30()
{
    calcularReemplazoOptimo(30);
}