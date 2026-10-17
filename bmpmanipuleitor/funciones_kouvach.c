#include "funciones_kouvach.h"
#include "compartido.h"

void espejarVertical(t_pixel **mat,int alto)
{

    for(int i=0; i<alto/2; i++) //Recorremos hasta la mitad de la matriz
    {
        //Realizamos intercambio de punteros a filas completas

        int filaOpuesta=alto-1-i;

        t_pixel* aux =*(mat+i);
        *(mat+i) = *(mat+filaOpuesta);
        *(mat+filaOpuesta) = aux;

    }

}

t_pixel** recortarImagen(t_pixel** matOrig, const t_metadata* metaOrig, t_metadata* metaNueva, int porcentaje)
{

    // Copiamos todos los datos base de la original

    *metaNueva = *metaOrig;

    //Calculamos nuevo ancho y alto

    //Chequeamos validacion con porcentaje 0

    if(porcentaje==0)
    {
        metaNueva->alto=metaOrig->alto;
        metaNueva->ancho=metaOrig->ancho;

    }else
    {
        metaNueva->ancho = (metaOrig->ancho * porcentaje) / 100;
        metaNueva->alto = (metaOrig->alto * porcentaje) / 100;

    }


    //Creamos matriz nueva mas chica

    t_pixel **nuevaMat=crearMatrizDinamica(metaNueva->alto,metaNueva->ancho);

    if(!nuevaMat)
    {
        printf("Error al crear nueva matriz.\n");
        return NULL;
    }

    for(int i=0; i<metaNueva->alto; i++)
    {
        for(int j=0; j<metaNueva->ancho; j++)
        {
            nuevaMat[i][j]=matOrig[i][j]; //Intercambiamos contenido de matrices
        }

    }


    return nuevaMat;

}
