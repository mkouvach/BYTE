#ifndef COMPARTIDO_H_INCLUDED
#define COMPARTIDO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AZUL  0
#define VERDE 1
#define ROJO  2

#define GRUPO "BYTE"

//Estructura para manejar cada pixel

typedef struct
{
    unsigned char pixel[3];

}t_pixel;

//Estructura para guardar informacion del archivo bmp

typedef struct
{
    unsigned int tamArchivo;
    unsigned int tamEncabezado;
    unsigned int ancho;
    unsigned int alto;
    unsigned short profundidad;

}t_metadata;

//Estructura para interpretar argumentos y su posterior llamado a funciones

typedef struct
{
    // Rutas de las imÃ¡genes

    char rutaImg1[256];
    char rutaImg2[256];
    int cantImagenes;

    // Filtros sin parÃ¡metros (0 = no solicitado, 1 = solicitado)
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


void liberarMatriz(void *mat, size_t cf);
void **crearMatrizDinamica(size_t cf, size_t cc, size_t tamElem);
t_pixel **clonarMatriz(t_pixel **mat,size_t cf, size_t cc);

int calcularPadding(int ancho);
int leerBmp(const char* ruta, t_metadata* infoBmp, t_pixel*** imagen);
int escribirBmp(const char* ruta, t_metadata* infoBmp, t_pixel** imagen);
unsigned char limitarColor(int num);
void inicializarMetadata(t_metadata* meta, unsigned int ancho, unsigned int alto);
void inicializarConfig(t_config* config);
void extraerNombreBase(const char *ruta, char *destino);
int parsearArgumentos(int argc, char *argv [], t_config *config);
int esPorcentajeValido(const char* texto, int* valorSalida);



#endif // COMPARTIDO_H_INCLUDED
