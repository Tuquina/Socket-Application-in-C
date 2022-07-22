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
#include <netinet/in.h>
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
    char op; // Caracter de opción para el menú     
    char mensaje[TAMANIO],salida[]="finConexionSSST";       
    int socketServidor, puerto, longitudMax=0, habilitarBroadcast=1;
    struct sockaddr_in serverAddr, 
                          cliaddr;

    // Comienzo de la lógica principal
    presentacion();  
    printf("\n\t\t/*******************************************************/");
    printf("\n\t\t/*           Se procederá a crear el socket            */");
    printf("\n\t\t/*******************************************************/\n\n");

    socketServidor = socket(AF_INET, SOCK_DGRAM, 0);    // Creamos el socket para el servidor
    if(socketServidor < 0){
        color_rojo();
        printf("\nError al crear el socket.\n");
        color_blanco();
        return 1;
    }
    color_verde();
    printf("\t\t\t\tSocket creado correctamente.\n");
    color_blanco();
    // SO_BROADCAST: habilita el envio de broadcast
    if (setsockopt(socketServidor, SOL_SOCKET, SO_BROADCAST, &habilitarBroadcast, sizeof(habilitarBroadcast))) {
        color_rojo();
        printf("\n\tNo se pudo abrir el socket para usar con broadcast");
        color_blanco();
        return 1;
    }

    //Obtengo puerto aleatorio entre 50 000 y 50 100
    srand (getpid());           //Inicializo el timmer con el número de proceso del programa
	puerto = rand(); 	
    puerto=puerto%100 + 50000;          
    color_verde();
	printf("\t\t\t\tPuerto abierto: ");
    color_blanco();
    printf("%d\n\n",puerto);

    /*     Servidor    */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(puerto);
    serverAddr.sin_addr.s_addr = htons(INADDR_ANY);

    bind(socketServidor,(struct sockaddr_in *)&serverAddr,sizeof(serverAddr));  //System call BIND

    /*     Cliente    */
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port=htons(2500);
    cliaddr.sin_addr.s_addr = inet_addr("255.255.255.255");    // Dirección de broadcast para todos los clientes de esta red

    pausa();
    do{
		system("clear");
		op=menu();
		system("clear");
		switch(op){
			case '1':     do{
                                printf("\n\t\t/*******************************************************/");
                                printf("\n\t\t/*         Ingrese el mensaje que desea enviar:        */");
                                printf("\n\t\t/*******************************************************/\n\n\n\t\t");
                                color_amarillo();
                                fgets(mensaje,TAMANIO,stdin);
		                        mensaje[strlen(mensaje)-1]='\0';
                                fflush( stdin );
                                color_blanco();
                                if(strlen(mensaje)>200){
                                    longitudMax=1;
                                }
                                else{
                                    longitudMax=0;
                                }
                                if(longitudMax==1){
                                    color_rojo();
                                    printf("\n\n\tEl mensaje a enviar debe ser menor o igual a 200 caracteres.");
                                    printf("Ingrese un texto nuevo.\n\n");
                                    color_blanco();
                                    pausa();
                                    system("clear");
                                }
                            }while(longitudMax==1);
                            
                            if(sendto(socketServidor, mensaje, strlen(mensaje), 0,
                                (struct sockaddr*)&cliaddr, sizeof(cliaddr)) < 0){
                                color_rojo();
                                printf("\n\tNo fue posible enviar el mensaje.\n\n");
                                color_blanco();
                                return 1;
                            }
                            color_verde();
                            printf("\n\t\tEl mensaje fue enviado correctamente.\n\n"); 
                            color_blanco();    
                            pausa();
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
    

    if(sendto(socketServidor, salida, strlen(salida), 0,
                                (struct sockaddr*) &cliaddr, sizeof(cliaddr)) < 0){
                                color_rojo();
                                printf("\n\tNo fue posible enviar el mensaje de cierre.\n\n");
                                color_blanco();
                                return 1;
                            }
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
	printf("\n\n\n\n\t\t\tBROADCASSST - Aplicacion Servidor\n\n");
	color_verde();
	printf("\t\t\tFecha actual: %d/%d/%d\n\n",actual.dia,actual.mes,actual.anio);
	color_blanco();
	printf("\t\t\tMenu de opciones: \n\n");
	color_amarillo();
	printf("\t\t\t    1 -> Enviar un mensaje\n");
	printf("\t\t\t    2 -> Ver presentacion\n");
	printf("\t\t\t    3 -> Salir\n");
	color_blanco();
	printf("\n\t\t\tSeleccionar una opcion:  ");
	op=fgetc(stdin);
	if(op!='\n')   fgetc(stdin);
	return op;
}
/*------------------------------------------------------------------------------------------*/
