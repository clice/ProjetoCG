#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "reta.h"

/*
 * DECLARAÇÃO DAS CORES FIXAS
 */
Cor azul = { 0.0, 0.0, 1.0 };
Cor preta = { 0.0, 0.0, 0.0 };

/*
 * FUNÇÃO PARA CRIAR A LISTA DE RETAS
 */
ListaRetas * criarListaRetas()
{
	// Ponteiro da lista de retas
	ListaRetas * listaRetas = (ListaRetas *)malloc(sizeof(ListaRetas));
	listaRetas->qtdRetas = 0;
	return listaRetas;
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA ADICIONAR UMA RETA A TELA
 */
int adicionarReta(float x, float y, int statusObjeto, ListaRetas * listaRetas)
{
	// Se a lista de retas estiver vazia ou cheia
	if (listaRetas == NULL || listaRetas->qtdRetas == MAX_RETAS) {
		return 0;
	}
	// Adicionar a reta
	else {
		// Se a reta tem somente o ponto inicial (está sendo desenhada ainda)
		if (statusObjeto == -1) {
			// Adicionar o ponto inicial da reta com as posições x e y, e a cor azul fixa
			listaRetas->retas[listaRetas->qtdRetas].inicial.x = x;
			listaRetas->retas[listaRetas->qtdRetas].inicial.y = y;
			listaRetas->retas[listaRetas->qtdRetas].inicial.cor = azul;
			return 1;
		}
		// Se o ponto final da reta foi informado (finalizando o desenho da reta)
		else {
			// Adicionar o ponto final da reta com as posições x e y, e a cor azul fixa
			listaRetas->retas[listaRetas->qtdRetas].final.x = x;
			listaRetas->retas[listaRetas->qtdRetas].final.y = y;
			listaRetas->retas[listaRetas->qtdRetas].final.cor = azul;

			// Calcular o ponto central da reta e adiciona a lista com as posições x e y, e a cor preta fixa
			listaRetas->retas[listaRetas->qtdRetas].central.x = (listaRetas->retas[listaRetas->qtdRetas].inicial.x + listaRetas->retas[listaRetas->qtdRetas].final.x) / 2;
			listaRetas->retas[listaRetas->qtdRetas].central.y = (listaRetas->retas[listaRetas->qtdRetas].inicial.y + listaRetas->retas[listaRetas->qtdRetas].final.y) / 2;
			listaRetas->retas[listaRetas->qtdRetas].central.cor = preta;

			// Acrescentando uma reta a lista
			listaRetas->qtdRetas++;

			// Retorna ao status inicial do objeto
			return -1;
		}
	}
}

/*
 * FUNÇÃO PARA EXCLUIR UMA RETA DA TELA
 */
int excluirReta(int reta, ListaRetas * listaRetas)
{
	// Se a lista de retas estiver vazia ou a quantidade de retas for zero
	if (listaRetas == NULL || listaRetas->qtdRetas == 0) {
		return 0;
	}
	// Remover reta
	else {
		for (int i = reta; i < listaRetas->qtdRetas; i++) {
			listaRetas->retas[i] = listaRetas->retas[i + 1];
		}

		// Diminuir uma unidade da quantidade de retas
		listaRetas->qtdRetas--;
		return 1;
	}
}

/*
 * FUNÇÃO PARA SELECIONAR UMA RETA DA TELA
 */
int selecionarReta(float mouseX, float mouseY, int aux, ListaRetas * listaRetas)
{
    // Se a lista de retas estiver vazia ou a quantidade de retas for zero
	if (listaRetas == NULL || listaRetas->qtdRetas == 0) {
		return 0;
	}
	//
	else {
		for (int i = 0; i < listaRetas->qtdRetas; i++) {

		}

		return 1;
	}
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA DESENHAR AS RETAS NA TELA
 */
void desenharRetas(int reta, ListaRetas * listaRetas)
{
    glLineWidth(3.0);
    glBegin(GL_LINES);

    for (int i = 0; i < listaRetas->qtdRetas; i++) {
    	// if (i != reta) {
    		// Imprimindo os valores e intensidades de cores RGB
			glColor3f(listaRetas->retas[i].inicial.cor.red, listaRetas->retas[i].inicial.cor.green, listaRetas->retas[i].inicial.cor.blue);
	        // Posicionando o ponto inicial na largura e altura corretas do mouse
			glVertex2f(listaRetas->retas[i].inicial.x, listaRetas->retas[i].inicial.y);

	        // Imprimindo os valores e intensidades de cores RGB
			glColor3f(listaRetas->retas[i].final.cor.red, listaRetas->retas[i].final.cor.green, listaRetas->retas[i].final.cor.blue);
	        // Posicionando o ponto final na largura e altura corretas do mouse
			glVertex2f(listaRetas->retas[i].final.x, listaRetas->retas[i].final.y);
    	// }
    }

    glEnd();

    // if (r != -1){
    //     glLineWidth(4.0);
    //     glBegin(GL_LINES);
    //         glColor3f(preto.red, preto.green, preto.blue);
    //         glVertex2f(lr->retas[r].inicio.x, lr->retas[r].inicio.y);
    //         glVertex2f(lr->retas[r].fim.x, lr->retas[r].fim.y);
    //     glEnd();
    //     glLineWidth(2.0);
    //     glBegin(GL_LINES);
    //         glColor3f(lr->retas[r].inicio.cor.red, lr->retas[r].inicio.cor.green, lr->retas[r].inicio.cor.blue);
    //         glVertex2f(lr->retas[r].inicio.x, lr->retas[r].inicio.y);
    //         glColor3f(lr->retas[r].fim.cor.red, lr->retas[r].fim.cor.green, lr->retas[r].fim.cor.blue);
    //         glVertex2f(lr->retas[r].fim.x, lr->retas[r].fim.y);
    //     glEnd();
    // }
}

/*
 * FUNÇÃO PARA IMPRIMIR LISTA DE RETAS
 */
void imprimirListaRetas(ListaRetas * listaRetas)
{
	for (int i = 0; i < listaRetas->qtdRetas; i++) {
		printf("Ponto %d:\n", i + 1);

		printf("Inicial:\nx: %.1f, y: %.1f, cor: { %.1f, %.1f, %.1f }\n",
            listaRetas->retas[i].inicial.x,
            listaRetas->retas[i].inicial.y,
            listaRetas->retas[i].inicial.cor.red,
            listaRetas->retas[i].inicial.cor.green,
            listaRetas->retas[i].inicial.cor.blue
        );

		printf("Central:\nx: %.1f, y: %.1f, cor: { %.1f, %.1f, %.1f }\n",
            listaRetas->retas[i].central.x,
            listaRetas->retas[i].central.y,
            listaRetas->retas[i].central.cor.red,
            listaRetas->retas[i].central.cor.green,
            listaRetas->retas[i].central.cor.blue
        );

		printf("Final:\nx: %.1f, y: %.1f, cor: { %.1f, %.1f, %.1f }\n",
            listaRetas->retas[i].final.x,
            listaRetas->retas[i].final.y,
            listaRetas->retas[i].final.cor.red,
            listaRetas->retas[i].final.cor.green,
            listaRetas->retas[i].final.cor.blue
        );
	}
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA SALVAR A LISTA DE RETAS
 */
void salvarRetas(ListaRetas * listaRetas)
{
	// Se a lista de retas não está vazia
	if (listaRetas != NULL) {
		// Nome do arquivo
		const char * nomeArquivo = "arquivos/retas/retas.txt";

		// Abrir o arquivo para salvar a lista
		FILE * arquivo = fopen(nomeArquivo, "w");

		// Checar se o arquivo foi aberto com sucesso
		if (arquivo == NULL) {
			fprintf(stderr, "Nao foi possivel abrir o arquivo %s.\n", nomeArquivo);
			return;
		}

		// Escrever as dimensões da lista no arquivo
		fprintf(arquivo, "%d\n", listaRetas->qtdRetas);

		// Escrever os elementos da lista no arquivo
		// (inicial.x, inicial.y, central.x, central.y, final.x, final.y, red, green, blue)
		for (int i = 0; i < listaRetas->qtdRetas; i++) {
			////////// Ponto inicial
			// Salvar posições do ponto inicial
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].inicial.x);
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].inicial.y);

			// Salvar os dados do RGB
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].inicial.cor.red);
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].inicial.cor.green);
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].inicial.cor.blue);

			////////// Ponto central
			// Salvar posições do ponto central
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].central.x);
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].central.y);

			// Salvar os dados do RGB
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].central.cor.red);
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].central.cor.green);
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].central.cor.blue);

			////////// Ponto final
			// Salvar posições do ponto final
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].final.x);
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].final.y);

			// Salvar os dados do RGB
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].final.cor.red);
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].final.cor.green);
			fprintf(arquivo, "%.1f ", listaRetas->retas[i].final.cor.blue);
			fprintf(arquivo, "\n"); // Mover para a próxima linha do arquivo
		}

		// Fechar arquivo
		fclose(arquivo);

		printf("Lista de retas salva com sucesso!");
	}
	// Se a lista de retas está vazia
	else {
		printf("A lista de retas esta vazia. Nada foi salvo no arquivo.\n");
		return;
	}
}

/*
 * FUNÇÃO PARA CARREGAR A LISTA DE RETAS NA TELA
 */
void carregarRetas(ListaRetas * listaRetas)
{

}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA TRANSLADAR UMA RETA (ARRASTAR E SOLTAR)
 */
int transladarReta(int reta, ListaRetas * listaRetas, MatrizTransformacao * matrizTranslacao)
{
    // Se a lista de retas estiver vazia ou a quantidade de retas for zero
	if (listaRetas == NULL || listaRetas->qtdRetas == 0) {
		return 0;
	}
	//
	else {
		return 1;
	}
}

/*
 * FUNÇÃO PARA ROTACIONAR UMA RETA
 */
int rotacionarReta(int reta, ListaRetas * listaRetas, MatrizTransformacao * matrizRotacao)
{
    // Se a lista de retas estiver vazia ou a quantidade de retas for zero
	if (listaRetas == NULL || listaRetas->qtdRetas == 0) {
		return 0;
	}
	//
	else {
		return 1;
	}
}

/*
 * FUNÇÃO PARA ESCALAR UMA RETA
 */
int escalarReta(int reta, ListaRetas * listaRetas, MatrizTransformacao * matrizEscalar)
{
    // Se a lista de retas estiver vazia ou a quantidade de retas for zero
	if (listaRetas == NULL || listaRetas->qtdRetas == 0) {
		return 0;
	}
	//
	else {
		return 1;
	}
}