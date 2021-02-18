/***********************************************
 * File: App.h
 * Description: Implements interface to App.c
 * Author: ssalazar
 **************************************************/

#include "App.h"

/*  Private function prototype */
void App_Init(void);
void Consulta_Op (int op);

void write_Cliente (int id);
void write_Articulo (int id);
void write_Venta (int id);

/*    Function Implementation */
void App_Init(void)
{
    /* Funcion para inicializar uno de cada cosa, para tene run default */
    /* Init Cliente */
    lista_cliente[index_cliente].id = index_cliente;
    strcpy(lista_cliente[index_cliente].nombre,"ANONIMO");
    strcpy(lista_cliente[index_cliente].direccion,"ANONIMO");
    lista_cliente[index_cliente].credito = 32767;
    index_cliente++;

    /*Init Articulo*/
    lista_articulo[index_articulo].id = index_articulo;
    strcpy(lista_articulo[index_articulo].nombre,"Lapiz");
    lista_articulo[index_articulo].cantidad = 100;
    lista_articulo[index_articulo].precio = 2;
    lista_articulo[index_articulo].tipo = ARTICULO;
    index_articulo++;

    /*Init Servicio*/
    lista_articulo[index_articulo].id = index_articulo;
    strcpy(lista_articulo[index_articulo].nombre,"Impresion");
    lista_articulo[index_articulo].cantidad = 32767;
    lista_articulo[index_articulo].precio = 1;
    lista_articulo[index_articulo].tipo = SERVICIO;
    index_articulo++;
}

int Menu_show(void)
{
    int res = APP_Total;

    App_Init();

    printf("\n Menu de la Papeleria La Gomita: \n");
    printf(" Alta -------> 0 \n");
    printf(" Baja -------> 1 \n");
    printf(" Consulta ---> 2 \n");
    printf(" Salir ------> 3 \n");
    printf(" Seleccione una accion de menu : \n");
    scanf("%d", &res);
    return res;
}

void Menu_consulta(void)
{
    int res = APP_Total;

    printf("\n Menu de Consulta: \n");
    printf(" Clientes ---> 0 \n");
    printf(" Servicios --> 1 \n");
    printf(" Acticulos --> 2 \n");
    printf(" Ventas -----> 3 \n");
    printf(" Salir ------> 4 \n");
    printf(" Seleccione una accion de menu : \n");
    scanf("%d", &res);
    Consulta_Op(res);
}

void Consulta_Op (int op)
{
    switch (op)
    {
        case Actor_Cliente:
            if(index_cliente > 0)
            {

            }
            else
            {
                printf("\n ERROR: Lista de Clientes vacia \n");
            }
        break;
        case Actor_Servicios:
            if(index_articulo > 0)
            {

            }
            else
            {
                printf("\n ERROR: Lista de Servicios vacia \n");
            }
        break;
        case Actor_Articulo:
            if(index_articulo > 0)
            {

            }
            else
            {
                printf("\n ERROR: Lista de Articulo vacia \n");
            }
        break;
        case Actor_Venta:
            if(index_venta > 0)
            {

            }
            else
            {
                printf("\n ERROR: Lista de Ventas vacia \n");
            }
        break;
        default:
            printf("\n ERROR en la consulta \n");
        break;
    }

}

