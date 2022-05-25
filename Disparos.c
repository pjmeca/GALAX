#include <stdlib.h>
#include "Disparos.h"
#include "Colision.h"

struct DisparosRep
{
    Disparo d;
    Disparos sig;
};

struct FlotaRep
{
    Enemigo e;
    Flota sig;
};

Disparos Disparos_Crea()
{
    Disparos ds = malloc(sizeof(struct DisparosRep));
    ds->sig=NULL;
    return ds;
}

void Disparos_Libera(Disparos ds)
{
    while (ds->sig != NULL)
    {
        Disparos aux = ds->sig;
        ds->sig = ds->sig->sig;
        Disparo_Libera(aux->d);
        free(aux);
    }
    free(ds);
}

void Disparos_Mueve(Disparos ds)
{
    while (ds->sig != NULL)
    {
        if(Disparo_Mueve(ds->sig->d))
        {
            Disparos aux = ds->sig;
            ds->sig = ds->sig->sig;
            Disparo_Libera(aux->d);
            free(aux);
        }
        else ds=ds->sig;
    }
}

void Disparos_Dibuja(Disparos ds)
{
    for(ds=ds->sig; ds!=NULL; ds=ds->sig)
        Disparo_Dibuja(ds->d);
}

void Disparos_InsertaNuevoDisparo(Disparos ds, Disparo disparo)
{
    Disparos aux = malloc(sizeof(struct DisparosRep));
    aux->d = disparo;
    aux->sig = ds->sig;
    ds->sig = aux;
}

int Disparos_Colision(Disparos ds, int x, int y, int w, int h)
{
    while((ds->sig != NULL) && !Colision(Disparo_GetX(ds->sig->d), Disparo_GetY(ds->sig->d),
                                         Disparo_GetH(ds->sig->d), Disparo_GetW(ds->sig->d),x,y,h,w, 'd') )
        ds = ds->sig;
    int colision = ds->sig != NULL;
    if (colision)
    {
        Disparos aux = ds->sig;
        ds->sig = ds->sig->sig;
        Disparo_Libera(aux->d);
        free(aux);
    }
    return (colision);
}

int Disparos_Colision_Flota(Disparos ds, Flota f, int* x, int* y)
{
    int col = 0;
    while((ds->sig != NULL) && (col!=1))
    {
        while((f->sig != NULL) && (col!=1))
        {
            if(Colision(Disparo_GetX(ds->sig->d), Disparo_GetY(ds->sig->d),
                                            Disparo_GetH(ds->sig->d), Disparo_GetW(ds->sig->d),
                                            Enemigo_GetX(f->sig->e), Enemigo_GetY(f->sig->e),
                                            Enemigo_GetH(f->sig->e), Enemigo_GetW(f->sig->e), 'd'))
            {
                col=1;
            }else f = f->sig;
        }if(col!=1) ds = ds->sig;
    }

    if (col)
    {
        //Obtención de la posición para la explosión
        *x = Enemigo_GetX(f->sig->e);
        *y = Enemigo_GetY(f->sig->e);

        //Liberar enemigo y disparo
        Disparos daux = ds->sig;
        ds->sig = ds->sig->sig;
        Disparo_Libera(daux->d);
        free(daux);
        Flota faux = f->sig;
        f->sig = f->sig->sig;
        Enemigo_Libera(faux->e);
        free(faux);
    }
    return (col);
}
