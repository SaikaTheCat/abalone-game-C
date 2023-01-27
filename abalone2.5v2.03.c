/*
 ============================================================================
 Name        : abalone.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#define C_F 9
#define C_C 17
#define TRUE 1
#define FALSE 0
#define BLANCO 'b'
#define NEGRO 'n'
#define VACIO 'v'
#define C_HUECO 70
typedef struct{
		int fila;
		int columna;
}tipo_posicion;
int juego_terminado;
int cant_max_jugadas;
int comienza_el_juego;
int turno;
char nombre1[20];
char nombre2[20];
enum tipo_seleccion{
	UNICO=0,
	DP=1,
	DS=2,
	HORIZONTAL=3
};
enum turno{
	JUGADOR=0,
	CPU=1
};
/*
 *Esta funcion seria la encargada de reunir los datos del jugador y del rival(CPU) de acuerdo a las preferencias del jugador local.
 *Parametros:
 *				*color, llama a la direccion de memoria de color para asignar el color del jugador local
 *				*color_enemigo,	llama la direccion de memoria de color_enemigo para asignar el color del rival
 *Retorno:
 *				Ninguno. */
void eleccion(char *color,char *color_enemigo);
/*Esta funcion contiene una matriz de char donde pasa los valores iniciales a la matriz principal a ser usada
 * Parametros:
 *	 	 	 	 tablero[C_F][C_C],recibe valor de la matriz inicial
 * Retorno:
 	 	 	 	 Ninguno*/
void inicializar_tablero(char tablero[C_F][C_C]);
/*Funcion para imprimir la matriz inicial
 *Parametros:
 *				 tablero[C_F][C_C],contiene la matriz inicial
 *Retorno:
 *				 Ninguno	*/
void imprimir_tablero(char tablero[C_F][C_C]);
/*Funcion para imprimir una referencia para poder guiarse al mover 1,2 o 3 canicas segun el tipo de seleccion que sea
 * Parametros:
 * 				tipo_seleccion, guarda los datos de seleccion donde se preguntara que tipo de seleccion es el que esta pasando a la funcion
 * 				cadena[4], cadena de caracteres de dimension 4 para poder guardar las fichas representativas segun el tipo de seleccion y orden que de el usuario
 * Retorno:
 * 				Ninguno	*/
void imprimir_guia_de_direccion(int tipo_seleccion,char cadena[4]);
/*Imprime la jugada hecha por la CPU, la ubicacion de la canica inicial y la ubicacion final, como tambien guarda la cantidad de fichas obtenidas del rival y verifica si sigue el juego
 * Parametros:
 * 				tablero[C_F][C_C],tablero donde estan las canicas y muestra la modificacion hecha por la CPU
 * 				color_enemigo, el color del rival segun la eleccion hecha
 * 				movimiento_posible[C_HUECO],struct donde guarda la coordenada de los movimientos validos que puede hacer
 * 				x, variable entera donde esta guardada la posicion inicial de la fila de la canica seleccionada
 * 				y, variable entera donde esta guardada la posicion inicial de la columna de la canica seleccionada
 * 				color,color del jugador local
 * Retorno:
 * 				Ninguno				 */
void imprimir_historial_CPU(char tablero[C_F][C_C],char color_enemigo,tipo_posicion movimiento_posible[C_HUECO],int x, int y,char color);
/*Imprime la jugada hecha por el jugador, como tambien guarda la cantidad de fichas obtenidas del rival y verifica si el juego sigue
 * Parametros:
 * 				tablero[C_F][C_C],tablero donde estan las canicas y muestra la modificacion hecha por el jugador
 * 				color, color del jugador local
 * 				D,variable struct donde contiene la fila y columna del destino de la/las canica/as
 * 				color_enemigo, color del rival segun la elccion hecha
 *Retorno:
 *				Ninguno 				*/
void imprimir_historial_JUGADOR(char tablero[C_F][C_C],char color,tipo_posicion D,char color_enemigo);
/*Funcion donde verifica quien de los 2 tiene la mayor cantidad de fichas al cumplir las condiciones finales del juego
 * Parametros:
 * 				tablero[C_F][C_C],tablero donde tiene la informacion final del juego
 * 				color, color del jugador
 * 				color_enemigo, color del rival
 */
void verificar_resultado(char tablero[C_F][C_C],char color,char color_enemigo);
/*Funcion donde cambia las coordenadas de tipo entero de la matriz del tablero por una coordenada de caracteres del juego
 * Parametros:
 * 				fila,un dato entero que se le pasa como parametro para poder convertir la coordenada de la fila de la matriz a la fila del tablero del juego
 * 				columna,un dato entero que se le pasa como parametro para poder convertir la coordenada de la columna de la matriz a la columna del tablero del juego
 * 				retorno[2],cadena de dimension 2 donde se le pasa los valores de fila y columna en referencia al juego
 * Retorno:
 * 				Ninguno
 */
void pasar_referenchia(int fila,int columna,char retorno[2]);
/*Funcion donde se espera un "Enter" por parte del usuario para que la CPU pueda hacer su correspondiente movimiento\
 */
void esperar_enter();
/*Funcion que retorna los valores en caracteres del tablero del juego a las coordenadas de la matriz del tablero
 * Parametros:
 * 				fila,coordenada de la fila del tablero para pasar como coordenada de la matriz
 * 				columna,coordenada de la columna del tablero para pasar como coordenada de la columna
 * Retorno:
 * 				posicion, posicion de la fila y columna de la matriz (enteros)				*/
tipo_posicion retornar_posicion(char fila, char columna);
/*Funciones de verificaci처n de ingreso*/
/*Funcion donde verifica si las coordenadas ingresadas son validas o no
 * Parametros:
 * 				fila,fila ingresada por el usuario
 * 				columna,columna ingresada por el usuario
 * Retorno:
 * 				FALSE,no se puede
 * 				TRUE,se puede
 * 				 				*/
int verificar_posicion(char fila, char columna);
/*Revisa las coordenadas de las canicas ingresadas y verifica si lo que forma/forman es unico, horizontal, diagonal principal, diagonal secundaria, y tambien si son 2 o 3
 * Parametros:
 * 				A,struct donde se le pasa la coordenada de la 1ra canica ingresada
 * 				B,struct donde se le pasa la coordenada de la 2da canica ingresada
 * 				posicion_i[3],cadena donde se guarda A,B y el intermedio entre esos 2 si es que hay
 * 				*cant_canica, al saber de que tipo de seleccion es lo que forma A y B, se guarda del valor de la cantidad de canicas seleccionadas
 * 				*tipo_seleccion, se guarda el tipo de seleccion segun lo que forman A y B
 * Retorno:
 * 				FALSE,no encuentra la seleccion de acuerdo a las canicas seleccionadas
 * 				TRUE, se encuentra la seleccion y cantidad de canicas				*/
int cargar_canica(tipo_posicion A, tipo_posicion B, tipo_posicion posicion_i[3], int *cant_canica, int *tipo_seleccion);
/*Verifica si el color seleccionado por la coordenada que el usuario ingreso es la correcta o no
 * Parametros:
 * 				posicion_i[3],cadena donde se guardan los valores de las canicas a mover
 * 				cant_canica, la cantidad de canicas a mover
 * 				color, el color del usuario o jugador local
 * 				tablero[C_F][C_C],tablero del juego*
 * Retornar:
 	 	 	 	FALSE,no se puede
 	 	 	 	TRUE, se puede*/
int verificar_color(tipo_posicion posicion_i[3], int cant_canica, char color,char tablero[C_F][C_C]);
/*Funciones generar posibles movimientos*/
/*Verifica todos los posibles movimientos que se puedan hacer dependiendo del tipo de seleccion y si es que hay espacio vacio por donde moverse
 * Parametros:
 * 				posicion_i[3],cadena donde estan guardadas las coordenadas de las canicas seleccionadas
 * 				tipo_seleccion, la seleccion hecha mediante las canicas seleccionadas por el usuario
 * 				cant_canica, cantidad de canica seleccionadas por el usuario
 * 				tablero[C_F][C_C], tablero del juego
 * 				movimiento_posible[C_HUECO],vector donde se almacenan las coordenadas de los movimientos posibles a realizar
 * 				*cant_movimiento_posible,cantidad de los movimientos posibles que se van acumulando segun las verificaciones que se hacen dentro de la funcion para guardarse dentro del vector movimiento_posible
 *Retorno:
 *				FALSE,no se puede realizar ningun movimiento libre
 *				TRUE,hay movimientos que se puedan realizar 				*/
int posible_libre(tipo_posicion posicion_i[3], int tipo_seleccion, int cant_canica, char tablero[C_F][C_C], tipo_posicion movimiento_posible[C_HUECO], int *cant_movimiento_posible);
/*Verifica si es posible empujar a la/las canica/s enemigas
 * Parametros:
 * 				posicion_i[3],cadena donde estan guardadas las coordenadas de las canicas seleccionadas
 * 				tipo_seleccion,la seleccion hecha mediante las canicas seleccionadas por el usuario
 * 				cant_canica,cantidad de canica seleccionadas por el usuario
 * 				color,color de las canicas del jugador local
 * 				color_enemigo, color del rival o CPU
 * 				tablero[C_F][C_C],tablero del juego
 * 				movimiento_posible[C_HUECO],vector donde se almacenan las coordenadas de los movimientos posibles a realizar
 * 				*cant_movimiento_posible,cantidad de los movimientos posibles que se van acumulando segun las verificaciones que se hacen dentro de la funcion para guardarse dentro del vector movimiento_posible
 * Retorno:
 * 				TRUE,siempre retorna 1
 */
int posibles_empujes(tipo_posicion posicion_i[3], int tipo_seleccion, int cant_canica,char color,char color_enemigo, char tablero[C_F][C_C], tipo_posicion movimiento_posible[C_HUECO], int *cant_movimiento_posible);
/*Funciones contar*/
/*Funcion que cuenta la cantidad de canicas que tiene el rival en la diagonal principal para poder empujar
 * Parametros:
 * 				posicion_i[3],posicion de las canicas guardadas
 * 				color,color de las canicas del jugador
 * 				color_enemigo, color de la CPU
 * 				tablero[C_F][C_C],tablero del juego
 * Retorno:
 * 				contador, cantidad de canicas enemigas hacia la diagonal principal inferior				*/
int contar_enemiga_DP_inferior(tipo_posicion posicion_i[3], char color, char color_enemigo,char tablero[C_F][C_C]);
/*Funcion que cuenta la cantidad de canicas que tiene el rival en la diagonal principal para poder empujar
 * Parametros:
 * 				posicion_i[3],posicion de las canicas guardadas
 * 				color,color de las canicas del jugador
 * 				color_enemigo, color de la CPU
 * 				tablero[C_F][C_C],tablero del juego
 * Retorno:
 * 				contador, cantidad de canicas enemigas hacia la diagonal principal superior				*/
int contar_enemiga_DP_superior(tipo_posicion posicion_i[3], char color, char color_enemigo,char tablero[C_F][C_C]);
/*Funcion que cuenta la cantidad de canicas que tiene el rival horizontalmente para poder empujar
 * Parametros:
 * 				posicion_i[3],posicion de las canicas guardadas
 * 				color,color de las canicas del jugador
 * 				color_enemigo, color de la CPU
 * 				tablero[C_F][C_C],tablero del juego
 * Retorno:
 * 				contador, cantidad de canicas enemigas hacia la derecha				*/
int contar_enemiga_HORIZONTAL_derecha(tipo_posicion posicion_i[3],char color, char color_enemigo,char tablero[C_F][C_C]);
/*Funcion que cuenta la cantidad de canicas que tiene el rival horizontalmente para poder empujar
 * Parametros:
 * 				posicion_i[3],posicion de las canicas guardadas
 * 				color,color de las canicas del jugador
 * 				color_enemigo, color de la CPU
 * 				tablero[C_F][C_C],tablero del juego
 * Retorno:
 * 				contador, cantidad de canicas enemigas hacia la izquierda */
int contar_enemiga_HORIZONTAL_izquierda(tipo_posicion posicion_i[3],char color, char color_enemigo,char tablero[C_F][C_C]);
/*Funcion que cuenta la cantidad de canicas que tiene el rival en la diagonal secundaria para poder empujar
 * Parametros:
 * 				posicion_i[3],posicion de las canicas guardadas
 * 				color,color de las canicas del jugador
 * 				color_enemigo, color de la CPU
 * 				tablero[C_F][C_C],tablero del juego
 * Retorno:
 * 				contador, cantidad de canicas enemigas hacia abajo*/
int contar_enemiga_DS_inferior(tipo_posicion posicion_i[3],char color, char color_enemigo,char tablero[C_F][C_C]);
/*Funcion que cuenta la cantidad de canicas que tiene el rival en la diagonal secundaria para poder empujar
 * Parametros:
 * 				posicion_i[3],posicion de las canicas guardadas
 * 				color,color de las canicas del jugador
 * 				color_enemigo, color de la CPU
 * 				tablero[C_F][C_C],tablero del juego
 * Retorno:
 * 				contador, cantidad de canicas enemigas hacia arriba*/
int contar_enemiga_DS_superior(tipo_posicion posicion_i[3],char color, char color_enemigo,char tablero[C_F][C_C]);
/*juegan*/
/*Funcion en donde estan estructuradas las funciones para hacer posible la entrada y salida del juego del usuario
 * Parametros:
 * 				tablero[C_F][C_C],tablero en donde se realiza el juego
 * 				color, color del usuario
 * 				color_enemigo, color del rival o CPU
 * 				*cant_movimiento_posible,cantidad de movimientos posibles a realizar por cada turno en que se seleccione determinadas canicas
 * 				movimiento_posible[C_HUECO],vector en donde esta guardado los posibles movimientos a realizar
 * 				*cant_canica,cantidad de canicas seleccionadas por el usuario
 * 				*posicion_i[3],vector en donde se guardan las coordenadas de las canicas seleccionadas
 * 				*tipo_seleccion, el tipo de seleccion que se genera mediante la seleccion de las canicas que introduce el usuario
 * Retorno:
 * 				Ninguno				*/
void juega_jugador(char tablero[C_F][C_C],char color,char color_enemigo, int *cant_movimiento_posible,tipo_posicion movimiento_posible[C_HUECO],int *cant_canica,tipo_posicion posicion_i[3],int *tipo_seleccion);
/*Funcion en donde se implementan los movimientos aleatorios de la CPU
 * Parametros:
 * 				posicion_i[3],posicion que la CPU selecciona al encontrar su color
 * 				tipo_seleccion, el tipo de seleccion segun lo que la CPU encontro
 * 				cant_canica, cantidad de canica que selecciona
 * 				tablero[C_F][C_C],tablero del juego
 * 				movimiento_posible[C_HUECO],movimiento posible que puede hacer al seleccionar la ficha
 * 				*cant_movimiento, la cantidad de movimiento que acumula con cierta ficha
 * 				color_enemigo, el color que le pertenece
 * 				color, color del rival (usuario local)
 * Retorno:
 * 				Ninguno				 */
void movimiento_CPU(tipo_posicion posicion_i[3], int tipo_seleccion, int cant_canica, char tablero[C_F][C_C], tipo_posicion movimiento_posible[C_HUECO], int *cant_movimiento_posible,char color_enemigo,char color);
/*Movimiento*/
/*Funcion que hace mover en linea a las canicas seleccionadas en diagonal principal superior
 *Parametros:
 *				posicion_i[3],vector donde estan guardadas las coordenadas de las canicas
 *				cant_canica, cantidad de canicas seleccionadas
 *				color,color del jugador local
 *				color_enemigo, color la CPU
 *				tablero[C_F][C_C],tablero del juego
 *Retorno:
 *				Ninguno				 */
void movimiento_DP_EN_LINEA_superior(tipo_posicion posicion_i[3], int cant_canica,char color, char color_enemigo,char tablero[C_F][C_C]);
/*Funcion que hace mover en linea a las canicas seleccionadas en diagonal principal inferior
 *Parametros:
 *				posicion_i[3],vector donde estan guardadas las coordenadas de las canicas
 *				cant_canica, cantidad de canicas seleccionadas
 *				color,color del jugador local
 *				color_enemigo, color la CPU
 *				tablero[C_F][C_C],tablero del juego
 *Retorno:
 *				Ninguno	*/
void movimiento_DP_EN_LINEA_inferior(tipo_posicion posicion_i[3], int cant_canica,char color, char color_enemigo,char tablero[C_F][C_C]);
/*Funcion que hace mover en linea a las canicas seleccionadas en diagonal secundaria superior
 *Parametros:
 *				posicion_i[3],vector donde estan guardadas las coordenadas de las canicas
 *				cant_canica, cantidad de canicas seleccionadas
 *				color,color del jugador local
 *				color_enemigo, color la CPU
 *				tablero[C_F][C_C],tablero del juego
 *Retorno:
 *				Ninguno	*/
void movimiento_DS_EN_LINEA_superior(tipo_posicion posicion_i[3],int cant_canica,char color,char color_enemigo,char tablero[C_F][C_C]);
/*Funcion que hace mover en linea a las canicas seleccionadas en diagonal secundaria inferior
 *Parametros:
 *				posicion_i[3],vector donde estan guardadas las coordenadas de las canicas
 *				cant_canica, cantidad de canicas seleccionadas
 *				color,color del jugador local
 *				color_enemigo, color la CPU
 *				tablero[C_F][C_C],tablero del juego
 *Retorno:
 *				Ninguno	*/
void movimiento_DS_EN_LINEA_inferior(tipo_posicion posicion_i[3],int cant_canica,char color,char color_enemigo,char tablero[C_F][C_C]);
/*Funcion que hace mover en linea a las canicas seleccionadas en horizontal izquierda
 *Parametros:
 *				posicion_i[3],vector donde estan guardadas las coordenadas de las canicas
 *				cant_canica, cantidad de canicas seleccionadas
 *				color,color del jugador local
 *				color_enemigo, color la CPU
 *				tablero[C_F][C_C],tablero del juego
 *Retorno:
 *				Ninguno	*/
void movimiento_HORIZONTAL_EN_LINEA_izquierda(tipo_posicion posicion_i[3],int cant_canica,char color,char color_enemigo,char tablero[C_F][C_C]);
/*Funcion que hace mover en linea a las canicas seleccionadas en horizontal derecha
 *Parametros:
 *				posicion_i[3],vector donde estan guardadas las coordenadas de las canicas
 *				cant_canica, cantidad de canicas seleccionadas
 *				color,color del jugador local
 *				color_enemigo, color la CPU
 *				tablero[C_F][C_C],tablero del juego
 *Retorno:
 *				Ninguno	*/
void movimiento_HORIZONTAL_EN_LINEA_derecha(tipo_posicion posicion_i[3],int cant_canica,char color,char color_enemigo,char tablero[C_F][C_C]);
/*Funcion que hace mover a una sola canica
 *Parametros:
 *				posicion_final,struct que almacena la fila y columna del destino de la canica
 *				posicion_i[3],vector donde estan guardadas las coordenadas de la canica
 *				color,color del jugador local
 *				color_enemigo, color la CPU
 *				tablero[C_F][C_C],tablero del juego
 *Retorno:
 *				Ninguno	*/
void movimiento_simple(tipo_posicion posicion_final,tipo_posicion posicion_i[3],char color,char tablero[C_F][C_C]);
/*Funcion que hace mover de lado a cualquier tipo de seleccion valida en donde incluya 2 o 3 canicas seleccionadas
 *Parametros:
 *				posicion_i[3],vector donde estan guardadas las coordenadas de las canicas
 *				cant_canica, cantidad de canicas seleccionadas
 *				color,color del jugador local
 *				color_enemigo, color la CPU
 *				tablero[C_F][C_C],tablero del juego
 *				diferencia_fila,el valor de la diferencia en la fila que se le pasa como parametro dependiendo de su tipo de seleccion
 *				diferencia_columna,el valor de la diferencia en la columna que se le pasa como parametro dependiendo de su tipo de seleccion
 *Retorno:
 *				Ninguno	*/
void movimiento_DE_LADO(tipo_posicion posicion_i[3],int cant_canica,char color,char color_enemigo,char tablero[C_F][C_C], int diferencia_fila, int diferencia_columna);

int main()
{
	tipo_posicion posicion_i[3],movimiento_posible[C_HUECO];
	char color,color_enemigo;
	char tablero[C_F][C_C];
	int cant_movimiento_posible=0,cant_canica=0,tipo_seleccion=0,cant_jugadas=0;
	eleccion(&color,&color_enemigo);
	inicializar_tablero(tablero);
	imprimir_tablero(tablero);
	do
	{
		if(cant_jugadas==0 && comienza_el_juego==JUGADOR)
		{
			juega_jugador(tablero,color,color_enemigo,&cant_movimiento_posible,movimiento_posible,&cant_canica,posicion_i,&tipo_seleccion);
			imprimir_tablero(tablero);
			esperar_enter();
			movimiento_CPU(posicion_i,tipo_seleccion,cant_canica,tablero,movimiento_posible,&cant_movimiento_posible,color_enemigo,color);
			imprimir_tablero(tablero);
			cant_jugadas++;
			turno=JUGADOR;

		}
		else if(cant_jugadas==0 && comienza_el_juego==CPU)
		{
			esperar_enter();
			movimiento_CPU(posicion_i,tipo_seleccion,cant_canica,tablero,movimiento_posible,&cant_movimiento_posible,color_enemigo,color);
			imprimir_tablero(tablero);
			juega_jugador(tablero,color,color_enemigo,&cant_movimiento_posible,movimiento_posible,&cant_canica,posicion_i,&tipo_seleccion);
			imprimir_tablero(tablero);
			cant_jugadas++;
			turno=CPU;
		}

		if(turno==JUGADOR && juego_terminado==FALSE && cant_jugadas<cant_max_jugadas)
		{
			juega_jugador(tablero,color,color_enemigo,&cant_movimiento_posible,movimiento_posible,&cant_canica,posicion_i,&tipo_seleccion);
			imprimir_tablero(tablero);
			if(juego_terminado==TRUE)
			{
				break;
			}
			esperar_enter();
			movimiento_CPU(posicion_i,tipo_seleccion,cant_canica,tablero,movimiento_posible,&cant_movimiento_posible,color_enemigo,color);
			imprimir_tablero(tablero);
			cant_jugadas++;
			turno=JUGADOR;
		}
		if(turno==CPU && juego_terminado==FALSE && cant_jugadas<cant_max_jugadas)
		{
			esperar_enter();
			movimiento_CPU(posicion_i,tipo_seleccion,cant_canica,tablero,movimiento_posible,&cant_movimiento_posible,color_enemigo,color);
			imprimir_tablero(tablero);
			if(juego_terminado==TRUE)
			{
				break;
			}
			juega_jugador(tablero,color,color_enemigo,&cant_movimiento_posible,movimiento_posible,&cant_canica,posicion_i,&tipo_seleccion);
			imprimir_tablero(tablero);
			cant_jugadas++;
			turno=CPU;
		}
		printf("\nNumeros de jugadas: %d\n",cant_jugadas);
	}while(cant_jugadas<cant_max_jugadas && juego_terminado!=TRUE);
	verificar_resultado(tablero,color,color_enemigo);
	return 0;
}
void pasar_referenchia(int fila,int columna,char retorno[2])
{
	retorno[0]='I'-fila;
	switch(fila)
	{
		case 0:
			retorno[1]=((columna-4)/2+5);
			break;
		case 1:
			retorno[1]=((columna-3)/2+4);
			break;
		case 2:
			retorno[1]=((columna-2)/2+3);
			break;
		case 3:
			retorno[1]=((columna-1)/2+2);
			break;
		case 4:
			retorno[1]=((columna-0)/2+1);
			break;
		case 5:
			retorno[1]=((columna-1)/2+1);
			break;
		case 6:
			retorno[1]=((columna-2)/2+1);
			break;
		case 7:
			retorno[1]=((columna-3)/2+1);
			break;
		case 8:
			retorno[1]=((columna-4)/2+1);
			break;
	};
}
void eleccion(char *color_local,char *color_rival)
{
	int contador=0,caracter,opcioncolor=0;
	int opcioncomenzar,opcionelegircolor;

    printf("Ingrese nombre local: ");
    do
    {
        caracter=getchar();
        nombre1[contador]=caracter;
        contador++;
    }while(caracter!='\n');
    nombre1[contador-1]='\0';
    printf("Ingrese nombre rival: ");
    contador=0;
    do
    {
        caracter=getchar();
        nombre2[contador]=caracter;
        contador++;
    }while(caracter!='\n');
    nombre2[contador-1]='\0';
	printf("Seleccione su color de ficha:");
	printf("\nElegir=1");
	printf("\nSortear=2\n");
    do
    {
    	printf("Su eleccion: ");
    	scanf("%d",&opcionelegircolor);
    	//LIMPIEZA DEL BUFFER
    	while(getchar()!='\n');
    }while(opcionelegircolor!=1 && opcionelegircolor!=2);
    if(opcionelegircolor==2)
    {
    	opcioncolor=(rand()%2);
        if (opcioncolor==1)
        {
        	*color_local=BLANCO;
        	*color_rival=NEGRO;
        	printf("Su color es el blanco");
        }
        else
        {
        	*color_local=NEGRO;
        	*color_rival=BLANCO;
        	printf("Su color es el negro");
        }

	}
    else
    {
		printf("\nBLANCO=1");
        printf("\nNEGRO=2\n");
        do
        {
            printf("Su eleccion: ");
            scanf("%d",&opcioncolor);
            //LIMPIEZA DEL BUFFER
            while(getchar()!='\n');
        }while(opcioncolor!=1 && opcioncolor!=2);
        if (opcioncolor==1)
        {
        	*color_local=BLANCO;
        	*color_rival=NEGRO;
        	printf("Su color es el blanco");
        }
        else
        {
        	*color_local=NEGRO;
        	*color_rival=BLANCO;
        	printf("Su color es el negro");
        }

	}


 	printf("\nQuien comienza el juego: ");
    printf("\nElegir=1");
    printf("\nSortear=2\n");
    do
    {
        printf("Su eleccion: ");
        scanf("%d",&opcioncomenzar);
        //LIMPIEZA DEL BUFFER
        while(getchar()!='\n');
    }while((opcioncomenzar!=1) && (opcioncomenzar!=2));
    if(opcioncomenzar==2)
    {
    	comienza_el_juego=(rand()%2);
    	if(comienza_el_juego==0)
    	{
    		printf("\nComienza %s\n",nombre1);
    	}
    	else
    	{
    		printf("\nComienza %s\n",nombre2);
    	}
    }
    else
    {
    	printf("\nElija quien comenzara el juego");
   		printf("\nJugador=%d, CPU=%d\n",JUGADOR,CPU);
        do
        {
            comienza_el_juego=100;
            printf("Su eleccion: ");
            scanf("%d",&comienza_el_juego);
            //LIMPIEZA DEL BUFFER
            while(getchar()!='\n');
        }while(comienza_el_juego!=JUGADOR && comienza_el_juego!=CPU);

    }
   do
   {
     printf("Defina el numero maximo de jugadas: ");
     scanf("%d",&cant_max_jugadas);
     //LIMPIEZA DEL BUFFER
     while(getchar()!='\n');
   }while(cant_max_jugadas<=0);
}
void juega_jugador(char tablero[C_F][C_C],char color,char color_enemigo, int *cant_movimiento_posible,tipo_posicion movimiento_posible[C_HUECO],int *cant_canica,tipo_posicion posicion_i[3],int *tipo_seleccion)
{
	char cadena[4];
	char c,aux1,aux2;
	tipo_posicion A,B,D;
	int x,i,comp,band=0;
	*cant_movimiento_posible=0;
	*cant_canica=0;
    /*Ingresa poisici처n de inicio*/
    do
    {
    	do
    	{
    		do
    		{
    			i=0;
    			printf("\nIngresar ubicaciones a mover. Formato[I6-G6] o [I6]: ");
    			comp=scanf("%c%c-%c%c",&cadena[0],&cadena[1],&cadena[2],&cadena[3]);
    			while((c=getchar())!='\n' && c!=EOF); //Limpieza de buffer
    		}while(comp!=2 && comp!=4);
    		/*Primer filtro: que meta la cadena en los limites establecidos*/
    		if(comp==2 && verificar_posicion(cadena[0],cadena[1])==FALSE)
    		{
    			printf("\nNo cumple los limites");
    			continue;
    		}
    		else if(comp==4 && (verificar_posicion(cadena[0],cadena[1])==FALSE || verificar_posicion(cadena[2],cadena[3])==FALSE))
    		{
    			printf("\nNo cumple los limites");
    			continue;
    		}
    		else
    			break;
    	}while(1);
    	/*Dado la cadena XX retorna su fila y su columna*/
    	A=retornar_posicion(cadena[0],cadena[1]);
    	/*Cero B por si ingresa una sola canica*/
    	B.fila=0;
    	B.columna=0;
    	/*Si ingreso dos extremos reescribo B*/
    	if(comp==4)
    		B=retornar_posicion(cadena[2],cadena[3]);
    	/*Verificaciones*/
    	if(cargar_canica(A,B,posicion_i,cant_canica,tipo_seleccion)==FALSE)
    	{
    		printf("\nIngreso en cuanto a posicion es incorrecto");
    		i++;
    	}
    	if(verificar_color(posicion_i,*cant_canica,color,tablero)==FALSE)
    	{
    		printf("\nIngreso en cuanto a color es incorrecto");
    		i++;
    	}
    }while(i!=0);
	if((posicion_i[0].fila!=A.fila && posicion_i[0].columna!=A.columna)||(posicion_i[0].fila==A.fila && posicion_i[0].columna!=A.columna))
	{
		aux1=cadena[0];
		aux2=cadena[1];
		cadena[0]=cadena[2];
		cadena[1]=cadena[3];
		cadena[2]=aux1;
		cadena[3]=aux2;
	}
	imprimir_guia_de_direccion(*tipo_seleccion,cadena);
	/*Posibles movimientos*/
	posible_libre(posicion_i, *tipo_seleccion, *cant_canica, tablero, movimiento_posible, cant_movimiento_posible);
    posibles_empujes(posicion_i, *tipo_seleccion, *cant_canica, color, color_enemigo, tablero, movimiento_posible, cant_movimiento_posible);
    printf("\nCANTIDAD DE MOVIMIENTOS POSIBLES=%d",*cant_movimiento_posible);
    /*Imprimir posibles movimientos*/
    for(x=0;x<(*cant_movimiento_posible);x++){
    	pasar_referenchia(movimiento_posible[x].fila,movimiento_posible[x].columna,cadena);
        printf("\n%c\t%d",cadena[0],cadena[1]);
    }
    /*Ingresar ubicacione de destino*/
    do
    {
        do
        {
            printf("\nIngresar ubicacion destino: ");
            comp=scanf("%c%c",&cadena[0],&cadena[1]);
            while((c=getchar())!='\n' && c!=EOF); //Limpieza de buffer
        }while(comp!=2);
        /*Primer filtro: que meta la cadena en los limites establecidos*/
        if(comp==2 && verificar_posicion(cadena[0],cadena[1])==FALSE)
        {
            printf("\nNo cumple los limites");
            continue;
        }
        D=retornar_posicion(cadena[0],cadena[1]);
       // printf("\nD=%d-%d",D.fila,D.columna);
        for(x=0;x<*cant_movimiento_posible;x++)
        {
        	if(movimiento_posible[x].fila==D.fila && movimiento_posible[x].columna==D.columna)
        	{
        		band=1;
        	}
        }

	}while(band==0);
    //Si es movimiento unico simple
    switch(*tipo_seleccion)
    {
    	case UNICO:
    		movimiento_simple(D,posicion_i,color,tablero);
    		break;
    	case DP: /*Sin errores*/
    		//en linea superior
    		if(posicion_i[0].fila-1==D.fila && posicion_i[0].columna-1==D.columna)
    		{
    			movimiento_DP_EN_LINEA_superior(posicion_i,*cant_canica,color,color_enemigo,tablero);
    		}
    		//en linea inferior
    		else if(posicion_i[*cant_canica-1].fila+1==D.fila && posicion_i[*cant_canica-1].columna+1==D.columna)
    		{
    			movimiento_DP_EN_LINEA_inferior(posicion_i,*cant_canica,color,color_enemigo,tablero);
    		}
    		//de lado izquierda
    		else if(posicion_i[0].fila==D.fila && posicion_i[0].columna-2==D.columna)
    		{
    			movimiento_DE_LADO(posicion_i,*cant_canica,color,color_enemigo,tablero,0,-2);
    		}
    		//de lado derecha
    		else if(posicion_i[*cant_canica-1].fila==D.fila && posicion_i[*cant_canica-1].columna+2==D.columna)
    		{
    		    movimiento_DE_LADO(posicion_i,*cant_canica,color,color_enemigo,tablero,0,2);
    		}
    		//de lado superior
    		else if(posicion_i[0].fila-1==D.fila && posicion_i[0].columna+1==D.columna)
    		{
    		    movimiento_DE_LADO(posicion_i,*cant_canica,color,color_enemigo,tablero,-1,1);
    		}
    		//de lado inferior
    		else if(posicion_i[*cant_canica-1].fila+1==D.fila && posicion_i[*cant_canica-1].columna-1==D.columna)
    		{
    		    movimiento_DE_LADO(posicion_i,*cant_canica,color,color_enemigo,tablero,1,-1);
    		}
    		break;
    	case DS: /*Sin errores*/
    		//en linea superior
    		if(posicion_i[0].fila-1==D.fila && posicion_i[0].columna+1==D.columna)
    		{
    			movimiento_DS_EN_LINEA_superior(posicion_i,*cant_canica,color,color_enemigo,tablero);
    		}
    		//en linea inferior
    		else if(posicion_i[*cant_canica-1].fila+1==D.fila && posicion_i[*cant_canica-1].columna-1==D.columna)
    		{
    			movimiento_DS_EN_LINEA_inferior(posicion_i,*cant_canica,color,color_enemigo,tablero);
    		}
    		//de lado izquierda
    		else if(posicion_i[*cant_canica-1].fila==D.fila && posicion_i[*cant_canica-1].columna-2==D.columna)
    		{
    			movimiento_DE_LADO(posicion_i,*cant_canica,color,color_enemigo,tablero,0,-2);
    		}
    		//de lado derecha
    		else if(posicion_i[0].fila==D.fila && posicion_i[0].columna+2==D.columna)
    		{
    		    movimiento_DE_LADO(posicion_i,*cant_canica,color,color_enemigo,tablero,0,2);
    		}
    		//de lado superior
    		else if(posicion_i[0].fila-1==D.fila && posicion_i[0].columna-1==D.columna)
    		{
    		    movimiento_DE_LADO(posicion_i,*cant_canica,color,color_enemigo,tablero,-1,-1);
    		}
    		//de lado inferior
    		else if(posicion_i[*cant_canica-1].fila+1==D.fila && posicion_i[*cant_canica-1].columna+1==D.columna)
    		{
    		    movimiento_DE_LADO(posicion_i,*cant_canica,color,color_enemigo,tablero,1,1);
    		}
    		break;
    	case HORIZONTAL: /*Sin errores*/
    		//en linea izquierda
    		if(posicion_i[0].fila==D.fila && posicion_i[0].columna-2==D.columna)
    		{
    			movimiento_HORIZONTAL_EN_LINEA_izquierda(posicion_i,*cant_canica,color,color_enemigo,tablero);
    		}
    		//en linea derecha
    		else if(posicion_i[*cant_canica-1].fila==D.fila && posicion_i[*cant_canica-1].columna+2==D.columna)
    		{
    			movimiento_HORIZONTAL_EN_LINEA_derecha(posicion_i,*cant_canica,color,color_enemigo,tablero);
    		}
    		//de lado izquierda superior
    		else if(posicion_i[0].fila-1==D.fila && posicion_i[0].columna-1==D.columna)
    		{
    			movimiento_DE_LADO(posicion_i,*cant_canica,color,color_enemigo,tablero,-1,-1);
    		}
    		//de lado derecha superior
    		else if(posicion_i[*cant_canica-1].fila-1==D.fila && posicion_i[*cant_canica-1].columna+1==D.columna)
    		{
    		    movimiento_DE_LADO(posicion_i,*cant_canica,color,color_enemigo,tablero,1,1);
    		}
    		//de lado izquierda inferior
    		else if(posicion_i[0].fila+1==D.fila && posicion_i[0].columna-1==D.columna)
    		{
    		    movimiento_DE_LADO(posicion_i,*cant_canica,color,color_enemigo,tablero,1,-1);
    		}
    		//de lado derecha inferior
    		else if(posicion_i[*cant_canica-1].fila+1==D.fila && posicion_i[*cant_canica-1].columna+1==D.columna)
    		{
    		    movimiento_DE_LADO(posicion_i,*cant_canica,color,color_enemigo,tablero,1,1);
    		}
    		break;
    }
    imprimir_historial_JUGADOR(tablero,color,D,color_enemigo);
}

/*
 * Inicializa el tablero con la configuraci?꾩?n inicial de juego
 */
void inicializar_tablero(char tablero[C_F][C_C])
{
	char tb_temp[C_F][C_C]={
			{"xxxxbxbxvxnxnxxxx"},
			{"xxxbxbxbxnxnxnxxx"},
			{"xxvxbxbxvxnxnxvxx"},
			{"xvxvxvxvxvxvxvxvx"},
			{"vxvxvxvxvxvxvxvxv"},
			{"xvxvxvxvxvxvxvxvx"},
			{"xxvxnxnxvxbxbxvxx"},
			{"xxxnxnxnxbxbxbxxx"},
			{"xxxxnxnxvxbxbxxxx"},
		};
	int x,y;
	for(x=0;x<C_F;x++)
		for(y=0;y<C_C;y++)
			tablero[x][y]=tb_temp[x][y];
}
/*
 * Imprime el tablero
 */
void imprimir_tablero(char tablero[C_F][C_C])
{
	int x,y,z=16,p=C_F;
	printf("\n");
	for(x=0;x<C_F;x++)
	{
		printf("[%c]",'I'-x);
		for(y=0;y<C_C;y++)
		{
			if(tablero[x][y]=='x')
				printf("  ");
				else if(tablero[x][y]=='b')
					printf(" B");
					else if(tablero[x][y]=='n')
						printf(" N");
						else if(tablero[x][y]=='v')
							printf(" %c",'*');
			if(x>4 && y==z)
			{
				printf(" %d",p);
				z--;
				p--;
			}

		}
		printf("\n");
	}
	printf("              1   2   3   4   5");
}
/*
 * Verifica si la posicion en char fue ingresada dentro de los limites permitidos por el tablero
 * No puede ingresar I0 por ejemplo
 */
int verificar_posicion(char fila, char columna)
{
	if((fila<'A' || fila>'I') && fila!='0')//F AND F=F; F AND V=F; V AND F=F
		return FALSE;
	switch(fila)
	{
		case 'I':
			if(columna<'5' || columna>'9')
				return FALSE;
			break;
		case 'H':
			if(columna<'4' || columna>'9')
				return FALSE;
			break;
		case 'G':
			if(columna<'3' || columna>'9')
				return FALSE;
			break;
		case 'F':
			if(columna<'2' || columna>'9')
				return FALSE;
			break;
		case 'E':
			if(columna<'1' || columna>'9')
				return FALSE;
			break;
		case 'D':
			if(columna<'1' || columna>'8')
				return FALSE;
			break;
		case 'C':
			if(columna<'1' || columna>'7')
				return FALSE;
			break;
		case 'B':
			if(columna<'1' || columna>'6')
				return FALSE;
			break;
		case 'A':
			if(columna<'1' || columna>'5')
				return FALSE;
			break;
		case '0':
			if(columna!='0')
				return FALSE;
	}
	return TRUE;
}
/*
 * Recibe por ejemplo I5 en chars, y devuelve la posicion del tablero que le
 * corresponde. tipo_posicion posee .fila y .columna
 */
tipo_posicion retornar_posicion(char fila, char columna)
{
	tipo_posicion posicion;
	if(fila=='0')
	{
		posicion.fila=0;
		posicion.columna=0;
		return posicion;
	}
	posicion.fila=8-(fila-'A');
	switch(fila)
	{
		case 'I':
			posicion.columna=(4+(columna-'5')*2);
			break;
		case 'H':
			posicion.columna=(3+(columna-'4')*2);
			break;
		case 'G':
			posicion.columna=(2+(columna-'3')*2);
			break;
		case 'F':
			posicion.columna=(1+(columna-'2')*2);
			break;
		case 'E':
			posicion.columna=(0+(columna-'1')*2);
			break;
		case 'D':
			posicion.columna=(1+(columna-'1')*2);
			break;
		case 'C':
			posicion.columna=(2+(columna-'1')*2);
			break;
		case 'B':
			posicion.columna=(3+(columna-'1')*2);
			break;
		case 'A':
			posicion.columna=(4+(columna-'1')*2);
			break;
	}
	return posicion;
}
/*
 * Se recibe los dos extremos de las canicas a mover, luego se cargan todas las canicas a mover en posicion_i[3]
 * Si se recibe canicas correctas en cuanto a posicion, retorna TRUE, en caso contrario FALSE
 * Si se recibe una sola posicion, B.fila=0 y B.columna=0 para se챰alar que solo se selecciona una ficha
 */
int cargar_canica(tipo_posicion A, tipo_posicion B, tipo_posicion posicion_i[3], int *cant_canica, int *tipo_seleccion)
{
	tipo_posicion aux;
	//el vector posicion[3] esta ordenado de las filas superiores a las inferiores,
	//si son iguales las filas, est李?ordenado por columnas de izquierda a derecha
	//cerar
	for(int x=0;x<3;x++)
	{
		posicion_i[x].fila=0;
		posicion_i[x].columna=0;
	}
	//Si solo hay una canica para mover, B.fila y B.columna son 0
	if(B.fila==0 && B.columna==0)
	{
		posicion_i[0]=A;
		*cant_canica=1;
		*tipo_seleccion=UNICO;
		return TRUE;
	}
	//ordenar de arriba para abajo, pues las formulas necesitan esta condicion
	if(A.fila>B.fila)
	{
		aux=A;
		A=B;
		B=aux;
	}
	//ordenar de izquierda a derecha si estan en la misma fila
	if(A.fila==B.fila && A.columna>B.columna)
	{
		aux=A;
		A=B;
		B=aux;
	}

	//Si son tres canicas en paralelo, los extremos A y B se configuran de la siguiente manera
	if(A.fila==B.fila && A.columna==B.columna-2*2 )
	{
		posicion_i[0]=A;
		posicion_i[1].fila=A.fila;
		posicion_i[1].columna=A.columna+1*2;
		posicion_i[2]=B;
		*cant_canica=3;
		*tipo_seleccion=HORIZONTAL;
		return TRUE;
	}
	//Si son tres canicas en diagonal principal, los extremos A y B se configuran de la siguiente manera
	if(A.fila==B.fila-2 && A.columna==B.columna-2)
	{
		posicion_i[0]=A;
		posicion_i[1].fila=A.fila+1;
		posicion_i[1].columna=A.columna+1;
		posicion_i[2]=B;
		*cant_canica=3;
		*tipo_seleccion=DP;
		return TRUE;
	}
	//Si son tres canicas en diagonal secundaria, los extremos A y B se configuran de la siguiente manera
	if(A.fila==B.fila-2 && A.columna==B.columna+2)
	{
		posicion_i[0]=A;
		posicion_i[1].fila=A.fila+1;
		posicion_i[1].columna=A.columna-1;
		posicion_i[2]=B;
		*cant_canica=3;
		*tipo_seleccion=DS;
		return TRUE;
	}
	//Si son dos canicas en paralelo, los extremos A y B se configuran de la siguiente manera
	if(A.fila==B.fila && A.columna==B.columna-1*2)
	{
		posicion_i[0]=A;
		posicion_i[1]=B;
		*cant_canica=2;
		*tipo_seleccion=HORIZONTAL;
		return TRUE;
	}
	//Si son dos canicas en diagonal principal, los extremos A y B se configuran de la siguiente manera
	if(A.fila==B.fila-1 && A.columna==B.columna-1)
	{
		posicion_i[0]=A;
		posicion_i[1]=B;
		*cant_canica=2;
		*tipo_seleccion=DP;
		return TRUE;
	}
	//Si son dos canicas en diagonal secundaria, los extremos A y B se configuran de la siguiente manera
	if(A.fila==B.fila-1 && A.columna==B.columna+1)
	{
		posicion_i[0]=A;
		posicion_i[1]=B;
		*cant_canica=2;
		*tipo_seleccion=DS;
		return TRUE;
	}

	return FALSE;
}
/*
 * Verifica que las canicas seleccionadas sean del color correspondiente
 * en char color se recibe el color del jugador actual
 */
int verificar_color(tipo_posicion posicion_i[3], int cant_canica, char color,char tablero[C_F][C_C])
{
	int x;
	for(x=0;x<cant_canica;x++)
		if(tablero[posicion_i[x].fila][posicion_i[x].columna]!=color)
			return FALSE;
	return TRUE;
}
/*
 * Dado las posiciones de canicas seleccionadas cargadas en posicion_i[3], cargo todos los movimientos posibles en donde
 * se puede acceder porque est李?libre.
 */
int posible_libre(tipo_posicion posicion_i[3], int tipo_seleccion, int cant_canica, char tablero[C_F][C_C], tipo_posicion movimiento_posible[C_HUECO], int *cant_movimiento_posible)
{
	int x,cont=0;
	if(tipo_seleccion==UNICO) //Mueve una sola canica
	{
        /*Si esta vacio izquierda superior*/
        if(posicion_i[0].fila>0 && posicion_i[0].columna>0 && tablero[posicion_i[0].fila-1][posicion_i[0].columna-1]==VACIO)
        {
            movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila-1;
            movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna-1;
            (*cant_movimiento_posible)++;
        }
        /*Si esta vacio derecha superior*/
        if(posicion_i[0].fila>0 && posicion_i[0].columna<C_C-1 && tablero[posicion_i[0].fila-1][posicion_i[0].columna+1]==VACIO)
        {
            movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila-1;
            movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna+1;
            (*cant_movimiento_posible)++;
        }
        /*Si esta vacio izquierda inferior*/
        if(posicion_i[0].fila<C_F-1 && posicion_i[0].columna>0 && tablero[posicion_i[0].fila+1][posicion_i[0].columna-1]==VACIO)
        {
            movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila+1;
            movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna-1;
            (*cant_movimiento_posible)++;
        }
        /*Si esta vacio derecha inferior*/
        if(posicion_i[0].fila<C_F-1 && posicion_i[0].columna<C_C-1 && tablero[posicion_i[0].fila+1][posicion_i[0].columna+1]==VACIO)
        {
            movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila+1;
            movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna+1;
            (*cant_movimiento_posible)++;
        }
        /*Si esta vacio izquierda*/
        if(posicion_i[0].columna>1 && tablero[posicion_i[0].fila][posicion_i[0].columna-2]==VACIO)
        {
            movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila;
            movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna-2;
            (*cant_movimiento_posible)++;
        }
        /*Si esta vacio derecha*/
        if(posicion_i[0].columna<C_C-2 && tablero[posicion_i[0].fila][posicion_i[0].columna+2]==VACIO)
        {
            movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila;
            movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna+2;
            (*cant_movimiento_posible)++;
        }
        if(*cant_movimiento_posible>0)
        	return TRUE;
	}
	else if(tipo_seleccion==DP)
	{
        /*Libre para de lado abajo izquierda*/
        cont=0;
		for(x=0;x<cant_canica;x++)
		{
			if(posicion_i[x].fila<C_F-1 && posicion_i[x].columna>0) //Es para que no salga del rango del tablero
			{
				if(tablero[posicion_i[x].fila+1][posicion_i[x].columna-1]==VACIO)
				{
					cont++;
				}
			}
		}
		if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[cant_canica-1].fila+1;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[cant_canica-1].columna-1; //ficha representativa=B
			(*cant_movimiento_posible)++;
		}
        /*Libre para abajo derecha(EN LINEA)*/
        cont=0;
		if(posicion_i[cant_canica-1].fila<C_F-1 && posicion_i[cant_canica-1].columna<C_C-1) //Es para que no salga del rango del tablero
		{
			if(tablero[posicion_i[cant_canica-1].fila+1][posicion_i[cant_canica-1].columna+1]==VACIO)
			{
				cont=cant_canica;
			}
		}
		if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[cant_canica-1].fila+1;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[cant_canica-1].columna+1; //ficha representativa=B
			(*cant_movimiento_posible)++;
		}
        /*Libre para arriba izquierda(EN LINEA)*/
        cont=0;
		if(posicion_i[0].fila>0 && posicion_i[0].columna>0) //Es para que no salga del rango del tablero
		{
			if(tablero[posicion_i[0].fila-1][posicion_i[0].columna-1]==VACIO)
			{
				cont=cant_canica;
			}
		}
        if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila-1;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna-1; //ficha representativa=A
			(*cant_movimiento_posible)++;
		}
        /*Libre para de lado arriba derecha*/
        cont=0;
		for(x=0;x<cant_canica;x++)
		{
			if(posicion_i[x].fila>0 && posicion_i[x].columna<C_C-1) //Es para que no salga del rango del tablero
			{
				if(tablero[posicion_i[x].fila-1][posicion_i[x].columna+1]==VACIO)
				{
					cont++;
				}
			}
		}
        if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila-1;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna+1; //ficha representativa=A
			(*cant_movimiento_posible)++;
		}
        /*Libre para izquierda*/
        cont=0;
        for(x=0;x<cant_canica;x++)
        {
        	if(posicion_i[x].columna>0)
        	{
        		if(tablero[posicion_i[x].fila][posicion_i[x].columna-2]==VACIO)
        		{
        			cont++;
        		}
        	}
        }
        if(cont==cant_canica)
        {
        	movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila;
        	movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna-2; //ficha representativa=A
        	(*cant_movimiento_posible)++;
        }
        /*Libre para derecha*/
        cont=0;
        for(x=0;x<cant_canica;x++)
        {
        	if(posicion_i[x].columna<C_C)
        	{
        		if(tablero[posicion_i[x].fila][posicion_i[x].columna+2]==VACIO)
        		{
        			cont++;
        		}
        	}
        }
        if(cont==cant_canica)
                {
                	movimiento_posible[*cant_movimiento_posible].fila=posicion_i[cant_canica-1].fila;
                	movimiento_posible[*cant_movimiento_posible].columna=posicion_i[cant_canica-1].columna-2; //ficha representativa=B
                	(*cant_movimiento_posible)++;
                }
        if(*cant_movimiento_posible>0)
        	return TRUE;
	}
	else if(tipo_seleccion==DS)
	{
		/*Libre para abajo izquierda(EN LINEA)*/
		cont=0;
		if(posicion_i[cant_canica-1].fila<C_F-1 && posicion_i[cant_canica-1].columna>0) //Es para que no salga del rango del tablero
		{
			if(tablero[posicion_i[cant_canica-1].fila+1][posicion_i[cant_canica-1].columna-1]==VACIO)
			{
				cont=cant_canica;
			}
		}
		if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[cant_canica-1].fila+1;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[cant_canica-1].columna-1; //ficha representativa=B
			(*cant_movimiento_posible)++;
		}
		/*Libre para de lado abajo derecha*/
		cont=0;
		for(x=0;x<cant_canica;x++)
		{
			if(posicion_i[x].fila<C_F-1 && posicion_i[x].columna<C_C-1) //Es para que no salga del rango del tablero
			{
				if(tablero[posicion_i[x].fila+1][posicion_i[x].columna+1]==VACIO)
				{
					cont++;
				}
			}
		}
		if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[cant_canica-1].fila+1;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[cant_canica-1].columna+1; //ficha representativa=B
			(*cant_movimiento_posible)++;
		}
		/*Libre para de lado arriba izquierda*/
		cont=0;
		for(x=0;x<cant_canica;x++)
		{
			if(posicion_i[x].fila>0 && posicion_i[x].columna>0) //Es para que no salga del rango del tablero
			{
				if(tablero[posicion_i[x].fila-1][posicion_i[x].columna-1]==VACIO)
				{
					cont++;
				}
			}
		}
		if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila-1;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna-1; //ficha representativa=A
			(*cant_movimiento_posible)++;
		}
		/*Libre para arriba derecha(EN LINEA)*/
		cont=0;
		if(posicion_i[0].fila>0 && posicion_i[0].columna<C_C-1) //Es para que no salga del rango del tablero
		{
			if(tablero[posicion_i[0].fila-1][posicion_i[0].columna+1]==VACIO)
			{
				cont=cant_canica;
			}
		}
		if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila-1;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna+1; //ficha representativa=A
			(*cant_movimiento_posible)++;
		}
		/*Libre para izquierda*/
		cont=0;
		for(x=0;x<cant_canica;x++)
		{
			if(posicion_i[x].columna>0)
			{
				if(tablero[posicion_i[x].fila][posicion_i[x].columna-2]==VACIO)
				{
					cont++;
				}
			}
		}
		if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[cant_canica-1].fila;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[cant_canica-1].columna-2; //ficha representativa=B
			(*cant_movimiento_posible)++;
		}
		/*Libre para derecha*/
		cont=0;
		for(x=0;x<cant_canica;x++)
		{
			if(posicion_i[x].columna<C_C-1)
			{
				if(tablero[posicion_i[x].fila][posicion_i[x].columna+2]==VACIO)
				{
					cont++;
				}
			}
		}
		if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna+2; //ficha representativa=A
			(*cant_movimiento_posible)++;
		}
        if(*cant_movimiento_posible>0)
        	return TRUE;
	}
	else if(tipo_seleccion==HORIZONTAL)
	{
		/*Libre para de lado abajo izquierda*/
		cont=0;
		for(x=0;x<cant_canica;x++)
		{
			if(posicion_i[x].fila<C_F-1 && posicion_i[x].columna>0) //Es para que no salga del rango del tablero
			{
				if(tablero[posicion_i[x].fila+1][posicion_i[x].columna-1]==VACIO)
				{
					cont++;
				}
			}
		}
		if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila+1;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna-1;//ficha representativa=A
			(*cant_movimiento_posible)++;
		}
		/*Libre para de lado bajo derecha*/
		cont=0;
		for(x=0;x<cant_canica;x++)
		{
			if(posicion_i[x].fila<C_F-1 && posicion_i[x].columna<C_C-1) //Es para que no salga del rango del tablero
			{
				if(tablero[posicion_i[x].fila+1][posicion_i[x].columna+1]==VACIO)
				{
					cont++;
				}
		}
				}
		if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[cant_canica-1].fila+1;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[cant_canica-1].columna+1;//ficha representativa=B
			(*cant_movimiento_posible)++;
		}
		/*Libre para de lado arriba izquierda*/
		cont=0;
		for(x=0;x<cant_canica;x++)
		{
			if(posicion_i[x].fila>0 && posicion_i[x].columna>0) //Es para que no salga del rango del tablero
			{
				if(tablero[posicion_i[x].fila-1][posicion_i[x].columna-1]==VACIO)
				{
					cont++;
				}
			}
		}
		if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila-1;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna-1;//ficha representativa=A
			(*cant_movimiento_posible)++;
		}
		/*Libre para de lado arriba derecha*/
		cont=0;
		for(x=0;x<cant_canica;x++)
		{
			if(posicion_i[x].fila>0 && posicion_i[x].columna<C_C-1) //Es para que no salga del rango del tablero
			{
				if(tablero[posicion_i[x].fila-1][posicion_i[x].columna+1]==VACIO)
				{
					cont++;
				}
			}
		}
		if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[cant_canica-1].fila-1;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[cant_canica-1].columna+1;//ficha representativa=B
			(*cant_movimiento_posible)++;
		}
		/*Libre para izquierda(EN LINEA)*/
		cont=0;
		if(posicion_i[0].columna>0)
		{
			if(tablero[posicion_i[0].fila][posicion_i[0].columna-2]==VACIO)
			{
				cont=cant_canica;
			}
		}
		if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna-2; //ficha representativa=A
			(*cant_movimiento_posible)++;
		}
		/*Libre para derecha(EN LINEA)*/
		cont=0;
		if(posicion_i[cant_canica-1].columna<C_C)
		{
			if(tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna+2]==VACIO)
			{
				cont=cant_canica;
			}
		}
		if(cont==cant_canica)
		{
			movimiento_posible[*cant_movimiento_posible].fila=posicion_i[cant_canica-1].fila;
			movimiento_posible[*cant_movimiento_posible].columna=posicion_i[cant_canica-1].columna+2; //ficha representativa=B
			(*cant_movimiento_posible)++;
		}
        if(*cant_movimiento_posible>0)
        	return TRUE;
	}
	return FALSE;
}
int posibles_empujes(tipo_posicion posicion_i[3], int tipo_seleccion, int cant_canica,char color,char color_enemigo, char tablero[C_F][C_C], tipo_posicion movimiento_posible[C_HUECO], int *cant_movimiento_posible)
{
	if(tipo_seleccion==DP)
	{	//verificacion de empuje hacia abajo
		if(posicion_i[cant_canica-1].fila<C_F-1 && posicion_i[cant_canica-1].columna<C_C-1)//para que no salga del rango del tablero
		{
			if(tablero[posicion_i[cant_canica-1].fila+1][posicion_i[cant_canica-1].columna+1]==color_enemigo)
			{
				if(cant_canica>contar_enemiga_DP_inferior(posicion_i,color,color_enemigo,tablero))
				{
					movimiento_posible[*cant_movimiento_posible].fila=posicion_i[cant_canica-1].fila+1;
					movimiento_posible[*cant_movimiento_posible].columna=posicion_i[cant_canica-1].columna+1;
					(*cant_movimiento_posible)++;
				}
			}
		}
		//verificacion de empuje hacia arriba
		if(posicion_i[0].fila>0 && posicion_i[0].columna>0)
		{
			if(tablero[posicion_i[0].fila-1][posicion_i[0].columna-1]==color_enemigo)
			{
				if(cant_canica>contar_enemiga_DP_superior(posicion_i,color,color_enemigo,tablero))
				{
					movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila-1;
					movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna-1;
					(*cant_movimiento_posible)++;
				}
			}
		}
	}
	else if(tipo_seleccion==DS)
	{
		//verificacion de empuje hacia abajo
		if(posicion_i[cant_canica-1].fila<C_F-1 && posicion_i[cant_canica-1].columna>0)//para que no salga del rango del tablero
		{
			if(tablero[posicion_i[cant_canica-1].fila+1][posicion_i[cant_canica-1].columna-1]==color_enemigo)
			{
				if(cant_canica>contar_enemiga_DS_inferior(posicion_i,color,color_enemigo,tablero))
				{
					movimiento_posible[*cant_movimiento_posible].fila=posicion_i[cant_canica-1].fila+1;
					movimiento_posible[*cant_movimiento_posible].columna=posicion_i[cant_canica-1].columna-1;
					(*cant_movimiento_posible)++;
				}
			}
		}
		//verificacion de empuje hacia arriba
		if(posicion_i[0].fila>0 && posicion_i[0].columna<C_C-1)
		{
			if(tablero[posicion_i[0].fila-1][posicion_i[0].columna+1]==color_enemigo)
			{
				if(cant_canica>contar_enemiga_DS_superior(posicion_i,color,color_enemigo,tablero))
				{
					movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila-1;
					movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna+1;
					(*cant_movimiento_posible)++;
				}
			}
		}
	}
	else if(tipo_seleccion==HORIZONTAL)
	{
		//verificacion de empuje hacia derecha
		if(posicion_i[cant_canica-1].columna<C_C-1)//para que no salga del rango del tablero
		{
			if(tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna+2]==color_enemigo)
			{
				if(cant_canica>contar_enemiga_HORIZONTAL_derecha(posicion_i,color,color_enemigo,tablero))
				{
					movimiento_posible[*cant_movimiento_posible].fila=posicion_i[cant_canica-1].fila;
					movimiento_posible[*cant_movimiento_posible].columna=posicion_i[cant_canica-1].columna+2;
					(*cant_movimiento_posible)++;
				}
			}
		}
		//verificacion de empuje hacia izquierda
		if(posicion_i[0].columna>0)
		{
			if(tablero[posicion_i[0].fila][posicion_i[0].columna-2]==color_enemigo)
			{
				if(cant_canica>contar_enemiga_HORIZONTAL_izquierda(posicion_i,color,color_enemigo,tablero))
				{
					movimiento_posible[*cant_movimiento_posible].fila=posicion_i[0].fila;
					movimiento_posible[*cant_movimiento_posible].columna=posicion_i[0].columna-2;
					(*cant_movimiento_posible)++;
				}
			}
		}
	}
	return TRUE;
}
int contar_enemiga_DP_superior(tipo_posicion posicion_i[3],char color, char color_enemigo,char tablero[C_F][C_C])
{
    //como parametro le envias posicion_i[0 o 2] en posicion que es la primera posicion de las canicas que seleccionas para mover
    int fila, columna, contador=0;
    fila=posicion_i[0].fila-1; //Desde la fila que empieza a contar
    columna=posicion_i[0].columna-1; //Desde la columna que empieza a contar
    while(fila>=0 || columna>=0) //Mientras no salga de los limites del tablero
    {
        if(tablero[fila][columna]==color_enemigo){
            contador++;
            if(fila==0 || columna==0)//Si la canica enemiga estaba en el limite extremo, retorna directo al valor del contador
            	return contador;
            fila--;
            columna--; //Voy a la siguiente posicion a contar
        }else if(tablero[fila][columna]==color)
        {
        	contador=100000;
        	break;
        }
        else
            break; // si no es su color corto el ciclo
    }
    return contador;
}
int contar_enemiga_DP_inferior(tipo_posicion posicion_i[3],char color, char color_enemigo,char tablero[C_F][C_C])
{

    int fila, columna, contador=0;
    fila=posicion_i[2].fila+1; //Desde la fila que empieza a contar
    columna=posicion_i[2].columna+1; //Desde la columna que empieza a contar
    while(fila<=C_F-1 || columna<=C_C-1) //Mientras no salga de los limites del tablero
    {
        if(tablero[fila][columna]==color_enemigo){
            contador++;
            if(fila==C_F-1 || columna==C_C-1)
            	return contador;
            fila++;
            columna++; //Voy a la siguiente posicion a contar
        }else if(tablero[fila][columna]==color)
        {
        	contador=100000;
        	break;
        }
        else
            break; // si no es su color corto el ciclo
    }
    return contador;
}
int contar_enemiga_DS_superior(tipo_posicion posicion_i[3],char color, char color_enemigo,char tablero[C_F][C_C])
{

    int fila, columna, contador=0;
    fila=posicion_i[0].fila-1; //Desde la fila que empieza a contar
    columna=posicion_i[0].columna+1; //Desde la columna que empieza a contar
    while(fila>=0 || columna<=C_C-1) //Mientras no salga de los limites del tablero
    {
        if(tablero[fila][columna]==color_enemigo){
            contador++;
            if(fila==0 || columna==C_C-1)
            	return contador;
            fila--;
            columna++; //Voy a la siguiente posicion a contar
        }else if(tablero[fila][columna]==color)
        {
        	contador=100000;
        	break;
        }
        else
            break; // si no es su color corto el ciclo
    }
    return contador;
}
int contar_enemiga_DS_inferior(tipo_posicion posicion_i[3],char color, char color_enemigo,char tablero[C_F][C_C])
{

    int fila, columna, contador=0;
    fila=posicion_i[2].fila+1; //Desde la fila que empieza a contar
    columna=posicion_i[2].columna-1; //Desde la columna que empieza a contar
    while(fila<=C_F-1 || columna>=0) //Mientras no salga de los limites del tablero
    {
        if(tablero[fila][columna]==color_enemigo){
            contador++;
            if(fila==C_F-1 || columna==0)
            	return contador;
            fila++;
            columna--; //Voy a la siguiente posicion a contar
        }else if(tablero[fila][columna]==color)
        {
        	contador=100000;
        	break;
        }
        else
            break; // si no es su color corto el ciclo
    }
    return contador;
}
int contar_enemiga_HORIZONTAL_izquierda(tipo_posicion posicion_i[3],char color, char color_enemigo,char tablero[C_F][C_C])
{

    int fila, columna, contador=0;
    fila=posicion_i[0].fila; //Desde la fila que empieza a contar
    columna=posicion_i[0].columna-2; //Desde la columna que empieza a contar
    while(columna>=0) //Mientras no salga de los limites del tablero
    {
        if(tablero[fila][columna]==color_enemigo){
            contador++;
            if(columna==0)
            	return contador;
            columna=columna-2; //Voy a la siguiente posicion a contar
        }else if(tablero[fila][columna]==color)
        {
        	contador=100000;
        	break;
        }
        else
            break; // si no es su color corto el ciclo
    }
    return contador;
}
int contar_enemiga_HORIZONTAL_derecha(tipo_posicion posicion_i[3],char color, char color_enemigo,char tablero[C_F][C_C])
{

    int fila, columna, contador=0;
    fila=posicion_i[2].fila; //Desde la fila que empieza a contar
    columna=posicion_i[2].columna+2; //Desde la columna que empieza a contar
    while(columna<=C_C-1) //Mientras no salga de los limites del tablero
    {
        if(tablero[fila][columna]==color_enemigo){
            contador++;
            if(columna==C_C-1)
            	return contador;
            columna=columna+2; //Voy a la siguiente posicion a contar
        }else if(tablero[fila][columna]==color)
        {
        	contador=100000;
        	break;
        }
        else
            break; // si no es su color corto el ciclo
    }
    return contador;
}
void imprimir_guia_de_direccion(int tipo_seleccion,char cadena[4])
{
	if(tipo_seleccion==DP)
	{
		printf("Para desplazarse (IZQUIERDA SUPERIOR)-(DERECHA SUPERIOR)-(IZQUIERDA)\nSu canica representante es %c%c",cadena[0],cadena[1]);
		printf("\nSino su canica representante es %c%c",cadena[2],cadena[3]);
	}
	else if(tipo_seleccion==DS)
	{
		printf("Para desplazarse (IZQUIERDA SUPERIOR)-(DERECHA SUPERIOR)-(DERECHA)\nSu canica representante es %c%c",cadena[0],cadena[1]);
		printf("\nSino su canica representante es %c%c",cadena[2],cadena[3]);
	}else if(tipo_seleccion==HORIZONTAL)
	{
		printf("Para desplazarse (IZQUIERDA SUPERIOR)-(IZQUIERDA INFERIOR)-(IZQUIERDA)\nSu canica representante es %c%c",cadena[0],cadena[1]);
		printf("\nSino su canica representante es %c%c",cadena[2],cadena[3]);
	}

}
/*Saber que tipo de movimiento ejecutar realizarlo afuera, aqui solo movera*/
void movimiento_DP_EN_LINEA_superior(tipo_posicion posicion_i[3], int cant_canica,char color, char color_enemigo,char tablero[C_F][C_C])
{
	int fila, columna;
	fila=posicion_i[0].fila-1;
	columna=posicion_i[0].columna-1;
	while((fila>0 && columna>0) && tablero[fila][columna]==color_enemigo)
	{
		fila--;
		columna--;
	}
	if(fila>0 && columna>0 && tablero[posicion_i[0].fila-1][posicion_i[0].columna-1]==color_enemigo)
	{
		if(tablero[fila][columna]!=VACIO)
		{
			tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna]=VACIO;
			tablero[posicion_i[0].fila-1][posicion_i[0].columna-1]=color;
		}
		else
		{
			tablero[fila][columna]=color_enemigo;
			tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna]=VACIO;
			tablero[posicion_i[0].fila-1][posicion_i[0].columna-1]=color;
		}
	}else
	{
		tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna]=VACIO;
		tablero[posicion_i[0].fila-1][posicion_i[0].columna-1]=color;
	}
}
void movimiento_DP_EN_LINEA_inferior(tipo_posicion posicion_i[3], int cant_canica,char color, char color_enemigo,char tablero[C_F][C_C])
{
	int fila,columna;
	fila=posicion_i[cant_canica-1].fila+1;
	columna=posicion_i[cant_canica-1].columna+1;
	while((fila<C_F && columna<C_C) && tablero[fila][columna]==color_enemigo)
	{
		fila++;
		columna++;
	}
	if(fila<C_F && columna<C_C && tablero[posicion_i[cant_canica-1].fila+1][posicion_i[cant_canica-1].columna+1]==color_enemigo)
	{
		if(tablero[fila][columna]!=VACIO)
		{
			tablero[posicion_i[0].fila][posicion_i[0].columna]=VACIO;
			tablero[posicion_i[cant_canica-1].fila+1][posicion_i[cant_canica-1].columna+1]=color;
		}
		else
		{
			tablero[fila][columna]=color_enemigo;
			tablero[posicion_i[0].fila][posicion_i[0].columna]=VACIO;
			tablero[posicion_i[cant_canica-1].fila+1][posicion_i[cant_canica-1].columna+1]=color;
		}
	}
	else
	{
		tablero[posicion_i[0].fila][posicion_i[0].columna]=VACIO;
		tablero[posicion_i[cant_canica-1].fila+1][posicion_i[cant_canica-1].columna+1]=color;
	}

}
void movimiento_DS_EN_LINEA_superior(tipo_posicion posicion_i[3],int cant_canica,char color,char color_enemigo,char tablero[C_F][C_C])
{
	int fila,columna;
	fila=posicion_i[0].fila-1;
	columna=posicion_i[0].columna+1;
	while((fila>0 && columna<C_C) && tablero[fila][columna]==color_enemigo)
	{
		fila++;
		columna++;
	}
	if(fila>0 && columna<C_C && tablero[posicion_i[0].fila-1][posicion_i[0].columna+1]==color_enemigo)
	{
		if(tablero[fila][columna]!=VACIO)
		{
			tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna]=VACIO;
			tablero[posicion_i[0].fila-1][posicion_i[0].columna+1]=color;
		}
		else
		{
			tablero[fila][columna]=color_enemigo;
			tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna]=VACIO;
			tablero[posicion_i[0].fila-1][posicion_i[0].columna+1]=color;
		}
	}
	else
	{
		tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna]=VACIO;
		tablero[posicion_i[0].fila-1][posicion_i[0].columna+1]=color;
	}
}
void movimiento_DS_EN_LINEA_inferior(tipo_posicion posicion_i[3],int cant_canica,char color,char color_enemigo,char tablero[C_F][C_C])
{
	int fila,columna;
		fila=posicion_i[cant_canica-1].fila+1;
		columna=posicion_i[cant_canica-1].columna-1;
		while((fila<C_F && columna>0) && tablero[fila][columna]==color_enemigo)
		{
			fila++;
			columna--;
		}
		if(fila<C_F && columna>0 && tablero[posicion_i[0].fila+1][posicion_i[0].columna-1]==color_enemigo)
		{
			if(tablero[fila][columna]!=VACIO)
			{
				tablero[posicion_i[0].fila][posicion_i[0].columna]=VACIO;
				tablero[posicion_i[cant_canica-1].fila+1][posicion_i[cant_canica-1].columna-1]=color;
			}
			else
			{
				tablero[fila][columna]=color_enemigo;
				tablero[posicion_i[0].fila][posicion_i[0].columna]=VACIO;
				tablero[posicion_i[cant_canica-1].fila+1][posicion_i[cant_canica-1].columna-1]=color;
			}
		}
		else
		{
			tablero[posicion_i[0].fila][posicion_i[0].columna]=VACIO;
			tablero[posicion_i[cant_canica-1].fila+1][posicion_i[cant_canica-1].columna-1]=color;
		}
}
void movimiento_HORIZONTAL_EN_LINEA_izquierda(tipo_posicion posicion_i[3],int cant_canica,char color,char color_enemigo,char tablero[C_F][C_C])
{
	int fila,columna;
			fila=posicion_i[0].fila;
			columna=posicion_i[0].columna-2;
			while(columna>0 && tablero[fila][columna]==color_enemigo)
			{
				columna=columna-2;
			}
			if(columna>0 && tablero[posicion_i[0].fila][posicion_i[0].columna-2]==color_enemigo)
			{
				if(tablero[fila][columna]!=VACIO)
				{
					tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna]=VACIO;
					tablero[posicion_i[0].fila][posicion_i[0].columna-2]=color;
				}
				else
				{
					tablero[fila][columna]=color_enemigo;
					tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna]=VACIO;
					tablero[posicion_i[0].fila][posicion_i[0].columna-2]=color;
				}
			}
			else
			{
				tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna]=VACIO;
				tablero[posicion_i[0].fila][posicion_i[0].columna-2]=color;
			}
}
void movimiento_HORIZONTAL_EN_LINEA_derecha(tipo_posicion posicion_i[3],int cant_canica,char color,char color_enemigo,char tablero[C_F][C_C])
{
	int fila,columna;
			fila=posicion_i[cant_canica-1].fila;
			columna=posicion_i[cant_canica-1].columna+2;
			while(columna<C_C && tablero[fila][columna]==color_enemigo)
			{
				columna=columna+2;
			}
			if(columna<C_C && tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna+2]==color_enemigo)
			{
				if(tablero[fila][columna]!=VACIO)
				{
					tablero[posicion_i[0].fila][posicion_i[0].columna]=VACIO;
					tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna+2]=color;
				}
				else
				{
					tablero[fila][columna]=color_enemigo;
					tablero[posicion_i[0].fila][posicion_i[0].columna]=VACIO;
					tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna+2]=color;
				}
			}
			else
			{
				tablero[posicion_i[0].fila][posicion_i[0].columna]=VACIO;
				tablero[posicion_i[cant_canica-1].fila][posicion_i[cant_canica-1].columna+2]=color;
			}
}
void movimiento_simple(tipo_posicion posicion_final,tipo_posicion posicion_i[3],char color,char tablero[C_F][C_C])
{
	tablero[posicion_i[0].fila][posicion_i[0].columna]=VACIO;
	tablero[posicion_final.fila][posicion_final.columna]=color;
}
void movimiento_DE_LADO(tipo_posicion posicion_i[3],int cant_canica,char color,char color_enemigo,char tablero[C_F][C_C], int diferencia_fila, int diferencia_columna)
{
	int x;
	int fila,columna;
	for(x=0;x<cant_canica;x++)
	{
		fila=posicion_i[x].fila+diferencia_fila;
		columna=posicion_i[x].columna+diferencia_columna;
		tablero[fila][columna]=color;
		tablero[posicion_i[x].fila][posicion_i[x].columna]=VACIO;
	}
}

void movimiento_CPU(tipo_posicion posicion_i[3], int tipo_seleccion, int cant_canica, char tablero[C_F][C_C], tipo_posicion movimiento_posible[C_HUECO], int *cant_movimiento_posible,char color_enemigo,char color)
{
	int x,y;
	*cant_movimiento_posible=0;
	tipo_seleccion=UNICO;
	cant_canica=1;
	for(x=0;x<3;x++)
	{
        posicion_i[x].fila=0;
        posicion_i[x].columna=0;
        movimiento_posible[x].fila=0;
        movimiento_posible[x].columna=0;
	}
	for(x=0;x<C_F;x++)
	{
		for(y=0;y<C_C;y++)
		{
			if(tablero[x][y]==color_enemigo)
			{
				posicion_i[0].fila=x;
				posicion_i[0].columna=y;
				if(posible_libre(posicion_i,tipo_seleccion,cant_canica,tablero,movimiento_posible,cant_movimiento_posible)==TRUE)
				{
				   /* printf("\nx=%d y=%d",x,y);
                    for(k=0;k<(*cant_movimiento_posible);k++)
                        printf("\n%d\t%d",movimiento_posible[k].fila,movimiento_posible[k].columna);*/

				    movimiento_simple(movimiento_posible[0],posicion_i,color_enemigo,tablero);
				    imprimir_historial_CPU(tablero,color_enemigo,movimiento_posible,x,y,color);
				    return;
				}
			}
		}
	}
}
void imprimir_historial_CPU(char tablero[C_F][C_C],char color_enemigo,tipo_posicion movimiento_posible[C_HUECO],int x, int y,char color)
{
	int i,j,contador=0,canicas_empujadas=0;
	char retorno[2];
	printf("\n");
	printf("%s ",nombre2);
	pasar_referenchia(x,y,retorno);
	printf("ha movido su canica %s %c%d a ",(color_enemigo==BLANCO)?"BLANCO":"NEGRO",retorno[0],retorno[1]);
	retorno[0]='0',retorno[1]='0';
	pasar_referenchia(movimiento_posible[0].fila,movimiento_posible[0].columna,retorno);
	printf("%c%d",retorno[0],retorno[1]);
	for(i=0;i<C_F;i++)
	{
		for(j=0;j<C_C;j++){
			if(tablero[i][j]==color)
				contador++;
		}
	}
	canicas_empujadas=14-contador;
	printf("\nCantidad de canicas obtenidas:%d",canicas_empujadas);
	if(canicas_empujadas>0)
	{
		printf("\n|");
		for(i=0;i<canicas_empujadas;i++)
		{
			printf(" %c |",(color==BLANCO)?'B':'N');
		}
	}
	if(canicas_empujadas==6)
	{
		juego_terminado=TRUE;
	}
	else
	{
		juego_terminado=FALSE;
	}
}
void imprimir_historial_JUGADOR(char tablero[C_F][C_C],char color,tipo_posicion D,char color_enemigo)
{
	int i,j,contador=0,canicas_empujadas=0;
	char retorno[2];

	printf("\n");
	printf("%s ",nombre1);
	pasar_referenchia(D.fila,D.columna,retorno);
	printf("ha movido su canica %s a %c%d",(color==BLANCO)?"BLANCO":"NEGRO",retorno[0],retorno[1]);
	for(i=0;i<C_F;i++)
	{
		for(j=0;j<C_C;j++){
			if(tablero[i][j]==color_enemigo)
				contador++;
		}
	}
	canicas_empujadas=14-contador;
	printf("\nCantidad de canicas obtenidas:%d",canicas_empujadas);
	if(canicas_empujadas>0)
	{
		printf("\n|");
		for(i=0;i<canicas_empujadas;i++)
		{
			printf(" %c |",(color_enemigo==BLANCO)?'B':'N');
		}
		printf("\n");
	}
	if(canicas_empujadas==6)
	{
		juego_terminado=TRUE;
	}
	else
	{
		juego_terminado=FALSE;
	}

}

void verificar_resultado(char tablero[C_F][C_C],char color,char color_enemigo)
{
	int cant_jugador=0,cant_enemigo=0,x,y;
	for(x=0;x<C_F;x++)
	{
		for(y=0;y<C_C;y++)
		{
			if(tablero[x][y]==color)
			{
				cant_jugador++;
			}
			else if(tablero[x][y]==color_enemigo)
			{
				cant_enemigo++;
			}
		}
	}
	if(cant_jugador>cant_enemigo)
	{
		printf("\nEl ganador es: %s ",nombre1);
	}
	else if(cant_enemigo>cant_jugador)
	{
		printf("\nEl ganador es: %s ",nombre2);
	}else
	{
		printf("\nEMPATE");
	}
}
void esperar_enter()
{
	printf("\nPresione enter para el siguiente turno");
	int c;
	do
	{
		c=getchar();

	}while(c!='\n');
}
