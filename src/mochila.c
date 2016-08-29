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
GtkWidget *button;

// Una función de utilidad que devuelve máximo de dos números enteros
static int max(int a, int b) { return (a > b)? a : b; }
 
// Devuelve el valor máximo que se puede poner en una mochila de la capacidad W
static int knapSack(int W, int wt[], int val[], int n)
{
   // Caso Base
   if (n == 0 || W == 0)
       return 0;
 
    // Si el peso del elemento enésimo es más que la capacidad de la mochila W, a continuación,
    // Este artículo no se puede incluir en la solución óptima
   if (wt[n-1] > W)
       return knapSack(W, wt, val, n-1);
 
   // Devuelve el máximo de dos casos:
    // (1) número de ítems incluidos
    // (2) no incluido
   else return max( val[n-1] + knapSack(W-wt[n-1], wt, val, n-1),
                    knapSack(W, wt, val, n-1)
                  );
}

 static void knapSackProblem(GtkWidget* button, gpointer window)
{
    printf("%s\n","La máxima ganancia es");
    int val[] = {11, 7, 12};
    int wt[] = {4, 3, 5};
    int  W = 10;
    int n = sizeof(val)/sizeof(val[0]);
    printf("%d\n", knapSack(W, wt, val, n));

}

int main(int argc, char *argv[])
{
    GtkBuilder      *builder;
    GtkWidget       *window;
 
    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "src/mochila.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "mochilaWindow"));
    gtk_builder_connect_signals(builder, NULL);

    button = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
    g_signal_connect(button, "clicked", G_CALLBACK(knapSackProblem), window);
 
    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
    return 0;

}



