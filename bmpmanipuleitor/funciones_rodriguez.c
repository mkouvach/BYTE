#include "funciones_rodriguez.h"
#include "compartido.h"

//ESCALA DE GRISES
void escalaDeGrises(t_pixel **mat, int alto, int ancho)
{
    int i, j, suma = 0, prom = 0;

    for(i=0; i<alto; i++)
    {
        for(j=0; j<ancho; j++)
        {
            suma = mat[i][j].pixel[ROJO] + mat[i][j].pixel[AZUL] + mat[i][j].pixel[VERDE];

            prom = (float)suma / 3;

            mat[i][j].pixel[ROJO] = prom;
            mat[i][j].pixel[AZUL] = prom;
            mat[i][j].pixel[VERDE] = prom;
        }
    }
}

//AUMENTAR CONTRASTE (PORCENTAJE)
void aumentarContraste(t_pixel **mat, int alto, int ancho, int porcentaje)
{
    int i, j, aux;
    float factor = 1 + porcentaje / 100.0;
    for(i=0; i<alto; i++)
    {
        for(j=0; j<ancho; j++)
        {
            aux = 128 + (mat[i][j].pixel[ROJO] - 128) * factor;
            mat[i][j].pixel[ROJO] = limitarColor(aux);

            aux = 128 + (mat[i][j].pixel[AZUL] - 128) * factor;
            mat[i][j].pixel[AZUL] = limitarColor(aux);

            aux = 128 + (mat[i][j].pixel[VERDE] - 128) * factor;
            mat[i][j].pixel[VERDE] = limitarColor(aux);
        }
    }
}

//REDUCIR CONTRASTE (PORCENTAJE)
void reducirContraste(t_pixel **mat, int alto, int ancho, int porcentaje)
{
    int i, j;
    float factor = 1 - porcentaje / 100.0;
    for(i=0; i<alto; i++)
    {
        for(j=0; j<ancho; j++)
        {
            mat[i][j].pixel[ROJO] = 128 + (mat[i][j].pixel[ROJO] - 128) * factor;
            mat[i][j].pixel[AZUL] = 128 + (mat[i][j].pixel[AZUL] - 128) * factor;
            mat[i][j].pixel[VERDE] = 128 + (mat[i][j].pixel[VERDE] - 128) * factor;
        }
    }
}

//ESPEJAR HORIZONTAL
void espejarHorizontal(t_pixel **mat, int alto, int ancho)
{
    t_pixel aux, *fila;
    for(int i=0; i<alto; i++)
    {
        fila = *(mat + i);

        for(int j=0; j<ancho/2; j++)
        {
            int colOpuesta = ancho - 1 - j;

            aux = *(fila + j);
            *(fila + j) = *(fila + colOpuesta);
            *(fila + colOpuesta) = aux;
        }
    }
}
