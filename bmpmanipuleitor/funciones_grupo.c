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
    t_config config;
    t_pixel** mat = NULL;

    inicializarConfig(&config);

    if(!parsearArgumentos(argc,argv,&config))
    {
        return 0; //Algo fallo en el parser
    }

    //Una vez que el parser ya nos devolvio todos los filtros, imagenes etc

    //LOGICA PARA IR PREGUNTANDO POR CADA FILTRO E IR DESGLOSANDO TODO



    //////////////////////////

    if(leerBmp(config.rutaImg1, &infoMeta, &mat) == 0)
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
