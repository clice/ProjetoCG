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
    Ponto ponto;   			 // Ponto para armazenar um ponto dos cantos do polígono
    struct PontoPoligono * prox;    // Ponteiro para o próximo ponto dos cantos do polígono
} PontoPoligono;

/*
 * ESTRUTURA PARA O POLÍGONO
 */
typedef struct
{
    int tamanho;   			  //
    Ponto centro;    		  // Ponto para armazenar o ponto central do polígono
    PontoPoligono * inicio;   // PontoPoligono para o início do polígono
} Poligono;

/*
 * ESTRUTURA PARA LISTA DE POLÍGONOS
 */
typedef struct
{
    int qtdPoligonos;    	     	 // Quantidade de polígonos na lista
    Poligono poligonos[MAX_POLIGONOS];   // Dados dos polígonos da lista de polígonos
} ListaPoligonos;

///////////////////////////////////////////////////////////////////

/*
 * DECLARAÇÕES DAS FUNÇÕES
 */
ListaPoligonos * criarListaPoligonos();

int adicionarListaPoligono(float mouseX, float mouseY, int poligono, ListaPoligonos * listaPoligonos);
int excluirPoligono(int poligono, ListaPoligonos * listaPoligonos);
int selecionarPoligono(float mouseX, float mouseY, int aux, ListaPoligonos * listaPoligonos);

void desenharPoligonos(int poligono, ListaPoligonos * listaPoligonos);
void imprimirListaPoligonos(ListaPoligonos * listaPoligonos);
void salvarPoligonos(ListaPoligonos * listaPoligonos);

int transladarPoligono(int poligono, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizTranslacao);
int rotacionarPoligono(int poligono, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizRotacao);
int escalarPoligono(int poligono, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizEscalar);

#endif // POLIGONO_H
