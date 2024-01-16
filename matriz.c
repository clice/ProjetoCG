#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "matriz.h"

/*
 * FUNÇÃO PARA CRIAR UMA MATRIZ COM AS INFORMAÇOES DO PONTO
 */
MatrizPonto * criarMatrizPonto(float x, float y)
{
    MatrizPonto * matrizPonto = (MatrizPonto *)malloc(sizeof(MatrizPonto));
    matrizPonto->matriz[0][0] = x;
    matrizPonto->matriz[1][0] = y;
    matrizPonto->matriz[2][0] = 1.0;
    return matrizPonto;
}

/*
 * ESTRUTURA PARA AS CORES
 */
MatrizPonto * multiplicarMatrizPonto(MatrizPonto * matrizPonto, MatrizTransformacao * matrizTransformacao)
{
    if (matrizTransformacao == NULL || matrizPonto == NULL) {
        return 0;
    }

    else {
        // Inicializando uma MatrizPonto para contar a matriz composta da transformação
        MatrizPonto * matrizComposta = criarMatrizPonto(0.0, 0.0);

        for (int i = 0; i < 3; i++) {
            matrizComposta->matriz[i][0] = matrizTransformacao->matriz[i][0] * matrizPonto->matriz[0][0] + matrizTransformacao->matriz[i][1] * matrizPonto->matriz[1][0] + matrizTransformacao->matriz[i][2] * matrizPonto->matriz[2][0];
        }

        return matrizComposta;
    }
}
