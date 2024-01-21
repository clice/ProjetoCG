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

/*
 * ESTRUTURA DE VETOR PARA O ALGORITIMO DE SELEÇÃO
 */
typedef struct
{
    int vetor[4];
}VetorSel;

///////////////////////////////////////////////////////////////////

/*
 * DECLARAÇÕES DAS FUNÇÕES
 */
ListaRetas * criarListaRetas();
void imprimirListaRetas(ListaRetas * listaRetas);
void salvarListaRetas(ListaRetas * listaRetas);
void carregarListaRetas();

int adicionarReta(float mouseX, float mouseY, int statusObjeto, ListaRetas * listaRetas);
int excluirReta(int chave, ListaRetas * listaRetas);
int selecionarReta(float mouseX, float mouseY, ListaRetas * listaRetas);
VetorSel * verificarPontoNaReta(float mouseX, float mouseY, float x, float y);
void desenharRetas(ListaRetas * listaRetas);

int transladarReta(int chave, ListaRetas * listaRetas, MatrizTransformacao * matrizTranslacao);
int rotacionarReta(int chave, ListaRetas * listaRetas, MatrizTransformacao * matrizRotacao, MatrizTransformacao * ida, MatrizTransformacao * volta);
int escalarReta(int chave, ListaRetas * listaRetas, MatrizTransformacao * matrizEscalar, MatrizTransformacao * ida, MatrizTransformacao * volta);

#endif // RETA_H
