#include "funciones_rodriguez.h"
#include "compartido.h"

//PRUEBA
void todoRojo(t_pixel **mat, int alto, int ancho)
{
    int i,j;

    for(i=0;i<alto;i++)
    {
        for(j=0;j<ancho;j++)
        {
            mat[i][j].pixel[ROJO]=255;
            mat[i][j].pixel[AZUL]=0;
            mat[i][j].pixel[VERDE]=0;
        }
    }
}

//ESCALA DE GRISES
void escalaDeGrises(t_pixel **mat, int alto, int ancho)
{
    int i,j, suma=0, prom=0;

    for(i=0;i<alto;i++)
    {
        for(j=0;j<ancho;j++)
        {
            suma=mat[i][j].pixel[ROJO]+mat[i][j].pixel[AZUL]+mat[i][j].pixel[VERDE];

            prom = (float)suma / 3;

            mat[i][j].pixel[ROJO] = prom;
            mat[i][j].pixel[AZUL] = prom;
            mat[i][j].pixel[VERDE] = prom;
        }
    }
}

//Aumentar contraste
void aumentarContraste(t_pixel **mat, int alto, int ancho, int porcentaje)
{
    int i,j,aux;
    float factor = 1 + porcentaje / 100.0;
    for(i=0;i<alto;i++)
    {
        for(j=0;j<ancho;j++)
        {
            aux = 128 + (mat[i][j].pixel[ROJO] -128) * factor;
            mat[i][j].pixel[ROJO] = limitarColor(aux);

            aux = 128 + (mat[i][j].pixel[AZUL] -128) * factor;
            mat[i][j].pixel[AZUL] = limitarColor(aux);

            aux = 128 + (mat[i][j].pixel[VERDE] -128) * factor;
            mat[i][j].pixel[VERDE] = limitarColor(aux);
        }
    }
}

