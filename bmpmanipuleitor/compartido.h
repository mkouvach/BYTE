#ifndef COMPARTIDO_H_INCLUDED
#define COMPARTIDO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

#define AZUL  0
#define VERDE 1
#define ROJO  2

typedef struct
{
    unsigned char pixel[3];

}t_pixel;

typedef struct
{
    unsigned int tamArchivo;
    unsigned int tamEncabezado;
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundidad;

}t_metadata;

typedef struct
{
    // Rutas de las imágenes

    char rutaImg1[256];
    char rutaImg2[256];
    int cantImagenes;

    // Filtros sin parámetros (0 = no solicitado, 1 = solicitado)
    int negativo;
    int escalaGrises;
    int espejarHorizontal;
    int espejarVertical;
    int rotarDerecha;
    int rotarIzquierda;
    int concatenarHorizontal;
    int concatenarVertical;
    int comodin;

    // Filtros con porcentaje (valor de 0 a 100 y -1 no solicitado)
    int aumentarContraste;
    int reducirContraste;
    int tonalidadAzul;
    int tonalidadVerde;
    int tonalidadRoja;
    int recortar;
    int achicar;

} t_config;

void liberarMatriz(t_pixel **mat,size_t cf);
t_pixel **crearMatrizDinamica(size_t cf,size_t cc);
int calcularPadding(int ancho);
int leerBmp(const char* ruta, t_metadata* infoBmp, t_pixel*** imagen);
int escribirBmp(const char* ruta, t_metadata* infoBmp, t_pixel** imagen);
unsigned char limitarColor(int num);



#endif // COMPARTIDO_H_INCLUDED
