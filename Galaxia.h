#ifndef GALAXIA_H_INCLUDED
#define GALAXIA_H_INCLUDED
#include "Astro.h"

/**
\file Galaxia.h
\brief El TDA Galaxia crea un conjunto de astros est�ticos en el juego.
*/

/**
\brief El TDA Galaxia.
*/
typedef struct GalaxiaRep * Galaxia;

/**
\brief Crea la galaxia.
\param max El n�mero m�ximo de astros que pueden haber en la galaxia.
\return La galaxia creada.
*/
Galaxia Galaxia_Crea(int max);

/**
\brief Libera la galaxia.
\param g La galaxia que deseamos liberar.
*/
void Galaxia_Libera(Galaxia g);

/**
\brief Crea un nuevo astro dentro de la galaxia.
\param g La galaxia en la que queremos crear el nuevo astro.
\param a El astro que queremos crear.
*/
void Galaxia_InsertaNuevoAstro(Galaxia g, Astro a);

/**
\brief Dibuja la galaxia.
\param g La galaxia que deseamos dibujar.
*/
void Galaxia_Dibuja(Galaxia g);

/**
\brief Comprueba si alg�n astro de la galaxia ha colisionado
con alg�n otro elemento.
\param g La galaxia en la que se encuentran los astros.
\param x La posici�n x del elemento que ha podido colisionar.
\param y La posici�n y del elemento que ha podido colisionar.
\param w La anchura del elemento que ha podido colisionar.
\param h La altura del elemento que ha podido colisionar.
\return Devuelve 1 si ha habido colisi�n, 0 si no.
*/
int Galaxia_Colision(Galaxia g, int x, int y, int w, int h);

#endif // GALAXIA_H_INCLUDED
