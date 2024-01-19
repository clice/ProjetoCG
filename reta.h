#ifndef RETA_H
#define RETA_H

#define MAX_RETAS 1000

#include "ponto.h"
#include "matriz.h"

/*
 * ESTRUTURA PARA A RETA
 */
typedef struct
{
    Ponto inicial;   // Ponto inicial da reta
    Ponto central;   // Ponto central da reta
    Ponto final;     // Ponto final da reta
} Reta;

/*
 * ESTRUTURA PARA LISTA DE RETAS
 */
typedef struct
{
    int qtdRetas;            // Quantidade de retas na lista
    Reta retas[MAX_RETAS];   // Dados das retas da lista de retas
} ListaRetas;

///////////////////////////////////////////////////////////////////

/*
 * DECLARAÇÕES DAS FUNÇÕES
 */
ListaRetas * criarListaRetas();

int adicionarReta(float x, float y, int aux, ListaRetas * listaRetas);
int excluirReta(int reta, ListaRetas * listaRetas);
int selecionarReta(float mouseX, float mouseY, int aux, ListaRetas * listaRetas);

void desenharRetas(int reta, ListaRetas * listaRetas);
void imprimirListaRetas(ListaRetas * listaRetas);

void salvarRetas(ListaRetas * listaRetas);
void carregarRetas(ListaRetas * listaRetas);

int transladarReta(int reta, ListaRetas * listaRetas, MatrizTransformacao * matrizTranslacao);
int rotacionarReta(int reta, ListaRetas * listaRetas, MatrizTransformacao * matrizRotacao);
int escalarReta(int reta, ListaRetas * listaRetas, MatrizTransformacao * matrizEscalar);

#endif // RETA_H