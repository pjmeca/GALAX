#include <stdlib.h>
#include "Flota.h"
#include "Colision.h"

struct FlotaRep
{
    Enemigo e;
    Flota sig;
};

Flota Flota_Crea()
{
    Flota f = malloc(sizeof(struct FlotaRep));
    f->sig=NULL;
    return f;
}

void Flota_Libera(Flota f)
{
    while (f->sig != NULL)
    {
        Flota aux = f->sig;
        f->sig = f->sig->sig;
        Enemigo_Libera(aux->e);
        free(aux);
    }
    free(f);
}

void Flota_Mueve(Flota f)
{
    while (f->sig != NULL)
    {
        if(Enemigo_Mueve(f->sig->e))
        {
            Flota aux = f->sig;
            f->sig = f->sig->sig;
            Enemigo_Libera(aux->e);
            free(aux);
        }
        else f=f->sig;
    }
}

void Flota_Dibuja(Flota f)
{
    for(f=f->sig; f!=NULL; f=f->sig)
        Enemigo_Dibuja(f->e);
}

void Flota_InsertaNuevoEnemigo(Flota f, Enemigo enemigo)
{
    Flota aux = malloc(sizeof(struct FlotaRep));
    aux->e = enemigo;
    aux->sig = f->sig;
    f->sig = aux;
}

int Flota_Colision(Flota f, int x, int y, int w, int h)
{
    while((f->sig != NULL) && !Colision(Enemigo_GetX(f->sig->e), Enemigo_GetY(f->sig->e),
                                        Enemigo_GetH(f->sig->e), Enemigo_GetW(f->sig->e),x,y,h,w, 'p') )
        f = f->sig;
    int colision = f->sig != NULL;
    if (colision)
    {
        Flota aux = f->sig;
        f->sig = f->sig->sig;
        Enemigo_Libera(aux->e);
        free(aux);
    }
    return (colision);
}
