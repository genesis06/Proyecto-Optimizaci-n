/*
   ITCR - Investigación de Operaciones
*/
#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//variables de todos los problemas
int MAX_INPUT_MATRIX_SIZE = 20;
GtkWidget *textInputsMatrix[20][4];
GtkWidget   *window;
GtkWidget *resultInputsMatrix[20][20];

//variables de interfaz
GtkGrid    *resultGrid;
GtkWidget *resultScreen;
GtkWidget *inputScreen;

//variables especificas de este programa
int tipo;//0=0/1, 1= bounded, 2= unbounded
int cantidadMaxima;
int cantidadObjetos;
int matrizValores[20][4];
char *nombreObjetos[20] = {"A1", "A2", "A3", "A4", "A5", "A6","A7","A8", "A9", "A10", "11","12","13","14","15","16" ,"17", "18", "19", "20"};
int contaNombres = 0;
int comboSelect ;
int comboBoxCapacidadSelected ;
int comboBoxObjetosSelect ;
GtkWidget *button;
GtkWidget *comboBox;
GtkWidget *comboBoxCapacidad;
GtkWidget *comboBoxObjetos;
GtkWidget *dialog;


//delcaraciones de funciones
int max(int a, int b);
void separarColumnas(int fila);
int knapSack01(int W, int wt[], int val[], int n);
int *knapsackBounded (int w);
void knapsackUnbounded (int i, int value, int weight);
static void knapSackProblem01();
static void knapSackBoundedProblem();
static void knapSackUnBoundedProblem();
static void getTextInputValues();
static void setTextInputValues();
void resolver (GtkWidget* button, gpointer window);
static void showOpenFile(GtkWidget* button, gpointer window);
void separarColumnas(int fila);



char linea[100];

typedef struct {
    char *name;
    double value;
    double weight;
    double volume;
} item_t_unbounded;

typedef struct {
    char *name;
    int weight;
    int value;
    int count;
} item_t_bounded;
 
item_t_unbounded itemsUnbounded[] = {
    {"Item1", 3000.0, 0.3, 0.025},
    {"Item2",   1800.0, 0.2, 0.015},
    {"Item3",    2500.0, 2.0, 0.002},
};
 
item_t_bounded items_bounded[] = {
    {"map",                      9,   150,   1},
    {"compass",                 13,    35,   1},
    {"water",                  153,   200,   2},
    {"sandwich",                50,    60,   2}
    /*{"glucose",                 15,    60,   2},
    {"tin",                     68,    45,   3},
    {"banana",                  27,    60,   3},
    {"apple",                   39,    40,   3},
    {"cheese",                  23,    30,   1},
    {"beer",                    52,    10,   3},
    {"suntan cream",            11,    70,   1},
    {"camera",                  32,    30,   1},
    {"T-shirt",                 24,    15,   2},
    {"trousers",                48,    10,   2},
    {"umbrella",                73,    40,   1},
    {"waterproof trousers",     42,    70,   1},
    {"waterproof overclothes",  43,    75,   1},
    {"note-case",               22,    80,   1},
    {"sunglasses",               7,    20,   1},
    {"towel",                   18,    12,   2},
    {"socks",                    4,    50,   1}*/
    
};

//-----------------------------Empieza Algoritmo knapSack 0/1 -----------
int max(int a, int b) { return (a > b)? a : b; }

/*
	W = Capacidad Maxima
	wt = El peso de cada objeto
	val = Valores de cada objeto
	n   = Cantidad Objetos
*/
int knapSack01(int W, int wt[], int val[], int n)
{
   int i, w;
   int K[n+1][W+1];
   char matrizString[500] = "";
   char row[100] = "";
   for (i = 0; i <= n; i++)
   {
       strcpy(row, "");
       for (w = 0; w <= W; w++)
       {
            
            if (i==0)
               K[i][w] = w;
           else if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
	         
           //imprimir en consola
          char num[50] = "";
          sprintf(num, "%d\t", K[i][w]);
          strcat(row, num);
          
          //imprimir en interfaz;
          char newLabelValue[20] = "";
          snprintf(newLabelValue, 50, "%d", K[i][w]);
          gtk_label_set_text(GTK_LABEL(resultInputsMatrix[i][w]), newLabelValue);
          //gtk_grid_attach(resultGrid,resultInputsMatrix[i][w],i,w,1,1);
          
       }
        strcat(row, "\n");
        strcat(matrizString, row);
   }

   printf("%s\n",matrizString );
	 


   for (int iClean = 0; iClean < 20; ++iClean)
    {
        for (int jClean = 0; jClean < 20; ++jClean)
        { 
             
          if(iClean > i - 1 || jClean > w - 1)
          gtk_widget_hide (resultInputsMatrix[iClean][jClean]);
           
        }
    }
   return K[n][W];

   
}



//-----------------------------Empieza Algoritmo Bounded----------------------------------------------

//int cantidadObjetos = sizeof (items_bounded) / sizeof (item_t_bounded);

int *knapsackBounded (int w) {
    int i, j, k, v, *mm, **m, *s;
    mm = calloc((cantidadObjetos + 1) * (w + 1), sizeof (int));
    m = malloc((cantidadObjetos + 1) * sizeof (int *));
    m[0] = mm;
    for (i = 1; i <= cantidadObjetos; i++) {
        m[i] = &mm[i * (w + 1)];
        for (j = 0; j <= w; j++) {
            m[i][j] = m[i - 1][j];
            for (k = 1; k <= matrizValores[i - 1][3]; k++) {
                if (k * matrizValores[i - 1][2] > j) {
                    break;
                }
                v =  matrizValores[i - 1][2];
                v = m[i - 1][j - k * v] ;
                v = v+ k * matrizValores[i - 1][1]; 
                if (v > m[i][j]) {
                    m[i][j] = v;
                }
            }
        }
    }
    s = calloc(cantidadObjetos, sizeof (int));
    for (i = cantidadObjetos, j = w; i > 0; i--) {
        int v = m[i][j];
        for (k = 0; v != m[i - 1][j] + k * matrizValores[i - 1][1]; k++) {
            s[i - 1]++;
            j -= matrizValores[i - 1][2];
        }
    }
    free(mm);
    free(m);
    return s;
}
//--------------------------Empieza Algoritmo UnBounded------------------------------------------------

int n_unbounded = sizeof (itemsUnbounded) / sizeof (item_t_unbounded);
int *count;
int *best;
int best_value;
void knapsackUnbounded (int i, int value, int weight) {
    int j, m1, m2, m;
    if (i == cantidadObjetos) {
        if (value > best_value) {
            best_value = value;
            for (j = 0; j < cantidadMaxima; j++) {
                best[j] = count[j];
            }
        }
        return;
    }
    if(weight > 0)
    {
      m = weight / matrizValores[i][2];
    for (count[i] = m; count[i] >= 0; count[i]--) {
        knapsackUnbounded(
            i + 1,
            value + count[i] * matrizValores[i][1],
            weight - count[i] * matrizValores[i][2]
        );
    }
    }
    
}
//------------------------------------------------------ Funciones de Ejemplo 

 static void knapSackProblem01()
{
    printf("%s\n","Maxima ganancia es");
    int val[] = {11, 7, 12};
    int wt[] = {4, 3, 5};
    int  W = 10;
    int n = sizeof(val)/sizeof(val[0]);
    printf("%d\n", knapSack01(W, wt, val, n));

}

 static void knapSackBoundedProblem()
{ 
    int i, tc = 0, tw = 0, tv = 0, *s;
    s = knapsackBounded(cantidadMaxima);
            //strings de titulo
            char nombre[20]= "Nombre";
            char peso[20] = "Cantidad";
            char cuenta[20] = "Peso";
            char valor[20] = "Valor";
            gtk_label_set_text(GTK_LABEL(resultInputsMatrix[0][0]), nombre);
            gtk_label_set_text(GTK_LABEL(resultInputsMatrix[1][0]), peso);
            gtk_label_set_text(GTK_LABEL(resultInputsMatrix[2][0]), cuenta);
            gtk_label_set_text(GTK_LABEL(resultInputsMatrix[3][0]), valor);
            gtk_widget_show (resultInputsMatrix[0][0]);
            gtk_widget_show (resultInputsMatrix[1][0]);
            gtk_widget_show (resultInputsMatrix[2][0]);
            gtk_widget_show (resultInputsMatrix[3][0]);


    for (i = 0; i < cantidadObjetos; i++) {
        if (s[i]) {
            //print in console
            printf("%-22s %5d %5d %5d\n", nombreObjetos[i], s[i], s[i] * matrizValores[i][2], s[i] * matrizValores[i][1]);
            
            //print in screen
            char peso[20] = "";
            char cuenta[20] = "";
            char valor[20] = "";
            snprintf(peso, 50, "%d", s[i]);
            snprintf(cuenta, 50, "%d",s[i] * matrizValores[i][2]);
            snprintf(valor, 50, "%d",  s[i] * matrizValores[i][1]);
            gtk_label_set_text(GTK_LABEL(resultInputsMatrix[0][i + 1]), nombreObjetos[i]);
            gtk_label_set_text(GTK_LABEL(resultInputsMatrix[1][i + 1]), peso);
            gtk_label_set_text(GTK_LABEL(resultInputsMatrix[2][i + 1]), cuenta);
            gtk_label_set_text(GTK_LABEL(resultInputsMatrix[3][i + 1]), valor);
            gtk_widget_show (resultInputsMatrix[0][i + 1]);
            gtk_widget_show (resultInputsMatrix[1][i + 1]);
            gtk_widget_show (resultInputsMatrix[2][i + 1]);
            gtk_widget_show (resultInputsMatrix[3][i + 1]);


            tc += s[i];
            tw += s[i] * matrizValores[i][2];
            tv += s[i] * matrizValores[i][1];
        }
    }
    printf("%-22s %5d %5d %5d\n", "Cuenta, Peso, Valor:", tc, tw, tv);

    //interfaz resultado
     //strings de titulo
            snprintf(nombre, 50, "Total:");
            snprintf(peso, 50, "%d", tc);
            snprintf(cuenta, 50, "%d",tw);
            snprintf(valor, 50, "%d",  tv);
            gtk_label_set_text(GTK_LABEL(resultInputsMatrix[0][i + 1]), nombre);
            gtk_label_set_text(GTK_LABEL(resultInputsMatrix[1][i + 1]), peso);
            gtk_label_set_text(GTK_LABEL(resultInputsMatrix[2][i + 1]), cuenta);
            gtk_label_set_text(GTK_LABEL(resultInputsMatrix[3][i + 1]), valor);
            gtk_widget_show (resultInputsMatrix[0][i + 1]);
            gtk_widget_show (resultInputsMatrix[1][i + 1]);
            gtk_widget_show (resultInputsMatrix[2][i + 1]);
            gtk_widget_show (resultInputsMatrix[3][i + 1]);

    for (int iClean = 0; iClean < 20; ++iClean)
    {
        for (int jClean = 0; jClean < 20; ++jClean)
        { 
             
          if(iClean > 3 || jClean > i + 1)
          gtk_widget_hide (resultInputsMatrix[iClean][jClean]);
           
        }
    }
}

 static void knapSackUnBoundedProblem()
{
   
    count = malloc(cantidadObjetos * sizeof (int));
    best = malloc(cantidadObjetos * sizeof (int));
    best_value = 0;
    knapsackUnbounded(0, 0, cantidadMaxima);
     //strings de titulo
    char nombre[20]= "Nombre";
    char cantidad[20] = "Cantidad";
    gtk_label_set_text(GTK_LABEL(resultInputsMatrix[0][0]), nombre);
    gtk_label_set_text(GTK_LABEL(resultInputsMatrix[1][0]), cantidad);
    gtk_widget_show (resultInputsMatrix[0][0]);
    gtk_widget_show (resultInputsMatrix[1][0]);

    int i;
    for (i = 0; i < cantidadObjetos; i++) {
        printf("%d %s\n", best[i], nombreObjetos[i]);

        snprintf(cantidad, 50, "%d", best[i]);
        gtk_label_set_text(GTK_LABEL(resultInputsMatrix[0][i + 1]), nombreObjetos[i]);
        gtk_label_set_text(GTK_LABEL(resultInputsMatrix[1][i + 1]), cantidad);
        gtk_widget_show (resultInputsMatrix[0][i + 1]);
        gtk_widget_show (resultInputsMatrix[1][i + 1]);
    }
    printf("Mejor Valor: %d\n", best_value);
    
    snprintf(cantidad, 50, "%d", best_value);
    gtk_label_set_text(GTK_LABEL(resultInputsMatrix[0][i + 1]), "Valor Maximo:");
    gtk_label_set_text(GTK_LABEL(resultInputsMatrix[1][i + 1]), cantidad);
    gtk_widget_show (resultInputsMatrix[0][i + 1]);
    gtk_widget_show (resultInputsMatrix[1][i + 1]);


    free(count); free(best);

    for (int iClean = 0; iClean < 20; ++iClean)
    {
        for (int jClean = 0; jClean < 20; ++jClean)
        { 
             
          if(iClean > 1 || jClean > i + 1)
          gtk_widget_hide (resultInputsMatrix[iClean][jClean]);
           
        }
    }
    
}
//--------------------------------------------------------Switch ComboBox
void resolver (GtkWidget* button, gpointer window){
 gtk_widget_hide(inputScreen);
  gtk_widget_show(resultScreen);

 comboSelect = gtk_combo_box_get_active(GTK_COMBO_BOX(comboBox));
 getTextInputValues();
 cleanLabels();
 switch(comboSelect) {
      case -1 :
         printf("Aún no se selecciona nda!\n" );
         break;
      case 2 :
	
	 knapSackProblem01();
         break;
      case 0 :
        
	 knapSackBoundedProblem();
         break;
      case 1 :
        
	 knapSackUnBoundedProblem();
         break;
     
      default :
         printf("Invalida seleccion, elige el tipo de algoritmo\n" );
   }

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
      //Conversion de tipos para guardar primera linea
      sprintf(cantMaxChar, "%d",3); // ***********CAMBIAR NUMERO POR cantidadMaxima
      sprintf(tipoChar, "%d",1); // **************CAMBIAR NUMERO POR tipo
      sprintf(cantObjChar, "%d",5); //*********** CAMBIAR NUMERO POR cantidadObjetos
      printf("%s %s %s\n",cantMaxChar,tipoChar,cantObjChar );


      char primerLinea[20];
      strcat(primerLinea, cantMaxChar);
      strcat(primerLinea," ");
      strcat(primerLinea, tipoChar);
      strcat(primerLinea," ");
      strcat(primerLinea, cantObjChar);
      strcat(primerLinea,"\n");

      printf("%s\n", primerLinea);
      fputs(primerLinea, fichero); // Escribe primera linea en archivo
      strcpy(primerLinea,"");

      for (int i = 0; i < 5; i++) // ***** Cambiar 5 por cantidadObjetos
      {
        for (int j = 0; j < 4; j++)
        {
          char valor[10];
          sprintf(valor, "%d", matrizValores[i][j]);

          printf("%d\n", matrizValores[i][j]);
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
          cantidadMaxima = atoi(primeraLinea[0]);
          tipo = atoi(primeraLinea[1]);
          cantidadObjetos = atoi(primeraLinea[2]);
          printf("Cantidad máxima: %d\n", cantidadMaxima);
          printf("Tipo algortimo: %d\n", tipo);
          printf("Cantidad objetos: %d\n", cantidadObjetos);
          
    /********************** Proceso para leer y guardar matriz ******************************/      
    int indiceFilas = 0;
    strcpy(linea,"");

    // Lee resto de líneas
		while (fgets(buff, 255, (FILE*)infile)){

       strcpy(linea, buff);
      if(indiceFilas < cantidadMaxima){
        separarColumnas(indiceFilas);  
      }

      indiceFilas++;
      strcpy(linea,"");
			
		}
    /*****************************************************************************************/

    /** Imprime matriz  **/
    printf("Matriz\n");

    for(int i=0;i<4;i++){
         for(int j=0;j<4;j++){
          //printf("%d %d\n", i,j);
        printf("%d ", matrizValores[i][j]); 
      }
      printf("\n");
    }
    /****************************/
		// Cerrar Archivo
		fclose(infile);
		}
	  gtk_widget_destroy(dialog);
  printf("Objeto: %s\n", nombreObjetos[0]);
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
        char *nombre;
        strcpy(nombre,token);
        nombreObjetos[fila]=nombre;
        printf("Nombre: %s\n", nombre);
        printf("Nombre: %s\n", nombreObjetos[fila]);
        contaNombres++;
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
    comboBoxObjetosSelect = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxObjetos));
    g_print("%d",comboBoxObjetosSelect);
    for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
           if(i <= comboBoxObjetosSelect)
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
    comboBoxObjetosSelect = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxObjetos));
    cantidadObjetos = comboBoxObjetosSelect + 1;
    comboBoxCapacidadSelected = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxCapacidad));
    cantidadMaxima = comboBoxCapacidadSelected + 1;
     printf("objetos: %d\n", cantidadObjetos);
      printf("pesio: %d\n", cantidadMaxima);
    for (int i = 0; i < cantidadObjetos; ++i)
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

              if(i <= comboBoxObjetosSelect)
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
            if(i <= cantidadObjetos)
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
       
         if(i <= cantidadObjetos)
        {
             gtk_widget_show(GTK_WIDGET (textInputsMatrix[i][0]));
              gtk_button_set_label (GTK_BUTTON (textInputsMatrix[i][0]), nombreObjetos[i]);
        }
        else
        {
             gtk_widget_hide(GTK_WIDGET (textInputsMatrix[i][0])); 
        }
    }
}
void cleanLabels()
{

    for (int i = 0; i < 20; ++i)
    {
        for (int j = 0; j < 20; ++j)
        { 
          gtk_label_set_text(GTK_LABEL(resultInputsMatrix[i][j])," - ");
           
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
//--------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    
    
    GtkBuilder      *builder;
    GtkGrid    *inputsGrid;
    


    gtk_init(&argc, &argv);

    
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "src/mochila.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "mochilaWindow"));
    gtk_builder_connect_signals(builder, NULL);

   
    comboBox = GTK_WIDGET(gtk_builder_get_object(builder, "comboboxtext3"));
    comboSelect = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBox));


    comboBoxCapacidad = GTK_WIDGET(gtk_builder_get_object(builder, "comboboxtext1"));
    comboBoxCapacidadSelected = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxCapacidad));

    comboBoxObjetos = GTK_WIDGET(gtk_builder_get_object(builder, "comboboxtext4"));
    comboBoxObjetosSelect = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxObjetos));
    
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
        for (int j = 0; j < 4; ++j)
        { 
            if(j == 0)
            {
              textInputsMatrix[i][j] = gtk_button_new ();
              //gtk_entry_set_max_length (GTK_BUTTON (textInputsMatrix[i][j]),4);
              gtk_button_set_label (GTK_BUTTON (textInputsMatrix[i][j]), nombreObjetos[i]);
              gtk_widget_show (textInputsMatrix[i][j]);
             // gtk_entry_set_max_width_chars(GTK_BUTTON (textInputsMatrix[i][j]), 4);
              //gtk_entry_set_width_chars(GTK_BUTTON (textInputsMatrix[i][j]), 4);
              gtk_grid_attach (inputsGrid,textInputsMatrix[i][j],j,i + 1,1,1);

            }
            else
            {
              textInputsMatrix[i][j] = gtk_entry_new ();
              gtk_entry_set_max_length (GTK_ENTRY (textInputsMatrix[i][j]),4);
              gtk_entry_set_text (GTK_ENTRY (textInputsMatrix[i][j]), "-1");
              gtk_widget_show (textInputsMatrix[i][j]);
              gtk_entry_set_max_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 4);
              gtk_entry_set_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 4);
              gtk_grid_attach (inputsGrid,textInputsMatrix[i][j],j,i + 1,1,1);
            }
            //GtkWidget *entry;
            //add one input and store reference
            
           
        }
    }

    for (int i = 0; i < 20; ++i)
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

