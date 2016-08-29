/*
   ITCR - Investigación de Operaciones
*/
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
int comboSelect ;
GtkWidget *button;
GtkWidget *comboBox;
GtkWidget *dialog;

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
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (wt[i-1] <= w)
                 K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
	  
	  char num[50] = "";
          sprintf(num, "%d\t", K[i][w]);
          strcat(row, num);
         
       }
        strcat(row, "\n");
        strcat(matrizString, row);
   }

   printf("%s\n",matrizString );
	
   return K[n][W];
}



//-----------------------------Empieza Algoritmo Bounded----------------------------------------------

int n_bounded = sizeof (items_bounded) / sizeof (item_t_bounded);
 
int *knapsackBounded (int w) {
    int i, j, k, v, *mm, **m, *s;
    mm = calloc((n_bounded + 1) * (w + 1), sizeof (int));
    m = malloc((n_bounded + 1) * sizeof (int *));
    m[0] = mm;
    for (i = 1; i <= n_bounded; i++) {
        m[i] = &mm[i * (w + 1)];
        for (j = 0; j <= w; j++) {
            m[i][j] = m[i - 1][j];
            for (k = 1; k <= items_bounded[i - 1].count; k++) {
                if (k * items_bounded[i - 1].weight > j) {
                    break;
                }
                v = m[i - 1][j - k * items_bounded[i - 1].weight] + k * items_bounded[i - 1].value;
                if (v > m[i][j]) {
                    m[i][j] = v;
                }
            }
        }
    }
    s = calloc(n_bounded, sizeof (int));
    for (i = n_bounded, j = w; i > 0; i--) {
        int v = m[i][j];
        for (k = 0; v != m[i - 1][j] + k * items_bounded[i - 1].value; k++) {
            s[i - 1]++;
            j -= items_bounded[i - 1].weight;
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
double best_value;
 
void knapsackUnbounded (int i, double value, double weight, double volume) {
    int j, m1, m2, m;
    if (i == n_unbounded) {
        if (value > best_value) {
            best_value = value;
            for (j = 0; j < n_unbounded; j++) {
                best[j] = count[j];
            }
        }
        return;
    }
    m1 = weight / itemsUnbounded[i].weight;
    m2 = volume / itemsUnbounded[i].volume;
    m = m1 < m2 ? m1 : m2;
    for (count[i] = m; count[i] >= 0; count[i]--) {
        knapsackUnbounded(
            i + 1,
            value + count[i] * itemsUnbounded[i].value,
            weight - count[i] * itemsUnbounded[i].weight,
            volume - count[i] * itemsUnbounded[i].volume
        );
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
    s = knapsackBounded(400);
    for (i = 0; i < n_bounded; i++) {
        if (s[i]) {
            printf("%-22s %5d %5d %5d\n", items_bounded[i].name, s[i], s[i] * items_bounded[i].weight, s[i] * items_bounded[i].value);
            tc += s[i];
            tw += s[i] * items_bounded[i].weight;
            tv += s[i] * items_bounded[i].value;
        }
    }
    printf("%-22s %5d %5d %5d\n", "Cuenta, Peso, Valor:", tc, tw, tv);
}

 static void knapSackUnBoundedProblem()
{
   
    count = malloc(n_unbounded * sizeof (int));
    best = malloc(n_unbounded * sizeof (int));
    best_value = 0;
    knapsackUnbounded(0, 0.0, 25.0, 0.25);
    int i;
    for (i = 0; i < n_unbounded; i++) {
        printf("%d %s\n", best[i], itemsUnbounded[i].name);
    }
    printf("Mejor Valor: %.0f\n", best_value);
    free(count); free(best);
    
}
//--------------------------------------------------------Switch ComboBox
void resolver (GtkWidget* button, gpointer window){
 comboSelect = gtk_combo_box_get_active(GTK_COMBO_BOX(comboBox));
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
		char firstLane[255] = "Nada" ;

		//Leer hasta que no hay lineas
		while (fgets(buff, 255, (FILE*)infile)){  
			
			//Lee primera Linea	
			if(strcmp(firstLane, "Nada") == 0){
				
			   strcpy(firstLane, buff);
			   printf("Primera Linea %s\n", firstLane );
			}else{
			//Lee resto de lineas
		           printf("%s\n", buff );
			}
		} 	
		// Cerrar Archivo
		fclose(infile);
		}
	else
		g_print("Presionó Cancelar\n");
           
	gtk_widget_destroy(dialog);
	
}

//--------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    
    GtkWidget       *window;
    GtkBuilder      *builder;

    gtk_init(&argc, &argv);

    
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "src/mochila.glade", NULL);
 
    window = GTK_WIDGET(gtk_builder_get_object(builder, "mochilaWindow"));
    gtk_builder_connect_signals(builder, NULL);

   
    comboBox = GTK_WIDGET(gtk_builder_get_object(builder, "comboboxtext3"));
    comboSelect = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBox));
    
    button = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
    g_signal_connect(button, "clicked", G_CALLBACK(resolver), window);

    button = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
    g_signal_connect(button, "clicked", G_CALLBACK(showOpenFile), window);
  

    g_object_unref(builder);
 
    gtk_widget_show(window);                
    gtk_main();
 
    return 0;

}
