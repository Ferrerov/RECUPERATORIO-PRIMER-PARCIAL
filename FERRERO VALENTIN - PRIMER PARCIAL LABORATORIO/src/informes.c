#include "informes.h"

int MostrarUnCliente(eCliente datosCliente, eLocalidad datosLocalidad[], int tam)
{
	int retorno = -1;
	char auxLocalidad[50];

	if(datosCliente.isEmpty == OCUPADO)
	{
		if(VerLocalidadPorId(auxLocalidad, datosLocalidad, tam, datosCliente.idLocalidad) == 0)
		{
			printf("\n|%-11d|%-30s|%-13s|%-23s|%-23s|",
					datosCliente.idCliente,
					datosCliente.empresa,
					datosCliente.cuit,
					datosCliente.direccion,
					auxLocalidad);
			retorno = 0;
		}

	}

	return retorno;
}

int VerListaClientes(eCliente datosCliente[], eLocalidad datosLocalidad[], int tam)
{
	int retorno = -1;
	printf("\n----------------------------------------------------------------------------------------------------------");
	printf("\n|%*s|%*s|%*s|%*s|%*s|", -11, "ID CLIENTE", -30, "NOMBRE DE LA EMPRESA",-13,"CUIT",-23 ,"DIRECCION", -23,"LOCALIDAD");
	printf("\n----------------------------------------------------------------------------------------------------------");

	for(int i = 0; i < tam; i++)
	{
		if(MostrarUnCliente(datosCliente[i], datosLocalidad, tam) == 0)
		{
			retorno = 0;
		}
	}
	printf("\n----------------------------------------------------------------------------------------------------------");
	return retorno;
}

int ContadorEstadoPedido(int* pCantidad, int idCliente, int estadoPedido,ePedido datosPedido[], int tamPedido)
{
	int retorno = -1;
	int contador = 0;

	for(int i = 0; i < tamPedido; i++)
	{
		if(datosPedido[i].isEmpty == OCUPADO && datosPedido[i].estadoPedido == estadoPedido && datosPedido[i].idCliente == idCliente)
		{
			contador++;
			retorno = 0;
		}
	}
	*pCantidad = contador;

	return retorno;
}

int InformarClientes(eLocalidad datosLocalidad[], eCliente datosCliente[], int tamCliente, ePedido datosPedido[], int tamPedido)
{
	int retorno = -1;
	int cantidad;

	printf("\n-----------------------------------------------------------------------------------------------------------------------------");
	printf("\n|%*s|%*s|%*s|%*s|%*s|%*s|", -11, "ID CLIENTE", -30, "NOMBRE DE LA EMPRESA",-13,"CUIT",-23 ,"DIRECCION", -23,"LOCALIDAD", -18, "PEDIDOS PENDIENTES");
	printf("\n"
			"|---------------------------------------------------------------------------------------------------------------------------|");
	for(int i = 0; i < tamCliente; i++)
	{
		if(MostrarUnCliente(datosCliente[i], datosLocalidad, tamCliente) == 0)
		{
			ContadorEstadoPedido(&cantidad, datosCliente[i].idCliente, PENDIENTE, datosPedido, tamPedido);
			printf("%d                 |", cantidad);
			printf("\n|---------------------------------------------------------------------------------------------------------------------------|");
			retorno = 0;
		}
	}
	return retorno;
}

int ClientesPorPedido(int idClientePedido, eCliente datosCliente[], int tamClientes)
{
	int retorno = -1;

	for(int i = 0; i < tamClientes; i++)
	{
		if(idClientePedido == datosCliente[i].idCliente && datosCliente[i].isEmpty == OCUPADO)
		{
			printf("\n----------------------------------------------");
			printf("\n|%*s|%*s|",-13,"CUIT",-30 ,"DIRECCION");
			printf("\n----------------------------------------------");
			printf("\n|%*s|%*s|", -13, datosCliente[i].cuit, -30, datosCliente[i].direccion);
			printf("\n----------------------------------------------");
			retorno = 0;
		}
	}

	return retorno;
}

int InformarClientesPorEstado(int estado, eCliente datosCliente[], int tamCliente, ePedido datosPedido[], int tamPedido)
{
	int retorno = -1;

	for(int i = 0; i < tamPedido; i++)
		{
			if(estado == PENDIENTE && datosPedido[i].estadoPedido == PENDIENTE && datosPedido[i].isEmpty == OCUPADO)
			{
				ClientesPorPedido(datosPedido[i].idCliente, datosCliente, tamCliente);
				printf("\nCantidad de kilos totales: %.2f\n" , datosPedido[i].kilosTotales);
				retorno = 0;
			}
			else
			{
				if(datosPedido[i].estadoPedido == COMPLETADO && datosPedido[i].isEmpty == OCUPADO)
				{
					ClientesPorPedido(datosPedido[i].idCliente, datosCliente, tamCliente);
					printf("\nCantidad de kilos de HDPE: %.2f" , datosPedido[i].HDPE);
					printf("\nCantidad de kilos de LDPE: %.2f" , datosPedido[i].LDPE);
					printf("\nCantidad de kilos de PP: %.2f" , datosPedido[i].PP);
					retorno = 0;
				}
			}
		}

	return retorno;
}

int InformarPendientesPorLocalidad(eLocalidad localidades[], eCliente datosCliente[], int tamCliente, ePedido datosPedido[], int tamPedido)
{
	int retorno = -1;
	int idLocalidad;
	char auxLocalidad[50];
	int cantidadPendientes;

	VerListadoDeLocalidades(localidades, tamCliente);
	if(GetString(auxLocalidad, "\nIngrese la localidad: ", "Error, ingrese al menos un caracter: ", 4) == 0 && BuscarLocalidad(&idLocalidad, auxLocalidad, localidades, tamCliente)==0)
	//if(BuscarLocalidad(&idLocalidad, auxLocalidad, localidades, tamCliente)==0)
	{
		for(int i = 0; i < tamCliente; i++)
		{
			if(datosCliente[i].idLocalidad == idLocalidad &&
					ContadorEstadoPedido(&cantidadPendientes, datosCliente[i].idCliente, PENDIENTE, datosPedido, tamPedido) == 0)
			{
				retorno = 0;
				printf("\nLocalidad seleccionada: %s" , auxLocalidad);
				printf("\nCantidad de pedidos pendientes: %d", cantidadPendientes);
			}
		}
	}
	else
	{
		printf("\nNo se ha encontrado la localidad ingresada.");
	}

	return retorno;
}

int PromedioPolipropileno(ePedido datosPedido[], int tamPedido, int idCliente, float* pPromedio)
{
	int retorno = -1;
	float acumulador = 0;
	int contador = 0;

	for(int i = 0; i < tamPedido; i++)
	{
		if(idCliente == datosPedido[i].idCliente && datosPedido[i].estadoPedido == COMPLETADO && datosPedido[i].HDPE > 0)
		{
			acumulador = acumulador + datosPedido[i].HDPE;
			contador++;
			retorno = 0;
		}
	}
	*pPromedio = acumulador / contador;

	return retorno;
}

int InformarPolipropilenoPromedio(eCliente datosCliente[], int tamCliente, ePedido datosPedido[], int tamPedido)
{
	int retorno = -1;
	float promedio;
	int flag = -1;

	for(int i = 0; i < tamCliente; i++)
	{
		if(datosCliente[i].isEmpty == OCUPADO && PromedioPolipropileno(datosPedido, tamPedido, datosCliente[i].idCliente, &promedio) == 0)
		{
			if(flag != 0)
			{
				printf("\n-------------------------------------------------------");
				printf("\n|%*s|%*s|" , -30, "NOMBRE DE LA EMPRESA", -22, "POLIPROPILENO PROMEDIO");
				printf("\n-------------------------------------------------------");
				flag = 0;
			}
			printf("\n|%*s|%*.2f|", -30, datosCliente[i].empresa, -22, promedio);
			printf("\n|-----------------------------------------------------|");
			retorno = 0;
		}
	}
	return retorno;
}

int BuscarMaxEstadoPedido(int* pIndice, int* pCantidad, int estadoPedido,eCliente datosCliente[], int tamCliente, ePedido datosPedido[], int tamPedido)
{
	int retorno = -1;
	int cantidad;
	int cantidadMax = 0;

	for(int i = 0; i < tamCliente; i++)
	{
		ContadorEstadoPedido(&cantidad, datosCliente[i].idCliente, estadoPedido, datosPedido, tamPedido);
		if(cantidad > cantidadMax)
		{
			cantidadMax = cantidad;
			*pIndice = datosCliente[i].idCliente;
			retorno = 0;
		}
	}
	*pCantidad = cantidadMax;

	return retorno;
}

int InformarClienteMaxPorEstado(int estado, eCliente datosCliente[], int tamCliente, ePedido datosPedido[], int tamPedido)
{
	int retorno = -1;
	int indice;
	int cantidad;

	if(BuscarMaxEstadoPedido(&indice, &cantidad, estado, datosCliente, tamCliente, datosPedido,tamPedido) == 0)
	{
		if(estado == PENDIENTE)
		{
			printf("\nEl cliente que mas pedidos pendientes tiene es: %s", datosCliente[indice].empresa);
			printf("\nLa cantidad de pedidos pendientes es de: %d\n", cantidad);
			retorno = 0;
		}
		else
		{
			printf("\nEl cliente que mas pedidos completados tiene es: %s", datosCliente[indice].empresa);
			printf("\nLa cantidad de pedidos completados es de: %d\n", cantidad);
			retorno = 0;
		}
	}

	return retorno;
}
