#include <stdio.h>
#include <stdlib.h>
#include "compartido.h"


void liberarMatriz(t_pixel **mat,size_t cf)
{
    for(int i=0; i<cf; i++)
    {
        free(*(mat+i));
    }

    free(mat);

}

t_pixel **crearMatrizDinamica(size_t cf,size_t cc)
{
    t_pixel **mat=malloc( cf* sizeof(t_pixel *)); //Reserva vector de punteros

    if(!mat)
    {
        printf("No se pudo reservar memoria\n");
        return NULL;
    }

    for(int i=0; i<cf; i++) //Recorremos cada fila
    {
        *(mat+i)=malloc(cc * sizeof(t_pixel)); //Reserva vector columna

        if(!*(mat+i))
        {
            liberarMatriz(mat,i); //Libera memoria hasta la fila que fallo
            return NULL;
        }


    }


    return mat;

}

int calcularPadding(int ancho)
{
    int bytesFila = ancho * sizeof(t_pixel); // 3 bytes
    int resto = bytesFila % 4;

    if (resto == 0)
    {
        return 0; // Multiplo de 4, no necesita padding
    }

    return 4 - resto; // Agregamos padding
}


int leerBmp(const char* ruta, t_metadata* infoBmp, t_pixel*** imagen)
{
    char tipo[2];

    FILE* bmp = fopen(ruta, "rb");
    if(!bmp)
    {
        printf("No se pudo abrir el archivo %s.\n", ruta);
        return 0;
    }

    //Tipo de Archivo
    fread(tipo, sizeof(char), 2, bmp);

    //Validamos Tipo de Archivo

    if (tipo[0] != 'B' || tipo[1] != 'M')
    {
        printf("El archivo no es un BMP válido.\n");
        fclose(bmp);
        return 0;
    }

    //Tamaño del Archivo
    fread(&(infoBmp->tamArchivo), sizeof(unsigned int), 1, bmp);

    //Bytes Reservados
    fseek(bmp, 4, SEEK_CUR); //Los avanzamos sin guardar nada (los ignoramos)

    //Inicio de los datos de la imagen
    fread(&(infoBmp->tamEncabezado), sizeof(unsigned int), 1, bmp); //Nos guardamos el byte exacto donde empiezan los pixeles

    //Tamaño de la Cabecera
    fseek(bmp, 4, SEEK_CUR); //Los avanzamos sin guardar nada (los ignoramos)

    //Ancho
    fread(&(infoBmp->ancho), sizeof(unsigned int), 1, bmp);

    //Alto
    fread(&(infoBmp->alto), sizeof(unsigned int), 1, bmp);

    //Número de planos
    fseek(bmp, 2, SEEK_CUR); //Los avanzamos sin guardar nada (los ignoramos)

    //Profundidad (tamaño de cada punto)
    fread(&(infoBmp->profundidad), sizeof(unsigned short), 1, bmp);

    //Validamos que la profundidad sea de 24 bits
    if(infoBmp->profundidad != 24)
    {
        printf("Profundidad inválida. Solo se admiten imagenes de 24 bits.\n");
        fclose(bmp);
        return 0;
    }

    //Nos posicionamos donde arrancan los pixeles (tamEncabezado)
    fseek(bmp, infoBmp->tamEncabezado, SEEK_SET);

    //Creamos la matriz dinámica de pixeles
    *imagen = crearMatrizDinamica(infoBmp->alto, infoBmp->ancho);
    if(!imagen)
    {
        fclose(bmp);
        return 0;
    }

    //Calculamos Padding
    int padding = calcularPadding(infoBmp->ancho);

    //Leemos la matriz de pixeles
    for(int i = 0; i < infoBmp->alto; i++)
    {
        //Leemos todos los pixeles de una fila en una sola lectura
        fread(*(imagen + i), sizeof(t_pixel), infoBmp->ancho, bmp);

        //Si la imagen tiene padding, saltamos bytes de relleno
        if(padding > 0)
        {
            fseek(bmp, padding, SEEK_CUR);
        }

    }


    fclose(bmp);
    return 1; //Se leyó correctamente la imagen

}












