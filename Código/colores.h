/********************************************************************
* Descripción: Librería de colores
* Autor: Tuquina, Fernando Nahuel
* Creaado el: Lunes 12 de Mayo del 2017
* Computadora: servidor
* Sistema: Linux 3.2.0-126-generic on x86_64
* Nota: la librería de colores SOLO funciona en Linux
* Copyright (c) 2017 #NO_COMPILA  All rights reserved.
********************************************************************/

void color_rojo(){
    printf("%c[%dm",0x1B,31);	// A través del printf se envía un valor en hexadecimal que indica que se va a
}								// modificar el color, el valor siguiente indica a qué color se cambiará.
void color_verde(){
    printf("%c[%dm",0x1B,32);
}
void color_amarillo(){
    printf("%c[%dm",0x1B,33);
}
void color_azul(){
    printf("%c[%dm",0x1B,34);
}
void color_morado(){
    printf("%c[%dm",0x1B,35);
}
void color_celeste(){
    printf("%c[%dm",0x1B,36);
}
void color_blanco(){
    printf("%c[%dm",0x1B,37);
}
void resaltar_rojo(){
    printf("%c[%dm",0x1B,41);
}
void resaltar_verde(){
    printf("%c[%dm",0x1B,42);
}
void resaltar_amarillo(){
    printf("%c[%dm",0x1B,43);
}
void resaltar_azul(){
    printf("%c[%dm",0x1B,44);
}
void resaltar_morado(){
    printf("%c[%dm",0x1B,45);
}
void resaltar_celeste(){
    printf("%c[%dm",0x1B,46);
}
void resaltar_blanco(){
    printf("%c[%dm",0x1B,47);
}

//Fin de la librería de colores
