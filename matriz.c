#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "matriz.h"

/*
 * FUN��O PARA CRIAR UMA MATRIZ COM AS INFORMA�OES DO PONTO
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
 * FUN��O PARA MULTIPLIZAR A MATRIZ PONTO PARA TRANSFORMA��O
 */
MatrizPonto * multiplicarMatrizPonto(MatrizPonto * matrizPonto, MatrizTransformacao * matrizTransformacao)
{
    if (matrizTransformacao == NULL || matrizPonto == NULL) {
        return 0;
    }

    else {
        // Inicializando uma MatrizPonto para contar a matriz composta da transforma��o
        MatrizPonto * matrizComposta = criarMatrizPonto(0.0, 0.0);

        for (int i = 0; i < 3; i++) {
            matrizComposta->matriz[i][0] = matrizTransformacao->matriz[i][0] * matrizPonto->matriz[0][0] + matrizTransformacao->matriz[i][1] * matrizPonto->matriz[1][0] + matrizTransformacao->matriz[i][2] * matrizPonto->matriz[2][0];
        }

        return matrizComposta;
    }
}

///////////////////////////////////////////////////////////////////

/*
 * FUN��O PARA CRIAR A MATRIZ DA TRANSFORMA��O
 */
MatrizTransformacao * criarMatrizTransformacao()
{
    MatrizTransformacao * matrizTransformacao = (MatrizTransformacao *)malloc(sizeof(MatrizTransformacao));

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) matrizTransformacao->matriz[i][j] = 1;
            else matrizTransformacao->matriz[i][j] = 0;
        }
    }

    return matrizTransformacao;
}

/*
 * FUN��O PARA CRIAR A MATRIZ DA TRANSFORMA��O
 */
MatrizTransformacao * criarMatrizTranslacao(float tX, float tY)
{
    MatrizTransformacao * matrizTranslacao = criarMatrizTransformacao();
    matrizTranslacao->matriz[0][2] = tX;
    matrizTranslacao->matriz[1][2] = tY;
    return matrizTranslacao;
}

/*
 * FUN��O PARA CRIAR A MATRIZ DA TRANSFORMA��O
 */
MatrizTransformacao * criarMatrizRotacao(float theta)
{
    MatrizTransformacao * matrizRotacao = criarMatrizTransformacao();
    matrizRotacao->matriz[0][0] = cosf(theta);
    matrizRotacao->matriz[0][1] = -sinf(theta);
    matrizRotacao->matriz[1][0] = sinf(theta);
    matrizRotacao->matriz[1][1] = cosf(theta);
    return matrizRotacao;
}

/*
 * FUN��O PARA CRIAR A MATRIZ DA TRANSFORMA��O
 */
MatrizTransformacao * criarMatrizEscalar(float escala)
{
    MatrizTransformacao * matrizEscalar = criarMatrizTransformacao();
    matrizEscalar->matriz[0][0] = escala;
    matrizEscalar->matriz[1][1] = escala;
    return matrizEscalar;
}

/*
 * FUN��O PARA CRIAR A MATRIZ DA TRANSFORMA��O
 */
MatrizTransformacao * multiplicarMatrizesTransformacao(MatrizTransformacao * matrizTransformacao1, MatrizTransformacao * matrizTransformacao2)
{
    if (matrizTransformacao1 == NULL || matrizTransformacao2 == NULL) {
        return 0;
    }
    else {
        MatrizTransformacao * matrizComposta = criarMatrizTransformacao();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                matrizComposta->matriz[i][j] = matrizTransformacao1->matriz[i][0] * matrizTransformacao2->matriz[0][j] + matrizTransformacao1->matriz[i][1] * matrizTransformacao2->matriz[1][j] + matrizTransformacao1->matriz[i][2] * matrizTransformacao2->matriz[2][j];
            }
        }

        return matrizComposta;
    }
}
