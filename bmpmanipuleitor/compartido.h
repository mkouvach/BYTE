#ifndef COMPARTIDO_H_INCLUDED
#define COMPARTIDO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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



void liberarMatriz(t_pixel **mat,size_t cf);
t_pixel **crearMatrizDinamica(size_t cf,size_t cc);
int calcularPadding(int ancho);
int leerBmp(const char* ruta, t_metadata* infoBmp, t_pixel*** imagen);
int escribirBmp(const char* ruta, t_metadata* infoBmp, t_pixel** imagen);
unsigned char limitarColor(int num);


int porcentajeEsCero(unsigned int ancho,unsigned int alto);



#endif // COMPARTIDO_H_INCLUDED
