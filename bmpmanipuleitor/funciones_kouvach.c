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
    unsigned int nuevoAlto, nuevoAncho;

    //Calculamos nuevo ancho y alto

    //Validamos si porcentaje == 0, no realiza cambios, la matriz/imagen se mantiene igual

    if(porcentaje == 0)
    {
        nuevoAlto = metaOrig->alto;
        nuevoAncho = metaOrig->ancho;
    }
    else
    {
        nuevoAncho = (metaOrig->ancho * porcentaje) / 100;
        nuevoAlto = (metaOrig->alto * porcentaje) / 100;
    }

    //No dejamos dimensiones en 0

    if(nuevoAncho == 0)
        nuevoAncho = 1;
    if(nuevoAlto == 0)
        nuevoAlto = 1;

    //Creamos matriz nueva mas chica

    t_pixel **nuevaMat = (t_pixel**)crearMatrizDinamica(nuevoAlto, nuevoAncho, sizeof(t_pixel));

    if(!nuevaMat)
    {
        printf("Error: Falló la asignación de memoria para crear la matriz.\n");
        return NULL;
    }

    for(unsigned int i = 0; i < nuevoAlto; i++)
    {
        for(unsigned int j = 0; j < nuevoAncho; j++)
        {
            nuevaMat[i][j] = matOrig[i][j]; //Copiamos contenido de matriz original a la recortada
        }
    }

    inicializarMetadata(metaNueva,nuevoAncho,nuevoAlto);

    return nuevaMat;

}

//ROTAR DERECHA
t_pixel** rotarDerecha(t_pixel** matOrig, t_metadata* metaOrig, t_metadata* metaNueva)
{
    unsigned int nuevoAlto, nuevoAncho;

    //Se intercambian dimensiones
    nuevoAlto = metaOrig->ancho;
    nuevoAncho = metaOrig->alto;

    t_pixel **nuevaMat = (t_pixel**)crearMatrizDinamica(nuevoAlto, nuevoAncho, sizeof(t_pixel));

    if(!nuevaMat)
    {
        printf("Error: Falló la asignación de memoria para crear la matriz.\n");
        return NULL;
    }

    for (unsigned int i = 0; i < metaOrig->alto; i++)
    {
        for (unsigned int j = 0; j < metaOrig->ancho; j++)
        {
            unsigned int nuevaFila = (metaOrig->ancho - 1) - j;
            unsigned int nuevaCol = i;

            nuevaMat[nuevaFila][nuevaCol] = matOrig[i][j];
        }
    }

    //Otra opcion hubiera sido trasponer la matriz
    //Y luego invertir los elementos de cada fila

    inicializarMetadata(metaNueva, nuevoAncho, nuevoAlto);

    return nuevaMat;
}

//ROTAR IZQUIERDA
t_pixel** rotarIzquierda(t_pixel** matOrig, t_metadata* metaOrig, t_metadata* metaNueva)
{
    unsigned int nuevoAlto, nuevoAncho;

    //Se intercambian dimensiones
    nuevoAlto = metaOrig->ancho;
    nuevoAncho = metaOrig->alto;

    t_pixel **nuevaMat = (t_pixel**)crearMatrizDinamica(nuevoAlto, nuevoAncho, sizeof(t_pixel));

    if(!nuevaMat)
    {
        printf("Error: Falló la asignación de memoria para crear la matriz.\n");
        return NULL;
    }

    for (unsigned int i = 0; i < metaOrig->alto; i++)
    {
        for (unsigned int j = 0; j < metaOrig->ancho; j++)
        {
            unsigned int nuevaFila = j;
            unsigned int nuevaCol = (metaOrig->alto - 1) - i;

            nuevaMat[nuevaFila][nuevaCol] = matOrig[i][j];
        }
    }

    //Otra opcion hubiera sido trasponer la matriz
    //Y luego invertir los elementos de cada columna

    inicializarMetadata(metaNueva, nuevoAncho, nuevoAlto);

    return nuevaMat;
}
