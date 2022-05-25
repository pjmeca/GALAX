#ifndef COLISION_H_INCLUDED
#define COLISION_H_INCLUDED

/**
\file Colision.h
\brief El m�dulo Colisi�n contiene una funci�n
para detectar la colisi�n entre dos objetos.
*/

/**
\brief Comprueba si hay una colisi�n entre dos elementos.
\param x1 La coordenada x del primer elemento.
\param y1 La coordenada y del primer elemento.
\param h1 La altura del primer elemento.
\param w1 La anchura del primer elemento.
\param x2 La coordenada x del segundo elemento.
\param y2 La coordenada y del segundo elemento.
\param h2 La altura del segundo elemento.
\param w2 La anchura del segundo elemento.
\param tipo_colision Una letra.
p si es una colisi�n relacionada con el personaje.
r si es una colisi�n relacionada con el rat�n.
O cualquier otra en otro caso.
\return Devuelve 1 si ha habido colisi�n, 0 si no.
*/
int Colision(int x1, int y1, int h1, int w1, int x2, int y2, int h2, int w2, char tipo_colision);

#endif // COLISION_H_INCLUDED
