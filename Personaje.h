#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED

#include "Pantalla.h"

/**
\file Personaje.h
\brief El TDA personaje crea un personaje que podremos
mover y hacer interactuar con otros elementos del juego.
*/

/**
\brief El TDA personaje.
*/
typedef struct PersonajeRep * Personaje; //Hay que hacer esto para todos los tipos que queramos hacer. Se completa en el h.

/**
\brief Crea el personaje.
\param i La imagen del personaje.
\param x La coordenada x del personaje.
\param y La coordenada y del personaje.
\param w La anchura del personaje.
\param h La altura del personaje.
\return El personaje ya creado.
*/
Personaje Personaje_Crea(Imagen i, int x, int y, int w, int h); //Prototipo de la función.

/**
\brief Libera el personaje.
\param p El personaje que deseamos liberar.
*/
void Personaje_Libera(Personaje p);

/**
\brief Mueve al personaje por el escenario.
\param p El personaje a mover.
\param vx La velocidad en el eje x con la que moveremos al personaje.
\param vy La velocidad en el eje y con la que moveremos al personaje.
*/
void Personaje_Mueve(Personaje p, int vx, int vy);

/**
\brief Dibuja al personaje.
\param p El personaje que deseamos dibujar.
*/
void Personaje_Dibuja(Personaje p);

/**
\brief Devuelve la coordenada x del personaje.
\param p El personaje.
\return Un entero cuyo valor se corresponde con la coordenada.
*/
int Personaje_GetX(Personaje p);

/**
\brief Devuelve la coordenada y del personaje.
\param p El personaje.
\return Un entero cuyo valor se corresponde con la coordenada.
*/
int Personaje_GetY(Personaje p);

/**
\brief Devuelve la anchura del personaje.
\param p El personaje.
\return Un entero cuyo valor se corresponde con la anchura.
*/
int Personaje_GetW(Personaje p);

/**
\brief Devuelve la altura del personaje.
\param p El personaje.
\return Un entero cuyo valor se corresponde con la altura.
*/
int Personaje_GetH(Personaje p);

/**
\brief Modifica la coordenada en el eje x del personaje.
\param p El personaje.
\param dato Un entero cuyo valor es la coordenada en
el eje x que deseamos establecer.
*/
void Personaje_SetX(Personaje p,int dato);

/**
\brief Modifica la coordenada en el eje y del personaje.
\param p El personaje.
\param dato Un entero cuyo valor es la coordenada en
el eje y que deseamos establecer.
*/
void Personaje_SetY(Personaje p,int dato);

/**
\brief Modifica la altura del personaje.
\param p El personaje.
\param dato Un entero cuyo valor es la altura
que deseamos establecer.
*/
void Personaje_SetH(Personaje p,int dato);

/**
\brief Modifica la anchura del personaje.
\param p El personaje.
\param dato Un entero cuyo valor es la anchura
que deseamos establecer.
*/
void Personaje_SetW(Personaje p,int dato);

#endif  // __PERSONAJE_H
