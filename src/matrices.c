







/*

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

    resultadoString1 =  GTK_WIDGET(gtk_builder_get_object(builder, "labelRespuestaMate2"));
    resultadoString2 =  GTK_WIDGET(gtk_builder_get_object(builder, "labelRespuestaMate4"));
    resultadoString3 =  GTK_WIDGET(gtk_builder_get_object(builder, "labelRespuestaMate5"));

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

/*---------------- CSS ----------------------------------------------------------------------------------------------------
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

*/
