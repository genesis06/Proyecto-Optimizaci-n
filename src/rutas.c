#include <gtk/gtk.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
//header for conseole warnings
int min(int num1, int num2, int x, int y, int matrixNumber);
int sumElements(int num1, int num2);
void pathBetweenNodes(int i, int j, int type);
void calculateAllPaths();
void drawMatrix();
void showInput();
void showintermediate();
void showResults();
void getTextInputValues();
void floydAlgorithm();
void printDistances(int m[10][10]);
void printPaths(int m[10][10]);
void updateMatrixSize();

//variables
int MAX_MATRIX_SIZE = 10;
int MATRIX_SIZE;
GtkWidget *inputBox;
GtkWidget *intermediateBox;
GtkWidget *resultBox;
GtkWidget *scrollContent;
GtkWidget *comboBox;
GtkWidget *textInputsMatrix[10][10];
int inputValuesMatrix[10][10];
GtkTextBuffer *bufferIntermediate; //buffer para la pantalla de resultados
GtkTextBuffer *bufferResult;//
GtkWidget *button;

//objetos temporales, necesitan ser borrados
int D0[10][10];

int D1[10][10];

int P[10][10];
char distancesString[100000] = "";
char pathsString[1000] = "";
char path[100000]="";
char resultString[1000000]="";
char *nodeNames[27] = {"A","B","C","D","E","F","G","H","I","G","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};




//Calcula todas las posibles rutas de una matriz
void calculateAllPaths(){
    strcat(path, "\n");
    for(int i=0; i<MATRIX_SIZE; i++){
        for(int j=0; j<MATRIX_SIZE; j++){
            pathBetweenNodes(i+1,j+1,0); //calcula ruta optima entre cualquier par de nodos     
            strcat(path, "\n");
        }
    }
    printf("%s\n", path);
}

//Esta funcion esconde los inputs para cambiar tamaño de matriz
void drawMatrix()
{
    updateMatrixSize();
     for (int i = 0; i < MAX_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MAX_MATRIX_SIZE; ++j)
        {
            if (i >= MATRIX_SIZE || j >= MATRIX_SIZE)
           {
               //mostrar
                gtk_widget_hide(GTK_WIDGET (textInputsMatrix[i][j])); 
            }
            else    
           {
               //ocultar
               gtk_widget_show(GTK_WIDGET (textInputsMatrix[i][j]));
           }   
           
        }
    }

}

//left panel buttons 
void showInput()
{
    gtk_widget_hide(resultBox);
    gtk_widget_hide(intermediateBox);
    gtk_widget_show(inputBox);

    gtk_widget_queue_draw(scrollContent);

}

void showintermediate()
{
    gtk_widget_hide(inputBox);
    gtk_widget_hide(resultBox);
    gtk_widget_show(intermediateBox);

    gtk_widget_queue_draw(scrollContent);  

}

//implementar la consturccion de string en esta parte
void showResults()
{
    char resultString[1000000]="";
    resultString[0] = '\0';
    memset(resultString,0,strlen(resultString));
    getTextInputValues();
    //printDistances(D0);
    //printf("\n%s\n", distancesString);

    floydAlgorithm(); // realiza el algoritmo de floyd
    printDistances(D1); // contruye el string de distancias para imprimir
    printPaths(P);      // contruye el string de distancias para imprimir
    printf("\n%s\n", distancesString);
    //printf("%s\n", pathsString);
    //printf("%s\n", path);
    
    //unir strings
    strcat(distancesString, pathsString);
    strcat(distancesString, path);
    strcat(resultString, distancesString);

    //actualizar resultados
    bufferResult = gtk_text_view_get_buffer (GTK_TEXT_VIEW (resultBox));
    gtk_text_buffer_set_text (bufferResult, resultString, -1);

    //cambiar la visibilidad
    gtk_widget_hide(intermediateBox);
    gtk_widget_hide(inputBox);
    gtk_widget_show(resultBox);

    gtk_widget_queue_draw(scrollContent);  

}



//utils functions for interfance

//this function replaces the textInputsMatrix with curret values
void getTextInputValues()
{
    for (int i = 0; i < MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MATRIX_SIZE; ++j)
        {
            gchar *currentTextInputText;
            currentTextInputText = gtk_entry_get_text(GTK_ENTRY(textInputsMatrix[i][j]));
            int newValue = atoi(currentTextInputText);
            D0[i][j] = newValue;
        }
    }
    //inputValuesMatrix
     printf("open from file, Allan");
}

//updates the matriz size value
void updateMatrixSize()
{
    MATRIX_SIZE = gtk_combo_box_get_active(GTK_COMBO_BOX(comboBox));
    MATRIX_SIZE++;


}

void saveTable()
{
    //esta funcionalidad ocupamoverse al lugar adecuado
    //Implementar esto, guardar la tabla D0 en el archivo
    
}


//utils functions general
//this functions recieves a matrix and returns a visual representation in a string or buffer
//char[] convertToString(char[][] matrixToPrint)



//window controllers
void closeWindow()
{
    gtk_main_quit();
}


///funciones del algoritmo de floyd


void pathBetweenNodes(int i, int j, int type){
    char node[100] = "";
    if((P[i-1][j-1])==0){
        if(type==0){
            //printf("%d\n %d\n", i ,j);    
            sprintf(node, "%s -> %s ", nodeNames[i-1], nodeNames[j-1]);
            strcat(path, node);
        }
        else if(type ==1){
            //printf("%d\n ", i );
            sprintf(node, "%s -> ", nodeNames[i-1]);
            strcat(path, node);
        }
        else{
            //printf("%d\n ", j );  
            sprintf(node, "%s ", nodeNames[j-1]);
            strcat(path, node);
        }
    }
    else{
        pathBetweenNodes(i,P[i-1][j-1], 1);
        pathBetweenNodes(P[i-1][j-1],j, 0);
    }
}

void floydAlgorithm(){
    //Initialize P
    for ( int i = 0; i < MATRIX_SIZE; i++ ) {
        for ( int j = 0; j < MATRIX_SIZE; j++){
             P[i][j] = 0;
        }
    }
    
    for(int D=0; D<MATRIX_SIZE; D++){
        for ( int i = 0; i < MATRIX_SIZE; i++ ) {
            for (int j = 0; j < MATRIX_SIZE; j++){
                 D1[i][j] = min(D0[i][j], sumElements(D0[i][D] , D0[D][j] ),i,j, D+1);
            }
        }
        memcpy(D0,D1,10*10*sizeof(int)); 
    }   
    calculateAllPaths();
}


void printDistances(int m[10][10]){
    
    char row[50] = "";
    char lineRow[100] = "";
    
    for (int i = 0; i < MATRIX_SIZE; i++ ) {
        strcpy(row, "");
        strcpy(lineRow, "");
       for (int j = 0; j < MATRIX_SIZE; j++ ) {

          char num[50] = "";
          char line[50] = "";
          sprintf(line, "____");
          sprintf(num, "|  %d  ", m[i][j]);
          strcat(row, num);
          strcat(lineRow, line);
          //printf("%d\t",m[i][j] );
        }
        //printf("\n");
        strcat(row, "|\n");
        strcat(lineRow, "\n");
        strcat(distancesString, lineRow);
        strcat(distancesString, row);
    }
    strcat(distancesString, lineRow);
}

void printPaths(int m[10][10]){
    
    char row[50] = "";
    char lineRow[100] = "";
    char tableP[50] = "";
    sprintf(tableP, "Tabla P:");
    strcat(pathsString, tableP);
    sprintf(tableP, "\n");
    strcat(pathsString, tableP);
    for (int i = 0; i < MATRIX_SIZE; i++ ) {
        strcpy(row, "");
        strcpy(lineRow, "");
       for (int j = 0; j < MATRIX_SIZE; j++ ) {

          char num[50] = "";
          char line[50] = "";
          sprintf(line, "___");
          sprintf(num, "|  %d  ", m[i][j]);
          strcat(row, num);
          strcat(lineRow, line);
        }
        //printf("\n");
        strcat(row, "|\n");
        strcat(lineRow, "\n");
        strcat(pathsString, lineRow);
        strcat(pathsString, row);
    }
    strcat(pathsString, lineRow);
}

int sumElements(int num1, int num2){
    if(num1 == -1 || num2 == -1){
        return -1;
    }
    else {
        return num1+num2;
    }

}

int min(int num1, int num2, int x, int y, int matrixNumber){
    if(num1 == -1 && num2 == -1){
        return -1;
    }
    else if(num1 == -1){
        P[x][y]=matrixNumber;
        return num2;
    }
    else if(num2 == -1){
        return num1;
    }
    else if(num1 > num2){
        P[x][y]=matrixNumber;
        return num2;
    }
    else{
        return num1;
    }

}

static void showOpenFile(GtkWidget* button, gpointer window)
{
     //Contruccion Dialog
    GtkWidget *dialog;

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
            for (int ii = 0; ii < MAX_MATRIX_SIZE; ++ii)
            {
                
                for (int jj = 0; jj < MAX_MATRIX_SIZE; ++jj)
                {  
                    gtk_widget_hide(GTK_WIDGET( textInputsMatrix[ii][jj]));
                }
            }


            //Leer del Archivo
            FILE *infile;
            
            char grid[10][10];
            unsigned int num_rows = 4;
            infile = fopen(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)), "r");
         
            int character;
            unsigned int cont = 0;
            unsigned int row = 0;
            unsigned int column = 0;
            unsigned int i ;
            unsigned int j ;

            // Iterar hasta el final del documento
            while (!feof(infile))
            {
                // Scanea el siguiente char que encuentre
                fscanf(infile, "%d", &character);
        
                // Set appropriate cell to next character.
                grid[row][column] = character;
                
                    
                //printf("\nRegistro %d in R-%d  and C-%d ", character,row,column);
                //-----------------------------------------------------------------------------------------------------------
                char newChar[3];
                snprintf(newChar, 3, "%d", character);            
                //mostrar celdas y cargar valores
                gtk_widget_show (GTK_WIDGET(textInputsMatrix[column][row]));
                if(row == (column))
                {
                    gtk_entry_set_placeholder_text (GTK_ENTRY (textInputsMatrix[column][row]), "0");
                    gtk_widget_set_can_focus (GTK_WIDGET (textInputsMatrix[column][row]),false);
                }
                else
                {
                    gtk_entry_set_text (GTK_ENTRY (textInputsMatrix[column][row]), newChar);
                }

                ++column;
                ++cont;
                //Salto de Linea     
                if(column==num_rows)
                {
                        cont = 0;
                        column = 0;
                        row++;                  
                }   
                                    
            }

            // Cerrar Archivo
            fclose(infile);
  
        }
    else
        g_print("You pressed Cancel\n");
    
}

// Carrgar y guardar archivo
 void showSaveFile(GtkWidget* button, gpointer window)
{
     //Contruccion Dialog
    GtkWidget *dialog;

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
            //Escribir en el Archivo
           
            FILE *outfile;
          
            outfile = fopen(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)), "wt");

            
            for (int i = 0; i < 5; i++ ) {
            
               for (int j = 0; j < 5; j++ ) 
               {

            
                //fputs( D0[i][j],outfile);
            
                }
            
                        //fputs( "\n",outfile);
            }
           
        fclose(outfile);
        }
    else
        g_print("You pressed Cancel\n");
    gtk_widget_destroy(dialog);
}






/////--------------------------main-----------------------

int main(int argc, char **argv)
{
    
    GtkWidget       *window;
    GtkGrid    *inputsGrid;
    GtkBuilder      *builder;
   

    //iniciacion ventana
    gtk_init(&argc, &argv);
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "rutas-2.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(builder, "rutasWindow"));
    
    //conseguir objetos
    inputBox = GTK_WIDGET(gtk_builder_get_object(builder, "inputBox"));
    intermediateBox = GTK_WIDGET(gtk_builder_get_object(builder, "textIntermadiate"));
    resultBox = GTK_WIDGET(gtk_builder_get_object(builder, "textResult"));
    scrollContent = GTK_WIDGET(gtk_builder_get_object(builder, "scrolledwindow1"));
    comboBox = GTK_WIDGET(gtk_builder_get_object(builder, "comboboxtext1"));
    inputsGrid =  GTK_GRID(gtk_builder_get_object(builder, "grid3"));
    button = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
    g_signal_connect(button, "clicked", G_CALLBACK(showOpenFile), window);



    MATRIX_SIZE = gtk_combo_box_get_active (GTK_COMBO_BOX(comboBox));
    MATRIX_SIZE++;

    for(int x=0; x<MATRIX_SIZE; x++){
        for(int y=0; y<MATRIX_SIZE; y++){
            D0[x][y]=-1;
            D1[x][y]=-1;
        }
    }
    
    for (int i = 0; i < MAX_MATRIX_SIZE; ++i)
    {
        for (int j = 0; j < MAX_MATRIX_SIZE; ++j)
        { 
            //GtkWidget *entry;
            //add one input and store reference
            textInputsMatrix[i][j] = gtk_entry_new ();
            gtk_entry_set_max_length (GTK_ENTRY (textInputsMatrix[i][j]),3);
            if(i ==j)
            {
                gtk_entry_set_placeholder_text (GTK_ENTRY (textInputsMatrix[i][j]), "0");
                gtk_widget_set_can_focus (GTK_WIDGET (textInputsMatrix[i][j]),false);
            }
            else
            {
                gtk_entry_set_text (GTK_ENTRY (textInputsMatrix[i][j]), "-1");
            }
            gtk_widget_show (textInputsMatrix[i][j]);
            gtk_entry_set_max_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 3);
            gtk_entry_set_width_chars(GTK_ENTRY (textInputsMatrix[i][j]), 3);
            gtk_grid_attach (inputsGrid,textInputsMatrix[i][j],i + 1,j + 1,1,1);
        }
    }

    gtk_widget_hide(resultBox);
    gtk_widget_hide(intermediateBox);
   
    gtk_builder_connect_signals(builder, NULL);

    gtk_widget_show(window);                
    gtk_main();
    
    return 0;
}
