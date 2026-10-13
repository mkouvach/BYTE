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

    // Para una primera prueba rápida, leemos la imagen que pasaron por argumento (o una fija de prueba)
    if (argc < 2)
    {
        printf("Uso: %s <imagen.bmp>\n", argv[0]);
        return 1;
    }
    const char* ruta_origen = argv[1];

    if(leerBmp(ruta_origen, &infoMeta, &mat) == 0)
    {
        printf("Error en la lectura de la imagen\n");
        return 0;
    }

    todoRojo(mat, infoMeta.alto, infoMeta.ancho);
    //escalaDeGrises(mat, infoMeta.alto, infoMeta.ancho);
    //aumentarContraste(mat, infoMeta.alto, infoMeta.ancho, 50);

    printf("DEBUG: Ancho = %u, Alto = %u\n", infoMeta.ancho, infoMeta.alto);

    if(escribirBmp("copiaUnlam.bmp", &infoMeta, mat) == 0)
    {
        printf("Error en la escritura de la imagen\n");
        return 0;
    }

    liberarMatriz(mat, infoMeta.alto);

    printf("Imagen leida con exito\n");

    return 1;
}
