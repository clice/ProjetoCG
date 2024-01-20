#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "poligono.h"

/*
 * FUNÇÃO PARA CRIAR A LISTA DE POLÍGONOS
 */
ListaPoligonos * criarListaPoligonos()
{
	ListaPoligonos * listaPoligonos = (ListaPoligonos *)malloc(sizeof(ListaPoligonos));
	listaPoligonos->qtdPoligonos = 0;
	return listaPoligonos;
}

/*
 * FUNÇÃO PARA IMPRIMIR LISTA DE POLÍGONOS
 */
void imprimirListaPoligonos(ListaPoligonos * listaPoligonos)
{
    // Se a lista de polígonos estiver vazia ou a quantidade de polígomos for zero
	if (listaPoligonos == NULL || listaPoligonos->qtdPoligonos == 0) {
		printf("Lista de poligonos nao foi criada ou esta cheia! Não é possivel imprimir os poligonos!\n");
		return 0;
	}
	//
	else {
		return 1;
	}
}

/*
 * FUNÇÃO PARA SALVAR A LISTA DE POLÍGONOS
 */
void salvarListaPoligonos(ListaPoligonos * listaPoligonos)
{
    
}

/*
 * FUNÇÃO PARA CARREGAR A LISTA DE POLÍGONOS NA TELA
 */
void carregarListaPoligonos()
{
    
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA ADICIONAR UM POLÍGONO A TELA
 */
int adicionarPoligono(float mouseX, float mouseY, int poligono, ListaPoligonos * listaPoligonos)
{
	return 0;
}

/*
 * FUNÇÃO PARA EXCLUIR UM POLÍGONO DA TELA
 */
int excluirPoligono(int poligono, ListaPoligonos * listaPoligonos)
{
	return 0;
}

/*
 * FUNÇÃO PARA SELECIONAR UM POLÍGONO DA TELA
 */
int selecionarPoligono(float mouseX, float mouseY, ListaPoligonos * listaPoligonos)
{
    return 0;
}

/*
 * FUNÇÃO PARA DESENHAR OS POLÍGONOS NA TELA
 */
void desenharPoligonos(ListaPoligonos * listaPoligonos)
{
    
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA TRANSLADAR UM POLÍGONO (ARRASTAR E SOLTAR)
 */
int transladarPoligono(int chave, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizTranslacao)
{
    return 0;
}

/*
 * FUNÇÃO PARA ROTACIONAR UM POLÍGONO
 */
int rotacionarPoligono(int chave, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizRotacao)
{
    return 0;
}

/*
 * FUNÇÃO PARA ESCALAR UM POLÍGONO
 */
int escalarPoligono(int chave, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizEscalar)
{
    return 0;
}