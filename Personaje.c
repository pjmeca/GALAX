#include <stdlib.h>
#include "Personaje.h"
#define WPERSONAJE 45

struct PersonajeRep
{
    Imagen i;
    int w,h,x,y;

};

Personaje Personaje_Crea(Imagen i, int x, int y, int w, int h)
{
    Personaje p = malloc(sizeof(struct PersonajeRep)); //Necesita la memoria de un struct de PersonajeRep.
    p->i=i; //Equivale a poner *(p.i)
    p->w=w;
    p->h=h;
    p->x=x;
    p->y=y;
    return p;
}

void Personaje_Libera(Personaje p)
{
    free(p); //Libera la memoria reservada en Personaje_Crea.
}

void Personaje_Mueve(Personaje p, int vx, int vy)
{
    p->x+=vx;
    p->y+=vy;

    //Evitar que el personaje se salga.
    if (p->x<-WPERSONAJE/2) p->x = -WPERSONAJE/2;
    if (p->y<0) p->y = 0;
    if (p->x>Pantalla_Anchura()-(p->w)/2)
        p->x = Pantalla_Anchura() -(p->w)/2;
    if (p->y>Pantalla_Altura()-(p->h)/2)
        p->y = Pantalla_Altura() -(p->h)/2;

}

void Personaje_Dibuja(Personaje p)
{
    Pantalla_DibujaImagen(p->i,p->x,p->y,p->w,p->h);
}

int Personaje_GetX(Personaje p)
{
    return p->x;
}

int Personaje_GetY(Personaje p)
{
    return p->y;
}

int Personaje_GetW(Personaje p)
{
    return p->w;
}

int Personaje_GetH(Personaje p)
{
    return p->h;
}

void Personaje_SetX(Personaje p,int dato)
{
    p->x=dato;
}

void Personaje_SetY(Personaje p,int dato)
{
    p->y=dato;
}

void Personaje_SetH(Personaje p,int dato)
{
    p->h=dato;
}

void Personaje_SetW(Personaje p,int dato)
{
    p->w=dato;
}
