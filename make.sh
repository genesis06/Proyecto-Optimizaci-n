#!/bin/bash

rm Proyecto0
cd src 
rm rutas pending mochila
gcc -rdynamic -o rutas rutas.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic -Wunused-function
gcc -rdynamic -o pending pending.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic 
gcc -rdynamic -o mochila mochila.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic 
cd ..

gcc -rdynamic -o Proyecto main.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic 

