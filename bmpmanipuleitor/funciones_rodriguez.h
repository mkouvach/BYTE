#ifndef FUNCIONES_RODRIGUEZ_H_INCLUDED
#define FUNCIONES_RODRIGUEZ_H_INCLUDED
#include "compartido.h"

void todoRojo(t_pixel **mat, int alto, int ancho);
void escalaDeGrises(t_pixel **mat, int alto, int ancho);
void aumentarContraste(t_pixel **mat, int alto, int ancho, int porcentaje);
void reducirContraste(t_pixel **mat, int alto, int ancho, int porcentaje);
void espejarHorizontal(t_pixel **mat, int alto, int ancho);

#endif // FUNCIONES_RODRIGUEZ_H_INCLUDED
