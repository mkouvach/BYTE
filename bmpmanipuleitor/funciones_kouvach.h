#ifndef FUNCIONES_KOUVACH_H_INCLUDED
#define FUNCIONES_KOUVACH_H_INCLUDED
#include "compartido.h"


void espejarVertical(t_pixel **mat,int alto);
t_pixel** recortarImagen(t_pixel** matOrig, const t_metadata* metaOrig, t_metadata* metaNueva, int porcentaje);




#endif // FUNCIONES_KOUVACH_H_INCLUDED
