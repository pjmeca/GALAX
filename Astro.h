#ifndef ASTRO_H_INCLUDED
#define ASTRO_H_INCLUDED
#include "Pantalla.h"

/**
\file Astro.h
\brief El TDA Astro crea un astro estático en el juego.
*/

/**
\brief TDA Astro
*/
typedef struct AstroRep * Astro;

/**
\brief Crea un Astro a partir de una imagen,
anchura, altura y coordenadas dadas por el usuario.
\param i La imagen del astro.
\param w La anchura de la imagen.
\param h La altura de la imagen.
\param x La coordenada en el eje x donde se colocará.
\param y La coordenada en el eje y donde se colocará.
\return El astro creado.
*/
Astro Astro_Crea(Imagen i, int w, int h, int x, int y);

/**
\brief Elimina un astro.
\param a El astro que deseamos eliminar.
*/
void Astro_Libera(Astro a);

/**
\brief Dibuja un astro.
\param a El astro que deseamos dibujar.
*/
void Astro_Dibuja(Astro a);

/**
\brief Obtiene la anchura del astro.
\param a El astro del que la deseamos obtener.
\return La anchura.
*/
int Astro_GetW(Astro a);

/**
\brief Obtiene la altura del astro.
\param a El astro del que la deseamos obtener.
\return La altura.
*/
int Astro_GetH(Astro a);

/**
\brief Obtiene la coordenada x del astro.
\param a El astro del que la deseamos obtener.
\return La coordenada.
*/
int Astro_GetX(Astro a);

/**
\brief Obtiene la coordenada y del astro.
\param a El astro del que la deseamos obtener.
\return La coordenada.
*/
int Astro_GetY(Astro a);

#endif // ASTRO_H_INCLUDED
