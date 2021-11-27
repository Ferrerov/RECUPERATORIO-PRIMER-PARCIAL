#ifndef ABMCLIENTES_H_
#define ABMCLIENTES_H_

#include "Input.h"
#include "localidad.h"

#define LIBRE 0
#define OCUPADO 1

typedef struct
{
	char empresa[50];
	char cuit[13];
	char direccion[50];
	int idLocalidad;
	int idCliente;
	int isEmpty;
}eCliente;


/// @fn void inicializarClientes(eCliente[], int)
/// @brief inicializa el array de clientes, poniendo en "LIBRE" el isEmpty
/// @param datosCliente estructura de datos de los clientes
/// @param tam  tama�o del array de clientes
void InicializarClientes(eCliente datosCliente[],int tam);

/// @fn int cargarDatosCliente(eCliente[], int, int*)
/// @brief da de alta un cliente
/// @param datosCliente estructura de datos de los clientes
/// @param tam  tama�o del array de clientes
/// @param pIdCliente devuelve mediante un puntero al id de cliente generado
/// @return devuelve 0 si se pudo cargar el array, -1 si no se pudo
int CargarDatosCliente(eCliente datosCliente[], eLocalidad localidad[], int tam, int ultimoId, int* pIdCliente);

/// @fn int buscarIdCliente(eCliente[], int, int, int*)
/// @brief busca el id del cliente
/// @param datosCliente estructura de datos de los clientes
/// @param tam  tama�o del array de clientes
/// @param reintentos cantidad de oportunidades que se le dan al usuario para ingresar los datos
/// @param pIndice devuelve la posicion del array en donde se encuentra el idcliente
/// @return devuelve 0 si se pudo cargar el array, -1 si no se pudo
int BuscarIdCliente(eCliente datosCliente[], int tam, int reintentos, int* pIndice);

/// @fn int modificarCliente(eCliente[], int, int)
/// @brief modifica datos del cliente
/// @param datosCliente estructura de datos de los clientes
/// @param tam  tama�o del array de clientes
/// @param reintentos cantidad de oportunidades que se le dan al usuario para ingresar los datos
/// @return devuelve 0 si se pudo cargar el array, -1 si no se pudo
int ModificarCliente(eCliente datosCliente[], eLocalidad localidad[], int tam, int reintentos);

/// @fn int bajaCliente(eCliente[], int, int)
/// @brief da de baja un cliente (isEmpty en LIBRE)
/// @param datosCliente estructura de datos de los clientes
/// @param tam  tama�o del array de clientes
/// @param reintentos cantidad de oportunidades que se le dan al usuario para ingresar los datos
/// @returndevuelve 0 si se pudo cargar el array, -1 si no se pudo
int BajaCliente(eCliente datosCliente[], int tam, int reintentos);

#endif /* ABMCLIENTES_H_ */
