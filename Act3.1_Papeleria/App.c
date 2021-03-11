/***********************************************
 * File: App.h
 * Description: Implements interface to App.c
 * Author: ssalazar
 **************************************************/

#include "App.h"

/*  Private function prototype */
void Consulta_Op (int op);
void Alta_Op (int op);
void Baja_Op (int op);
void Imprimir_Cliente(void);
void Imprimir_Catalogo(void);
void Imprimir_Articulo(void);
void Imprimir_Servicios(void);
void Imprimir_Venta(void);


/*    Function Implementation */
void App_Init(void)
{
    /* Funcion para inicializar uno de cada cosa, para tener un default */
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

    printf("\n Menu de la Papeleria La Gomita: \n");
    printf(" Alta -------> 0 \n");
    printf(" Baja -------> 1 \n");
    printf(" Consulta ---> 2 \n");
    printf(" Salir ------> 3 \n");
    printf(" Seleccione una accion de menu : ");
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
    printf(" Seleccione una accion de menu : ");
    scanf("%d", &res);
    Consulta_Op(res);
}

void Menu_alta(void)
{
    int res = APP_Total;

    printf("\n Menu de Alta: \n");
    printf(" Clientes ---> 0 \n");
    printf(" Servicios --> 1 \n");
    printf(" Acticulos --> 2 \n");
    printf(" Ventas -----> 3 \n");
    printf(" Salir ------> 4 \n");
    printf(" Seleccione una accion de menu : ");
    scanf("%d", &res);
    Alta_Op(res);
}

void Menu_baja(void)
{
    int res = APP_Total;

    printf("\n Menu de Baja: \n");
    printf(" Clientes ---> 0 \n");
    printf(" Servicios --> 1 \n");
    printf(" Acticulos --> 2 \n");
    printf(" Ventas -----> 3 \n");
    printf(" Salir ------> 4 \n");
    printf(" Seleccione una accion de menu : ");
    scanf("%d", &res);
    Baja_Op(res);
}

void Imprimir_Cliente(void)
{
    int i = 0;
    if(index_cliente > 0)
    {
        while(i < index_cliente)
        {
            printf(" ID de Cliente: %d Nombre del Cliente: %s Direccion del Cliente: %s Credito Disponible: %d \n",lista_cliente[i].id,lista_cliente[i].nombre, lista_cliente[i].direccion,lista_cliente[i].credito);
            i++;
        }
    }
    else
    {
        printf("\n ERROR: Lista de Clientes vacia \n");
    }
}
void Imprimir_Catalogo(void)
{
    int i = 0;
    char temp[10];
    printf("\n Catalogos de Productos: \n");
    if(index_articulo > 0)
    {
        while(i < index_articulo)
        {
            if(SERVICIO == lista_articulo[i].tipo)
            {
                strcpy(temp,"SERVICIO");
            }
            else
            {
                strcpy(temp,"ARTICULO");
            }
            printf(" ID del Producto: %d Nombre del Producto: %s Tipo de Producto %s Precio: %d Inventario Disponible: %d \n",lista_articulo[i].id,lista_articulo[i].nombre, temp,lista_articulo[i].precio,lista_articulo[i].cantidad);
            i++;
        }
    }
    else
    {
        printf("\n ERROR: Lista de Clientes vacia \n");
    }
}
void Imprimir_Articulo(void)
{
    int i = 0;
    if(index_articulo > 0)
    {
        while(i < index_articulo)
        {
            if(ARTICULO == lista_articulo[i].tipo)
            {
                printf(" ID del Articulo: %d Nombre del Articulo: %s Precio: %d Cantidad Disponible %d\n",lista_articulo[i].id, lista_articulo[i].nombre, lista_articulo[i].precio, lista_articulo[i].cantidad);
            }
            i++;
        }
    }
    else
    {
        printf("\n ERROR: Lista de Servicios vacia \n");
    }
}
void Imprimir_Servicios(void)
{
    int i = 0;
    if(index_articulo > 0)
    {
        while(i < index_articulo)
        {
            if(SERVICIO == lista_articulo[i].tipo)
            {
                printf(" ID del Servicio: %d Nombre del Servicio: %s Precio: %d \n",lista_articulo[i].id, lista_articulo[i].nombre, lista_articulo[i].precio);
            }
            i++;
        }
    }
    else
    {
        printf("\n ERROR: Lista de Articulo vacia \n");
    }
}
void Imprimir_Venta(void)
{
    int i = 0;
    char temp[10];
    if(index_venta > 0)
    {
        while(i < index_venta)
        {
            printf("\n Resumen de venta #%d \n",i);
            printf(" ID de Cliente: %d Nombre del Cliente: %s Direccion del Cliente: %s Monto total de la venta:$ %d  \n",historial_venta[i].comprador.id,historial_venta[i].comprador.nombre, historial_venta[i].comprador.direccion,historial_venta[i].monto_total );
            printf(" Productos:\n");
            for(int index = 0; index < historial_venta[i].cant_prod; index++)
            {
                if(SERVICIO == historial_venta[i].objetos[index].tipo)
                {
                    strcpy(temp,"SERVICIO");
                }
                else
                {
                    strcpy(temp,"ARTICULO");
                }
                printf(" ID del Producto: %d Nombre del Producto: %s Tipo de Producto %s Precio: %d \n",historial_venta[i].objetos[index].id,historial_venta[i].objetos[index].nombre, temp,historial_venta[i].objetos[index].precio);
            }
            i++;
        }
    }
    else
    {
        printf("\n ERROR: Lista de Ventas vacia \n");
    }
}


void Consulta_Op (int op)
{
    switch (op)
    {
        case Actor_Cliente:
            printf("\n Consulta de Clientes: \n");
            Imprimir_Cliente();
        break;
        case Actor_Articulo:
            printf("\n Consulta de Articulos: \n");
            Imprimir_Articulo();
        break;
        case Actor_Servicios:
            printf("\n Consulta de Servicios: \n");
            Imprimir_Servicios();
        break;
        case Actor_Venta:
            printf("\n Consulta de Ventas: \n");
            Imprimir_Venta();
        break;
        default:
            printf("\n ERROR en la Consulta \n");
        break;
    }
}

void Alta_Op (int op)
{
    int temp_int = 0;
    char temp_text[30];
    bool fin = false;
    int venta_count = 0;
    char temp_char;
    int cliente_i = 0;
    switch(op)
    {
        case Actor_Cliente:
            printf("\n Menu de Alta de Cliente : \n");
            lista_cliente[index_cliente].id = index_cliente;
            printf(" Escriba el Nombre del Cliente : ");
            scanf(" %49[^\n]s",temp_text);
            strcpy(lista_cliente[index_cliente].nombre,temp_text);
            printf(" Escriba la Direccion del Cliente : ");
            scanf(" %49[^\n]s", &temp_text);
            strcpy(lista_cliente[index_cliente].direccion,temp_text);
            printf(" Escriba el Credito otorgado a Cliente : $ ");
            scanf("%d", &temp_int);
            lista_cliente[index_cliente].credito = temp_int;
            index_cliente++;
        break;
        case Actor_Articulo:
            printf("\n Menu de Alta de Articulos : \n");
            lista_articulo[index_articulo].id = index_articulo;
            printf(" Escriba el Nombre del Articulo : ");
            scanf(" %49[^\n]s",temp_text);
            strcpy(lista_articulo[index_articulo].nombre,temp_text);
            lista_articulo[index_articulo].tipo = ARTICULO;
            printf(" Escriba el Precio del Articulo : $ ");
            scanf("%d", &temp_int);
            lista_articulo[index_articulo].precio = temp_int;
            printf(" Escriba el Inventario del Articulo : ");
            scanf("%d", &temp_int);
            lista_articulo[index_articulo].cantidad = temp_int;
            index_articulo++;
        break;
        case Actor_Servicios:
            printf("\n Menu de Alta de Servicio : \n");
            lista_articulo[index_articulo].id = index_articulo;
            printf(" Escriba el Nombre del Servicio : ");
            scanf(" %49[^\n]s",temp_text);
            strcpy(lista_articulo[index_articulo].nombre,temp_text);
            lista_articulo[index_articulo].tipo = SERVICIO;
            printf(" Escriba el Precio del Servicio : $ ");
            scanf("%d", &temp_int);
            lista_articulo[index_articulo].precio = temp_int;
            lista_articulo[index_articulo].cantidad = 32767;
            index_articulo++;
        break;
        case Actor_Venta:
            printf("\n Lista de Clientes \n");
            Imprimir_Cliente();
            printf("\n Menu de Alta de Ventas : \n");
            printf(" Escriba el Id del Cliente que compra: ");
            scanf("%d", &cliente_i);
            historial_venta[index_venta].comprador = lista_cliente[cliente_i];
            do
            {
                Imprimir_Catalogo();
                printf(" Escriba el Id del Producto a agregar: ");
                scanf("%d", &temp_int);
                historial_venta[index_venta].objetos[venta_count] = lista_articulo[temp_int];
                venta_count++;
                historial_venta[index_venta].cant_prod = venta_count;
                historial_venta[index_venta].monto_total += lista_articulo[temp_int].precio;
                lista_articulo[temp_int].cantidad--;
                printf(" Desea agregar otro articulo: [Y/N] ");
                scanf(" %c", &temp_char);
                if(temp_char == 'Y')
                {
                    fin = false;
                }
                else if(temp_char == 'N')
                {
                    fin = true;
                }
                else
                {
                    printf("\n Error en la Opcion \n");
                }
            }
            while(true != fin);
            lista_cliente[cliente_i].credito -= historial_venta[index_venta].monto_total;
            index_venta++;
        break;
        default:
            printf("\n ERROR en la Alta \n");
        break;
    }
}
void Baja_Op (int op)
{
    int temp_int = 0;
    switch(op)
    {
        case Actor_Cliente:
            printf("\n Lista de Clientes \n");
            Imprimir_Cliente();
            printf("\n Menu de Baja de Cliente : \n");
            printf(" Escriba el Id del Cliente a dar de baja: ");
            scanf("%d", &temp_int);
            if(temp_int < index_cliente)
            {

                for(int i = temp_int;i<index_cliente; i++)
                {
                    lista_cliente[i] = lista_cliente[i+1];
                    lista_cliente[i].id--;
                }
                index_cliente--;
                printf("\n Baja EXITOSA \n");
            }
            else
            {
                printf("\n Error en la Opcion \n");
            }
        break;
        case Actor_Servicios:
            printf("\n Lista de Servicios \n");
            Imprimir_Servicios();
            printf("\n Menu de Baja de Servicios : \n");
            printf(" Escriba el Id del Servicio a dar de baja: ");
            scanf("%d", &temp_int);
            if(temp_int < index_articulo)
            {

                for(int i = temp_int;i<index_articulo; i++)
                {
                    lista_articulo[i] = lista_articulo[i+1];
                    lista_articulo[i].id--;
                }
                index_articulo--;
                printf("\n Baja EXITOSA \n");
            }
            else
            {
                printf("\n Error en la Opcion \n");
            }
        break;
        case Actor_Articulo:
            printf("\n Lista de Articulos \n");
            Imprimir_Articulo();
            printf("\n Menu de Baja de Articulos : \n");
            printf(" Escriba el Id del Articulo a dar de baja: ");
            scanf("%d", &temp_int);
            if(temp_int < index_articulo)
            {
                for(int i = temp_int;i<index_articulo; i++)
                {
                    lista_articulo[i] = lista_articulo[i+1];
                    lista_articulo[i].id--;
                }
                index_articulo--;
                printf("\n Baja EXITOSA \n");
            }
            else
            {
                printf("\n Error en la Opcion \n");
            }
        break;
        case Actor_Venta:
            printf("\n Lista de Ventas \n");
            Imprimir_Venta();
             printf("\n Menu de Baja de Articulos : \n");
            printf(" Escriba el # de lq venta a dar de baja: ");
            scanf("%d", &temp_int);
            if(temp_int < index_venta)
            {
                for(int i = temp_int;i<index_venta; i++)
                {
                    historial_venta[i] = historial_venta[i+1];
                }
                index_venta--;
                printf("\n Baja EXITOSA \n");
            }
            else
            {
                printf("\n Error en la Opcion \n");
            }
        break;
        default:
            printf("\n ERROR en la Baja \n");
        break;
    }
}

