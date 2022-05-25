#ifndef DISPARO_H_INCLUDED
#define DISPARO_H_INCLUDED
#include "Pantalla.h"

/**
\file Disparo.h
\brief El TDA Disparo crea un disparo en eñ juego.
*/

/**
\brief TDA Disparo
*/
typedef struct DisparoRep * Disparo;

/**
\brief Crea un disparo.
\param i La imagen del disparo.
\param x La posición en el eje x del disparo.
\param y La posición en el eje y del disparo.
\param w La anchura del disparo.
\param h La altura del disparo.
\return El disparo.
*/
Disparo Disparo_Crea(Imagen i, int x, int y, int w, int h);

/**
\brief Elimina el disparo.
\param d El disparo a eliminar.
*/
void Disparo_Libera(Disparo d);

/**
\brief Mueve el disparo hacia arriba.
\param d El disparo a mover.
\return El disparo.
*/
int Disparo_Mueve(Disparo d);

/**
\brief Dibuja el disparo.
\param d El disparo a dibujar.
*/
void Disparo_Dibuja(Disparo d);

/**
\brief Obtiene la coordenada x del disparo.
\param d El disparo del que la deseamos obtener.
\return La coordenada.
*/
int Disparo_GetX(Disparo d);

/**
\brief Obtiene la coordenada y del disparo.
\param d El disparo del que la deseamos obtener.
\return La coordenada.
*/
int Disparo_GetY(Disparo d);

/**
\brief Obtiene la anchura del disparo.
\param d El astro del que la deseamos obtener.
\return La anchura.
*/
int Disparo_GetW(Disparo d);

/**
\brief Obtiene la altura del disparo.
\param d El astro del que la deseamos obtener.
\return La altura.
*/
int Disparo_GetH(Disparo d);

#endif // DISPARO_H_INCLUDED
