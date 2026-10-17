#include <stdio.h>
#include <stdlib.h>
#include "compartido.h"


void liberarMatriz(t_pixel **mat, size_t cf)
{
    if(mat == NULL) return; // <-- Evita crasheos si la matriz no se creó

    for(int i=0; i<cf; i++)
    {
        free(*(mat + i));
    }

    free(mat);
}

t_pixel **crearMatrizDinamica(size_t cf, size_t cc)
{
    t_pixel **mat = (t_pixel**)malloc(cf* sizeof(t_pixel *)); //Reserva vector de punteros

    if(!mat)
    {
        printf("No se pudo reservar memoria\n");
        return NULL;
    }

    for(int i=0; i<cf; i++) //Recorremos cada fila
    {
        *(mat + i) = (t_pixel*)malloc(cc * sizeof(t_pixel)); //Reserva vector columna

        if(!*(mat + i))
        {
            liberarMatriz(mat, i); //Libera memoria hasta la fila que fallo
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
    if(!*imagen)
    {
        fclose(bmp);
        return 0;
    }

    //Calculamos Padding
    int padding = calcularPadding(infoBmp->ancho);

    //Leemos la matriz de pixeles
    for(int i = 0; i < infoBmp->alto; i++)
    {
        fread(*((*imagen) + i), sizeof(t_pixel), infoBmp->ancho, bmp);

        //Si la imagen tiene padding, saltamos bytes de relleno
        if(padding > 0)
        {
            fseek(bmp, padding, SEEK_CUR);
        }

    }

    fclose(bmp);
    return 1; //Se leyó correctamente la imagen

}

int escribirBmp(const char* ruta, t_metadata* infoBmp, t_pixel** imagen)
{
    FILE* bmp = fopen(ruta, "wb");
    if(!bmp)
    {
        printf("No se pudo abrir el archivo %s.\n", ruta);
        return 0;
    }
    //Realizamos el padding
    int padding = calcularPadding(infoBmp->ancho);

    //Calculamos el tamaño total de la fila en bytes
    int tamFil = (infoBmp->ancho * sizeof(t_pixel) + padding);

    //Calculamos el tamaño total de la imagen
    unsigned int tamDatosImg = (tamFil * infoBmp->alto);

    //Calculamos el tamaño total del archivo
    unsigned int tamArch = (54 + tamDatosImg);

    //Escribimos el tipo de archivo
    char tipo[2]= {'B', 'M'};
    fwrite(tipo, sizeof(char), 2, bmp);

    //Tamaño del Archivo
    fwrite(&tamArch, sizeof(unsigned int), 1, bmp);

    //Definimos una variable para escribir Bytes vacios
    unsigned int reservado = 0;
    fwrite(&reservado, sizeof(unsigned int), 1, bmp);

    //Escribimos el offset
    unsigned int offset=54;
    fwrite(&offset, sizeof(unsigned int), 1, bmp);

    //Definimos el tamaño de la cabecera de la imagen
    unsigned int tamInfo = 40;
    fwrite(&tamInfo, sizeof(unsigned int), 1, bmp);

    //Ancho
    fwrite(&(infoBmp->ancho), sizeof(unsigned int), 1, bmp);

    //Alto
    fwrite(&(infoBmp->alto), sizeof(unsigned int), 1, bmp);

    //Número de planos
    unsigned short planos = 1;
    fwrite(&planos, sizeof(unsigned short), 1, bmp);

    //Profundidad (tamaño de cada punto)
    unsigned short profundidad = 24;
    fwrite(&profundidad, sizeof(unsigned short), 1, bmp);

    //Compresion
    unsigned int compresion = 0;
    fwrite(&compresion, sizeof(unsigned int), 1, bmp);

    //Tamaño de imagen
    fwrite(&tamDatosImg, sizeof(unsigned int), 1, bmp);

    //Escribimos los ultimos 16 bytes
    unsigned int resto[4] = {0,0,0,0};
    fwrite(resto, sizeof(unsigned int), 4, bmp);

    //Definimos los pixeles
    unsigned char relleno[3] = {0,0,0};

    for(int i = 0; i < infoBmp->alto; i++)
    {
        //Escribimos todos los pixeles de una fila en una sola lectura
        fwrite(*(imagen + i), sizeof(t_pixel), infoBmp->ancho, bmp);

        //Si la fila requiere padding, escribimos los bytes de relleno
        if(padding > 0)
        {
            fwrite(relleno, sizeof(unsigned char), padding, bmp);
        }
    }
    fclose(bmp);
    return 1; //Se escribió correctamente la imagen
}

unsigned char limitarColor(int num)
{
    if(num > 255)
        num = 255;
    if(num < 0)
        num = 0;
    return num;
}

void inicializarMetadata(t_metadata* meta, unsigned int ancho, unsigned int alto)
{
    meta->ancho = ancho;
    meta->alto = alto;
    meta->profundidad = 24;
    meta->tamEncabezado = 54;
    meta->tamArchivo = 54 + (ancho * 3 * calcularPadding(ancho)) * alto;
}

//Inicializa estructura t_config
void inicializarConfig(t_config* config)
{
    config->cantImagenes = 0;
    config->rutaImg1[0] = '\0';
    config->rutaImg2[0] = '\0';

    // Banderas en 0

    config->negativo = 0;
    config->escalaGrises = 0;
    config->espejarHorizontal = 0;
    config->espejarVertical = 0;
    config->rotarDerecha = 0;
    config->rotarIzquierda = 0;
    config->concatenarHorizontal = 0;
    config->concatenarVertical = 0;
    config->comodin = 0;

    // Valores en -1 (no solicitados)

    config->aumentarContraste = -1;
    config->reducirContraste = -1;
    config->tonalidadAzul = -1;
    config->tonalidadVerde = -1;
    config->tonalidadRoja = -1;
    config->recortar = -1;
    config->achicar = -1;
}

//Limpia la ruta de la imagen
void extraerNombreBase(const char *ruta, char *destino)
{
    char *ultBarra = strrchr(ruta,'/');
    char *ultBarra1 = strrchr(ruta,'\\'); //Barra invertida '\'
    const char *ini = ruta;

    //Recorremos rutas inversamente hasta encontrar "/ o \\" y descartamos el resto

    if(ultBarra!=NULL && ultBarra>=ini)
    {
        ini = ultBarra + 1;
    }

    if(ultBarra1!=NULL && ultBarra1>=ini)
    {
        ini = ultBarra1 + 1;
    }


    strcpy(destino, ini); //Copiamos nombre archivo con extension .bmp

    char *punto = strrchr(destino, '.'); //Reverse

    if(punto!=NULL)
    {
        *punto = '\0'; //Cortamos la cadena en el punto
    }
}













