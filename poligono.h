#ifndef POLIGONO_H
#define POLIGONO_H

#define MAX_POLIGONOS 1000

#include "ponto.h"
#include "matriz.h"

/*
 * ESTRUTURA PARA OS PONTOS QUE COMPOEM OS CANTOS DO POLÍGONO
 */
typedef struct
{
    Ponto ponto;   			       // Ponto para armazenar um ponto dos cantos do polígono
    struct PontoPoligono * prox;   // Ponteiro para o próximo ponto dos cantos do polígono
} PontoPoligono;

/*
 * ESTRUTURA PARA O POLÍGONO
 */
typedef struct
{
    int tamanho;   			  // Quantos lados tem o polígono
    Ponto centro;    		  // Ponto para armazenar o ponto central do polígono
    PontoPoligono * inicial;  // PontoPoligono para o ponto inicial do polígono
} Poligono;

/*
 * ESTRUTURA PARA LISTA DE POLÍGONOS
 */
typedef struct
{
    int qtdPoligonos;    	     	     // Quantidade de polígonos na lista
    Poligono poligonos[MAX_POLIGONOS];   // Dados dos polígonos da lista de polígonos
} ListaPoligonos;

///////////////////////////////////////////////////////////////////

/*
 * DECLARAÇÕES DAS FUNÇÕES
 */
ListaPoligonos * criarListaPoligonos();
void imprimirListaPoligonos(ListaPoligonos * listaPoligonos);
void salvarListaPoligonos(ListaPoligonos * listaPoligonos);
void carregarListaPoligonos();

PontoPoligono * criarPontoPoligono(float mouseX, float mouseY);
PontoPoligono * ultimoPontoPoligono(PontoPoligono * auxPontoPoligono);
// void imprimirPontosPoligono(ListaPoligonos * listaPoligonos);

int adicionarPoligono(float mouseX, float mouseY, int statusObjeto, ListaPoligonos * listaPoligonos);
int excluirPoligono(int chave, ListaPoligonos * listaPoligonos);
int selecionarPoligono(float mouseX, float mouseY, ListaPoligonos * listaPoligonos);
void desenharPoligonos(ListaPoligonos * listaPoligonos);

int transladarPoligono(int chave, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizTranslacao);
int rotacionarPoligono(int chave, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizRotacao);
int escalarPoligono(int chave, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizEscalar);

#endif // POLIGONO_H
