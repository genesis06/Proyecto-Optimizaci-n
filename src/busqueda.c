/*
   ITCR - Investigación de Operaciones

   Arboles de busqueda
   Licencia GNU Free Documentation License 1.2 
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

float answerMatrix[20][20] = {{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0}};//TODO cambiar, datos de prueb
Item datos[29] = {{"Harrison", 0.18},{"Lennon" ,0.32},{"McCartney", 0.39},{"Starr", 0.11}};
int tamDatos = 4;

//variables de todos los problemas
int MAX_INPUT_MATRIX_SIZE = 29;
GtkWidget *textInputsMatrix[20][2];
GtkWidget   *window;
GtkWidget *resultInputsMatrix[20][32];

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
int numeroLlaves = 10;


//declaraciones de funcion .h
static void getTextInputValues();
static void displayAnswer();




//---funciones del problema----------------


//---funciones de interfaz----------------
//llamada a todas las funciones para resolver el problema
void resolver (GtkWidget* button, gpointer window)
{
    
    gtk_widget_show(resultScreen);
    gtk_widget_hide(inputScreen);
    //TODO uncomment
    //gtk_widget_hide(labelInput);
   //gtk_widget_hide(comboBoxNumero);
    //gtk_widget_hide(inputsGrid);
    getTextInputValues();
    


    //cleanLabels();
    //displayAnswer();
}

//this function replaces the textInputsMatrix with curret values
void getTextInputValues()
{
    numeroLlaves = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxNumero));       
    for (int i = 0; i < numeroLlaves; ++i)
    {
        
            gchar *currentTextInputTextName;
            currentTextInputTextName = gtk_entry_get_text(GTK_ENTRY(textInputsMatrix[i][0]));
            gchar *currentTextInputTextValue;
            currentTextInputTextValue = gtk_entry_get_text(GTK_ENTRY(textInputsMatrix[i][1]));

            float newValue = atof(currentTextInputTextValue);
            
            datos[i].name = currentTextInputTextName;
            datos[i].value = newValue;
            /*
            if(j == 0)
            {
               
              datos[i]->name = currentTextInputText;
            }
            else
            {
              int newValue = atoi(currentTextInputText);
              datos[i]->value = newValue;
              
              if(i <= numeroLlaves)
              {
                 gtk_widget_show(GTK_WIDGET (textInputsMatrix[i][j]));
              }
              else
              {
                   gtk_widget_hide(GTK_WIDGET (textInputsMatrix[i][j])); 
              }
              
            }*/        
        
    }
    for (int i = 0; i < numeroLlaves; ++i)
    {
        printf(" %s  ",  datos[i].name);
        printf(" %f  \n",  datos[i].value);
    }

}
//Esta funcion esconde los inputs para cambiar tamaño de matriz
void updateInput()
{
    numeroLlaves = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxNumero));
    for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
           if(i <= numeroLlaves)
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
    gtk_widget_show(inputScreen);

    //TODO uncomment
    //gtk_widget_show(inputsGrid);
    //gtk_widget_show(labelInput);
    //gtk_widget_show(comboBoxNumero);

}
void closeWindow()
{
    gtk_main_quit();
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

    
    button = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
    //g_signal_connect(button, "clicked", G_CALLBACK(resolver), window);

    button = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
    //g_signal_connect(button, "clicked", G_CALLBACK(showOpenFile), window);
    
    labelInput =  GTK_WIDGET(gtk_builder_get_object(builder, "Label2"));
    
    inputsGrid =  GTK_GRID(gtk_builder_get_object(builder, "gridInput"));
    resultGridA =  GTK_GRID(gtk_builder_get_object(builder, "gridA"));
    resultGridR =  GTK_GRID(gtk_builder_get_object(builder, "gridA"));
    

    inputScreen =  GTK_WIDGET(gtk_builder_get_object(builder, "box8"));
    resultScreen =  GTK_WIDGET(gtk_builder_get_object(builder, "boxResult"));


    gtk_widget_hide(resultScreen);
    gtk_widget_show(inputScreen);
    //TODO uncomment
    //gtk_widget_show(inputsGrid);
    
 
   

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
            gtk_entry_set_max_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 5);
            gtk_entry_set_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 5);
            gtk_entry_set_max_length (GTK_ENTRY (textInputsMatrix[i][j]),5);
          }
         
          gtk_widget_show (textInputsMatrix[i][j]);
          gtk_grid_attach (inputsGrid,textInputsMatrix[i][j],j,i + 1,1,1);
            
        }  
    }
    /*
    for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MAX_INPUT_MATRIX_SIZE; ++j)
        {  
          resultInputsMatrix[i][j] = gtk_label_new (" " );
          gtk_widget_show (resultInputsMatrix[i][j]);
          gtk_grid_attach (resultGridA,resultInputsMatrix[i][j],i,j,1,1);  
        }
    }

    for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MAX_INPUT_MATRIX_SIZE; ++j)
        {  
          resultInputsMatrix[i][j] = gtk_label_new (" " );
          gtk_widget_show (resultInputsMatrix[i][j]);
          gtk_grid_attach (resultGridR,resultInputsMatrix[i][j],i,j,1,1);  
        }
    }
    */

    
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