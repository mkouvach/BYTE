#include <stdio.h>
#include <stdlib.h>
#include "compartido.h"


void liberarMatriz(t_pixel **mat,size_t cf)
{
    for(int i=0; i<cf; i++)
    {
        free(*(mat+i));
    }

    free(mat);

}

t_pixel **crearMatrizDinamica(size_t cf,size_t cc)
{
    t_pixel **mat=malloc( cf* sizeof(t_pixel *)); //Reserva vector de punteros

    if(!mat)
    {
        printf("No se pudo reservar memoria\n");
        return NULL;
    }

    for(int i=0; i<cf; i++) //Recorremos cada fila
    {
        *(mat+i)=malloc(cc * sizeof(t_pixel)); //Reserva vector columna

        if(!*(mat+i))
        {
            liberarMatriz(mat,i); //Libera memoria hasta la fila que fallo
            return NULL;
        }


    }


    return mat;

}

int calcular_padding(int ancho)
{
    int bytes_fila = ancho * sizeof(t_pixel); // 3 bytes
    int resto = bytes_fila % 4;

    if (resto == 0)
    {
        return 0; // Multiplo de 4, no necesita padding
    }

    return 4 - resto; // Agregamos padding
}
