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
  int i, w,j;
   int K[n+1][W+1];
 
   // Build table K[][] in bottom up manner
   for (i = 0; i <= n; i++)
   {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   }

    unsigned int column = 0;
    char matrizString[300] = "";

    //Crea el String
    char row[50] = "";

    for (i = 0; i < n+1; i++ ) {
        strcpy(row, "");
       for (j = 0; j < W+1; j++ ) {

          char num[50] = "";
          sprintf(num, "%d\t", K[i][j]);
          strcat(row, num);
          //printf("%d\t",m[i][j] );
        }
        //printf("\n");
        strcat(row, "\n");
        strcat(matrizString, row);
    }
   printf("%s\n",matrizString );
	
  
   return K[n][W];
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



