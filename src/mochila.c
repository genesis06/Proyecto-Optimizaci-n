#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int cantidadMaxima;
int cantidadObjetos;
int tipo;//0=0/1, 1= bounded, 2= unbounded
int matrizValores[20][3];
char *nombreObjetos[20];

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "src/mochila.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "mochilaWindow"));
    gtk_builder_connect_signals(builder, NULL);
 
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;
}
