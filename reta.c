#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "reta.h"

/*
 * FUNÇÃO PARA CRIAR A LISTA DE RETAS
 */
ListaRetas * listaRetas()
{
	ListaRetas * listaRetas = (ListaRetas *)malloc(sizeof(ListaRetas));
	listaRetas->qtdRetas = 0;
	return listaRetas;
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA ADICIONAR UMA RETA A TELA
 */
int adicionarReta(float mouseX, float mouseY, int reta, ListaRetas * listaRetas)
{
	return 0;
}

/*
 * FUNÇÃO PARA EXCLUIR UMA RETA DA TELA
 */
int excluirReta(int reta, ListaRetas * listaRetas)
{
	return 0;
}

/*
 * FUNÇÃO PARA SELECIONAR UMA RETA DA TELA
 */
int selecionarReta(float mouseX, float mouseY, int aux, ListaRetas * listaRetas)
{
    return 0;
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA DESENHAR AS RETAS NA TELA
 */
void desenharRetas(int reta, ListaRetas * listaRetas)
{
    
}

/*
 * FUNÇÃO PARA IMPRIMIR LISTA DE RETAS
 */
void imprimirListaRetas(ListaRetas * listaRetas)
{
    
}

/*
 * FUNÇÃO PARA SALVAR A LISTA DE RETAS
 */
void salvarRetas(ListaRetas * listaRetas)
{
    
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA TRANSLADAR UMA RETA (ARRASTAR E SOLTAR)
 */
int transladarReta(int reta, ListaRetas * listaRetas, MatrizTransformacao * matrizTranslacao)
{
    return 0;
}

/*
 * FUNÇÃO PARA ROTACIONAR UMA RETA
 */
int rotacionarReta(int reta, ListaRetas * listaRetas, MatrizTransformacao * matrizRotacao)
{
    return 0;
}

/*
 * FUNÇÃO PARA ESCALAR UMA RETA
 */
int escalarReta(int reta, ListaRetas * listaRetas, MatrizTransformacao * matrizEscalar)
{
    return 0;
}