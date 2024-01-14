#include <stdlib.h>
#include <GL/glut.h>

#include "cor.h"
#include "ponto.h"
#include "matriz.h"


Cor preto = { 0.0, 0.0, 0.0 };

/*
 * FUNÇÃO PARA CRIAR A LISTA DE PONTOS INICIAL (ZERADA)
*/
ListaPontos * criarListaPontos()
{
    // Ponteiro da lista de pontos
    ListaPontos * listaPontos = (ListaPontos *)malloc(sizeof(ListaPontos));
    listaPontos->qtdPontos = 0; // Inicializa com zero pontos
    return listaPontos;
}

/*
 * FUNÇÃO PARA ADICIONAR UM PONTO A LISTA
 * Parametros:
 * ListaPontos * listaPontos (lista de pontos)
 * float x ()
 * float y ()
*/
int adicionarPonto(ListaPontos * listaPontos, float x, float y)
{
    // Se a lista está vazia
    if (listaPontos == NULL || listaPontos->qtdPontos == 1000) {
        return 0;
    }
    // Adicionar o ponto
    else {
        Ponto ponto = { x, y };
        listaPontos->pontos[listaPontos->qtdPontos] = ponto;
        listaPontos->qtdPontos++;
        return 1;
    }
}

/*
 * FUNÇÃO PARA REMOVER UM PONTO DA LISTA
*/
int removerPonto(ListaPontos * listaPontos, int ponto)
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
 * FUNÇÃO PARA SELECIONAR UM PONTO
*/
int selecionarPonto(ListaPontos * listaPontos, float x, float y, int ponto)
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

/*
 * FUNÇÃO PARA DESENHAR OS PONTOS DA LISTA NA TELA
*/
void desenharPontos(ListaPontos * listaPontos, int ponto)
{
    glPointSize(5.0);
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
        glColor3f(preto.red, preto.green, preto.blue);
        glVertex2f(listaPontos->pontos[ponto].x, listaPontos->pontos[ponto].y);
        glEnd();
        glPointSize(5.0);
        glBegin(GL_POINTS);
        glColor3f(listaPontos->pontos[ponto].cor.red, listaPontos->pontos[ponto].cor.green, listaPontos->pontos[ponto].cor.blue);
        glVertex2f(listaPontos->pontos[ponto].x, listaPontos->pontos[ponto].y);
        glEnd();
    }
}

// FUNÇÃO PARA TRANSLADAR UM PONTO (ARRASTAR E SOLTAR)
int transladarPonto(ListaPontos * listaPontos, int ponto)
{
    if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
        return 0;
    } else {
        return 1;
    }
}

// FUNÇÃO PARA ROTACIONAR UM PONTO EM RELAÇÃO AO CENTRO DO OBJETO
int rotacionarPonto(ListaPontos * listaPontos, int ponto)
{
    if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
        return 0;
    } else {
        return 1;
    }
}
