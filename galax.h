#ifndef GALAX_H_INCLUDED
#define GALAX_H_INCLUDED
#include "Pantalla.h"
#include "Disparos.h"
#include "Flota.h"
#include "Personaje.h"

/**
\file galax.h
\brief Una serie de funciones de apoyo para el juego.
*/

/**
\brief Crea una animación a partir de varias imágenes.
\param imagen0  Primera imagen.
\param imagen25 Segunda imagen.
\param imagen50 Tercera imagen.
\param imagen75 Cuarta imagen.
\param imagen100 Quinta imagen.
*/
void animacion(Imagen imagen0,Imagen imagen25,Imagen imagen50,Imagen imagen75,Imagen imagen100);

/**
\brief Crea una animación a partir de dos imágenes.
\param imagen0  Primera imagen.
\param imagen1 Segunda imagen.
*/
void animacion2(Imagen imagen0,Imagen imagen1);

/**
\brief Crea una animación específica para los fuegos artificiales.
\param imagen0  Primera imagen.
\param imagen25 Segunda imagen.
\param imagen50 Tercera imagen.
\param imagen75 Cuarta imagen.
\param imagen100 Quinta imagen.
*/
void animacionFW(Imagen imagen0,Imagen imagen25,Imagen imagen50,Imagen imagen75,Imagen imagen100);

/**
\brief Permite cambiar la imagen del personaje.
\param p El personaje.
\param imagen1 Primera imagen.
\param imagen2 Segunda imagen.
*/
void animacion2p(Personaje p, Imagen imagen1,Imagen imagen2);

/**
\brief Secuencia que muestra los controles al usuario.
*/
void controles();

/**
\brief Secuencia de presentación con los logos.
*/
void presentacion();

#endif // GALAX_H_INCLUDED
