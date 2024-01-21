#ifndef POLIGONO_H
#define POLIGONO_H

#define MAX_POLIGONOS 1000

#include "reta.h"

/*
 * ESTRUTURA PARA OS PONTOS QUE COMPOEM OS CANTOS DO POLÍGONO
 */
typedef struct PontoPoligono
{
    Ponto ponto;   			       // Ponto para armazenar um ponto dos cantos do polígono
    struct PontoPoligono * prox;   // Ponteiro para o próximo ponto dos cantos do polígono
} PontoPoligono;

/*
 * ESTRUTURA PARA O POLÍGONO
 */
typedef struct Poligono
{
    int qtdLados;   		   // Quantos lados tem o polígono
    Ponto centroide;    	   // Ponto para armazenar o ponto central do polígono (centróide)
    PontoPoligono * inicial;   // PontoPoligono para o ponto inicial do polígono
} Poligono;

/*
 * ESTRUTURA PARA LISTA DE POLÍGONOS
 */
typedef struct ListaPoligonos
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
void liberarListaPoligonos(ListaPoligonos * listaPoligonos);
void salvarListaPoligonos(ListaPoligonos * listaPoligonos);
void carregarListaPoligonos();

PontoPoligono * criarPontoPoligono(float mouseX, float mouseY);
void inserirPontoPoligono(PontoPoligono ** pontoPoligonoInicial, float mouseX, float mouseY);
void imprimirPontosPoligono(PontoPoligono * pontoPoligonoInicial);
PontoPoligono * buscarUltimoPontoPoligono(PontoPoligono * pontoPoligonoInicial);

int adicionarPoligono(float mouseX, float mouseY, int statusObjeto, ListaPoligonos * listaPoligonos);
int excluirPoligono(int chave, ListaPoligonos * listaPoligonos);
int selecionarPoligono(float mouseX, float mouseY, ListaPoligonos * listaPoligonos);
// int verificarPontoPoligono(float mouseX, float mouseY, ListaPoligonos * listaPoligonos);
void desenharPoligonos(ListaPoligonos * listaPoligonos);

int transladarPoligono(int chave, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizTranslacaoPoligono);
int rotacionarPoligono(int chave, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizRotacaoPoligono);
int escalarPoligono(int chave, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizEscalarPoligono);

#endif // POLIGONO_H
