#include <stdlib.h>
#include "Disparo.h"
#define HPANTALLA 900

struct DisparoRep
{
    Imagen i;
    int w,h,x,y;

};

Disparo Disparo_Crea(Imagen i, int x, int y, int w, int h)
{
    Disparo d = malloc(sizeof(struct DisparoRep)); //Necesita la memoria de un struct de PersonajeRep.
    d->i=i; //Equivale a poner *(p.i)
    d->w=w;
    d->h=h;
    d->x=x;
    d->y=y;
    return d;
}

void Disparo_Libera(Disparo d)
{
    free(d); //Libera la memoria reservada en Personaje_Crea.
}

int Disparo_Mueve(Disparo d)
{
    d->y+=-30;
    return (d->y>Pantalla_Altura());
}

void Disparo_Dibuja(Disparo d)
{
    Pantalla_DibujaImagen(d->i,d->x,d->y,d->w,d->h);
}

int Disparo_GetX(Disparo d)
{
    return d->x;
}

int Disparo_GetY(Disparo d)
{
    return d->y;
}

int Disparo_GetW(Disparo d)
{
    return d->w;
}

int Disparo_GetH(Disparo d)
{
    return d->h;
}
