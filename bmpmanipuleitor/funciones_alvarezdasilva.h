#ifndef FUNCIONES_ALVAREZDASILVA_H_INCLUDED
#define FUNCIONES_ALVAREZDASILVA_H_INCLUDED
#include "compartido.h"

//Funciones Complementarias
void rellenarMatriz(t_pixel** mat, unsigned int alto, unsigned int ancho);
void copiarImagen(t_pixel** destino, t_pixel** origen, unsigned int alto, unsigned int ancho, unsigned int filaIni, unsigned int colIni);

t_pixel** achicarImagen(t_pixel** matOrig, const t_metadata* metaOrig, t_metadata* metaNueva, int porcentaje);
t_pixel** concatenarHorizontal(t_pixel** mat1, const t_metadata* meta1, t_pixel** mat2, const t_metadata* meta2, t_metadata* metaNueva);
t_pixel** concatenarVertical(t_pixel** mat1, const t_metadata* meta1, t_pixel** mat2, const t_metadata* meta2, t_metadata* metaNueva);


#endif // FUNCIONES_ALVAREZDASILVA_H_INCLUDED
