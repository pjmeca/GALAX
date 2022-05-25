#include <stdlib.h>
#include "Astro.h"

struct AstroRep
{
    Imagen i;
    int w,h,x,y;

};

Astro Astro_Crea(Imagen i, int x, int y, int w, int h)
{
    Astro a = malloc(sizeof(struct AstroRep));
    a->i=i;
    a->w=w;
    a->h=h;
    a->x=x;
    a->y=y;
    return a;
}

void Astro_Libera(Astro a)
{
    free(a);
}



void Astro_Dibuja(Astro a)
{
    Pantalla_DibujaImagen(a->i,a->x,a->y,a->w,a->h);
}

int Astro_GetX(Astro a)
{
    return a->x;
}

int Astro_GetY(Astro a)
{
    return a->y;
}

int Astro_GetW(Astro a)
{
    return a->w;
}

int Astro_GetH(Astro a)
{
    return a->h;
}
