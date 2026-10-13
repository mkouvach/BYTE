#ifndef FUNCIONES_RODRIGUEZ_H_INCLUDED
#define FUNCIONES_RODRIGUEZ_H_INCLUDED
#include "compartido.h"

void todoRojo(t_pixel **mat, int alto, int ancho);
void escalaDeGrises(t_pixel **mat, int alto, int ancho);
void aumentarContraste(t_pixel **mat, int alto, int ancho, int porcentaje);

#endif // FUNCIONES_RODRIGUEZ_H_INCLUDED
