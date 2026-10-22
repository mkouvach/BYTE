#include "funciones_kouvach.h"
#include "compartido.h"

//ESPEJAR VERTICAL
void espejarVertical(t_pixel **mat, int alto)
{

    for(int i=0; i<alto/2; i++) //Recorremos hasta la mitad de la matriz
    {
        //Realizamos intercambio de punteros a filas completas

        int filaOpuesta = alto - 1 - i;

        t_pixel* aux = *(mat + i);
        *(mat + i) = *(mat + filaOpuesta);
        *(mat + filaOpuesta) = aux;

    }

}

//RECORTAR (PORCENTAJE)
t_pixel** recortarImagen(t_pixel** matOrig, const t_metadata* metaOrig, t_metadata* metaNueva, int porcentaje)
{

    //Copiamos todos los datos base de la original

    *metaNueva = *metaOrig;

    //Calculamos nuevo ancho y alto

    //Validamos si porcentaje == 0, no realiza cambios, la matriz/imagen se mantiene igual
    if(porcentaje == 0)
    {
        metaNueva->alto = metaOrig->alto;
        metaNueva->ancho = metaOrig->ancho;

    }
    else
    {
        metaNueva->ancho = (metaOrig->ancho * porcentaje) / 100;
        metaNueva->alto = (metaOrig->alto * porcentaje) / 100;

    }


    //Creamos matriz nueva mas chica

    t_pixel **nuevaMat=crearMatrizDinamica(metaNueva->alto,metaNueva->ancho);

    if(!nuevaMat)
    {
        printf("Error: Falló la asignación de memoria para crear la matriz.\n");
        return NULL;
    }

    for(int i = 0; i<metaNueva->alto; i++)
    {
        for(int j = 0; j<metaNueva->ancho; j++)
        {
            nuevaMat[i][j] = matOrig[i][j]; //Intercambiamos contenido de matrices
        }

    }


    return nuevaMat;

}

//ROTAR DERECHA

t_pixel** rotarDerecha(t_pixel** matOrig, t_metadata* metaOrig, t_metadata* metaNueva)
{

    //Se intercambian dimensiones

    metaNueva->alto = metaOrig->ancho;
    metaNueva->ancho = metaOrig->alto;

    t_pixel **nuevaMat = crearMatrizDinamica(metaNueva->alto, metaNueva->ancho);

    if(!nuevaMat)
    {
        printf("Error: Falló la asignación de memoria para crear la matriz.\n");
        return NULL;
    }


    for (int i = 0; i < metaOrig->alto; i++)
    {
        for (int j = 0; j < metaOrig->ancho; j++)
        {
            int nuevaFila = j;
            int nuevaCol = (metaOrig->alto - 1) - i;

            nuevaMat[nuevaFila][nuevaCol] = matOrig[i][j];
        }
    }

    //Otra opcion hubiera sido trasponer la matriz
    //Y luego invertir los elementos de cada fila


    return nuevaMat;

}

//ROTAR IZQUIERDA

t_pixel** rotarIzquierda(t_pixel** matOrig, t_metadata* metaOrig, t_metadata* metaNueva)
{
    //Se intercambian dimensiones

    metaNueva->alto = metaOrig->ancho;
    metaNueva->ancho = metaOrig->alto;

    t_pixel **nuevaMat = crearMatrizDinamica(metaNueva->alto, metaNueva->ancho);

    if(!nuevaMat)
    {
        printf("Error: Falló la asignación de memoria para crear la matriz.\n");
        return NULL;
    }


    for (int i = 0; i < metaOrig->alto; i++)
    {
        for (int j = 0; j < metaOrig->ancho; j++)
        {
            int nuevaFila = (metaOrig->ancho - 1) - j;
            int nuevaCol = i;

            nuevaMat[nuevaFila][nuevaCol] = matOrig[i][j];
        }
    }

    //Otra opcion hubiera sido trasponer la matriz
    //Y luego invertir los elementos de cada columna


    return nuevaMat;

}
