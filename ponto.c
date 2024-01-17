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
 * FUNÇÃO PARA ADICIONAR UM PONTO A TELA
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
        listaPontos->pontos[listaPontos->qtdPontos] = ponto;
        listaPontos->qtdPontos++;
        return 1;
    }
}

/*
 * FUNÇÃO PARA EXCLUIR UM PONTO DA TELA
 */
int excluirPonto(int ponto, ListaPontos * listaPontos)
{
    // Se a lista de pontos estiver vazia ou a quantidade de pontos for zero
    if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
        return 0;
    }
    // 
    else {
        // Laço para percorrer a lista de pontos de trás para frente
        for (int i = listaPontos->qtdPontos - 1; i > ponto; i--) {
            listaPontos->pontos[i] = listaPontos->pontos[i - 1];
        }

        // Diminuir uma unidade da quantidade de pontos
        listaPontos->qtdPontos--;
        return 1;
    }
}

/*
 * FUNÇÃO PARA SELECIONAR UM PONTO DA TELA
 */
int selecionarPonto(float mouseX, float mouseY, int aux, ListaPontos * listaPontos)
{
    // // Se a lista de pontos estiver vazia ou a quantidade de pontos for zero
    // if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
    //     return 0;
    // }
    // //
    // else {
    //     //
    //     for (int i = 0; i < listaPontos->qtdPontos; i++) {
    //         if () {
    //             return 1;
    //         }
    //     }

    //     return -1;
    // }

    return 0;
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA DESENHAR OS PONTOS NA TELA
 */
void desenharPontos(int ponto, ListaPontos * listaPontos)
{
    glPointSize(3.0);
    glBegin(GL_POINTS);

    for (int i = 0; i < listaPontos->qtdPontos; i++) {
        // Imprimindo os valores e intensidades de cores RGB
        glColor3f(listaPontos->pontos[i].cor.red, listaPontos->pontos[i].cor.green, listaPontos->pontos[i].cor.blue);
        // Posicionando o ponto na largura e altura corretas do mouse
        glVertex2f(listaPontos->pontos[i].x, listaPontos->pontos[i].y);
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
        printf("%d: x: %f, y: %f\n", i + 1, listaPontos->pontos[i].x, listaPontos->pontos[i].y);
    }
}

/*
 * FUNÇÃO PARA SALVAR A LISTA DE PONTOS
 */
void salvarPontos(ListaPontos * listaPontos)
{
    if (listaPontos != NULL) {
        // Nome do arquivo
        const char * nomeArquivo = "pontos.txt";

        // Abrir o arquivo para salvar a lista
        FILE * arquivo = fopen(nomeArquivo, "w");

        // Checar se o arquivo foi aberto com sucesso
        if (arquivo == NULL) {
            fprintf(stderr, "Nao foi possivel abrir o arquivo %s.\n", nomeArquivo);
            return;
        }

        // Escrever as dimensões da lista no arquivo
        fprintf(arquivo, "%d\n", listaPontos->qtdPontos);

        // Escrever os elementos da lista no arquivo (x, y, red, green, blue)
        for (int i = 0; i < listaPontos->qtdPontos; i++) {
            fprintf(arquivo, "%f ", listaPontos->pontos[i].x);
            fprintf(arquivo, "%f ", listaPontos->pontos[i].y);
            fprintf(arquivo, "%f ", listaPontos->pontos[i].cor.red);
            fprintf(arquivo, "%f ", listaPontos->pontos[i].cor.green);
            fprintf(arquivo, "%f", listaPontos->pontos[i].cor.blue);
            fprintf(arquivo, "\n"); // Mover para a próxima linha do arquivo
        }

        // Fechar arquivo
        fclose(arquivo);

        printf("Lista salva com sucesso!\n");
    }
    // Se a lista de pontos está vazia
    else {
        printf("A lista de pontos esta vazia. Nada foi salvo no arquivo.\n");
        return;
    }
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA TRANSLADAR UM PONTO (ARRASTAR E SOLTAR)
 */
int transladarPonto(int ponto, ListaPontos * listaPontos, MatrizTransformacao * matrizTranslacao)
{
    if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
        return 0;
    }
    //
    else {
        MatrizPonto * matrizComposta = criarMatrizPonto(listaPontos->pontos[ponto].x, listaPontos->pontos[ponto].y);
        matrizComposta = multiplicarMatrizPonto(matrizComposta, matrizTranslacao);
        listaPontos->pontos[ponto].x = matrizComposta->matriz[0][0];
        listaPontos->pontos[ponto].y = matrizComposta->matriz[0][1];
        return 1;
    }
}

/*
 * FUNÇÃO PARA ROTACIONAR UM PONTO
 */
int rotacionarPonto(int ponto, ListaPontos * listaPontos, MatrizTransformacao * matrizRotacao)
{
    if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
        return 0;
    }
    //
    else {
        MatrizPonto * matrizPonto = criarMatrizPonto(listaPontos->pontos[ponto].x, listaPontos->pontos[ponto].y);
        matrizPonto = multiplicarMatrizPonto(matrizPonto, matrizRotacao);
        listaPontos->pontos[ponto].x = matrizPonto->matriz[0][0];
        listaPontos->pontos[ponto].y = matrizPonto->matriz[0][1];
        return 1;
    }
}
