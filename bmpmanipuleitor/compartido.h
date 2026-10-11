#ifndef COMPARTIDO_H_INCLUDED
#define COMPARTIDO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "estructuras.h"


t_pixel **crearMatrizDinamica(size_t cf,size_t cc);
void liberarMatriz(t_pixel **mat,size_t cf);



#endif // COMPARTIDO_H_INCLUDED
