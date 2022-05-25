#ifndef FLOTA_H_INCLUDED
#define FLOTA_H_INCLUDED
#include "Enemigo.h"

/**
\file Flota.h
\brief El TDA Flota crea una flota con enemigos en el juego.
*/

/**
\brief TDA Flota
*/
typedef struct FlotaRep * Flota;

/**
\brief Crea la flota.
*/
Flota Flota_Crea();

/**
\brief Libera todos los enemigos de la flota.
\param f La flota a liberar.
*/
void Flota_Libera(Flota f);

/**
\brief Mueve todas las flota.
\param f La flota.
*/
void Flota_Mueve(Flota f);

/**
\brief Dibuja la flota.
\param f La flota a dibujar.
*/
void Flota_Dibuja(Flota f); //Mueve a los enemigos de la flota.

/**
\brief Inserta un nuevo enemigo en la flota.
\param f La flota.
\param enemigo El enemigo a insertar.
*/
void Flota_InsertaNuevoEnemigo(Flota f, Enemigo enemigo);

/**
\brief Comprueba si ha habido una colisión con la flota.
\param f La flota.
\param x La coordenada x con la que queremos comprobar la colisión.
\param y La coordenada y con la que queremos comprobar la colisión.
\param w La anchura del elemento con el que queremos comprobar la colisión.
\param h La altura del elemento con el que queremos comprobar la colisión.
\return Devuelve 1 si sí ha habido colisión, 0 si no.
*/
int Flota_Colision(Flota f, int x, int y, int w, int h);


#endif // FLOTA_H_INCLUDED
