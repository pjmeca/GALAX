#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <MMsystem.h>
#include "Personaje.h"
#include "Enemigo.h"
#include "Pantalla.h"
#include "Colision.h"
#include "Galaxia.h"
#include "Flota.h"
#include "galax.h"
#include "Disparo.h"
#include "Disparos.h"
#define WPANTALLA 1600
#define HPANTALLA 900
#define WPERSONAJE 45
#define HPERSONAJE 60
#define WENEMIGO 100
#define HENEMIGO 60
#define WDISPARO 52
#define HDISPARO 83
#define MAXASTROS 4
#define TIPOSASTROS 4
#define FRECASTROS 20

/**
\mainpage Proyecto de videojuego - Tecnología de la Programación
\file main.c
\brief Código principal del videojuego, controlamos a una nave que
debe eliminar alienígenas y recolectar orbes.
*/

/**
\brief Obtiene la cordenada x de la posición de ratón.
\return Un entero con el valor de dicha coordenada.
*/
//Control del raton:
int Raton_X()
{
    int x;
    SDL_PumpEvents();
    SDL_GetMouseState(&x, NULL);
    return x;
}

/**
\brief Obtiene la cordenada y de la posición de ratón.
\return Un entero con el valor de dicha coordenada.
*/
int Raton_Y()
{
    int y;
    SDL_PumpEvents();
    SDL_GetMouseState(NULL, &y);
    return y;
}

Personaje p;
Enemigo e;
Disparo d;
Astro explosion, vextra;

//Variables afectadas por la dificultad:
int PUNTOSEXTRA     = 10;
int VXENEMIGO       = 18;
int VYENEMIGO       = 18;
int FRECENEMIGOS    = 25;
int VIDASTOTALES    = 4;
int VXPERSONAJE     = 25;
int VYPERSONAJE     = 20;

/**
\brief Comienza el juego.
\return Devuelve 0 cuando el juego termina.
*/
int main(int argc, char *argv[])
{
    Pantalla_Crea("GALAX: Human Saviors",WPANTALLA,HPANTALLA);
    int fin = 0;

    presentacion();

    Imagen diffacil = Pantalla_ImagenLee("./Materiales/Dificultad/Dif_Facil.bmp",0);
    Imagen difnormal = Pantalla_ImagenLee("./Materiales/Dificultad/Dif_Normal.bmp",0);
    Imagen difdificil = Pantalla_ImagenLee("./Materiales/Dificultad/Dif_Dificil.bmp",0);
    Imagen difhardcore = Pantalla_ImagenLee("./Materiales/Dificultad/Dif_Hardcore.bmp",0);

//SELECCION DIFICULTAD
    int posdif = 0;
    int cooldown = 5; //Para evitar que la pulsacion del espacio pase de una fase a otra.
    while(Pantalla_Activa() && (!fin))
    {
        if (Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE)) return 0;
        //Control con raton:
        if(Colision(Raton_X(),Raton_Y(),10,10,500,268,110,600,'r')) posdif=-1;
        if(Colision(Raton_X(),Raton_Y(),10,10,500,383,110,600,'r')) posdif=0;
        if(Colision(Raton_X(),Raton_Y(),10,10,500,498,110,600,'r')) posdif=1;
        if(Colision(Raton_X(),Raton_Y(),10,10,500,613,110,600,'r')) posdif=2;


        //Control con teclado:
        if ((Pantalla_TeclaPulsada(SDL_SCANCODE_DOWN) || Pantalla_TeclaPulsada(SDL_SCANCODE_S)) && (posdif<2))
        {
            //PlaySound(TEXT("s"), NULL, SND_ALIAS);
            posdif++;
        }
        if ((Pantalla_TeclaPulsada(SDL_SCANCODE_UP) || Pantalla_TeclaPulsada(SDL_SCANCODE_W)) && (posdif>-1))
        {
            //PlaySound(TEXT("s"), NULL, SND_ALIAS);
            posdif--;
        }
        if (((Pantalla_TeclaPulsada(SDL_SCANCODE_SPACE)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_RETURN)) || (Pantalla_RatonBotonPulsado(1))) && (cooldown == 0))
        {
            //PlaySound(TEXT("s"), NULL, SND_ALIAS);
            switch(posdif)
            {
            case -1:
                PUNTOSEXTRA     = 5;
                VXENEMIGO       = 14;
                VYENEMIGO       = 14;
                FRECENEMIGOS    = 35;
                VIDASTOTALES    = 6;
                fin = 1;
                break;
            case 1:
                PUNTOSEXTRA     = 18;
                VXENEMIGO       = 20;
                VYENEMIGO       = 20;
                FRECENEMIGOS    = 15;
                VIDASTOTALES    = 4;
                fin = 1;
                break;
            case 2:
                PUNTOSEXTRA     = 25;
                VXENEMIGO       = 25;
                VYENEMIGO       = 25;
                FRECENEMIGOS    = 8;
                VIDASTOTALES    = 3;
                fin = 1;
                break;
            default:
                fin = 1;
                break;
            }
        }
        else if(cooldown>0) cooldown--;

        switch(posdif)
        {
        case -1:
            Pantalla_DibujaImagen(diffacil,0,0,WPANTALLA,HPANTALLA);
            break;
        case 1:
            Pantalla_DibujaImagen(difdificil,0,0,WPANTALLA,HPANTALLA);
            break;
        case 2:
            Pantalla_DibujaImagen(difhardcore,0,0,WPANTALLA,HPANTALLA);
            break;
        default:
            Pantalla_DibujaImagen(difnormal,0,0,WPANTALLA,HPANTALLA);
            posdif = 0;
            break;
        }
        Pantalla_Actualiza();
        Pantalla_Espera(120);
    }
    Pantalla_ImagenLibera(diffacil);
    Pantalla_ImagenLibera(difnormal);
    Pantalla_ImagenLibera(difdificil);
    Pantalla_ImagenLibera(difhardcore);

    while(Pantalla_Activa())
    {
        PlaySound(TEXT("./Materiales/MusicaBienvenida-2.wav"),NULL,SND_ASYNC | SND_LOOP);

        //Lectura de imágenes
        Imagen bienvenida0 = Pantalla_ImagenLee("./Materiales/Bienvenida/bienvenida0.bmp",0);
        Imagen bienvenida25 = Pantalla_ImagenLee("./Materiales/Bienvenida/bienvenida25.bmp",0);
        Imagen bienvenida50 = Pantalla_ImagenLee("./Materiales/Bienvenida/bienvenida50.bmp",0);
        Imagen bienvenida75 = Pantalla_ImagenLee("./Materiales/Bienvenida/bienvenida75.bmp",0);
        Imagen bienvenida100 = Pantalla_ImagenLee("./Materiales/Bienvenida/bienvenida100.bmp",0);
        Imagen bienvenida_comenzar = Pantalla_ImagenLee("./Materiales/Bienvenida/bienvenida_comenzar.bmp",0);
        Imagen bienvenida_informacion = Pantalla_ImagenLee("./Materiales/Bienvenida/bienvenida_informacion.bmp",0);
        srand(time(NULL));
        fin = 0;

//FASE DE BIENVENIDA
        int posmen = 0;
        cooldown = 5;
        fin = 0;
        while((Pantalla_Activa()) && (!fin))
        {
            if(((Pantalla_TeclaPulsada(SDL_SCANCODE_SPACE)) || (Pantalla_RatonBotonPulsado(1)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE))) && (cooldown==0)) fin = 1;
            else if (cooldown>0) cooldown--;
            animacion(bienvenida0,bienvenida25,bienvenida50,bienvenida75,bienvenida100);
            Pantalla_Actualiza();
            Pantalla_Espera(75);
        }
        cooldown = 5;
        posmen = 0;
        fin = 0;
        while(Pantalla_Activa() && (!fin))
        {
            if (Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE)) return 0;

            //Raton
            if(Colision(Raton_X(),Raton_Y(),10,10,650,540,55,300,'r')) posmen=0;
            if(Colision(Raton_X(),Raton_Y(),10,10,650,610,55,300,'r')) posmen=1;

            //Teclado
            if ((Pantalla_TeclaPulsada(SDL_SCANCODE_DOWN) || Pantalla_TeclaPulsada(SDL_SCANCODE_S)) && (posmen==0))
            {
                //PlaySound(TEXT("s"), NULL, SND_ALIAS);
                posmen++;
            }
            if ((Pantalla_TeclaPulsada(SDL_SCANCODE_UP) || Pantalla_TeclaPulsada(SDL_SCANCODE_W)) && (posmen==1))
            {
                //PlaySound(TEXT("s"), NULL, SND_ALIAS);
                posmen--;
            }
            if (((Pantalla_TeclaPulsada(SDL_SCANCODE_SPACE)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_RETURN)) || (Pantalla_RatonBotonPulsado(1))) && (cooldown == 0))
            {
                //PlaySound(TEXT("s"), NULL, SND_ALIAS);
                switch(posmen)
                {
                case 1:
                    controles();
                    break;
                default:
                    fin = 1;
                    break;
                }
            }
            else if(cooldown>0) cooldown--;

            switch(posmen)
            {
            case 1:
                Pantalla_DibujaImagen(bienvenida_informacion,0,0,WPANTALLA,HPANTALLA);
                break;
            default:
                Pantalla_DibujaImagen(bienvenida_comenzar,0,0,WPANTALLA,HPANTALLA);
                posmen = 0;
                break;
            }
            Pantalla_Actualiza();
            Pantalla_Espera(50);
        }

        Pantalla_ImagenLibera(bienvenida0);
        Pantalla_ImagenLibera(bienvenida25);
        Pantalla_ImagenLibera(bienvenida50);
        Pantalla_ImagenLibera(bienvenida75);
        Pantalla_ImagenLibera(bienvenida100);
        Pantalla_ImagenLibera(bienvenida_comenzar);
        Pantalla_ImagenLibera(bienvenida_informacion);

//INTRO
        fin = 0;
        Imagen secuencia = Pantalla_ImagenLee("./Materiales/Secuencia Inicio.bmp",0);
        Imagen logo = Pantalla_ImagenLee("./Materiales/GalaX Logo.bmp",1);
        int secanim = -3050;
        int espera = 0;
        //char secanimacion[100];
        Pantalla_Espera(20);
        while (Pantalla_Activa() && (espera<200) && (!fin))
        {
            Pantalla_Espera(20);
            Pantalla_DibujaImagen(secuencia,0,HPANTALLA+secanim,WPANTALLA, 3050);
            if ((Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE) || (Pantalla_TeclaPulsada(SDL_SCANCODE_SPACE)) || (Pantalla_RatonBotonPulsado(1)))) fin=1;
            espera++;
            Pantalla_Actualiza();
        }
        fin = 0;
        cooldown=5;
        //Secuencia subiendo
        while(Pantalla_Activa() && (secanim < -HPANTALLA-140) && (!fin))
        {
            if ((Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE)) && (cooldown==0)) fin=1;
            else if(cooldown>0) cooldown--;
            Pantalla_DibujaImagen(secuencia,0,HPANTALLA+secanim,WPANTALLA, 3050);
            //sprintf(secanimacion, "%d", secanim);
            //Pantalla_ColorTrazo(255,255,255,255);
            //Pantalla_DibujaTexto(secanimacion,20,20);
            if (secanim > -1500)
                secanim+=6;
            else
            {
                if (secanim > -1100)
                    secanim+=3;
                else secanim+=13;
            }
            Pantalla_Actualiza();
            Pantalla_Espera(25);
        }
        //Logo animado
        if(!fin)
        {
            for(int logoanim=0; (logoanim<100); logoanim++)
            {
                Pantalla_DibujaImagen(secuencia,0,HPANTALLA+secanim,WPANTALLA, 3050);
                Pantalla_DibujaImagen(logo,WPANTALLA/2-868/2-logoanim*5/2,HPANTALLA/2-437/2-logoanim*4/2,868+logoanim*5,437+logoanim*4);
                Pantalla_Actualiza();
                Pantalla_Espera(30);
            }
        }
        Pantalla_ImagenLibera(secuencia);
        Pantalla_ImagenLibera(logo);

        //Recursos para la fase de juego
        PlaySound(NULL,NULL,SND_ASYNC);
        Imagen fondo1 = Pantalla_ImagenLee("./Materiales/Fondo/fondo1.bmp",0);
        Imagen fondo2 = Pantalla_ImagenLee("./Materiales/Fondo/fondo2.bmp",0);
        Imagen fondo3 = Pantalla_ImagenLee("./Materiales/Fondo/fondo3.bmp",0);
        Imagen fondo4 = Pantalla_ImagenLee("./Materiales/Fondo/fondo4.bmp",0);
        Imagen fondo5 = Pantalla_ImagenLee("./Materiales/Fondo/fondo5.bmp",0);
        Imagen hud = Pantalla_ImagenLee("./Materiales/HUD.bmp",1);
        Imagen nave1 = Pantalla_ImagenLee("./Materiales/nave1.bmp",1);
        Imagen nave2 = Pantalla_ImagenLee("./Materiales/nave2.bmp",1);
        Imagen escuadron = Pantalla_ImagenLee("./Materiales/escuadron.bmp",1);
        Imagen naveescudo1 = Pantalla_ImagenLee("./Materiales/naveescudo1.bmp",1);
        Imagen naveescudo2 = Pantalla_ImagenLee("./Materiales/naveescudo2.bmp",1);
        Imagen life = Pantalla_ImagenLee("./Materiales/planetalife.bmp",1);
        Imagen disparo = Pantalla_ImagenLee("./Materiales/disparo.bmp",1);
        Imagen enemigo = Pantalla_ImagenLee("./Materiales/enemigo.bmp",1);
        Imagen alien = Pantalla_ImagenLee("./Materiales/escuadronalienigena.bmp",1);
        Imagen explosionimg = Pantalla_ImagenLee("./Materiales/explosion.bmp",1);
        Imagen ca3 = Pantalla_ImagenLee("./Materiales/3.bmp", 1);
        Imagen ca2 = Pantalla_ImagenLee("./Materiales/2.bmp", 1);
        Imagen ca1 = Pantalla_ImagenLee("./Materiales/1.bmp", 1);
        /*Imagen vida100 = Pantalla_ImagenLee("./Materiales/vida100.bmp",1);
        Imagen vida75 = Pantalla_ImagenLee("./Materiales/vida75.bmp",1);
        Imagen vida50 = Pantalla_ImagenLee("./Materiales/vida50.bmp",1);
        Imagen vida25 = Pantalla_ImagenLee("./Materiales/vida25.bmp",1);*/
        p=Personaje_Crea(nave1, 70+rand()%(WPANTALLA/2-WPERSONAJE), HPANTALLA-HPERSONAJE, WPERSONAJE, HPERSONAJE);
        e=Enemigo_Crea(enemigo,rand()%(WPANTALLA-WENEMIGO),0,WENEMIGO,HENEMIGO,VXENEMIGO,VYENEMIGO);
        fin = 0;

        //Variables para la FASE DE JUEGO
        int posescuadrony=HPANTALLA;
        int posescuadronx=rand()%WPANTALLA;
        int t1 = time(NULL);
        int numpuntos = 0;
        int puntosExtra = 0;
        int numvidas = VIDASTOTALES;
        int hayexplosion = 0;
        int dir=1;
        int sobrecarga_disparo = 0;
        int unsigned escudo = 0;
        int unsigned hayescudo = 0;
        int countdownescudo = 0;
        int contadorvidaextra = 0;
        char puntos[100];

        //Creación de la Galaxia
        Galaxia galaxia = Galaxia_Crea(MAXASTROS);
        typedef struct
        {
            Imagen img;
            int w,h;
        } imagen_astro;
        imagen_astro img_astros[TIPOSASTROS];
        img_astros[0].img = Pantalla_ImagenLee("./Materiales/planetapurpura.bmp",1);
        img_astros[0].w = 30;
        img_astros[0].h = 30;
        img_astros[1].img = Pantalla_ImagenLee("./Materiales/planetamorado.bmp",1);
        img_astros[1].w = 30;
        img_astros[1].h = 30;
        img_astros[2].img = Pantalla_ImagenLee("./Materiales/planetarojo.bmp",1);
        img_astros[2].w = 30;
        img_astros[2].h = 30;
        img_astros[3].img = Pantalla_ImagenLee("./Materiales/planetatierra.bmp",1);
        img_astros[3].w = 30;
        img_astros[3].h = 30;

        Flota f1 = Flota_Crea();
        Disparos d1 = Disparos_Crea();
//CUENTA ATRAS
        for(int i=0; i<75; i++)
        {
            Pantalla_DibujaImagen(fondo1,0,0,WPANTALLA,HPANTALLA);
            if(i<25)
            {
                Pantalla_DibujaImagen(ca3,0,0,WPANTALLA,HPANTALLA);
                //if(i==0) PlaySound(TEXT("s"),NULL,SND_ALIAS | SND_ASYNC);
            }
            else if(i<50)
            {
                Pantalla_DibujaImagen(ca2,0,0,WPANTALLA,HPANTALLA);
                //if(i==25) PlaySound(TEXT("s"),NULL,SND_ALIAS | SND_ASYNC);
            }
            else
            {
                Pantalla_DibujaImagen(ca1,0,0,WPANTALLA,HPANTALLA);
                //if(i==50)PlaySound(TEXT("s"),NULL,SND_ALIAS | SND_ASYNC);
            }
            Personaje_Dibuja(p);
            Pantalla_Actualiza();
            Pantalla_Espera(10);
        }
        //PlaySound(TEXT("s"),NULL,SND_ALIAS | SND_ASYNC);
        Pantalla_ImagenLibera(ca3);
        Pantalla_ImagenLibera(ca2);
        Pantalla_ImagenLibera(ca1);

        PlaySound(TEXT("./Materiales/MusicaBatalla-2.wav"),NULL,SND_LOOP | SND_ASYNC);
//FASE DE JUEGO
        while(Pantalla_Activa() && (!fin))
        {
            //Restaura la velocidad del personaje en caso de haber sido modificada:
            switch(posdif)
            {
            case -1:
                VXPERSONAJE     = 20;
                VYPERSONAJE     = 18;
                break;
            case 1:
                VXPERSONAJE     = 28;
                VYPERSONAJE     = 23;
                break;
            case 2:
                VXPERSONAJE     = 30;
                VYPERSONAJE     = 25;
                break;
            default:
                VXPERSONAJE     = 25;
                VYPERSONAJE     = 20;
                break;
            }

            //Disparos (van aquí arriba para poder modificar la velocidad del personaje).
            if ((Pantalla_TeclaPulsada(SDL_SCANCODE_SPACE)) && (sobrecarga_disparo<30))
            {
                //PlaySound(TEXT("s"), NULL, SND_ALIAS | SND_ASYNC);
                Disparos_InsertaNuevoDisparo(d1,Disparo_Crea(disparo,Personaje_GetX(p),Personaje_GetY(p),WDISPARO,HDISPARO));
                sobrecarga_disparo+=7;
                VXPERSONAJE -= 10;
                if(VYPERSONAJE!=0) VYPERSONAJE = -2;
                else VYPERSONAJE = +2;
            }
            else if (sobrecarga_disparo>0) sobrecarga_disparo--;
            Disparos_Mueve(d1);

            //Movimiento.
            if (Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE)) fin=1;
            if ((Pantalla_TeclaPulsada(SDL_SCANCODE_A)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_LEFT)))
                Personaje_Mueve(p,-VXPERSONAJE,0);
            else if ((Pantalla_TeclaPulsada(SDL_SCANCODE_D)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_RIGHT)))
                Personaje_Mueve(p,VXPERSONAJE,0);
            if ((Pantalla_TeclaPulsada(SDL_SCANCODE_S)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_DOWN)))
                Personaje_Mueve(p,0,VYPERSONAJE);
            else if ((Pantalla_TeclaPulsada(SDL_SCANCODE_W)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_UP)))
                Personaje_Mueve(p,0,-VYPERSONAJE);
            else if (Pantalla_TeclaPulsada(SDL_SCANCODE_SPACE))
                Personaje_Mueve(p,0,VYPERSONAJE);

            //Escudo
            if ((Pantalla_TeclaPulsada(SDL_SCANCODE_E)) && (countdownescudo == 0))
            {
                switch(hayescudo)
                {
                case 0:
                    if (escudo>20)
                    {
                        hayescudo = 1;
                        countdownescudo = 5;
                    }
                    break;

                case 1:
                    hayescudo = 0;
                    countdownescudo = 5;
                    break;

                }
            }
            else
            {
                switch(hayescudo)
                {
                case 0:
                    if (escudo<180)
                        escudo++;
                    break;
                case 1:
                    if (escudo>0)
                        escudo--;
                    else
                        hayescudo = 0;
                    break;

                }
                if (countdownescudo>0)
                    countdownescudo--;
            }


            //Mueve a los enemigos y calcula si se salen de la pantalla.
            if (Enemigo_Mueve(e))
            {
                Enemigo_Libera(e);
                if (rand()%2)
                    dir*=-1;
                e=Enemigo_Crea(enemigo,rand()%(WPANTALLA-WENEMIGO),0,WENEMIGO,HENEMIGO,dir*VXENEMIGO,VYENEMIGO);
            }

            //Flota con Enemigos
            if (!(rand()%FRECENEMIGOS))
            {
                int dir=1;
                if (rand()%2)
                    dir*=-1;
                Flota_InsertaNuevoEnemigo(f1,Enemigo_Crea(enemigo,rand()%(WPANTALLA-WENEMIGO),0,WENEMIGO,HENEMIGO,dir*VXENEMIGO,VYENEMIGO));
            }
            Flota_Mueve(f1);

            //Creacion Astros
            int tamastro = rand()*WPANTALLA%70;
            if (!(rand()%FRECASTROS))
            {
                int tipo=rand()%(TIPOSASTROS);
                Galaxia_InsertaNuevoAstro(galaxia,
                                          Astro_Crea(img_astros[tipo].img,
                                                     rand()%(WPANTALLA-img_astros[tipo].w),
                                                     rand()%(HPANTALLA-img_astros[tipo].h),
                                                     img_astros[tipo].w+tamastro,
                                                     img_astros[tipo].h+tamastro));
            }

            //Vida Extra
            if (((rand()*Personaje_GetX(p)<100)) && (contadorvidaextra==0) && (numvidas<VIDASTOTALES) && (posdif != 2))
            {
                vextra = Astro_Crea(life,rand()%WPANTALLA,rand()%HPANTALLA,50,50);
                contadorvidaextra=1200;
            }
            else if (contadorvidaextra>0)
                contadorvidaextra--;


            //COLISIONES
            //Personaje con enemigo
            if (Colision(Enemigo_GetX(e),Enemigo_GetY(e),Enemigo_GetH(e),Enemigo_GetW(e),Personaje_GetX(p),
                         Personaje_GetY(p),Personaje_GetH(p),Personaje_GetW(p),'p'))
            {
                if(!hayescudo)
                {
                    explosion = Astro_Crea(explosionimg, Enemigo_GetX(e),Enemigo_GetY(e),100,100);
                    hayexplosion += 20;
                    numvidas--;
                    Enemigo_Libera(e);
                    int dir=1;
                    if (rand()%2)
                        dir*=-1;
                    e=Enemigo_Crea(enemigo,rand()%(WPANTALLA-WENEMIGO),0,WENEMIGO,HENEMIGO,dir*VXENEMIGO,VYENEMIGO);
                }
                else
                {
                    explosion = Astro_Crea(explosionimg, Enemigo_GetX(e),Enemigo_GetY(e),100,100);
                    hayexplosion += 20;
                    Enemigo_Libera(e);
                    int dir=1;
                    if (rand()%2)
                        dir*=-1;
                    e=Enemigo_Crea(enemigo,rand()%(WPANTALLA-WENEMIGO),0,WENEMIGO,HENEMIGO,dir*VXENEMIGO,VYENEMIGO);
                    hayescudo = 0;
                    escudo = 0;
                }
            }
            //Disparo con enemigo
            if (Disparos_Colision(d1,Enemigo_GetX(e),Enemigo_GetY(e),Enemigo_GetH(e),Enemigo_GetW(e)))
            {
                explosion = Astro_Crea(explosionimg, Enemigo_GetX(e),Enemigo_GetY(e),100,100);
                hayexplosion += 20;
                Enemigo_Libera(e);
                if (rand()%2)
                    dir*=-1;
                e=Enemigo_Crea(enemigo,rand()%(WPANTALLA-WENEMIGO),0,WENEMIGO,HENEMIGO,dir*VXENEMIGO,VYENEMIGO);
                puntosExtra+=PUNTOSEXTRA*2;
            }

            //Disparo con flota
            int dcf_x, dcf_y =0;
            if (Disparos_Colision_Flota(d1,f1,&dcf_x,&dcf_y))
            {
                explosion = Astro_Crea(explosionimg, dcf_x,dcf_y,100,100);
                hayexplosion += 20;
                puntosExtra+=PUNTOSEXTRA*2;
            }

            //Personaje con flota
            if (Flota_Colision(f1,Personaje_GetX(p),Personaje_GetY(p),Personaje_GetW(p),Personaje_GetH(p)))
            {
                if (!hayescudo)
                    numvidas--;
                else
                {
                    hayescudo = 0;
                    escudo = 0;
                }
            }

            //Personaje con galaxia
            if (Galaxia_Colision(galaxia,Personaje_GetX(p),Personaje_GetY(p),Personaje_GetW(p),Personaje_GetH(p)))
                puntosExtra+=PUNTOSEXTRA;

            //Personaje con vida extra
            if ((contadorvidaextra>0) && (Colision(Astro_GetX(vextra),Astro_GetY(vextra),Astro_GetH(vextra),Astro_GetW(vextra),
                                                   Personaje_GetX(p),Personaje_GetY(p),Personaje_GetH(p),Personaje_GetW(p),'p')))
            {
                numvidas++;
                Astro_Libera(vextra);
                contadorvidaextra=0;
            }
            if (numvidas==0)
                fin=1;

            //Puntuación
            numpuntos = time(NULL)-t1+puntosExtra;
            sprintf(puntos,"Puntuacion: \%d",numpuntos);

            //Dibujo
            animacion(fondo1,fondo2,fondo3,fondo4,fondo5);
            Pantalla_DibujaImagen(alien,0,0,WPANTALLA,HPANTALLA);
            //Miembros del escuadron GalaX volando de fondo
            if(posescuadrony<HPANTALLA)
            {
                if(posescuadrony<-100) posescuadrony=HPANTALLA;
                else posescuadrony-=15;
            }
            else if(rand()%20==0)
            {
                posescuadrony-=15;
                posescuadronx=rand()%WPANTALLA;
            }
            Pantalla_DibujaImagen(escuadron,posescuadronx,posescuadrony,125,100);
            //
            if (hayescudo)
                animacion2p(p,naveescudo1,naveescudo2);
            else
                animacion2p(p,nave1,nave2);
            Enemigo_Dibuja(e);
            Disparos_Dibuja(d1);
            if (hayexplosion>0)
            {
                Astro_Dibuja(explosion);
                hayexplosion--;
            }
            Galaxia_Dibuja(galaxia);
            Flota_Dibuja(f1);
            if (contadorvidaextra>0)
                Astro_Dibuja(vextra);
            Pantalla_ColorTrazo(255,0,0,255);
            Pantalla_ColorRelleno(255,0,0,255);
            Pantalla_DibujaRectangulo(5,700+200-sobrecarga_disparo/30*200,20,sobrecarga_disparo/30*200);
            Pantalla_ColorTrazo(0,0,255,255);
            Pantalla_ColorRelleno(0,0,255,255);
            Pantalla_DibujaRectangulo(76,888-escudo,20,escudo);
            if(rand()%5==0) Pantalla_DibujaImagen(explosionimg,rand()%WPANTALLA,rand()%HPANTALLA/2,30,30);
            if (numvidas>VIDASTOTALES/2) //Dibuja la gráfica de vidas restantes.
            {
                Pantalla_ColorTrazo(0,255,0,255);
                Pantalla_ColorRelleno(0,255,0,255);
            }
            else
            {
                Pantalla_ColorTrazo(255,0,0,255);
                Pantalla_ColorRelleno(255,0,0,255);
            }
            Pantalla_DibujaRectangulo(20,700+200-200/VIDASTOTALES*numvidas,60,200/VIDASTOTALES*numvidas);
            Pantalla_DibujaImagen(hud,0,0,WPANTALLA,HPANTALLA);
            Pantalla_ColorTrazo(255,255,255,255);
            Pantalla_ColorRelleno(255,255,255,255);
            Pantalla_DibujaRectangulo(105,880,150,2);
            Pantalla_DibujaTexto(puntos,110,860);

            /*Corazón con las vidas
            int posicion_vidas = numvidas/4;
            for (int vid=0; vid<numvidas/4; vid++)
                Pantalla_DibujaImagen(vida100,WPANTALLA-100-50*vid,30,70,70);
            switch(numvidas%4)
            {
            case    3:
                Pantalla_DibujaImagen(vida75,WPANTALLA-100-50*posicion_vidas,30,70,70);
                break;
            case    2:
                Pantalla_DibujaImagen(vida50,WPANTALLA-100-50*posicion_vidas,30,70,70);
                break;
            case    1:
                Pantalla_DibujaImagen(vida25,WPANTALLA-100-50*posicion_vidas,30,70,70);
                break;
            default:
                break;
            }*/

            Pantalla_DibujaTexto("Pulsa [ESCAPE] para salir.", WPANTALLA/2-100, 40);
            Pantalla_Actualiza();
            Pantalla_Espera(16);
        }

        //Record de Puntuación
        int puntosMax=0;
        int dato;
        FILE * f = fopen("record.txt","r");
        if (f!=NULL) //el fichero f existe
        {
            while(!feof(f))
            {
                fscanf(f,"%d",&dato);
                if(dato>puntosMax)
                    puntosMax=dato;
            }
            fclose(f);
        }
        char textorecord[100];
        if (numpuntos>puntosMax)
            sprintf(textorecord,"Enhorabuena, has batido un nuevo record!");
        else sprintf(textorecord,"Uy! El record actual sigue siendo: %d", puntosMax);

        f = fopen("record.txt","a");
        fprintf(f,"%d\n",numpuntos);
        fclose(f);

        Pantalla_ImagenLibera(nave1);
        Pantalla_ImagenLibera(escuadron);
        Pantalla_ImagenLibera(enemigo);
        Pantalla_ImagenLibera(fondo1);
        Pantalla_ImagenLibera(fondo2);
        Pantalla_ImagenLibera(fondo3);
        Pantalla_ImagenLibera(fondo4);
        Pantalla_ImagenLibera(fondo5);
        Pantalla_ImagenLibera(explosionimg);
        /*Pantalla_ImagenLibera(vida100);
        Pantalla_ImagenLibera(vida75);
        Pantalla_ImagenLibera(vida50);
        Pantalla_ImagenLibera(vida25);*/
        Flota_Libera(f1);
        Galaxia_Libera(galaxia);
        for(int i=0; i<TIPOSASTROS; i++)
            Pantalla_ImagenLibera(img_astros[i].img);
        Personaje_Libera(p);
        Enemigo_Libera(e);
        PlaySound(NULL,NULL,SND_ASYNC);

        fin = 0;

//FASE DE DESPEDIDA
        //VICTORIA
        if(numpuntos>1000)
        {
            PlaySound(TEXT("./Materiales/PC8bit.wav"),NULL,SND_ASYNC | SND_LOOP);
            Imagen victoria = Pantalla_ImagenLee("./Materiales/SecuenciaFin/Victoria/victoria.bmp",0);
            Imagen fw1 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/Victoria/fw1.bmp",1);
            Imagen fw2 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/Victoria/fw2.bmp",1);
            Imagen fw3 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/Victoria/fw3.bmp",1);
            Imagen fw4 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/Victoria/fw4.bmp",1);
            Imagen fw5 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/Victoria/fw5.bmp",1);
            Imagen d_esc = Pantalla_ImagenLee("./Materiales/SecuenciaFin/Victoria/d_escuadron.bmp",1);
            Imagen i_esc = Pantalla_ImagenLee("./Materiales/SecuenciaFin/Victoria/i_escuadron.bmp",1);
            Imagen esc = i_esc;

            posescuadronx = WPANTALLA+100;
            posescuadrony = 2*HPANTALLA/6;

            while(Pantalla_Activa() && (!fin))
            {
                if ((Pantalla_TeclaPulsada(SDL_SCANCODE_E)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_SPACE)) || (Pantalla_RatonBotonPulsado(1))) fin =1;
                Pantalla_DibujaImagen(victoria,0,0,WPANTALLA,HPANTALLA);
                //Miembros del escuadron GalaX volando de fondo
                if(esc==i_esc)
                {
                    if(posescuadronx<-100) esc = d_esc;
                    else posescuadronx-=20;
                }
                else
                {
                    if(posescuadronx>WPANTALLA+100) esc = i_esc;
                    else posescuadronx+=20;
                }
                Pantalla_DibujaImagen(esc,posescuadronx,posescuadrony,150,175);
                //
                animacionFW(fw1,fw2,fw3,fw4,fw5);
                Pantalla_DibujaTexto(textorecord,WPANTALLA/2-strlen(textorecord)*8/2,7*HPANTALLA/8);
                Pantalla_DibujaTexto(puntos,WPANTALLA/2-strlen(puntos)*8/2,7*HPANTALLA/8+20);
                Pantalla_Actualiza();
                Pantalla_Espera(50);
            }
            Pantalla_ImagenLibera(victoria);
            Pantalla_ImagenLibera(fw1);
            Pantalla_ImagenLibera(fw2);
            Pantalla_ImagenLibera(fw3);
            Pantalla_ImagenLibera(fw4);
            Pantalla_ImagenLibera(fw5);
            Pantalla_ImagenLibera(esc);
            Pantalla_ImagenLibera(i_esc);
            Pantalla_ImagenLibera(d_esc);
        }
        else  //DERROTA
        {
            PlaySound(TEXT("./Materiales/8-Bit Game Over Theme.wav"),NULL,SND_ASYNC | SND_LOOP);
            Imagen fin0 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin0.bmp",0);
            Imagen fin1 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin1.bmp",0);
            Imagen fin2 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin2.bmp",0);
            Imagen fin3 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin3.bmp",0);
            Imagen fin4 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin4.bmp",0);
            Imagen fin5 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin5.bmp",0);
            Imagen fin6 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin6.bmp",0);
            Imagen fin7 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin7.bmp",0);
            Imagen fin8 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin8.bmp",0);
            Imagen fin9 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin9.bmp",0);
            Imagen fin10 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin10.bmp",0);
            Imagen fin11 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin11.bmp",0);
            Imagen fin00 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin00.bmp",0);
            Imagen fin25 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin25.bmp",0);
            Imagen fin50 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin50.bmp",0);
            Imagen fin75 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin75.bmp",0);
            Imagen fin100 = Pantalla_ImagenLee("./Materiales/SecuenciaFin/fin100.bmp",0);
            Imagen calavera0= Pantalla_ImagenLee("./Materiales/SecuenciaFin/calavera cerrada.bmp",1);
            Imagen calavera1= Pantalla_ImagenLee("./Materiales/SecuenciaFin/calavera semiabierta.bmp",1);
            Imagen calavera2= Pantalla_ImagenLee("./Materiales/SecuenciaFin/calavera abierta.bmp",1);

            int InicioAnimacionDespedida = 0;

            while(Pantalla_Activa() && (!fin))
            {
                if ((Pantalla_TeclaPulsada(SDL_SCANCODE_F)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_SPACE)) || (Pantalla_RatonBotonPulsado(1))) fin =1;
                if (InicioAnimacionDespedida <= 11)
                {
                    switch (InicioAnimacionDespedida)
                    {
                    case 0  :
                        Pantalla_DibujaImagen(fin0,0,0,WPANTALLA,HPANTALLA);
                        InicioAnimacionDespedida++;
                        break;
                    case 1  :
                        Pantalla_DibujaImagen(fin1,0,0,WPANTALLA,HPANTALLA);
                        InicioAnimacionDespedida++;
                        break;
                    case 2  :
                        Pantalla_DibujaImagen(fin2,0,0,WPANTALLA,HPANTALLA);
                        InicioAnimacionDespedida++;
                        break;
                    case 3  :
                        Pantalla_DibujaImagen(fin3,0,0,WPANTALLA,HPANTALLA);
                        InicioAnimacionDespedida++;
                        break;
                    case 4  :
                        Pantalla_DibujaImagen(fin4,0,0,WPANTALLA,HPANTALLA);
                        InicioAnimacionDespedida++;
                        break;
                    case 5  :
                        Pantalla_DibujaImagen(fin5,0,0,WPANTALLA,HPANTALLA);
                        InicioAnimacionDespedida++;
                        break;
                    case 6  :
                        Pantalla_DibujaImagen(fin6,0,0,WPANTALLA,HPANTALLA);
                        InicioAnimacionDespedida++;
                        break;
                    case 7  :
                        Pantalla_DibujaImagen(fin7,0,0,WPANTALLA,HPANTALLA);
                        InicioAnimacionDespedida++;
                        break;
                    case 8  :
                        Pantalla_DibujaImagen(fin8,0,0,WPANTALLA,HPANTALLA);
                        InicioAnimacionDespedida++;
                        break;
                    case 9  :
                        Pantalla_DibujaImagen(fin9,0,0,WPANTALLA,HPANTALLA);
                        InicioAnimacionDespedida++;
                        break;
                    case 10 :
                        Pantalla_DibujaImagen(fin10,0,0,WPANTALLA,HPANTALLA);
                        InicioAnimacionDespedida++;
                        break;
                    case 11 :
                        Pantalla_DibujaImagen(fin11,0,0,WPANTALLA,HPANTALLA);
                        InicioAnimacionDespedida++;
                        break;
                    }
                }
                else
                {
                    animacion(fin00,fin25,fin50,fin75,fin100);
                    animacion(calavera1,calavera0,calavera2,calavera2,calavera1);
                    Pantalla_DibujaTexto(textorecord,WPANTALLA/2-strlen(textorecord)*8/2,5*HPANTALLA/6);
                    Pantalla_DibujaTexto(puntos,WPANTALLA/2-strlen(puntos)*8/2,5*HPANTALLA/6+20);
                }

                Pantalla_Actualiza();
                Pantalla_Espera(75);
            }
            Pantalla_ImagenLibera(fin0);
            Pantalla_ImagenLibera(fin1);
            Pantalla_ImagenLibera(fin2);
            Pantalla_ImagenLibera(fin3);
            Pantalla_ImagenLibera(fin4);
            Pantalla_ImagenLibera(fin5);
            Pantalla_ImagenLibera(fin6);
            Pantalla_ImagenLibera(fin7);
            Pantalla_ImagenLibera(fin8);
            Pantalla_ImagenLibera(fin9);
            Pantalla_ImagenLibera(fin10);
            Pantalla_ImagenLibera(fin11);
            Pantalla_ImagenLibera(fin00);
            Pantalla_ImagenLibera(fin25);
            Pantalla_ImagenLibera(fin50);
            Pantalla_ImagenLibera(fin75);
            Pantalla_ImagenLibera(fin100);
        }
        PlaySound(NULL,NULL,SND_ASYNC);

        fin=0;
        Imagen MenuSi = Pantalla_ImagenLee("./Materiales/SecuenciaFin/VolverMenuSi.bmp",0);
        Imagen MenuNo = Pantalla_ImagenLee("./Materiales/SecuenciaFin/VolverMenuNo.bmp",0);
        posmen=0;
        while(Pantalla_Activa()&& (!fin))
        {
            if (Pantalla_TeclaPulsada(SDL_SCANCODE_ESCAPE)) return 0;
            //Raton
            if(Colision(Raton_X(),Raton_Y(),10,10,500,360,130,600,'r')) posmen=0;
            if(Colision(Raton_X(),Raton_Y(),10,10,500,498,130,600,'r')) posmen=1;

            //Teclado
            if ((Pantalla_TeclaPulsada(SDL_SCANCODE_DOWN) || Pantalla_TeclaPulsada(SDL_SCANCODE_S)) && (posmen==0))
            {
                //PlaySound(TEXT("s"), NULL, SND_ALIAS);
                posmen=1;
            }
            if ((Pantalla_TeclaPulsada(SDL_SCANCODE_UP) || Pantalla_TeclaPulsada(SDL_SCANCODE_W)) && (posmen==1))
            {
                //PlaySound(TEXT("s"), NULL, SND_ALIAS);
                posmen=0;
            }
            if (((Pantalla_TeclaPulsada(SDL_SCANCODE_SPACE)) || (Pantalla_TeclaPulsada(SDL_SCANCODE_RETURN) || (Pantalla_RatonBotonPulsado(1)))))
            {
                //PlaySound(TEXT("s"), NULL, SND_ALIAS);
                switch(posmen)
                {
                case 0:
                    fin = 1;
                    break;
                case 1:
                    Pantalla_ImagenLibera(MenuSi);
                    Pantalla_ImagenLibera(MenuNo);
                    return 0;
                    break;
                }
            }
            switch(posmen)
            {
            case 0:
                Pantalla_DibujaImagen(MenuSi,0,0,WPANTALLA,HPANTALLA);
                break;
            case 1:
                Pantalla_DibujaImagen(MenuNo,0,0,WPANTALLA,HPANTALLA);
                break;
            }
            Pantalla_Actualiza();
            Pantalla_Espera(20);
        }
        Pantalla_ImagenLibera(MenuSi);
        Pantalla_ImagenLibera(MenuNo);
    }
    return 0;
}
