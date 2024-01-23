#ifndef RETA_H
#define RETA_H

#define MAX_RETAS 1000

#include "ponto.h"

/*
 * ESTRUTURA PARA A RETA
 */
typedef struct Reta
{
    Ponto inicial;   // Ponto inicial da reta
    Ponto central;   // Ponto central da reta
    Ponto final;     // Ponto final da reta
} Reta;

/*
 * ESTRUTURA PARA LISTA DE RETAS
 */
typedef struct ListaRetas
{
    int qtdRetas;            // Quantidade de retas na lista
    Reta retas[MAX_RETAS];   // Dados das retas da lista de retas
} ListaRetas;

///////////////////////////////////////////////////////////////////

/*
 * DECLARAÇÕES DAS FUNÇÕES
 */
ListaRetas * criarListaRetas();
void imprimirListaRetas(ListaRetas * listaRetas);
void liberarListaRetas(ListaRetas * listaRetas);
void salvarListaRetas(ListaRetas * listaRetas);
void carregarListaRetas();

int adicionarReta(float mouseX, float mouseY, int statusObjeto, ListaRetas * listaRetas);
int excluirReta(int chave, ListaRetas * listaRetas);
int selecionarReta(float mouseX, float mouseY, ListaRetas * listaRetas);
int verificarPontoReta(float mouseX, float mouseY, float x1, float y1, float x2, float y2);
void desenharRetas(ListaRetas * listaRetas);

int transladarReta(int chave, ListaRetas * listaRetas, Matriz3Por3 * matrizTranslacaoReta);
int rotacionarReta(int chave, ListaRetas * listaRetas, Matriz3Por3 * matrizRotacaoReta);
int escalarReta(int chave, ListaRetas * listaRetas, Matriz3Por3 * matrizEscalarReta);
int refletirReta(int chave, ListaRetas * listaRetas, Matriz3Por3 * matrizReflexaoReta);

#endif // RETA_H
