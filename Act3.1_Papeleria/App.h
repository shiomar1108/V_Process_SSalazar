/***********************************************
 * File: App.h
 * Description: Define interface to App.c
 * Author: ssalazar
 **************************************************/

#ifndef INC_APP_H
#define INC_APP_H

/* Standard library include */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Typedefs */
#define SERVICIO   (0)
#define ARTICULO   (1)

typedef enum {
    APP_Alta = 0,
    APP_Baja = 1,
    App_Consulta = 2,
    App_Salida = 3,
    APP_Total = 4
}APP_Menu_t;

typedef enum {
    Actor_Cliente = 0,
    Actor_Servicios = 1,
    Actor_Articulo = 2,
    Actor_Venta = 3,
    Actor_Total = 4
}App_Actor_t;

typedef struct{
    int id;
    char nombre[30];
    int credito;
    char direccion[30];
}Cliente_t;

typedef struct{
    int id;
    char nombre[15];
    bool tipo;
    int precio;
    int cantidad;
} Articulo_t;

typedef struct{
    Cliente_t comprador;
    Articulo_t objetos[20];
    int cant_prod;
    int monto_total;
}Venta_t;

/* Desicion de Diseño:
 * Los servicios se trataran como articulos,
 * pero sin cantidad */

/* Static variable definition */
static Venta_t historial_venta[20] = {0};
static Cliente_t lista_cliente[40]={0};
static Articulo_t lista_articulo[100] = {0};

static int index_venta = 0;
static int index_cliente = 0;
static int index_articulo = 0;

/* Public Function prototype */
void App_Init(void);
int Menu_show(void);
void Menu_consulta(void);
void Menu_alta(void);
void Menu_baja(void);



#endif // INC_APP_H
