#ifndef MATRIZ_H
#define MATRIZ_H

/*
 * ESTRUTURA PARA A MATRIZ DO PONTO
 */
typedef struct MatrizPonto
{
    float matriz[3][1];     // Matriz para armazenar as informações do ponto (largura, altura e cor)
} MatrizPonto;

/*
 * ESTRUTURA PARA A MATRIZ DA TRANSFORMAÇÃO
 */
typedef struct MatrizTransformacao
{
    float matriz[3][3];   // Matriz para o cálculo da transformação realizada
} MatrizTransformacao;

///////////////////////////////////////////////////////////////////

/*
 * DECLARAÇÕES DAS FUNÇÕES
 */
MatrizPonto * criarMatrizPonto(float x, float y);
MatrizPonto * multiplicarMatrizPonto(MatrizPonto * matrizPonto, MatrizTransformacao * matrizTransformacao);

MatrizTransformacao * criarMatrizTransformacao();
MatrizTransformacao * criarMatrizTranslacao(float tX, float tY);
MatrizTransformacao * criarMatrizRotacao(float theta);
MatrizTransformacao * criarMatrizEscalar(float escala);
MatrizTransformacao * multiplicarMatrizesTransformacao(MatrizTransformacao * matrizTransformacao1, MatrizTransformacao * matrizTransformacao2);

#endif // MATRIZ_H
