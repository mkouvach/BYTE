/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el último campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Alvarez da Silva
    Nombre: Keila
    DNI: 45236512
    Entrega: Sí
    -----------------
    Apellido: Espinoza
    Nombre: Nahuel
    DNI: 34738657
    Entrega: Sí
    -----------------
    Apellido: Kouvach
    Nombre: Marcos Andrés
    DNI: 45013925
    Entrega: Sí
    -----------------
    Apellido: Rodriguez
    Nombre: Lautaro David
    DNI: 45349281
    Entrega: Sí
    -----------------
*/
#include "funciones_grupo.h"
#include "compartido.h"

int solucion(int argc, char *argv[])
{
    t_metadata infoMeta;
    t_pixel** mat = NULL;

    if(leerBmp(ruta_origen, &infoMeta, &mat) == 0)
    {
        printf("Error en la lectura de la imagen\n");
        return 0;
    }

    if(escribirBmp("copiaUnlam.bmp", &infoMeta, mat) == 0)
    {
        printf("Error en la escritura de la imagen\n");
        return 0;
    }

    liberarMatriz(mat, infoMeta.alto);


    printf("Imagen leida con exito\n");

    return 1;
}
