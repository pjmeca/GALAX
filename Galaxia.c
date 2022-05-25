#include <stdlib.h>
#include "Galaxia.h"
#include "Colision.h"

struct GalaxiaRep
{
    Astro * a;
    int max,n;
};

Galaxia Galaxia_Crea(int max)
{
    Galaxia g = malloc(sizeof(struct GalaxiaRep));
    g->a = malloc(sizeof(Astro)*max);
    g->max = max;
    g->n = 0;
    return g;
}

void Galaxia_Libera(Galaxia g)
{
    for(int i=0; i<g->n; i++)
        Astro_Libera(g->a[i]);
    free(g->a);
    free(g);
}

void Galaxia_InsertaNuevoAstro(Galaxia g, Astro a)
{
    if (g->n<g->max)
    {
        g->a[g->n] = a;
        g->n++;
    }
}

void Galaxia_Dibuja(Galaxia g)
{
    for(int i=0; i<g->n; i++)
        Astro_Dibuja(g->a[i]);
}

int Galaxia_Colision(Galaxia g, int x, int y, int w, int h)
{
    int i=0;
    while((i<g->n)&&(!Colision(Astro_GetX(g->a[i]),Astro_GetY(g->a[i]),Astro_GetW(g->a[i]),Astro_GetH(g->a[i]),x,y,w,h, 'p')))
        i++;
    int colision = (i<g->n);
    if (colision)
    {
        Astro_Libera(g->a[i]);
        g->a[i] = g->a[g->n-1];
        g->n--;
    }
    return colision;
}
