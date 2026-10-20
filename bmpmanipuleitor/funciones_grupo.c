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
    t_metadata nuevaMeta;
    t_config config;
    t_pixel** mat = NULL;

    inicializarConfig(&config);

    if(!parsearArgumentos(argc,argv,&config))
    {
        return 0; //Algo fallo en el parser
    }

    //Una vez que el parser ya nos devolvio todos los filtros, imagenes etc

    //LOGICA PARA IR PREGUNTANDO POR CADA FILTRO E IR DESGLOSANDO TODO

    leerBmp(config.rutaImg1,&infoMeta,&mat);

    if(config.negativo==1)
    {
        //Falta hacer
        escribirBmp(config.rutaImg1,"_negativo_",&infoMeta,mat);

    }

    if(config.escalaGrises==1)
    {
        escalaDeGrises(mat,infoMeta.alto,infoMeta.ancho);
        escribirBmp(config.rutaImg1,"_escala-de-grises_",&infoMeta,mat);

    }

    if(config.espejarHorizontal==1)
    {

        espejarHorizontal(mat,infoMeta.alto,infoMeta.ancho);
        escribirBmp(config.rutaImg1,"_espejar-horizontal_",&infoMeta,mat);

    }

    if(config.espejarVertical==1)
    {

        espejarVertical(mat,infoMeta.alto);
        escribirBmp(config.rutaImg1,"_espejar-vertical_",&infoMeta,mat);

    }

    if(config.rotarDerecha==1)
    {

        mat=rotarDerecha(mat,&infoMeta,&nuevaMeta);
        escribirBmp(config.rutaImg1,"_rotar-derecha_",&infoMeta,mat);

    }

    if(config.rotarIzquierda==1)
    {
        mat=rotarIzquierda(mat,&infoMeta,&nuevaMeta);
        escribirBmp(config.rutaImg1,"_rotar-izquierda_",&infoMeta,mat);

    }

    if(config.concatenarHorizontal==1)
    {
        leerBmp(config.rutaImg2,&infoMeta,&mat); //Leemos segundo archivo

        //Falta hacer

        escribirBmp(config.rutaImg1,"_concatenar-horizontal_",&infoMeta,mat);

    }

    if(config.concatenarVertical==1)
    {

        leerBmp(config.rutaImg2,&infoMeta,&mat); //Leemos segundo archivo

        //Falta hacer

        escribirBmp(config.rutaImg1,"_concatenar-vertical_",&infoMeta,mat);

    }
    if(config.comodin==1)
    {

        //Falta hacer

        escribirBmp(config.rutaImg1,"_comodin_",&infoMeta,mat);

    }



    liberarMatriz(mat, infoMeta.alto);

    printf("Imagen leida con exito\n");

    return 1;
}
