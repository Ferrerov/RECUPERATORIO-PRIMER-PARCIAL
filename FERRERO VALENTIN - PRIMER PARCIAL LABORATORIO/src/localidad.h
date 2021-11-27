#ifndef LOCALIDAD_H_
#define LOCALIDAD_H_

#include "Input.h"

#define LIBRE 0
#define OCUPADO 1

typedef struct
{
	int idLocalidad;
	char localidad[50];
	int isEmpty;
}eLocalidad;

/// @fn void InicializarLocalidades(eLocalidad[], int)
/// @brief coloca a cada isEmpty de la entidad en LIBRE
/// @param localidades array de la estructura localidad
/// @param tam tamaño del array localidad
void InicializarLocalidades(eLocalidad localidades[], int tam);

/// @fn int BuscarLocalidad(int*, char[], eLocalidad[], int)
/// @brief entregandole una string compara en la entidad localidad y si lo encuentra devuelve el id asignado
/// @param idLocalidad obtiene un puntero del idLocalidad
/// @param localidad string a comparar
/// @param localidades array de la estructura localidad
/// @param tamLocalidades tamaño del array localidad
/// @return devuelve 0 si se encontro la localidad
int BuscarLocalidad(int* idLocalidad, char localidad[], eLocalidad localidades[], int tamLocalidades);

/// @fn int NuevaLocalidad(int*, eLocalidad[], int)
/// @brief solicita una localidad, verifica si ya fue ingresada y le asigna un id de ser necesario
/// @param idLocalidad devuelve como puntero el id generado
/// @param localidad array de la estructura localidad
/// @param tamLocalidades tamaño del array localidad
/// @return devuelve 0 si se pudo cargar la localidad
int NuevaLocalidad(int* idLocalidad, eLocalidad localidad[], int tamLocalidades);

/// @fn void VerLocalidadPorId(char[], eLocalidad[], int, int)
/// @brief Obtiene el dato localidad buscando un id coincidente en la estructura
/// @param localidad Dato a obtener
/// @param localidades array de la estructura eLocalidad
/// @param tamLocalidad tamaño del array localidad
/// @param idLocalidad id obtenido como parametro para comparar
int VerLocalidadPorId(char localidad[], eLocalidad localidades[], int tamLocalidad, int idLocalidad);

/// @fn int VerUnaLocalidad(eLocalidad[], int, int)
/// @brief Muestra una localidad
/// @param localidad array de la estructura eLocalidad
/// @param tamLocalidades tamaño del array localidad
/// @param idLocalidad id obtenido como parametro para comparar
/// @return Retorna (-1) Si no encontro la localidad coincidente
/// 				(0) Si encontro el dato y imprimio la localidad
int VerUnaLocalidad(eLocalidad localidad[], int tamLocalidades, int idLocalidad);

/// @fn int VerListadoDeLocalidades(eLocalidad[], int)
/// @brief Muestra un listado de todas las localidades
/// @param localidad array de la estructura eLocalidad
/// @param tamLocalidad tamaño del array localidad
/// @return Retorna (-1) Si no imprimio datos
/// 				(0) Si encontro al menos una localidad y la imprimio
int VerListadoDeLocalidades(eLocalidad localidad[], int tamLocalidad);


#endif /* LOCALIDAD_H_ */
