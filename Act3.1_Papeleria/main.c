#include "App.h"

int op_menu = APP_Total;

int main()
{
    App_Init();

    while (op_menu != App_Salida)
    {
        op_menu = Menu_show();
        switch(op_menu)
        {
            case APP_Alta:
                printf("\n Se solicito Operacion de Alta \n");
                Menu_alta();
            break;
            case APP_Baja:
                printf("\n Se solicito Operacion de Baja \n");
                Menu_baja();
            break;
            case App_Consulta:
                printf("\n Se solicito Operacion de Consulta \n");
                Menu_consulta();
            break;
            case App_Salida:
                printf("\n ADIOS !!! :D \n");
            break;
            default:
                printf("\n Se solicito una Operacion Erronea \n");
            break;
        }
    }
    return 0;
}
