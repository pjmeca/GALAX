#ifndef ENEMIGO_H_INCLUDED
#define ENEMIGO_H_INCLUDED
#include "Pantalla.h"

/**
\file Enemigo.h
\brief El TDA Enemigo crea un enemigo en el juego.
*/

/**
\brief TDA Enemigo
*/
typedef struct EnemigoRep * Enemigo; //Hay que hacer esto para todos los tipos que queramos hacer. Se completa en el h.

/**
\brief Crea un enemigo.
\param i La imagen del enemigo.
\param x La posición en el eje x del enemigo.
\param y La posición en el eje y del enemigo.
\param w La anchura del enemigo.
\param h La altura del enemigo.
\param vx La velocidad en el eje x del enemigo.
\param vy La velocidad en el eje y del enemigo.
\return El disparo.
*/
Enemigo Enemigo_Crea(Imagen i, int x, int y, int w, int h, int vx, int vy); //Prototipo de la función.

/**
\brief Elimina el enemigo.
\param e El enemigo a eliminar.
*/
void Enemigo_Libera(Enemigo e);

/**
\brief Mueve el enemigo y comprueba si se ha salido de los límites.
\param e El enemigo a mover.
\return 1 si el enemigo se ha salido.
*/
int Enemigo_Mueve(Enemigo e);

/**
\brief Dibuja el enemigo.
\param e El enemigo a dibujar.
*/
void Enemigo_Dibuja(Enemigo e);

/**
\brief Obtiene la coordenada x del enemigo.
\param e El enemigo del que la deseamos obtener.
\return La coordenada.
*/
int Enemigo_GetX(Enemigo e);

/**
\brief Obtiene la coordenada y del enemigo.
\param e El enemigo del que la deseamos obtener.
\return La coordenada.
*/
int Enemigo_GetY(Enemigo e);

/**
\brief Obtiene la anchura del enemigo.
\param e El enemigo del que la deseamos obtener.
\return La anchura.
*/
int Enemigo_GetW(Enemigo e);

/**
\brief Obtiene la altura del enemigo.
\param e El enemigo del que la deseamos obtener.
\return La altura.
*/
int Enemigo_GetH(Enemigo e);

#endif // ENEMIGO_H_INCLUDED
