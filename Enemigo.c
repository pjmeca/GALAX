#include <stdlib.h>
#include "Enemigo.h"


struct EnemigoRep
{
    Imagen i;
    int w,h,x,y,vx,vy;

};

Enemigo Enemigo_Crea(Imagen i, int x, int y, int w, int h, int vx, int vy)
{
    Enemigo e = malloc(sizeof(struct EnemigoRep));
    e->i=i; //Equivale a poner *(e.i)
    e->w=w;
    e->h=h;
    e->x=x;
    e->y=y;
    e->vx=vx;
    e->vy=vy;
    return e;
}

void Enemigo_Libera(Enemigo e)
{
    free(e);
}

int Enemigo_Mueve(Enemigo e)
{
    e->x+= e->vx;
    e->y+= e->vy;

    //Enemigo rebota
    if (e->x<0)
    {
        e->x = 0;
        e->vx*=-1;
    }
    if (e->x>Pantalla_Anchura()- e->w)
    {
        e->x=(Pantalla_Anchura() - e->w);
        e->vx*=-1;
    }
    return(e->y>Pantalla_Altura());
}


void Enemigo_Dibuja(Enemigo e)
{
    Pantalla_DibujaImagen(e->i,e->x,e->y,e->w,e->h);
}

int Enemigo_GetX(Enemigo e)
{
    return e->x;
}

int Enemigo_GetY(Enemigo e)
{
    return e->y;
}

int Enemigo_GetW(Enemigo e)
{
    return e->w;
}

int Enemigo_GetH(Enemigo e)
{
    return e->h;
}
