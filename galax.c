#include "galax.h"
#include "Pantalla.h"
#include "stdio.h"
#include "stdlib.h"
#include <windows.h>
#include <MMsystem.h>
#define WPANTALLA 1600
#define HPANTALLA 900

struct PersonajeRep
{
    Imagen i;
    int w,h,x,y;

};

void animacion(Imagen imagen0,Imagen imagen25,Imagen imagen50,Imagen imagen75,Imagen imagen100)
{
    static int anim = 0;
    switch(anim=anim%10)
    {
    case 0  :
    case 9  :
        Pantalla_DibujaImagen(imagen0,0,0,WPANTALLA,HPANTALLA);
        break;
    case 1  :
    case 8  :
        Pantalla_DibujaImagen(imagen25,0,0,WPANTALLA,HPANTALLA);
        break;
    case 2  :
    case 7  :
        if(imagen50!=NULL) Pantalla_DibujaImagen(imagen50,0,0,WPANTALLA,HPANTALLA);
        break;
    case 3  :
    case 6  :
        Pantalla_DibujaImagen(imagen75,0,0,WPANTALLA,HPANTALLA);
        break;
    case 4  :
    case 5  :
        Pantalla_DibujaImagen(imagen100,0,0,WPANTALLA,HPANTALLA);
        break;
    }
    anim++;
}

void animacion2(Imagen imagen0,Imagen imagen1)
{
    static int anim = 0;
    switch(anim=anim%2)
    {
    case 0  :
        Pantalla_DibujaImagen(imagen0,0,0,WPANTALLA,HPANTALLA);
        break;
    case 1  :
        Pantalla_DibujaImagen(imagen1,0,0,WPANTALLA,HPANTALLA);
        break;
    }
    anim++;
}

void animacionFW(Imagen imagen0,Imagen imagen25,Imagen imagen50,Imagen imagen75,Imagen imagen100)
{
    static int anim = 0;
    static int posx = 0;
    static int posy = 0;
    switch(anim=anim%5)
    {
    case 0  :
        posx = rand()%WPANTALLA;
        posy = rand()%HPANTALLA/2;
        Pantalla_DibujaImagen(imagen0,posx,posy,300,300);
        break;
    case 1  :
        Pantalla_DibujaImagen(imagen25,posx,posy,300,300);
        break;
    case 2  :
        if(imagen50!=NULL) Pantalla_DibujaImagen(imagen50,posx,posy,300,300);
        break;
    case 3  :
        Pantalla_DibujaImagen(imagen75,posx,posy,300,300);
        break;
    case 4  :
        Pantalla_DibujaImagen(imagen100,posx,posy,300,300);
        break;
    }
    anim++;
}

void animacion2p(Personaje p, Imagen imagen1,Imagen imagen2)
{
    static int anim = 0;
    switch(anim=anim%2)
    {
    case 0  :
        p->i = imagen1;
        Personaje_Dibuja(p);
        break;
    case 1  :
        p->i = imagen2;
        Personaje_Dibuja(p);
        break;
    }
    anim++;
}

void controles()
{
    int fin = 0;

    Imagen c0 = Pantalla_ImagenLee("./Materiales/Informacion/Controles1 - 0.bmp",0);
    Imagen c25 = Pantalla_ImagenLee("./Materiales/Informacion/Controles1 - 25.bmp",0);
    Imagen c50 = Pantalla_ImagenLee("./Materiales/Informacion/Controles1 - 50.bmp",0);
    Imagen c75 = Pantalla_ImagenLee("./Materiales/Informacion/Controles1 - 75.bmp",0);
    Imagen c100 = Pantalla_ImagenLee("./Materiales/Informacion/Controles1 - 100.bmp",0);

    while(Pantalla_Activa() && (!fin))
    {
        if((Pantalla_TeclaPulsada(SDL_SCANCODE_SPACE)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE)) || (Pantalla_RatonBotonPulsado(1))) fin=1;
        animacion(c0,c25,c50,c75,c100);
        Pantalla_Actualiza();
        Pantalla_Espera(75);
    }

    fin = 0;

    Pantalla_ImagenLibera(c0);
    Pantalla_ImagenLibera(c25);
    Pantalla_ImagenLibera(c50);
    Pantalla_ImagenLibera(c75);
    Pantalla_ImagenLibera(c100);

    c0 = Pantalla_ImagenLee("./Materiales/Informacion/Controles2 - 0.bmp",0);
    c25 = Pantalla_ImagenLee("./Materiales/Informacion/Controles2 - 25.bmp",0);
    c50 = Pantalla_ImagenLee("./Materiales/Informacion/Controles2 - 50.bmp",0);
    c75 = Pantalla_ImagenLee("./Materiales/Informacion/Controles2 - 75.bmp",0);
    c100 = Pantalla_ImagenLee("./Materiales/Informacion/Controles2 - 100.bmp",0);

    while(Pantalla_Activa() && (!fin))
    {
        if((Pantalla_TeclaPulsada(SDL_SCANCODE_SPACE)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE)) || (Pantalla_RatonBotonPulsado(1))) fin=1;
        animacion(c0,c25,c50,c75,c100);
        Pantalla_Actualiza();
        Pantalla_Espera(75);
    }

    fin = 0;

    Pantalla_ImagenLibera(c0);
    Pantalla_ImagenLibera(c25);
    Pantalla_ImagenLibera(c50);
    Pantalla_ImagenLibera(c75);
    Pantalla_ImagenLibera(c100);

    c0 = Pantalla_ImagenLee("./Materiales/Informacion/Planetas - 0.bmp",0);
    c25 = Pantalla_ImagenLee("./Materiales/Informacion/Planetas - 25.bmp",0);
    c50 = Pantalla_ImagenLee("./Materiales/Informacion/Planetas - 50.bmp",0);
    c75 = Pantalla_ImagenLee("./Materiales/Informacion/Planetas - 75.bmp",0);
    c100 = Pantalla_ImagenLee("./Materiales/Informacion/Planetas - 100.bmp",0);

    while(Pantalla_Activa() && (!fin))
    {
        if((Pantalla_TeclaPulsada(SDL_SCANCODE_SPACE)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE)) || (Pantalla_RatonBotonPulsado(1))) fin=1;
        animacion(c0,c25,c50,c75,c100);
        Pantalla_Actualiza();
        Pantalla_Espera(75);
    }

    Pantalla_ImagenLibera(c0);
    Pantalla_ImagenLibera(c25);
    Pantalla_ImagenLibera(c50);
    Pantalla_ImagenLibera(c75);
    Pantalla_ImagenLibera(c100);
}

void presentacion()
{
    /*He decidido hacerlo así para evitar tener que almacenar en variables las imágenes,
     ya que no volverán a ser usadas en el código.*/
    PlaySound(TEXT("./Materiales/intro.wav"),NULL,SND_ASYNC);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/0.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(80);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/1.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(80);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/2.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(80);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/3.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(80);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/4.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(80);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/5.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(80);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/6.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(80);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/7.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(80);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/8.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(1000);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/9.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(200);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/0.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(100);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/10.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(80);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/11.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(80);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/12.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(80);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/13.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(80);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/14.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(80);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/15.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(1000);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/16.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(200);
    Pantalla_DibujaImagen(Pantalla_ImagenLee("./Materiales/SecuenciaPresentacion/0.bmp",0),0,0,WPANTALLA,HPANTALLA);
    Pantalla_Actualiza();
    Pantalla_Espera(80);
}

