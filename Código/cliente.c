/*------------------------------------------------------------------------------------------*/
/*                              
            Grupo Nº5 - Protocolos de Comunicación TCP/IP - 2021   

            Integrantes:
                            Berretta Gali, Santiago Martín
                            Gianotti, Santiago
                            Latina, Santiago
                            Tuquina, Fernando Nahuel
                                                                                            */               
/*------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------*/
/*                              Archivos de cabecera                                        */               
/*------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include "colores.h"
#define  TAMANIO  1000

/*------------------------------------------------------------------------------------------*/
/*                             Definición de estructuras                                    */               
/*------------------------------------------------------------------------------------------*/
typedef struct{
		int dia,mes,anio;
	      }fecha;

/*------------------------------------------------------------------------------------------*/
/*                             Declaración de funciones                                     */               
/*------------------------------------------------------------------------------------------*/
void mostrar_logo();
fecha fecha_actual();
void pausa();
char menu();
void presentacion();

/*------------------------------------------------------------------------------------------*/
/*                                   PROGRAMA PRINCIPAL                                     */               
/*------------------------------------------------------------------------------------------*/

int main(int argc, char *argv[]){

    // Definición de variables
    int socketCliente,reinicio;
    char op; // Caracter de opción para el menú     
    char mensaje[TAMANIO],salida[]="finConexionSSST",hora[128];  
    struct sockaddr_in server_address, 
                       client_address;
    int client_struct_length = sizeof(client_address);
    int server_struct_length = sizeof(server_address);

    // Comienzo de la lógica principal
    presentacion();  
    printf("\n\t\t/*******************************************************/");
    printf("\n\t\t/*           Se procederá a crear el socket            */");
    printf("\n\t\t/*******************************************************/\n\n");

    socketCliente = socket(AF_INET, SOCK_DGRAM, 0); //Se crea el socket tipo UDP
    if(socketCliente < 0){
        color_rojo();
        printf("\nError al crear el socket.\n");
        color_blanco();
        return 1;
    }
    color_verde();
    printf("\t\t\t\tSocket creado correctamente.");
    color_blanco();

    /*     Cliente    */
    client_address.sin_family = AF_INET; 
    client_address.sin_port = htons(2500); 
    client_address.sin_addr.s_addr = htons(INADDR_ANY); 

    if(bind(socketCliente, (struct sockaddr*)&client_address, sizeof(client_address)) < 0){
        color_rojo();
        printf("\n\n\tError en la system call bind.\n\n");
        color_blanco();
        return 1;
    }
    color_verde();
    printf("\n\t\t\t    Configuracion del socket terminada.\n\n");
    color_blanco();

    pausa();
    do{
		system("clear");
		op=menu();
		system("clear");
        reinicio=1;
		switch(op){
			case '1':   
                        while(reinicio){ 
                            printf("\n\t\t/*******************************************************/");
                            printf("\n\t\t/*        Se está esperando a recibir un mensaje:      */");
                            printf("\n\t\t/*******************************************************/\n");
                            memset(mensaje, '\0', sizeof(mensaje)); // Se limpia el buffer del mensaje:
                            if (recvfrom(socketCliente, mensaje, sizeof(mensaje), 0,(struct sockaddr*) &server_address,             &server_struct_length) < 0){
                                color_rojo();
                                printf("\n\n\tEl mensaje no pudo ser recibido correctamente.\n");
                                color_blanco();
                                return 1;
                            }              
                            if(strcmp(mensaje,salida)==0){
                                reinicio=0;
                                color_rojo();
                                printf("\n\t\tEl servidor se ha cerrado, volviendo al menu principal.\n");
                                color_blanco();
                                pausa();
                            }
                            else{
                                color_verde();
                                printf("\n\t\tSe ha recibido un nuevo mensaje: \n");
                                color_amarillo();
                                printf("\n\t\t%s\n", mensaje);
                                memset(mensaje, '\0', sizeof(mensaje)); // Se limpia el buffer del mensaje:
                                color_azul();
                                printf("\n\t\tInformación:\n\n");
                                color_blanco();
                                time_t tiempo = time(0);
                                struct tm *tlocal = localtime(&tiempo);                              
                                strftime(hora,128,"\t\tFecha del mensaje:\t%d/%m/%y\n\t\tHora del mensaje:\t%H:%M:%S",tlocal);
                                printf("%s\n",hora);
                                printf("\t\tIP Origen:\t\t%s\n", inet_ntoa(server_address.sin_addr));        
                                printf("\t\tPuerto origen:\t\t%i\n\n", ntohs(server_address.sin_port));;
                            }                      
                        }                           
						break;
			case '2': 	presentacion();
                        pausa();
                        system("clear");
						break;
			case '3': 	system("clear");
                        color_rojo();
                        printf("\n\tSaliendo del programa...\n\n");
                        color_blanco();
						break;
			default: 	color_rojo();
			            printf("\n\t\tOpcion NO valida\n");
			            color_blanco();
                        pausa();
						break;
		}
	}while(op!='3');
    return 0;
}

/*------------------------------------------------------------------------------------------*/
/*                             Definición de funciones                                      */               
/*------------------------------------------------------------------------------------------*/

fecha fecha_actual(){		// Toma la fecha actual del sistema y la devuelve como una estructura tipo fecha.
    fecha f;
    time_t ahora;
    struct tm *fech;
    time(&ahora);
    fech=localtime(&ahora);
    f.dia=(fech->tm_mday);
    f.mes=(fech->tm_mon+1);
    f.anio=(fech->tm_year+1900);
    return f;
}

/*------------------------------------------------------------------------------------------*/
void mostrar_logo(){
	FILE *p;
	char c;
	p=fopen("logo.txt","r");
    color_amarillo();
	if(p==NULL){
		exit(0);
	}
	while(feof(p)==0){
		c=fgetc(p);
		if(feof(p)==0){
			printf("%c",c);
		}
	}
	color_blanco();
	fclose(p);
	printf("\n");
	return;
}

/*------------------------------------------------------------------------------------------*/
void pausa(){
    char c;
    printf("\nPresione enter para continuar...");
    c=fgetc(stdin);
	if(c!='\n')   fgetc(stdin);
    return;
}

/*------------------------------------------------------------------------------------------*/
void presentacion(){
    system("clear"); 
    color_blanco();   
    printf("\n\t\t/*******************************************************/");
    printf("\n\t\t/*             BIENVENIDO A BROADCASSST                */");
    printf("\n\t\t/*******************************************************/\n\n\n");
    mostrar_logo();
    return;
}   

/*------------------------------------------------------------------------------------------*/
char menu(){
	char op;
	fecha actual;
	actual=fecha_actual();
	color_azul();
	printf("\n\n\n\n\t\t\tBROADCASSST - Aplicacion Cliente\n\n");
	color_verde();
	printf("\t\t\tFecha actual: %d/%d/%d\n\n",actual.dia,actual.mes,actual.anio);
	color_blanco();
	printf("\t\t\tMenu de opciones: \n\n");
	color_amarillo();
	printf("\t\t\t    1 -> Escuchar mensajes\n");
	printf("\t\t\t    2 -> Ver presentacion\n");
	printf("\t\t\t    3 -> Salir\n");
	color_blanco();
	printf("\n\t\t\tSeleccionar una opcion:  ");
	op=fgetc(stdin);
	if(op!='\n')   fgetc(stdin);
	return op;
}

/*------------------------------------------------------------------------------------------*/
