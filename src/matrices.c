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
//global
int MAX_INPUT_MATRIX_SIZE = 20;
typedef struct {
    int n;
    int m;
} matriz;


matriz inputValues[20] = {{1,2},{2,3},{3,2},{2,7}};
int cantidadMatrices = 9;
int columnaInicial = 2;

char linea[300];

//variables de todos los problemas

GtkWidget *textInputsMatrix[20][2];
GtkWidget   *window;
GtkWidget   *resultadoString0;
GtkWidget *resultadoString1 ;
GtkWidget *resultadoStringWarning;

//variables de interfaz

GtkWidget *resultScreen;
GtkWidget *inputScreen;
GtkWidget *button;
GtkWidget *cantidadMatricesComboBox;
GtkWidget *labelCantidad;
GtkGrid    *inputsGrid;
//variables especificas de este algoritmo
int numeroLlaves = 9;


//declaraciones de funcion .h
static void displayAnswer();
static void getTextInputValues();
static void displayAnswer();



//---funciones del problema----------------
void resolver ()
{
    //sow screen
    gtk_widget_show(resultadoString0);
    gtk_widget_show(resultadoString1);
    gtk_widget_show(resultadoStringWarning);
    
    gtk_widget_hide(inputsGrid);
    gtk_widget_hide(labelCantidad);
    gtk_widget_hide(cantidadMatricesComboBox);
    
    //get values
    //getTextInputValues();
    
    //TODO insert problem functions



    //update answer with values
    //displayAnswer();


}

//----------------funciones de interfaz--------------
void cleanInput()
{
    gtk_widget_hide(resultadoString0);
    gtk_widget_hide(resultadoString1);
    gtk_widget_hide(resultadoStringWarning);
    
    gtk_widget_show(inputsGrid);
    gtk_widget_show(labelCantidad);
    gtk_widget_show(cantidadMatricesComboBox);

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

    inputScreen =  GTK_WIDGET(gtk_builder_get_object(builder, "boxInput"));
    resultScreen =  GTK_WIDGET(gtk_builder_get_object(builder, "boxResult"));

    resultadoString0 =  GTK_WIDGET(gtk_builder_get_object(builder, "labelRespuestaMate1"));
    resultadoString1 =  GTK_WIDGET(gtk_builder_get_object(builder, "labelRespuestaMate2"));
    resultadoStringWarning =  GTK_WIDGET(gtk_builder_get_object(builder, "labelRespuestaMate3"));
    
    //assign  save and load buttons callback
    //TODO uncomment
    button = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));

    button = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
    //g_signal_connect(button, "clicked", G_CALLBACK(showOpenFile), window);


    for (int i = 0; i < MAX_INPUT_MATRIX_SIZE; ++i)
        {
            for (int j = 0; j < 3; ++j)
            { 
                if(j == 1)
                {
                  textInputsMatrix[i][j] = gtk_label_new ("  x  " );
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
                //GtkWidget *entry;
                //add one input and store reference
                
               
            }
        }




    //hide answer
    gtk_widget_hide(resultadoString0);
    gtk_widget_hide(resultadoString1);
    gtk_widget_hide(resultadoStringWarning);
    
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


