#include "funciones_kouvach.h"
#include "compartido.h"

void espejarVertical(t_pixel **mat,int alto)
{

    for(int i=0;i<alto/2;i++) //Recorremos hasta la mitad de la matriz
    {
        //Realizamos intercambio de punteros a filas completas

        int filaOpuesta=alto-1-i;

        t_pixel* aux =*(mat+i);
        *(mat+i) = *(mat+filaOpuesta);
        *(mat+filaOpuesta) = aux;

    }

}

t_pixel** recortarImagen(t_pixel** matOrig, t_metadata* metaOrig, int porcentaje)
{
    //Calculamos nuevo ancho y alto

    int nuevoAlto=(metaOrig->alto*porcentaje)/100;
    int nuevoAncho=(metaOrig->ancho*porcentaje)/100;

    //Creamos matriz nueva mas chica

    t_pixel **nuevaMat=crearMatrizDinamica(nuevoAlto,nuevoAncho);

    if(!nuevaMat)
    {
        printf("Error al crear nueva matriz.\n");
        return NULL;
    }

    for(int i=0;i<nuevoAlto;i++)
    {
        for(int j=0;j<nuevoAncho;j++)
        {
            nuevaMat[i][j]=matOrig[i][j]; //Intercambiamos contenido de matrices
        }

    }

    //Actualizamos ancho y alto en la estructura

    metaOrig->alto=nuevoAlto;
    metaOrig->ancho=nuevoAncho;

    return nuevaMat;


}
