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
double probGaneACasa = 1.0;//tomada de la interfaz
double probPerderACasa = 0;//calculado

double probGaneAVisita = 1.0;//tomada de la interfaz
double probPerderAVisita = 0;//calculado

double probGaneBCasa = 1.0;//calculado
double probPerderBCasa = 0;//calculado

double probGaneBVisita = 1.0;//calculado
double probPerderBVisita = 0;//calculado
//usar esta variable para los valores de la respuesta
double answerMatrix[20][20] = {{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0}};//TODO cambiar, datos de prueb

int totalJuegos = 4;//TODO cambiar, datos de prueb
//variables para la localidad de juego
char *lugarJuegos[20] = {"casa", "casa", "casa", "casa", "casa",
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

//intefaz con valores de variables
GtkWidget *comboJuegos;//numero de juegos
GtkWidget *probCasaInput;
GtkWidget *probVisitaInput;
GtkWidget *lugarJuegosLabels[20];

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


    comboJuegos = GTK_WIDGET(gtk_builder_get_object(builder, "totalJuegosCombo"));
    //totalJuegos = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBoxPlazo)); //TODO remove comment
  
    inputsGrid =  GTK_GRID(gtk_builder_get_object(builder, "gridInput"));
    //resultGrid =  GTK_GRID(gtk_builder_get_object(builder, "gridRespuesta"));
    //gtk_widget_set_name (GTK_WIDGET(resultGrid), "gridRespuesta");

    inputScreen =  GTK_WIDGET(gtk_builder_get_object(builder, "boxInput"));
    resultScreen =  GTK_WIDGET(gtk_builder_get_object(builder, "boxResult"));

    gtk_widget_hide(resultScreen);
    gtk_widget_show(inputScreen);
    

    for (int i = 0; i < 20; ++i)
    {
        

    	lugarJuegosLabels[i] = gtk_grid_get_child_at(GTK_GRID(inputsGrid),1 ,i+2);
        
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
	if(strcmp(comparingValue, lugarJuegos[2]) == 0){
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

