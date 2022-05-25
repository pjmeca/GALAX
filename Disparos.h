#ifndef DISPAROS_H_INCLUDED
#define DISPAROS_H_INCLUDED
#include "Disparo.h"
#include "Flota.h"

/**
\file Disparos.h
\brief El TDA Disparos crea un conjunto de disparos en el juego.
*/

/**
\brief TDA Disparos.
*/
typedef struct DisparosRep *Disparos;

/**
\brief TDA Flota.
*/
typedef struct FlotaRep * Flota;

/**
\brief Crea el conjunto de disparos.
*/
Disparos Disparos_Crea();

/**
\brief Libera todos los disparos.
\param ds Los disparos a liberar.
*/
void Disparos_Libera(Disparos ds);

/**
\brief Mueve todos los disparos hacia arriba.
\param ds El conjunto de disparos.
*/
void Disparos_Mueve(Disparos ds);

/**
\brief Dibuja todos los disparos.
\param ds Los disparos a dibujar.
*/
void Disparos_Dibuja(Disparos ds);

/**
\brief Inserta un nuevo disparo en el conjunto.
\param ds El conjunto de disparos.
\param disparo El disparo a insertar.
*/
void Disparos_InsertaNuevoDisparo(Disparos ds, Disparo disparo);

/**
\brief Comprueba si ha habido una colisión con algún disparo.
\param ds El conjunto de disparos.
\param x La coordenada x con la que queremos comprobar la colisión.
\param y La coordenada y con la que queremos comprobar la colisión.
\param w La anchura del elemento con el que queremos comprobar la colisión.
\param h La altura del elemento con el que queremos comprobar la colisión.
\return Devuelve 1 si sí ha habido colisión, 0 si no.
*/
int Disparos_Colision(Disparos ds, int x, int y, int w, int h);

/**
\brief Comprueba si ha habido una colisión entre algún disparo y alguna nave de la flota.
\param ds El conjunto de disparos.
\param f La flota.
\param x Un paso por referencia de la coordenada x con la que queremos comprobar la colisión.
\param y Un paso por referencia de la coordenada y con la que queremos comprobar la colisión.
\return Devuelve 1 si sí ha habido colisión, 0 si no.
*/
int Disparos_Colision_Flota(Disparos ds, Flota f, int* x, int* y);

#endif // DISPAROS_H_INCLUDED
