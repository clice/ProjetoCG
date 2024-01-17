#ifndef PONTO_H
#define PONTO_H

#define MAX_PONTOS 1000

#include "matriz.h"

/*
 * ESTRUTURA PARA AS CORES
 */
typedef struct
{
    float red;     // Valor da cor vermelha
    float green;   // Valor da cor verde
    float blue;    // Valor da cor azul
} Cor;

/*
 * ESTRUTURA PARA O PONTO
 */
typedef struct
{
    float x;   // Posição na largura
    float y;   // Posição na altura
    Cor cor;   // Estrutura das cores
} Ponto;

/*
 * ESTRUTURA PARA LISTA DE PONTOS
 */
typedef struct
{
    int qtdPontos;    			// Quantidade de pontos na lista
    Ponto pontos[MAX_PONTOS];   // Dados dos pontos da lista de pontos
} ListaPontos;

///////////////////////////////////////////////////////////////////

/*
 * DECLARAÇÕES DAS FUNÇÕES
 */
ListaPontos * criarListaPontos();

int adicionarPonto(float x, float y, ListaPontos * listaPontos);
int excluirPonto(int ponto, ListaPontos * listaPontos);
int selecionarPonto(float mouseX, float mouseY, int aux, ListaPontos * listaPontos);

void desenharPontos(int ponto, ListaPontos * listaPontos);
void imprimirListaPontos(ListaPontos * listaPontos);
void salvarPontos(ListaPontos * listaPontos);

int transladarPonto(int ponto, ListaPontos * listaPontos, MatrizTransformacao * matrizTranslacao);
int rotacionarPonto(int ponto, ListaPontos * listaPontos, MatrizTransformacao * matrizRotacao);

#endif // PONTO_H
