#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "matriz.h"

/*
 *
*/
MatrizPonto * criarMatrizPonto(float x, float y)
{
    MatrizPonto * matrizPonto = (MatrizPonto *)malloc(sizeof(MatrizPonto));
    matrizPonto->matriz[0][0] = x;     //
    matrizPonto->matriz[1][0] = y;     //
    matrizPonto->matriz[2][0] = 1.0;   //
    return matrizPonto;
}

/*
 *
*/
MatrizPonto * multiplicarMatrizPonto(Matriz * matriz, MatrizPonto * matrizPonto)
{
    if (matriz == NULL || matrizPonto == NULL) {
        return 0;
    } else {
        MatrizPonto * matrizComposta = criarMatrizPonto(0, 0);

        for (int i = 0; i < 3; i++) {
            matrizComposta->matriz[i][0] = matriz->matriz[i][0] * matrizPonto->matriz[0][0] + matriz->matriz[i][1] * matrizPonto->matriz[1][0] + matriz->matriz[i][2] * matrizPonto->matriz[2][0];
        }

        return matrizComposta;
    }
}
