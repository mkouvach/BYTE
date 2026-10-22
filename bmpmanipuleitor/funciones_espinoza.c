#include "funciones_espinoza.h"
#include "compartido.h"

//NEGATIVO
void negativo(t_pixel **mat, int alto, int ancho)
{
    for(int i = 0; i<alto; i++)
    {
        for(int j = 0; j<ancho; j++)
        {

            mat[i][j].pixel[ROJO] = 255 - mat[i][j].pixel[ROJO];
            mat[i][j].pixel[AZUL] = 255 - mat[i][j].pixel[AZUL];
            mat[i][j].pixel[VERDE] = 255 - mat[i][j].pixel[VERDE];
        }
    }
}


//TONALIDAD ROJA (PORCENTAJE)
void tonalidadRoja(t_pixel **mat, int alto, int ancho, int porcentaje)
{
    float factor = 1 + porcentaje / 100;
    int aux;

    for(int i = 0; i<alto; i++)
    {
        for(int j = 0; j<ancho; j++)
        {
            aux = mat[i][j].pixel[ROJO] * factor;
            mat[i][j].pixel[ROJO] = limitarColor(aux);
        }
    }
}

//TONALIDAD VERDE (PORCENTAJE)
void tonalidadVerde(t_pixel **mat, int alto, int ancho, int porcentaje)
{
    float factor = 1 + porcentaje / 100;
    int aux;

    for(int i = 0; i<alto; i++)
    {
        for(int j = 0; j<ancho; j++)
        {
            aux = mat[i][j].pixel[VERDE] * factor;
            mat[i][j].pixel[VERDE] = limitarColor(aux);
        }
    }
}


//TONALIDAD AZUL (PORCENTAJE)
void tonalidadAzul(t_pixel **mat, int alto, int ancho, int porcentaje)
{
    float factor = 1 + porcentaje / 100;
    int aux;

    for(int i = 0; i<alto; i++)
    {
        for(int j = 0; j<ancho; j++)
        {
            aux = mat[i][j].pixel[AZUL] * factor;
            mat[i][j].pixel[AZUL] = limitarColor(aux);
        }
    }
}
