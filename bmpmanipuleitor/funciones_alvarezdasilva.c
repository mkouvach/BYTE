#include "funciones_alvarezdasilva.h"
#include "compartido.h"

//FUNCIONES COMPLEMENTARIAS

// Pinta toda la matriz con un color neutro (ni blanco ni negro)
void rellenarMatriz(t_pixel** mat, unsigned int alto, unsigned int ancho)
{
    t_pixel relleno;
    relleno.pixel[AZUL] = 180;
    relleno.pixel[VERDE] = 130;
    relleno.pixel[ROJO] = 70;

    for(unsigned int i = 0; i < alto; i++)
    {
        for(unsigned int j = 0; j < ancho; j++)
        {
            mat[i][j] = relleno;
        }
    }
}

// Copia imagen origen (alto x ancho) en destino desde (filaIni, colIni)
void copiarImagen(t_pixel** destino, t_pixel** origen, unsigned int alto, unsigned int ancho, unsigned int filaIni, unsigned int colIni)
{
    for(unsigned int i = 0; i < alto; i++)
    {
        for(unsigned int j = 0; j < ancho; j++)
        {
            destino[filaIni + i][colIni + j] = origen[i][j];
        }
    }
}

//ACHICAR (PORCENTAJE)
t_pixel** achicarImagen(t_pixel** matOrig, const t_metadata* metaOrig, t_metadata* metaNueva, int porcentaje)
{
    //Validamos si porcentaje == 0, no realiza cambios, la matriz/imagen se mantiene igual
    if(porcentaje == 0)
        porcentaje = 100;

    unsigned int nuevoAncho = (metaOrig->ancho * (unsigned int) porcentaje) / 100;
    unsigned int nuevoAlto = (metaOrig->alto * (unsigned int) porcentaje) / 100;

    //No dejamos dimensiones en 0
    if(nuevoAncho == 0)
        nuevoAncho = 1;
    if(nuevoAlto == 0)
        nuevoAlto = 1;

    t_pixel** nueva = crearMatrizDinamica(nuevoAlto, nuevoAncho);
    if(!nueva)
    {
        printf("Error: Falló la asignación de memoria para crear la matriz.\n");
        return NULL;
    }

    unsigned int i, j;

    //Recorrmos matriz destino y calculamos con cual quedarnos de la matriz original.
    for(i=0; i < nuevoAlto; i++)
    {
        unsigned int origI = (i * metaOrig->alto) / nuevoAlto;

        for(j=0; j < nuevoAncho; j++)
        {
            unsigned int origJ = (j * metaOrig->ancho) / nuevoAncho;
            nueva[i][j] = matOrig[origI][origJ];
        }
    }

    inicializarMetadata(metaNueva, nuevoAncho, nuevoAlto);
    return nueva;
}

//CONCATENAR HORIZONTAL (2 IMAGENES)
//Imagen/Mat A Izquierda - Imagen/Mat B Derecha
t_pixel** concatenarHorizontal(t_pixel** mat1, const t_metadata* meta1, t_pixel** mat2, const t_metadata* meta2, t_metadata* metaNueva)
{
    unsigned int anchoTotal = meta1->ancho + meta2->ancho;
    unsigned int altoTotal;

    if(meta1->alto > meta2->alto)
    {
        altoTotal = meta1->alto;
    }
    else
    {
        altoTotal = meta2->alto;
    }

    t_pixel** nueva = crearMatrizDinamica(altoTotal, anchoTotal);
    if(!nueva)
    {
        printf("Error: Falló la asignación de memoria para crear la matriz.\n");
        return NULL;
    }

    //rellenamos por si una de las dos imagenes es de menor altura
    rellenarMatriz(nueva, altoTotal, anchoTotal);

    copiarImagen(nueva, mat1, meta1->alto, meta1->ancho, altoTotal - meta1->alto, 0);
    //comienza donde finaliza el ancho de la primer imagen
    copiarImagen(nueva, mat2, meta2->alto, meta2->ancho, altoTotal - meta2->alto, meta1->ancho);

    inicializarMetadata(metaNueva, anchoTotal, altoTotal);
    return nueva;
}


//CONCATENAR VERTICAL (2 IMAGENES)
//Imagen/Mat A Arriba - Imagen/Mat B Abajo
t_pixel** concatenarVertical(t_pixel** mat1, const t_metadata* meta1, t_pixel** mat2, const t_metadata* meta2, t_metadata* metaNueva)
{
    unsigned int altoTotal  = meta1->alto + meta2->alto;
    unsigned int anchoTotal;

    if(meta1->ancho > meta2->ancho)
    {
        anchoTotal = meta1->ancho;
    }
    else
    {
        anchoTotal = meta2->ancho;
    }

    t_pixel** nueva = crearMatrizDinamica(altoTotal, anchoTotal);
    if(!nueva)
    {
        printf("Error: Falló la asignación de memoria para crear la matriz.\n");
        return NULL;
    }

    //rellenamos por si una de las dos imagenes es de menor ancho
    rellenarMatriz(nueva, altoTotal, anchoTotal);

    copiarImagen(nueva, mat2, meta2->alto, meta2->ancho, 0, 0);
    //comienza donde finaliza el alto de la primer imagen
    copiarImagen(nueva, mat1, meta1->alto, meta1->ancho, meta2->alto, 0);

    inicializarMetadata(metaNueva, anchoTotal, altoTotal);
    return nueva;
}

//COMODIN
//BLUR (promedio de vecindario 3x3)
int comodinBlur(t_pixel** mat, int alto, int ancho)
{
    t_pixel** nueva = clonarMatriz(mat, alto, ancho);
    if(!nueva)
    {
        printf("Error: Falló la asignación de memoria para crear la matriz.\n");
        return 0;
    }

    //Recorremos cada pixel
    for(int i = 0; i<alto; i++)
    {
        for(int j = 0; j<ancho; j++)
        {
            int sumaB = 0, sumaG = 0, sumaR = 0, cantidad = 0;

            //Recorremos la ventana 3x3 alrededor de (i, j)
            for(int di = -1; di <= 1; di++)
            {
                for(int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Solo vecinos que existen (limites en bordes y esquinas)
                    if(ni >= 0 && ni < alto && nj >= 0 && nj < ancho)
                    {
                        sumaB += nueva[ni][nj].pixel[AZUL];
                        sumaG += nueva[ni][nj].pixel[VERDE];
                        sumaR += nueva[ni][nj].pixel[ROJO];
                        cantidad++;
                    }
                }
            }

            mat[i][j].pixel[AZUL]  = limitarColor(sumaB / cantidad);
            mat[i][j].pixel[VERDE] = limitarColor(sumaG / cantidad);
            mat[i][j].pixel[ROJO]  = limitarColor(sumaR / cantidad);
        }
    }

    liberarMatriz(nueva, alto);
    return 1;
}
