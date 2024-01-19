#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "ponto.h"

/*
 * DECLARAÇÃO DAS CORES FIXAS
 */
Cor vermelha = { 1.0, 0.0, 0.0 };

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

/*
 * FUNÇÃO PARA IMPRIMIR LISTA DE PONTOS
 */
void imprimirListaPontos(ListaPontos * listaPontos)
{
    for (int i = 0; i < listaPontos->qtdPontos; i++) {
        printf("%d: x: %.1f, y: %.1f, cor: { %.1f, %.1f, %.1f }\n",
            i + 1,
            listaPontos->pontos[i].x,
            listaPontos->pontos[i].y,
            listaPontos->pontos[i].cor.red,
            listaPontos->pontos[i].cor.green,
            listaPontos->pontos[i].cor.blue
        );
    }
}

/*
 * FUNÇÃO PARA SALVAR A LISTA DE PONTOS
 */
void salvarListaPontos(ListaPontos * listaPontos)
{
    // Se a lista de pontos não está vazia
    if (listaPontos != NULL) {
        // Nome do arquivo
        const char * nomeArquivo = "arquivos/pontos/pontos.txt";

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
            // Salvar posições dos pontos
            fprintf(arquivo, "%.1f ", listaPontos->pontos[i].x);
            fprintf(arquivo, "%.1f ", listaPontos->pontos[i].y);

            // Salvar os dados do RGB
            fprintf(arquivo, "%.1f ", listaPontos->pontos[i].cor.red);
            fprintf(arquivo, "%.1f ", listaPontos->pontos[i].cor.green);
            fprintf(arquivo, "%.1f", listaPontos->pontos[i].cor.blue);
            fprintf(arquivo, "\n"); // Mover para a próxima linha do arquivo
        }

        // Fechar arquivo
        fclose(arquivo);

        printf("Lista de pontos salva com sucesso!\n");
    }
    // Se a lista de pontos está vazia
    else {
        printf("A lista de pontos esta vazia. Nada foi salvo no arquivo.\n");
        return;
    }
}

/*
 * FUNÇÃO PARA CARREGAR A LISTA DE PONTOS NA TELA
 */
void carregarListaPontos()
{
    // int ponto = -1;
    int * qtdPontos;
    float auxListaPontos[1][5];

    ListaPontos * listaPontos = criarListaPontos();

    // Nome do arquivo
    const char * nomeArquivo = "arquivos/pontos/pontos.txt";

    // Abrir o arquivo para carregar a lista
    FILE * arquivo = fopen(nomeArquivo, "r");

    // Checar se o arquivo foi aberto com sucesso
    if (arquivo == NULL) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo %s.\n", nomeArquivo);
        return;
    }

    // Ler as dimensões da lista no arquivo
    fscanf(arquivo, "%d", qtdPontos);

    // Adicionando a quantidade de pontos na lista
    listaPontos->qtdPontos = *qtdPontos;

    // Ler os elementos da lista no arquivo (x, y, red, green, blue)
    for (int i = 0; i < 9; i++) {
        printf("Lista de pontos carregada com sucesso!\n");
        // // Salvar posições dos pontos
        // fscanf(arquivo, "%.1f ", &listaPontos->pontos[i].x);
        // fscanf(arquivo, "%.1f ", &listaPontos->pontos[i].y);

        // // Salvar os dados do RGB
        // fscanf(arquivo, "%.1f ", &listaPontos->pontos[i].cor.red);
        // fscanf(arquivo, "%.1f ", &listaPontos->pontos[i].cor.green);
        // fscanf(arquivo, "%.1f", &listaPontos->pontos[i].cor.blue);
        // fscanf(arquivo, "\n"); // Mover para a próxima linha do arquivo

        // printf("%.1f ", &auxListaPontos[0][0]);
        // printf("%.1f ", &auxListaPontos[0][1]);
        // printf("%.1f ", &auxListaPontos[0][2]);
        // printf("%.1f ", &auxListaPontos[0][3]);
        // printf("%.1f\n", &auxListaPontos[0][4]);

        // Adicionando os dados na lista de pontos
    }

    // Desenhar na tela os pontos da lista
    // desenharPontos(ponto, listaPontos);

    // Fechar arquivo
    fclose(arquivo);

    printf("Lista de pontos carregada com sucesso!\n");
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
        listaPontos->pontos[listaPontos->qtdPontos].x = x;
        listaPontos->pontos[listaPontos->qtdPontos].y = y;
        listaPontos->pontos[listaPontos->qtdPontos].cor = vermelha;
        listaPontos->qtdPontos++;
        return 1;
    }
}

/*
 * FUNÇÃO PARA EXCLUIR UM PONTO DA TELA
 */
int excluirPonto(int chavePonto, ListaPontos * listaPontos)
{
    // Se a lista de pontos estiver vazia ou a quantidade de pontos for zero
    if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
        printf("Lista de pontos esta vazia!");
        return 0;
    }
    // Excluir um ponto
    else {
        // Laço para percorrer a lista de pontos a partir da chave do ponto até o final da lista
        // Para não quebrar a integridade da lista
        for (int i = chavePonto; i < listaPontos->qtdPontos; i++) {
            listaPontos->pontos[i] = listaPontos->pontos[i + 1];
        }

        // Diminuir uma unidade da quantidade de pontos
        listaPontos->qtdPontos--;
        return 1;
    }
}

/*
 * FUNÇÃO PARA SELECIONAR UM PONTO DA TELA RETORNANDO A CHAVE ONDE O PONTO ESTÁ NA LISTA
 */
int selecionarPonto(float mouseX, float mouseY, ListaPontos * listaPontos)
{
    // Se a lista de pontos estiver vazia ou a quantidade de pontos for zero
    if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
        return -1;
    }
    // Selecionar o ponto
    else {
        // Procurar na lista de pontos algum ponto que esteja sendo clicado pelo mouse
        for (int i = 0; i < listaPontos->qtdPontos; i++) {
            if (mouseX <= listaPontos->pontos[i].x + 3 && mouseX >= listaPontos->pontos[i].x - 3) { // O 3 é o valor de tolerância para a região de detecção
                if (mouseY <= listaPontos->pontos[i].y + 3 && mouseY >= listaPontos->pontos[i].y - 3) { // O valor é 3 porque é metade do size do ponto
                    return i;
                }
            }
        }

        return -1;
    }
}

/*
 * FUNÇÃO PARA DESENHAR OS PONTOS NA TELA
 */
void desenharPontos(ListaPontos * listaPontos)
{
    glPointSize(6.0);
    glBegin(GL_POINTS);

    for (int i = 0; i < listaPontos->qtdPontos; i++) {
        // Imprimindo os valores e intensidades de cores RGB
        glColor3f(listaPontos->pontos[i].cor.red, listaPontos->pontos[i].cor.green, listaPontos->pontos[i].cor.blue);
        // Posicionando o ponto na largura e altura corretas do mouse
        glVertex2f(listaPontos->pontos[i].x, listaPontos->pontos[i].y);
    }

    glEnd();
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA TRANSLADAR UM PONTO (ARRASTAR E SOLTAR)
 */
int transladarPonto(int ponto, ListaPontos * listaPontos, MatrizTransformacao * matrizTranslacao)
{
    // Se a lista de pontos estiver vazia ou a quantidade de pontos for zero
    if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
        return 0;
    }
    // Transladar ponto
    else {
        MatrizPonto * matrizComposta = criarMatrizPonto(listaPontos->pontos[ponto].x, listaPontos->pontos[ponto].y);
        matrizComposta = multiplicarMatrizPonto(matrizComposta, matrizTranslacao);
        listaPontos->pontos[ponto].x = matrizComposta->matriz[0][0];
        listaPontos->pontos[ponto].y = matrizComposta->matriz[0][1];
        return 1;
    }
}

/*
 * FUNÇÃO PARA ROTACIONAR UM PONTO (GIRAR PONTO NA TELA A PARTIR DE GRAUS)
 */
int rotacionarPonto(int ponto, ListaPontos * listaPontos, MatrizTransformacao * matrizRotacao)
{
    // Se a lista de pontos estiver vazia ou a quantidade de pontos for zero
    if (listaPontos == NULL || listaPontos->qtdPontos == 0) {
        return 0;
    }
    // Rotacionar ponto
    else {
        MatrizPonto * matrizPonto = criarMatrizPonto(listaPontos->pontos[ponto].x, listaPontos->pontos[ponto].y);
        matrizPonto = multiplicarMatrizPonto(matrizPonto, matrizRotacao);
        listaPontos->pontos[ponto].x = matrizPonto->matriz[0][0];
        listaPontos->pontos[ponto].y = matrizPonto->matriz[0][1];
        return 1;
    }
}