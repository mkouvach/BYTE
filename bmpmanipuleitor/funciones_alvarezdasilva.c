#include "funciones_alvarezdasilva.h"
#include "compartido.h"


//ACHICAR (PORCENTAJE)
t_pixel** achicarImagen(t_pixel** matOrig, const t_metadata* metaOrig, t_metadata* metaNueva, int porcentaje)
{
    if(porcentaje < 1 || porcentaje > 100)
    {
        printf("Porcentaje incorrecto. Se necesita un valor entr 1 y 100\n");
        return NULL;
    }

    unsigned int nuevoAncho = (metaOrig->ancho * porcentaje) / 100;
    unsigned int nuevoAlto = (metaOrig->alto * porcentaje) / 100;

    //No dejamos dimensiones en 0
    if(nuevoAncho == 0)
        nuevoAncho = 1;
    if(nuevoAlto == 0)
        nuevoAlto = 1;

    t_pixel** nueva = crearMatrizDinamica(nuevoAlto, nuevoAncho);
    if(!nueva)
    {
        printf("Error: Falló la asignación de memoria para crear la matriz.\n");
        return NULL;
    }

    unsigned int i, j;

    for(i=0; i < nuevoAlto; i++)
    {
        unsigned int origI = (i * metaOrig->alto) / nuevoAlto;

        for(j=0; j < nuevoAncho; j++)
        {
            unsigned int origJ = (j * metaOrig->ancho) / nuevoAncho;
            nueva[i][j] = matOrig[origI][origJ];
        }
    }

    inicializarMetadata(metaNueva, nuevoAncho, nuevoAlto);
    return nueva;
}

//CONCATENAR HORIZONTAL (2 IMAGENES)

//CONCATENAR VERTICAL (2 IMAGENES)

//COMODIN

