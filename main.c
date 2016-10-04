#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
 

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "src/proyecto0.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "menuProgram"));
    gtk_builder_connect_signals(builder, NULL);
 
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}

void runRutas()
{
  
    system("cd src ; ./rutas &");
}
void runMochila()
{
  
    system("./src/mochila &");
}
void runRemplazo()
{
  
    system(".cd src ; ./src/equipos Remplazo &");
}
void runArboles()
{
  
    system("cd src ; ./pending Arboles &");
}
void runSeries()
{
  
    system("cd src ; ./series &");
}
void runMultiplicacion()
{
  
    system("cd src ; ./pending Multiplicacioxn &");
}
 
// called when window is closed
void closeMainWindow()
{
    gtk_main_quit();
}