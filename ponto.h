#ifndef PONTO_H
#define PONTO_H

#define MAX_PONTOS 1000

#include "matriz.h"

/*
 * ESTRUTURA PARA AS CORES
 */
typedef struct Cor
{
    float red;     // Valor da cor vermelha
    float green;   // Valor da cor verde
    float blue;    // Valor da cor azul
} Cor;

/*
 * ESTRUTURA PARA O PONTO
 */
typedef struct Ponto
{
    float teta;
    float x;   // Posição na largura
    float y;   // Posição na altura
    Cor cor;   // Estrutura das cores
    int vsele[4];
} Ponto;

/*
 * ESTRUTURA PARA LISTA DE PONTOS
 */
typedef struct ListaPontos
{
    int qtdPontos;              // Quantidade de pontos na lista
    Ponto pontos[MAX_PONTOS];   // Dados dos pontos da lista de pontos
} ListaPontos;

///////////////////////////////////////////////////////////////////

/*
 * DECLARAÇÕES DAS FUNÇÕES
 */
ListaPontos * criarListaPontos();
void imprimirListaPontos(ListaPontos * listaPontos);
void liberarListaPontos(ListaPontos * listaPontos);
void salvarListaPontos(ListaPontos * listaPontos);
void carregarListaPontos();

int adicionarPonto(float mouseX, float mouseY, ListaPontos * listaPontos);
int excluirPonto(int chave, ListaPontos * listaPontos);
int selecionarPonto(float mouseX, float mouseY, ListaPontos * listaPontos);
void desenharPontos(ListaPontos * listaPontos);

int transladarPonto(int chave, ListaPontos * listaPontos, Matriz3Por3 * matrizTranslacaoPonto);
int rotacionarPonto(int chave, ListaPontos * listaPontos, Matriz3Por3 * matrizRotacaoPonto);

#endif // PONTO_H
