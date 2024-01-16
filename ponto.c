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
        // Adicionando na lista a posição x e y, assim como a cor vermelha fixa para os pontos
        Ponto ponto = { x, y, vermelha };
        printf("listaPontos->qtdPontos: %d\n", listaPontos->qtdPontos);
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
int selecionarPonto(float pontoX, float pontoY, float mouseX, float mouseY, int aux)
{
    // if (mouseX <= pontoX + aux && mouseX >= pontoX - aux) {
    //     return 1;
    // }

    // return 0;
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA CRIAR A LISTA DE PONTOS
 */
void desenharPontos(int ponto, ListaPontos * listaPontos)
{
    glPointSize(3.0);
    glBegin(GL_POINTS);

    for (int i = 0; i < listaPontos->qtdPontos; i++) {
        if (i != ponto) {
            // Imprimindo os valores e intensidades de cores RGB
            glColor3f(listaPontos->pontos[i].cor.red, listaPontos->pontos[i].cor.green, listaPontos->pontos[i].cor.blue);
            // Posicionando o ponto na largura e altura corretas do mouse
            glVertex2f(listaPontos->pontos[i].x, listaPontos->pontos[i].y);
        }
    }

    glEnd();

    // if (ponto != -1) {
    //     glPointSize(7.0);
    //     glBegin(GL_POINTS);
    //     glColor3f(preta.red, preta.green, preta.blue);
    //     glVertex2f(listaPontos->pontos[ponto].x, listaPontos->pontos[ponto].y);
    //     glEnd();
    //     glPointSize(5.0);
    //     glBegin(GL_POINTS);
    //     glColor3f(listaPontos->pontos[ponto].cor.red, listaPontos->pontos[ponto].cor.green, listaPontos->pontos[ponto].cor.blue);
    //     glVertex2f(listaPontos->pontos[ponto].x, listaPontos->pontos[ponto].y);
    //     glEnd();
    // }
}

/*
 * FUNÇÃO PARA IMPRIMIR LISTA DE PONTOS
 */
void imprimirListaPontos(ListaPontos * listaPontos)
{
    for (int i = 0; i < listaPontos->qtdPontos; i++) {
        printf("%d: x: %d, y: %d\n", i + 1, listaPontos->pontos[i].x, listaPontos->pontos[i].y);
    }
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA CRIAR A LISTA DE PONTOS
 */
int transladarPonto(Ponto p, ListaPontos * listaPontos, float ty, float tx)
{
    if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
        return 0;
    } else {
        MatrizPonto* mp = criarMatrizPonto(p.x, p.y);
        MatrizTransformacao* transl = criarMatrizTranslacao(tx, ty);
        mp = multiplicarMatrizPonto(mp, transl);
        p.x = mp->matriz[0][0];
        p.y = mp->matriz[0][1];
        free(mp);
        free(transl);
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
