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
 * FUNÇÃO PARA REALIZAR AS MULTIPLICAÇÕES DAS TRANSFORMAÇÕES
 */
Matriz3Por3 * multiplicarMatrizComposta(float centralX, float centralY, Matriz3Por3 * matrizTransformacao)
{
    // Criar a matriz3Por3 para auxiliar nos cálculos
    // Primeiramente, a matriz é uma matriz identidade
    Matriz3Por3 * matrizComposta = criarMatriz3Por3();

    // Criar matriz translação com os pontos centrais
    Matriz3Por3 * matrizCentral = criarMatrizTranslacao(centralX, centralY);

    // Realizar a multiplicação das matrizes
    // Primeiro passo da transformação, multiplicar a matriz translação central pela matriz transformação
    matrizComposta = multiplicarMatrizes3Por3(matrizCentral, matrizTransformacao);

    // Criar matriz translação com os pontos da diferença entre a origem e o centro
    Matriz3Por3 * matrizOrigemCentral = criarMatrizTranslacao(0 - centralX, 0 - centralY);

    // Realizar a multiplicação das matrizes
    // Segundo passo da transformação, multiplicar a matriz resultante pela matriz referente a origem
    matrizComposta = multiplicarMatrizes3Por3(matrizComposta, matrizOrigemCentral);

    return matrizComposta;
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA CRIAR A MATRIZ DA TRANSLAÇÃO
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
 * FUNÇÃO PARA CRIAR A MATRIZ DA ROTAÇÃO
 */
Matriz3Por3 * criarMatrizRotacao(float anguloTheta)
{
    // Inicializando uma matriz3Por3
    Matriz3Por3 * matrizRotacao = criarMatriz3Por3();

    // Inicializando a matriz para a rotação
    matrizRotacao->matriz[0][0] = cosf(anguloTheta);
    matrizRotacao->matriz[0][1] = -sinf(anguloTheta);
    matrizRotacao->matriz[1][0] = sinf(anguloTheta);
    matrizRotacao->matriz[1][1] = cosf(anguloTheta);

    return matrizRotacao;
}

/*
 * FUNÇÃO PARA CRIAR A MATRIZ ESCALAR
 */
Matriz3Por3 * criarMatrizEscalar(float escala)
{
    Matriz3Por3 * matrizEscalar = criarMatriz3Por3();

    // Inicializando a matriz para a escala
    matrizEscalar->matriz[0][0] = escala;
    matrizEscalar->matriz[1][1] = escala;

    return matrizEscalar;
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA CRIAR A MATRIZ DA TRANSLAÇÃO INVERSA
 */
Matriz3Por3 * criarMatrizTranslacaoInversa(float finalX, float finalY)
{
    // Inicializando uma matriz3Por3
    Matriz3Por3 * matrizTranslacaoInversa = criarMatriz3Por3();

    // Inicializando a matriz para a translação inversa
    matrizTranslacaoInversa->matriz[0][2] = -finalX;
    matrizTranslacaoInversa->matriz[1][2] = -finalY;

    return matrizTranslacaoInversa;
}

/*
 * FUNÇÃO PARA CRIAR A MATRIZ DA ROTAÇÃO INVERSA
 */
Matriz3Por3 * criarMatrizRotacaoInversa(float anguloTheta)
{
    // Inicializando uma matriz3Por3
    Matriz3Por3 * matrizRotacaoInversa = criarMatriz3Por3();

    // Inicializando a matriz para a rotação inversa
    matrizRotacaoInversa->matriz[0][0] = cosf(anguloTheta);
    matrizRotacaoInversa->matriz[0][1] = sinf(anguloTheta);
    matrizRotacaoInversa->matriz[1][0] = -sinf(anguloTheta);
    matrizRotacaoInversa->matriz[1][1] = cosf(anguloTheta);

    return matrizRotacaoInversa;
}

/*
 * FUNÇÃO PARA CRIAR A MATRIZ ESCALAR INVERSA
 */
Matriz3Por3 * criarMatrizEscalarInversa(float escala)
{
    Matriz3Por3 * matrizEscalarInversa = criarMatriz3Por3();

    // Inicializando a matriz para a escala inversa
    matrizEscalarInversa->matriz[0][0] = 1 / escala;
    matrizEscalarInversa->matriz[1][1] = 1 / escala;

    return matrizEscalarInversa;
}