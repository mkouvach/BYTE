/*
    Integrantes del grupo. En caso de ser un grupo de dos integrantes, no completar el ultimo campo.
    Si alguno de los integrantes del grupo dejara la materia, completar de todos modos sus datos, aclarando que no entrega.
    -----------------
    Apellido: Alvarez da Silva
    Nombre: Keila
    DNI: 45236512
    Entrega: Si
    -----------------
    Apellido: Espinoza
    Nombre: Nahuel
    DNI: 34738657
    Entrega: No
    -----------------
    Apellido: Kouvach
    Nombre: Marcos
    DNI: 45013925
    Entrega: Si
    -----------------
    Apellido: Rodriguez
    Nombre: Lautaro David
    DNI: 45349281
    Entrega: Si
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

    if(!parsearArgumentos(argc, argv, &config))
    {
        printf("Fallo en la funcion parsear.\n");
        return 0;
    }


    if(!leerBmp(config.rutaImg1, &infoMeta, &mat))
    {
        printf("No se pudo leer bien el archivo.\n");
        return 0;

    }

    char nombreBase[128];
    char nombreSalida[256];

    extraerNombreBase(config.rutaImg1, nombreBase); //Limpiamos ruta de imagen

    //Ejecucion de filtros

    //GRUPO A: Filtros que mantienen las dimensiones originales

    if(config.negativo == 1)
    {
        t_pixel **copia = clonarMatriz(mat, infoMeta.alto, infoMeta.ancho);

        if(copia != NULL)
        {
            negativo(copia, infoMeta.alto, infoMeta.ancho);

            sprintf(nombreSalida,"BYTE_negativo_%s.bmp", nombreBase); //Generamos nombre archivo salida

            escribirBmp(nombreSalida, &infoMeta, copia);

            liberarMatriz(copia, infoMeta.alto);

            printf("Imagen con filtro negativo generada con exito.\n");
        }
    }

    if(config.escalaGrises == 1)
    {
        t_pixel **copia = clonarMatriz(mat, infoMeta.alto, infoMeta.ancho);

        if(copia != NULL)
        {
            escalaDeGrises(copia, infoMeta.alto, infoMeta.ancho);

            sprintf(nombreSalida,"BYTE_escala-de-grises_%s.bmp", nombreBase); //Generamos nombre archivo salida

            escribirBmp(nombreSalida, &infoMeta, copia);

            liberarMatriz(copia, infoMeta.alto);

            printf("Imagen con filtro escala grises generada con exito.\n");
        }

    }

    if(config.espejarHorizontal == 1)
    {
        t_pixel **copia = clonarMatriz(mat, infoMeta.alto, infoMeta.ancho);

        if(copia != NULL)
        {
            espejarHorizontal(copia, infoMeta.alto, infoMeta.ancho);

            sprintf(nombreSalida, "BYTE_espejar-horizontal_%s.bmp", nombreBase); //Generamos nombre archivo salida

            escribirBmp(nombreSalida, &infoMeta, copia);

            liberarMatriz(copia, infoMeta.alto);

            printf("Imagen con filtro espejar horizontal generada con exito.\n");
        }
    }

    if(config.espejarVertical == 1)
    {
        t_pixel **copia = clonarMatriz(mat, infoMeta.alto, infoMeta.ancho);

        if(copia != NULL)
        {
            espejarVertical(copia, infoMeta.alto);

            sprintf(nombreSalida, "BYTE_espejar-vertical_%s.bmp", nombreBase); //Generamos nombre archivo salida

            escribirBmp(nombreSalida, &infoMeta, copia);

            liberarMatriz(copia, infoMeta.alto);

            printf("Imagen con filtro espejar vertical generada con exito.\n");
        }
    }

    if(config.tonalidadAzul != -1)
    {
        t_pixel **copia = clonarMatriz(mat, infoMeta.alto, infoMeta.ancho);

        if(copia != NULL)
        {
            tonalidadAzul(copia, infoMeta.alto, infoMeta.ancho, config.tonalidadAzul);

            sprintf(nombreSalida, "BYTE_tonalidad-azul_%s.bmp", nombreBase); //Generamos nombre archivo salida

            escribirBmp(nombreSalida, &infoMeta, copia);

            liberarMatriz(copia, infoMeta.alto);

            printf("Imagen con filtro tonalidad azul generada con exito.\n");
        }

    }

    if(config.tonalidadRoja != -1)
    {
        t_pixel **copia = clonarMatriz(mat, infoMeta.alto, infoMeta.ancho);

        if(copia != NULL)
        {
            tonalidadRoja(copia, infoMeta.alto, infoMeta.ancho, config.tonalidadRoja);

            sprintf(nombreSalida, "BYTE_tonalidad-roja_%s.bmp", nombreBase); //Generamos nombre archivo salida

            escribirBmp(nombreSalida, &infoMeta, copia);

            liberarMatriz(copia, infoMeta.alto);

            printf("Imagen con filtro tonalidad roja generada con exito.\n");
        }
    }

    if(config.tonalidadVerde != -1)
    {
        t_pixel **copia = clonarMatriz(mat, infoMeta.alto, infoMeta.ancho);

        if(copia != NULL)
        {
            tonalidadVerde(copia, infoMeta.alto, infoMeta.ancho, config.tonalidadVerde);

            sprintf(nombreSalida, "BYTE_tonalidad-verde_%s.bmp", nombreBase); //Generamos nombre archivo salida

            escribirBmp(nombreSalida, &infoMeta, copia);

            liberarMatriz(copia, infoMeta.alto);

            printf("Imagen con filtro tonalidad verde generada con exito.\n");
        }
    }

    if(config.aumentarContraste != -1)
    {
        t_pixel **copia = clonarMatriz(mat, infoMeta.alto, infoMeta.ancho);

        if(copia != NULL)
        {
            aumentarContraste(copia, infoMeta.alto, infoMeta.ancho, config.aumentarContraste);

            sprintf(nombreSalida, "BYTE_aumentar-contraste_%s.bmp", nombreBase); //Generamos nombre archivo salida

            escribirBmp(nombreSalida, &infoMeta, copia);

            liberarMatriz(copia, infoMeta.alto);

            printf("Imagen con filtro aumentar contraste generada con exito.\n");
        }
    }

    if(config.reducirContraste != -1)
    {
        t_pixel **copia = clonarMatriz(mat, infoMeta.alto, infoMeta.ancho);

        if(copia != NULL)
        {
            reducirContraste(copia, infoMeta.alto, infoMeta.ancho, config.reducirContraste);

            sprintf(nombreSalida, "BYTE_reducir-contraste_%s.bmp", nombreBase); //Generamos nombre archivo salida

            escribirBmp(nombreSalida, &infoMeta, copia);

            liberarMatriz(copia, infoMeta.alto);

            printf("Imagen con filtro reducir contraste generada con exito.\n");
        }
    }

    // --- GRUPO B: Filtros que crean una matriz nueva con dimensiones distintas

    if(config.rotarDerecha == 1)
    {
        t_metadata nuevaMeta;

        t_pixel **matNueva = rotarDerecha(mat, &infoMeta, &nuevaMeta);

        if(matNueva != NULL)
        {
            sprintf(nombreSalida, "BYTE_rotar-derecha_%s.bmp", nombreBase); //Generamos nombre archivo salida

            escribirBmp(nombreSalida, &nuevaMeta, matNueva);

            liberarMatriz(matNueva, nuevaMeta.alto);

            printf("Imagen con filtro rotar derecha generada con exito.\n");
        }
    }

    if(config.rotarIzquierda == 1)
    {
        t_metadata nuevaMeta;

        t_pixel **matNueva = rotarIzquierda(mat, &infoMeta, &nuevaMeta);

        if(matNueva != NULL)
        {
            sprintf(nombreSalida, "BYTE_rotar-izquierda_%s.bmp", nombreBase); //Generamos nombre archivo salida

            escribirBmp(nombreSalida, &nuevaMeta, matNueva);

            liberarMatriz(matNueva, nuevaMeta.alto);

            printf("Imagen con filtro rotar izquierda generada con exito.\n");
        }
    }

    if (config.recortar != -1)
    {
        t_metadata metaNueva;

        t_pixel** matNueva = recortarImagen(mat, &infoMeta, &metaNueva, config.recortar);

        if (matNueva != NULL)
        {
            sprintf(nombreSalida, "BYTE_recortar_%s.bmp", nombreBase);

            escribirBmp(nombreSalida, &metaNueva, matNueva);

            liberarMatriz(matNueva, metaNueva.alto);

            printf("Imagen con filtro recortar con exito.\n");
        }
    }

    if (config.achicar != -1)
    {
        t_metadata metaNueva;

        t_pixel** matNueva = achicarImagen(mat, &infoMeta, &metaNueva, config.achicar);

        if (matNueva != NULL)
        {
            sprintf(nombreSalida, "BYTE_achicar_%s.bmp", nombreBase);

            escribirBmp(nombreSalida, &metaNueva, matNueva);

            liberarMatriz(matNueva, metaNueva.alto);

            printf("Imagen con filtro achicar con exito.\n");
        }
    }

    // --- GRUPO C: Filtros que reciben dos imÃ¡genes (Concatenar)

    if(config.concatenarHorizontal == 1 || config.concatenarVertical == 1)
    {
        if(config.cantImagenes < 2)
        {
            printf("Cantidad de imagenes insuficientes para concatenar.\n");

        }
        else
        {
            t_metadata infoMeta2;
            t_pixel **mat2 = NULL;

            if(!leerBmp(config.rutaImg2, &infoMeta2, &mat2))
            {
                printf("Error en la lectura del archivo.\n");
            }
            else
            {
                if(config.concatenarHorizontal == 1)
                {
                    t_metadata metaNueva;
                    t_pixel** matNueva = concatenarHorizontal(mat, &infoMeta, mat2, &infoMeta2, &metaNueva);

                    if (matNueva != NULL)
                    {
                        sprintf(nombreSalida, "BYTE_concatenar-horizontal_%s.bmp", nombreBase);

                        escribirBmp(nombreSalida, &metaNueva, matNueva);

                        liberarMatriz(matNueva, metaNueva.alto);

                        printf("Imagen con filtro concatenar horizontal con exito.\n");
                    }
                }

                if(config.concatenarVertical == 1)
                {
                    t_metadata metaNueva;
                    t_pixel** matNueva = concatenarVertical(mat, &infoMeta, mat2, &infoMeta2, &metaNueva);

                    if (matNueva != NULL)
                    {
                        sprintf(nombreSalida, "BYTE_concatenar-vertical_%s.bmp", nombreBase);

                        escribirBmp(nombreSalida, &metaNueva, matNueva);

                        liberarMatriz(matNueva, metaNueva.alto);

                        printf("Imagen con filtro concatenar vertical con exito.\n");
                    }
                }

                //Liberamos segunda imagen

                liberarMatriz(mat2,infoMeta2.alto);
            }
        }
    }

    if(config.comodin == 1)
    {
        t_pixel **matNueva = comodinBlur(mat, infoMeta.alto, infoMeta.ancho);

        if(matNueva != NULL)
        {
            sprintf(nombreSalida, "BYTE_comodin_%s.bmp", nombreBase); //Generamos nombre archivo salida

            escribirBmp(nombreSalida, &infoMeta, matNueva);

            liberarMatriz(matNueva, infoMeta.alto);

            printf("Imagen con filtro comodin generada con exito.\n");
        }
    }

    //Liberamos matriz original

    liberarMatriz(mat, infoMeta.alto);

    return 0;
}
