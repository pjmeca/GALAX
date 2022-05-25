#include <math.h>
#include "Colision.h"
int Colision(int x1, int y1, int h1, int w1, int x2, int y2, int h2, int w2, char tipo_colision)
{
    int PERCENT_DENTRO;
    if(tipo_colision=='p') PERCENT_DENTRO=0.5;
    else PERCENT_DENTRO=0.3;
    //De esta manera será mucho más fácil acertar con un disparo.

    if(tipo_colision=='r')
    {
        if(((x2<=(x1+w1)) && ((x1+w1)<=(x2+w2))) || ((x2<=(x1-w1)) && ((x1-w1)<=(x2+w2)))){
            if (((y2<=(y1+h1)) && ((y1+h1)<=(y2+h2))) || ((y2<=(y1-h1)) && ((y1-h1)<=(y2+h2))))
                return 1;
        }else return 0;

    }else
    {
        double cx1 = x1+w1/2.0;
        double cy1 = y1+h1/2.0;
        double cx2 = x2+w2/2.0;
        double cy2 = y2+h2/2.0;
        double r1 = sqrt(pow(w1/2.0,2.0)+pow(h1/2.0,2.0));
        double r2 = sqrt(pow(w2/2.0,2.0)+pow(h2/2.0,2.0));
        double dentro = (r1+r2)*PERCENT_DENTRO;
        return sqrt(pow(cx1-cx2,2.0)+pow(cy1-cy2,2.0))<((r1+r2)-dentro);
    }
    return 0;
}
