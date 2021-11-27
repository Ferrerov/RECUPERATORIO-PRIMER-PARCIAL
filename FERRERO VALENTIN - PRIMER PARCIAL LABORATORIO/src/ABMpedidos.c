#include "ABMpedidos.h"

void InicializarPedidos(ePedido datosPedido[], int tam)
{
    for(int i = 0; i < tam; i++) {
    	datosPedido[i].isEmpty = LIBRE;
    }
}

int CargarPedido( ePedido datosPedido[], int tamPedidos, eCliente datosCliente[], int tamCliente, int* pIdPedido, int reintentos)
{
	int retorno = -1;
	int indiceCliente;

	if(BuscarIdCliente(datosCliente, tamCliente, reintentos, &indiceCliente) == 0)
	{
		for(int i = 0; i < tamPedidos; i++)
		{
			if(datosPedido[i].isEmpty == LIBRE &&
			   GetFloat(&datosPedido[i].kilosTotales, "\nIngrese la cantidad de kilos totales a recolectar: ", "\nError, por favor ingrese la catnidad de kilos totales: ", 1, INT_MAX, 5) == 0)
			{
				datosPedido[i].estadoPedido = PENDIENTE;
				datosPedido[i].idCliente = datosCliente[indiceCliente].idCliente;
				datosPedido[i].idPedido = i + 1;
				*pIdPedido = datosPedido[i].idPedido;
				datosPedido[i].isEmpty = OCUPADO;
				retorno = 0;
				break;
			}
		}
	}
	if(retorno != 0)
	{
			printf("\nNo se ha podido cargar el pedido, se ha cancelado la operación. ");
	}
	return retorno;
}

int VerListaPedidosPendientes(eCliente datosCliente[], int tamCliente, ePedido datosPedido[], int tamPedido)
{
	int retorno = -1;

	for(int i = 0; i < tamCliente; i++)
	{
		if(datosCliente[i].isEmpty == OCUPADO && VerUnPedidoPendiente(datosPedido, tamPedido, datosCliente[i].idCliente) == 0)
		{
			retorno = 0;
		}
	}

	return retorno;
}

int VerUnPedidoPendiente(ePedido datosPedido[], int tamPedido, int idCliente)
{
	int retorno = -1;
	int flagEncabezado = -1;

	for(int i = 0; i < tamPedido; i++)
	{
		if(datosPedido[i].idCliente == idCliente && datosPedido[i].estadoPedido == PENDIENTE)
		{
			if(flagEncabezado != 0)
			{
				printf("\n---------------------------");
				printf("\n|%*s|%*s|", -11, "ID PEDIDO", -11, "KILOS TOTALES");
				printf("\n---------------------------");
				flagEncabezado = 0;
			}
			printf("\n|%*d|%*f", -11, datosPedido[i].idPedido, -11, datosPedido[i].kilosTotales);
			retorno = 0;
		}
	}
	return retorno;
}

int BuscarIdPedido(ePedido datosPedido[], int tam, int* pIndice)// SE PUEDE IR  ANEXO
{
	int retorno = -1;
	int idBuscar;

	if(GetInt(&idBuscar, "\nIngrese el ID del pedido: ", "\nError, ID fuera de rango. Ingrese nuevamente: ", 1, tam, 5) == 0)
	{
		for(int i = 0; i < tam; i++)
		{
			if(datosPedido[i].isEmpty == OCUPADO &&  datosPedido[i].idPedido == idBuscar)
			{
				*pIndice = i;
				retorno = 0;
				break;
			}
		}
	}

	return retorno;
}

int ProcesarResiduos(ePedido datosPedido[], int tamPedido, int reintentos)
{
	int retorno = -1;
	int indicePedido;

	do
	{
		reintentos--;
		if(BuscarIdPedido(datosPedido, tamPedido, &indicePedido) == 0)
		{

			if(GetFloat(&datosPedido[indicePedido].HDPE,
				"\nIngrese los kilos de plastico HDPE: ",
				"\nLa cantidad de kilos ingresada excede los kilos totales declarados. Por favor reingrese los datos.\nIngrese los kilos de plastico HDPE: ",
				0, datosPedido[indicePedido].kilosTotales, 5) == 0 &&
			   GetFloat(&datosPedido[indicePedido].LDPE,
				"\nIngrese los kilos de plastico LDPE: ",
				"\nLa cantidad de kilos ingresada excede los kilos totales declarados. Por favor reingrese los datos.\nIngrese los kilos de plastico LDPE:  ",
				0, datosPedido[indicePedido].kilosTotales - datosPedido[indicePedido].HDPE, 5) == 0 &&
			   GetFloat(&datosPedido[indicePedido].PP,
				"\nIngrese los kilos de plastico PP: ",
				"\nLa cantidad de kilos ingresada excede los kilos totales declarados. Por favor reingrese los datos.\nIngrese los kilos de plastico PP: ",
				0, datosPedido[indicePedido].kilosTotales - datosPedido[indicePedido].HDPE - datosPedido[indicePedido].LDPE, 5) == 0)
			{
				retorno = 0;
				datosPedido[indicePedido].estadoPedido = COMPLETADO;
				break;
			}
		}
		else
		{
			fflush(stdin);
			printf("ID no encontrado.");
		}
	}while( reintentos > 0 && retorno != 0);

	return retorno;
}

