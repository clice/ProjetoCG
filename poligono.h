#ifndef POLIGONO_H
#define POLIGONO_H

#define MAX_POLIGONOS 1000

#include <stdbool.h>

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
void salvarListaPoligonos(const char * nomeArquivoPoligonos, ListaPoligonos * listaPoligonos);
void carregarListaPoligonos(const char * nomeArquivoPoligonos, ListaPoligonos * listaPoligonos, ListaPoligonos * listaPoligonosArquivo);

PontoPoligono * criarPontoPoligono(float mouseX, float mouseY);
void inserirPontoPoligono(PontoPoligono ** pontoPoligonoInicial, float mouseX, float mouseY);
void imprimirPontosPoligono(PontoPoligono * pontoPoligonoInicial);
PontoPoligono * buscarUltimoPontoPoligono(PontoPoligono * pontoPoligonoInicial);

int adicionarPoligono(float mouseX, float mouseY, int statusObjeto, ListaPoligonos * listaPoligonos);
void finalizarPoligono(int statusObjeto, ListaPoligonos * listaPoligonos);
void calcularCentroidePoligono(int chave, ListaPoligonos * listaPoligonos);
int excluirPoligono(int chave, ListaPoligonos * listaPoligonos);
int selecionarPoligono(float mouseX, float mouseY, ListaPoligonos * listaPoligonos);
bool verificarPontoPoligono(float mouseX, float mouseY, Poligono * poligono);
void desenharPoligonos(ListaPoligonos * listaPoligonos);

int transladarPoligono(int chave, ListaPoligonos * listaPoligonos, Matriz3Por3 * matrizTranslacaoPoligono);
int rotacionarPoligono(int chave, ListaPoligonos * listaPoligonos, Matriz3Por3 * matrizRotacaoPoligono);
int escalarPoligono(int chave, ListaPoligonos * listaPoligonos, Matriz3Por3 * matrizEscalarPoligono);
int refletirPoligono(int chave, ListaPoligonos * listaPoligonos, Matriz3Por3 * matrizReflexaoPoligono);
int cisalharPoligono(int chave, ListaPoligonos * listaPoligonos, Matriz3Por3 * matrizCisalharPoligono);

#endif // POLIGONO_H
