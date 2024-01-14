#ifndef PONTO_H
#define PONTO_H

#include "cor.h"

// ESTRUTURA PARA REPRESENTAR O PONTO
typedef struct {
    float x; // Posição da largura
    float y; // Posição da altura
    Cor cor; // Cor do ponto
} Ponto;

// ESTRUTURA PARA A LISTA DE PONTOS
typedef struct {
    int qtdPontos;      // Quantidade de pontos na lista
    Ponto pontos[1000]; // Vetor de pontos com a estrutura Ponto
} ListaPontos;

ListaPontos * criarListaPontos();

int adicionarPonto(ListaPontos * listaPontos, float x, float y);
int removerPonto(ListaPontos * listaPontos, int ponto);
int selecionarPonto(ListaPontos * listaPontos, float x, float y, int ponto);

void desenharPontos(ListaPontos * listaPontos, int ponto);

int transladarPonto(ListaPontos * listaPontos, int ponto);
int rotacionarPonto(ListaPontos * listaPontos, int ponto);

// int pickPonto(float px, float py, float mx, float my, int t);
// int transladarPonto(Lista_Pontos *, int p, Matriz_Transformacao *);
// int rotacionarPonto(Lista_Pontos *, int p, Matriz_Transformacao *);

#endif // PONTO_H
