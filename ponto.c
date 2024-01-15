#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "ponto.h"

/*
 * DECLARAÇÃO DAS CORES FIXAS
 */
Cor vermelha = { 1.0, 0.0, 0.0 };
Cor verde = { 0.0, 1.0, 0.0 };
Cor azul = { 0.0, 0.0, 1.0 };
Cor preta = { 0.0, 0.0, 0.0 };

/*
 * FUNÇÃO PARA CRIAR A LISTA DE PONTOS
 */
ListaPontos * criarListaPontos()
{
	// Ponteiro da lista de pontos
	ListaPontos * listaPontos = (ListaPontos *)malloc(sizeof(ListaPontos));
	listaPontos->qtdPontos = 0;
	return listaPontos;
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA CRIAR A LISTA DE PONTOS
 */
int adicionarPonto(float x, float y, ListaPontos * listaPontos)
{
    // Se a lista está vazia
    if (listaPontos == NULL || listaPontos->qtdPontos == MAX_PONTOS) {
        return 0;
    }
    // Adicionar o ponto
    else {
        Ponto ponto = { x, y, verde };
        listaPontos->pontos[listaPontos->qtdPontos] = ponto;
        listaPontos->qtdPontos++;
        return 1;
    }
}

/*
 * FUNÇÃO PARA CRIAR A LISTA DE PONTOS
 */
int removerPonto(int ponto, ListaPontos * listaPontos)
{
    // Se a lista de pontos estiver vazia ou a quantidade de pontos for zero
    if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
        return 0;
    }
    // Caso
    else {
        // Laço para percorrer a lista de pontos
        for (int i = ponto; i < listaPontos->qtdPontos; i++) {
            listaPontos->pontos[i] = listaPontos->pontos[i + 1];
        }

        // Remover uma unidade da quantidade de pontos
        listaPontos->qtdPontos--;
        return 1;
    }
}

/*
 * FUNÇÃO PARA CRIAR A LISTA DE PONTOS
 */
int selecionarPonto(float x, float y, int ponto, ListaPontos * listaPontos)
{
    if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
        return 0;
    }
    //
    else {
        //
        for (int i = 0; i < listaPontos->qtdPontos; i++) {

        }

        return -1;
    }
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA CRIAR A LISTA DE PONTOS
 */
void desenharPontos(int ponto, ListaPontos * listaPontos)
{
    glPointSize(3.0);
    glBegin(GL_POINTS);

    for (int i = 0; i < listaPontos->qtdPontos; i++){
        if (i != ponto){
            glColor3f(listaPontos->pontos[i].cor.red, listaPontos->pontos[i].cor.green, listaPontos->pontos[i].cor.blue);
            glVertex2f(listaPontos->pontos[i].x, listaPontos->pontos[i].y);
        }
    }

    glEnd();

    if (ponto != -1) {
        glPointSize(7.0);
        glBegin(GL_POINTS);
        glColor3f(preta.red, preta.green, preta.blue);
        glVertex2f(listaPontos->pontos[ponto].x, listaPontos->pontos[ponto].y);
        glEnd();
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glColor3f(listaPontos->pontos[ponto].cor.red, listaPontos->pontos[ponto].cor.green, listaPontos->pontos[ponto].cor.blue);
        glVertex2f(listaPontos->pontos[ponto].x, listaPontos->pontos[ponto].y);
        glEnd();
    }
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA CRIAR A LISTA DE PONTOS
 */
int transladarPonto(int ponto, ListaPontos * listaPontos)
{
    if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
        return 0;
    } else {
        return 1;
    }
}

/*
 * FUNÇÃO PARA CRIAR A LISTA DE PONTOS
 */
int rotacionarPonto(int ponto, ListaPontos * listaPontos)
{
    if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
        return 0;
    } else {
        return 1;
    }
}
