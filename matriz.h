#ifndef MATRIZ_H
#define MATRIZ_H

// ESTRUTURA PARA REPRESENTAR A MATRIZ
typedef struct {
    float matriz[3][3];
} Matriz;

// ESTRUTURA PARA A LISTA DE PONTOS
typedef struct {
    float matriz[3][1];
} MatrizPonto;

MatrizPonto * criarMatrizPonto(float x, float y);
MatrizPonto * multiplicarMatrizPonto(Matriz * matriz, MatrizPonto * matrizPonto);

// Matriz_Transformacao* criarMatrizTransformacao();
// Matriz_Transformacao* criarMatrizTranslacao(float tx, float ty);
// Matriz_Transformacao* criarMatrizRotacao(float theta);
// Matriz_Transformacao* criarMatrizEscalar(float scale);
// Matriz_Transformacao* multiplicarMatrizesTransformacao(Matriz_Transformacao *, Matriz_Transformacao *);

#endif // MATRIZ_H
