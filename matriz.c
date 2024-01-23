#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "matriz.h"

/*
 * FUNÇÃO PARA CRIAR UMA MATRIZ 3x1 COM AS INFORMAÇÕES DO PONTO
 */
Matriz3Por1 * criarMatriz3Por1(float x, float y)
{
    Matriz3Por1 * matriz3Por1 = (Matriz3Por1 *)malloc(sizeof(Matriz3Por1));

    // Inicializando a matriz3Por1 com os valores do ponto nos eixo x e y
    matriz3Por1->matriz[0][0] = x;
    matriz3Por1->matriz[1][0] = y;
    matriz3Por1->matriz[2][0] = 1.0;

    return matriz3Por1;
}

/*
 * FUNÇÃO PARA MULTIPLICAR UMA MATRIZ 3x3 POR UMA MATRIZ 3x1
 */
Matriz3Por1 * multiplicarMatriz3Por3PorMatriz3Por1(Matriz3Por3 * matriz3Por3, Matriz3Por1 * matriz3Por1)
{
    // Caso as variáveis passadas não tenham dados
    if (matriz3Por3 == NULL || matriz3Por1 == NULL) {
        return 0;
    }
    // Multiplicar matriz3Por3 por matriz3Por1
    else {
        // Inicializando uma matriz3Por1 para contar a matriz composta da transformação
        Matriz3Por1 * matrizComposta = criarMatriz3Por1(0.0, 0.0);

        // Laço para percorrer as linhas da matriz
        for (int i = 0; i < 3; i++) {
            // Realizando a multiplicação de uma matriz3Por3 por uma matriz3Por1
            matrizComposta->matriz[i][0] = matriz3Por3->matriz[i][0] * matriz3Por1->matriz[0][0] + matriz3Por3->matriz[i][1] * matriz3Por1->matriz[1][0] + matriz3Por3->matriz[i][2] * matriz3Por1->matriz[2][0];
        }

        return matrizComposta;
    }
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA CRIAR UMA MATRIZ 3x3 INICIALIZANDO COMO MATRIZ IDENTIDADE
 */
Matriz3Por3 * criarMatriz3Por3()
{
    Matriz3Por3 * matriz3Por3 = (Matriz3Por3 *)malloc(sizeof(Matriz3Por3));

    // Inicializando a matriz3Por3
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Se a linha for igual a coluna inicializa com 1, caso contrário com 0
            if (i == j) {
                matriz3Por3->matriz[i][j] = 1;
            } else {
                matriz3Por3->matriz[i][j] = 0;
            }
        }
    }

    return matriz3Por3;
}

/*
 * FUNÇÃO PARA MULTIPLICAR UMA MATRIZ TRANSFORMAÇÃO 3x3 POR OUTRA MATRIZ TRANSFORMAÇÃO 3X3
 */
Matriz3Por3 * multiplicarMatrizes3Por3(Matriz3Por3 * matriz1, Matriz3Por3 * matriz2)
{
    // Caso as variáveis passadas não tenham dados
    if (matriz1 == NULL || matriz2 == NULL) {
        return 0;
    }
    // Multiplicar duas Matriz3Por3
    else {
        Matriz3Por3 * matrizComposta = criarMatriz3Por3();

        // Laço para percorrer as linhas da matriz
        for (int i = 0; i < 3; i++) {
            // Laço para percorrer as colunas da matriz
            for (int j = 0; j < 3; j++) {
                matrizComposta->matriz[i][j] = matriz1->matriz[i][0] * matriz2->matriz[0][j] + matriz1->matriz[i][1] * matriz2->matriz[1][j] + matriz1->matriz[i][2] * matriz2->matriz[2][j];
            }
        }

        return matrizComposta;
    }
}


///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA CRIAR A MATRIZ DA TRANSLAÇÃO COM OS PONTOS CORRETOS
 */
Matriz3Por3 * criarMatrizTranslacao(float finalX, float finalY)
{
    // Inicializando uma matriz3Por3
    Matriz3Por3 * matrizTranslacao = criarMatriz3Por3();

    // Inicializando a matriz para a translação
    matrizTranslacao->matriz[0][2] = finalX;
    matrizTranslacao->matriz[1][2] = finalY;

    return matrizTranslacao;
}

/*
 * FUNÇÃO PARA CRIAR A MATRIZ DA ROTAÇÃO COM OS ÂNGULOS CORRETOS
 */
Matriz3Por3 * criarMatrizRotacao(float theta)
{
    // Inicializando uma matriz3Por3
    Matriz3Por3 * matrizRotacao = criarMatriz3Por3();

    // Inicializando a matriz para a rotação
    matrizRotacao->matriz[0][0] = cosf(theta);
    matrizRotacao->matriz[0][1] = -sinf(theta);
    matrizRotacao->matriz[1][0] = sinf(theta);
    matrizRotacao->matriz[1][1] = cosf(theta);

    return matrizRotacao;
}

/*
 * FUNÇÃO PARA CRIAR A MATRIZ ESCALAR COM AS ESCALAS CORRETAS
 */
Matriz3Por3 * criarMatrizEscalar(float escala)
{
    Matriz3Por3 * matrizEscalar = criarMatriz3Por3();

    // Inicializando a matriz para a escala
    matrizEscalar->matriz[0][0] = escala;
    matrizEscalar->matriz[1][1] = escala;

    return matrizEscalar;
}

Matriz3Por3 * testeMatriz(float centralX, float centralY, Matriz3Por3 * matriz)
{
    // Criar a Matriz3Por3 para auxiliar nos cálculos
    // Primeiramente, a matriz é uma matriz identidade
    Matriz3Por3 * matrizComposta = criarMatriz3Por3();

    // 
    Matriz3Por3 * matrizCentral = criarMatrizTranslacao(centralX, centralY);

    matrizComposta = multiplicarMatrizes3Por3(matrizComposta, matriz);

    return matrizComposta;
}
