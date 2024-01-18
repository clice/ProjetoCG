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
int selecionarPoligono(float mouseX, float mouseY, int aux, ListaPoligonos * listaPoligonos)
{
    return 0;
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA DESENHAR OS POLÍGONOS NA TELA
 */
void desenharPoligonos(int poligono, ListaPoligonos * listaPoligonos)
{
    
}

/*
 * FUNÇÃO PARA IMPRIMIR LISTA DE POLÍGONOS
 */
void imprimirListaPoligonos(ListaPoligonos * listaPoligonos)
{
    
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA SALVAR A LISTA DE POLÍGONOS
 */
void salvarPoligonos(ListaPoligonos * listaPoligonos)
{
    
}

/*
 * FUNÇÃO PARA CARREGAR A LISTA DE POLÍGONOS NA TELA
 */
void carregarPoligonos(ListaPoligonos * listaPoligonos)
{
    
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA TRANSLADAR UM POLÍGONO (ARRASTAR E SOLTAR)
 */
int transladarPoligono(int poligono, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizTranslacao)
{
    return 0;
}

/*
 * FUNÇÃO PARA ROTACIONAR UM POLÍGONO
 */
int rotacionarPoligono(int poligono, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizRotacao)
{
    return 0;
}

/*
 * FUNÇÃO PARA ESCALAR UM POLÍGONO
 */
int escalarPoligono(int poligono, ListaPoligonos * listaPoligonos, MatrizTransformacao * matrizEscalar)
{
    return 0;
}