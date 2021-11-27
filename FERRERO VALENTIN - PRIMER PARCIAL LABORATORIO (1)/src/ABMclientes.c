#include "ABMclientes.h"

void InicializarClientes(eCliente datosCliente[],int tam)
{
    for(int i = 0; i < tam; i++) {
    	datosCliente[i].isEmpty = 0;
    }
}

int CargarDatosCliente(eCliente datosCliente[], eLocalidad localidad[], int tam, int ultimoId, int* pIdCliente)
{
	int retorno = -1;
	for(int i = 0; i < tam; i++)
	{
		if(datosCliente[i].isEmpty == LIBRE)
		{
			if(GetString(datosCliente[i].empresa, "Ingrese el nombre de la empresa: ", "Error, por favor ingrese al menos un caracter: \n",4) == 0 &&
			GetCuit(datosCliente[i].cuit, "Ingrese el cuit de la empresa: ", "Error, ingrese un cuit válido: ", 4) == 0 &&
			GetString( datosCliente[i].direccion,"Ingrese la dirección de la empresa: ", "Error, por favor ingrese al menos un caracter: \n",4) == 0 &&
			NuevaLocalidad(&datosCliente[i].idLocalidad, localidad, tam) == 0)
			{
				datosCliente[i].idCliente = ultimoId + 1;
				*pIdCliente = datosCliente[i].idCliente;
				datosCliente[i].isEmpty = OCUPADO;
				retorno = 0;
			}
			break;
		}
	}

	return retorno;
}

int BuscarIdCliente(eCliente datosCliente[], int tam, int reintentos, int* pIndice)//PUEDE IR EN BIBLIOTECA NEXO
{
	int retorno = -1;
	int idBuscar;

	do
	{
		reintentos--;

		GetInt(&idBuscar, "\nIngrese el ID del cliente: ", "\nError, ID fuera de rango. Ingrese nuevamente: ", 1, tam, 5);

		for(int i = 0; i < tam; i++)
		{
			if(datosCliente[i].isEmpty == OCUPADO &&  datosCliente[i].idCliente == idBuscar)
			{
				*pIndice = i;
				reintentos = 0;
				retorno = 0;
				break;
			}
		}
		if(retorno != 0)
		{
			printf("ID no encontrado.");
		}
	}while(reintentos > 0);

	return retorno;
}

int ModificarCliente(eCliente datosCliente[], eLocalidad localidad[], int tam, int reintentos)
{
	int retorno = -1;
	int indiceId;

	if(BuscarIdCliente(datosCliente, tam, reintentos, &indiceId) == 0)
	{
		GetString(datosCliente[indiceId].direccion, "Ingrese la nueva dirección de la empresa: ", "Error, por favor ingrese al menos un caracter: \n",4);
		NuevaLocalidad(&datosCliente[indiceId].idLocalidad, localidad, tam);
		retorno = 0;
	}

	return retorno;
}

int BajaCliente(eCliente datosCliente[], int tam, int reintentos)
{
	int retorno = -1;
	int idBaja;
	char respuesta;

	do
	{
		reintentos--;
		GetInt(&idBaja, "\nIngrese el ID del cliente a dar de baja: ","\nError, ID fuera de rango. Ingrese nuevamente: ", 1,100, 5);

		for(int i = 0; i < tam; i++)
		{
			if(datosCliente[i].isEmpty == OCUPADO && datosCliente[i].idCliente == idBaja)
			{
				GetYesNo("\nEsta seguro que desea dar de baja al cliente? (s/n): ", "\nError, ingrese una opción válida: ", &respuesta, 5);

				if(respuesta == 's')
				{
					datosCliente[i].isEmpty = LIBRE;
					retorno = 0;
				}
			}
		}

	}while(retorno != 0 && reintentos > 0);
	return retorno;
}

