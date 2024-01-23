#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "reta.h"

/*
 * DECLARAÇÃO DAS CORES FIXAS
 */
Cor azul = { 0.0, 0.0, 1.0 };
Cor preta = { 0.0, 0.0, 0.0 };

///////////////////////////////////////////////////////////////////

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

/*
 * FUNÇÃO PARA IMPRIMIR LISTA DE RETAS
 */
void imprimirListaRetas(ListaRetas * listaRetas)
{
	// Se a lista de retas estiver vazia ou a quantidade de retas for zero
	if (listaRetas == NULL || listaRetas->qtdRetas == 0) {
		printf("Lista de retas nao foi criada ou nao ha retas! Nao e possivel imprimir retas!\n");
	}
	// Imprimir retas
	else {
		for (int i = 0; i < listaRetas->qtdRetas; i++) {
			printf("Ponto: %d:\n", i + 1);

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
}

/*
 * FUNÇÃO PARA LIBERAR O ESPAÇO DE MEMÓRIA USADO PARA ARMAZENAR A LISTA DE RETAS
 */
void liberarListaRetas(ListaRetas * listaRetas)
{
    
}

/*
 * FUNÇÃO PARA SALVAR A LISTA DE RETAS
 */
void salvarListaRetas(const char * nomeArquivoRetas, ListaRetas * listaRetas)
{
	// Se a lista de retas não está vazia
	if (listaRetas != NULL) {
		// Abrir o arquivo para salvar a lista
		FILE * arquivoRetas = fopen(nomeArquivoRetas, "w");

		// Checar se o arquivo foi aberto com sucesso
		if (arquivoRetas == NULL) {
			fprintf(stderr, "Nao foi possivel abrir o arquivo %s.\n", nomeArquivoRetas);
			return;
		}

		// Escrever as dimensões da lista no arquivo
		fprintf(arquivoRetas, "%d\n", listaRetas->qtdRetas);

		// Escrever os elementos da lista no arquivo
		// (inicial.x, inicial.y, central.x, central.y, final.x, final.y, red, green, blue)
		for (int i = 0; i < listaRetas->qtdRetas; i++) {
			////////// Ponto inicial
			// Salvar posições do ponto inicial
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].inicial.x);
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].inicial.y);

			// Salvar os dados do RGB
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].inicial.cor.red);
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].inicial.cor.green);
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].inicial.cor.blue);

			////////// Ponto central
			// Salvar posições do ponto central
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].central.x);
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].central.y);

			// Salvar os dados do RGB
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].central.cor.red);
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].central.cor.green);
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].central.cor.blue);

			////////// Ponto final
			// Salvar posições do ponto final
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].final.x);
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].final.y);

			// Salvar os dados do RGB
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].final.cor.red);
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].final.cor.green);
			fprintf(arquivoRetas, "%.1f ", listaRetas->retas[i].final.cor.blue);
			fprintf(arquivoRetas, "\n"); // Mover para a próxima linha do arquivo
		}

		// Fechar arquivo
		fclose(arquivoRetas);

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
void carregarListaRetas(const char * nomeArquivoRetas, ListaRetas * listaRetas, ListaRetas * listaRetasArquivo)
{

}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA ADICIONAR UMA RETA A TELA
 */
int adicionarReta(float mouseX, float mouseY, int statusObjeto, ListaRetas * listaRetas)
{
	// Se a lista de retas não foi criada ou está cheia não é possível adicionar mais retas
	if (listaRetas == NULL || listaRetas->qtdRetas == MAX_RETAS) {
		printf("Lista de retas nao foi criada ou esta cheia! Nao e possivel adicionar a reta!\n");
		return 0;
	}
	// Adicionar a reta
	else {
		// Se a reta tem somente o ponto inicial (está sendo desenhada ainda)
		if (statusObjeto == -1) {
			// Adicionar o ponto inicial da reta com as posições x e y, e a cor azul fixa
			listaRetas->retas[listaRetas->qtdRetas].inicial.x = mouseX;
			listaRetas->retas[listaRetas->qtdRetas].inicial.y = mouseY;
			listaRetas->retas[listaRetas->qtdRetas].inicial.cor = azul;
			return 1;
		}
		// Se o ponto final da reta foi informado (finalizando o desenho da reta)
		else {
			// Adicionar o ponto final da reta com as posições x e y, e a cor azul fixa
			listaRetas->retas[listaRetas->qtdRetas].final.x = mouseX;
			listaRetas->retas[listaRetas->qtdRetas].final.y = mouseY;
			listaRetas->retas[listaRetas->qtdRetas].final.cor = azul;

			// Calcular o ponto central da reta e adiciona a lista com as posições x e y, e a cor preta fixa
			listaRetas->retas[listaRetas->qtdRetas].central.x = (listaRetas->retas[listaRetas->qtdRetas].inicial.x + listaRetas->retas[listaRetas->qtdRetas].final.x) / 2;
			listaRetas->retas[listaRetas->qtdRetas].central.y = (listaRetas->retas[listaRetas->qtdRetas].inicial.y + listaRetas->retas[listaRetas->qtdRetas].final.y) / 2;
			listaRetas->retas[listaRetas->qtdRetas].central.cor = preta;

			// Acrescentando uma reta a lista
			listaRetas->qtdRetas++;

			printf("Reta adicionada com sucesso!\n");

			// Retorna ao status inicial do objeto
			return -1;
		}
	}
}

/*
 * FUNÇÃO PARA EXCLUIR UMA RETA DA TELA
 */
int excluirReta(int chave, ListaRetas * listaRetas)
{
	// Se a lista de retas não foi criada ou a quantidade de retas for zero
	if (listaRetas == NULL || listaRetas->qtdRetas == 0) {
		printf("Lista de retas nao foi criada ou nao ha retas! Nao e possivel excluir a reta!\n");
		return 0;
	}
	// Remover uma reta
	else {
		// Laço para percorrer a lista de retas a partir da chave da reta até o final da lista
        // Para não quebrar a integridade da lista
		for (int i = chave; i < listaRetas->qtdRetas; i++) {
			listaRetas->retas[i] = listaRetas->retas[i + 1];
		}

		// Diminuir uma unidade da quantidade de retas
		listaRetas->qtdRetas--;

		printf("Reta excluida com sucesso!\n");
		return 1;
	}
}

/*
 * FUNÇÃO PARA SELECIONAR UMA RETA DA TELA
 */
int selecionarReta(float mouseX, float mouseY, ListaRetas * listaRetas)
{
    // Se a lista de retas estiver vazia ou a quantidade de retas for zero
	if (listaRetas == NULL || listaRetas->qtdRetas == 0) {
		printf("Lista de retas nao foi criada ou nao ha retas! Nao e possivel selecionar a reta!\n");
		return 0;
	}
	// Selecionar reta
	else {
		for (int i = 0; i < listaRetas->qtdRetas; i++) {
			// Calcular formula da reta para saber se um ponto pertence a ela
			// Pegando o ponto inicial da reta
			float x1 = listaRetas->retas[i].inicial.x;
			float y1 = listaRetas->retas[i].inicial.y;

			// Pegando o ponto final da reta
			float x2 = listaRetas->retas[i].final.x;
			float y2 = listaRetas->retas[i].final.y;

			// Verificando se o ponto do mouse quando clicado pertence a reta
			if (verificarPontoReta(mouseX, mouseY, x1, y1, x2, y2)) {
				printf("Reta selecionada com sucesso!\n");
				return i;
			}
		}

		printf("Ponto nao encontrado na lista de retas!\n");
		return -1;
	}
}

/*
 * FUNÇÃO PARA VERIFICAR SE UM PONTO PERTENCE A UMA RETA
 */
int verificarPontoReta(float mouseX, float mouseY, float x1, float y1, float x2, float y2)
{
	float m, b, aux;
	int tolerancia = 3; // Representa metade do tamanho da linha desenhada da reta, dando uma área para a reta

	// Baseado na equação da reta: y = mx + b
	// Pode ser encontrada tendo dois pontos que pertencem a reta, assim encontramos o valor de m
	m = (y2 - y1) / (x2 - x1);

	// Substituindo na equação por um dos pontos conhecidos, assim encontramos o valor de b
	b = y1 - (m * x1);

	// Realiza o cálculo para saber o valor da coordenada y
	aux = (mouseX * m) + b;
	float distance = fabs(m * mouseX - mouseY + b) / sqrt(m * m + 1);

	// Verificando se o ponto do mouse quando clicado pertence a reta
	// Como existe a tolerância, tem que contar a área da reta
	// Se o valor estiver entre o valor da área da reta no ponto onde o mouse foi clicado
	if ((mouseY <= aux + tolerancia) && (mouseY >= aux - tolerancia)) {
		printf("O ponto selecionado pertence a reta!\n");
		return 1;
	} else {
		printf("O ponto selecionado nao pertence a reta!\n");
		return 0;
	}
}

/*
 * FUNÇÃO PARA DESENHAR AS RETAS NA TELA
 */
void desenharRetas(ListaRetas * listaRetas)
{
    glLineWidth(6.0);
    glBegin(GL_LINES);

    for (int i = 0; i < listaRetas->qtdRetas; i++) {
    	// Imprimindo os valores e intensidades de cores RGB
		glColor3f(listaRetas->retas[i].inicial.cor.red, listaRetas->retas[i].inicial.cor.green, listaRetas->retas[i].inicial.cor.blue);
		// Posicionando o ponto inicial na largura e altura corretas do mouse
		glVertex2f(listaRetas->retas[i].inicial.x, listaRetas->retas[i].inicial.y);

		// Imprimindo os valores e intensidades de cores RGB
		glColor3f(listaRetas->retas[i].final.cor.red, listaRetas->retas[i].final.cor.green, listaRetas->retas[i].final.cor.blue);
		// Posicionando o ponto final na largura e altura corretas do mouse
		glVertex2f(listaRetas->retas[i].final.x, listaRetas->retas[i].final.y);
    }

    glEnd();
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA TRANSLADAR UMA RETA (ARRASTAR E SOLTAR)
 */
int transladarReta(int chave, ListaRetas * listaRetas, Matriz3Por3 * matrizTranslacaoReta)
{
    // Se a lista de retas estiver vazia ou a quantidade de retas for zero
	if (listaRetas == NULL || listaRetas->qtdRetas == 0) {
		printf("Lista de retas nao foi criada ou nao ha retas! Nao e possivel transladar a reta!\n");
		return 0;
	}
	// Transladar reta
	else {
		// Criar matrizes de ponto para auxiliar nos cálculos
        // Primeiramente, as matrizes contêm as coordenadas originais dos pontos da reta
		Matriz3Por1 * matrizCompostaInicial = criarMatriz3Por1(listaRetas->retas[chave].inicial.x, listaRetas->retas[chave].inicial.y);
		Matriz3Por1 * matrizCompostaCentral = criarMatriz3Por1(listaRetas->retas[chave].central.x, listaRetas->retas[chave].central.y);
		Matriz3Por1 * matrizCompostaFinal = criarMatriz3Por1(listaRetas->retas[chave].final.x, listaRetas->retas[chave].final.y);

		// Realizar a multiplicação transformação de cada um dos pontos inicial, central e final
		matrizCompostaInicial = multiplicarMatriz3Por3PorMatriz3Por1(matrizTranslacaoReta, matrizCompostaInicial);
		matrizCompostaCentral = multiplicarMatriz3Por3PorMatriz3Por1(matrizTranslacaoReta, matrizCompostaCentral);
		matrizCompostaFinal = multiplicarMatriz3Por3PorMatriz3Por1(matrizTranslacaoReta, matrizCompostaFinal);

		// Atualizar a posição do ponto inicial a partir do resultado do cálculo da transformação
		listaRetas->retas[chave].inicial.x = matrizCompostaInicial->matriz[0][0];
		listaRetas->retas[chave].inicial.y = matrizCompostaInicial->matriz[0][1];

		// Atualizar a posição do ponto central a partir do resultado do cálculo da transformação
		listaRetas->retas[chave].central.x = matrizCompostaCentral->matriz[0][0];
		listaRetas->retas[chave].central.y = matrizCompostaCentral->matriz[0][1];

		// Atualizar a posição do ponto final a partir do resultado do cálculo da transformação
		listaRetas->retas[chave].final.x = matrizCompostaFinal->matriz[0][0];
		listaRetas->retas[chave].final.y = matrizCompostaFinal->matriz[0][1];

		return 1;
	}
}

/*
 * FUNÇÃO PARA ROTACIONAR UMA RETA
 */
int rotacionarReta(int chave, ListaRetas * listaRetas, Matriz3Por3 * matrizRotacaoReta)
{
    // Se a lista de retas estiver vazia ou a quantidade de retas for zero
	if (listaRetas == NULL || listaRetas->qtdRetas == 0) {
		printf("Lista de retas nao foi criada ou nao ha retas! Nao e possivel rotacionar a reta!\n");
		return 0;
	}
	// Rotacionar reta
	else {
		// Criar a matriz3Por3 para auxiliar nos cálculos
        // Primeiramente, a matriz contêm o resultado das multiplicações necessárias para a rotação
        Matriz3Por3 * matrizCompostaReta = multiplicarMatrizComposta(
			listaRetas->retas[chave].central.x, 
			listaRetas->retas[chave].central.y, 
			matrizRotacaoReta
        );

        // Criar duas matriz3Por1 para auxiliar nos cálculos
        // Primeiramente, as matrizes contêm as coordenadas originais dos pontos inicial, central e final
		Matriz3Por1 * matrizCompostaInicial = criarMatriz3Por1(listaRetas->retas[chave].inicial.x, listaRetas->retas[chave].inicial.y);
		Matriz3Por1 * matrizCompostaFinal = criarMatriz3Por1(listaRetas->retas[chave].final.x, listaRetas->retas[chave].final.y);

		// Realizar a multiplicação gerando as matrizes rotacionando os pontos inicial, central e final da reta
		matrizCompostaInicial = multiplicarMatriz3Por3PorMatriz3Por1(matrizCompostaReta, matrizCompostaInicial);
		matrizCompostaFinal = multiplicarMatriz3Por3PorMatriz3Por1(matrizCompostaReta, matrizCompostaFinal);

		// Atualizar a posição dos pontos inicial, central e final a partir do resultado do cálculo da transformação
		listaRetas->retas[chave].inicial.x = matrizCompostaInicial->matriz[0][0];
		listaRetas->retas[chave].inicial.y = matrizCompostaInicial->matriz[0][1];
		listaRetas->retas[chave].final.x = matrizCompostaFinal->matriz[0][0];
		listaRetas->retas[chave].final.y = matrizCompostaFinal->matriz[0][1];

		return 1;
	}
}

/*
 * FUNÇÃO PARA ESCALAR UMA RETA
 */
int escalarReta(int chave, ListaRetas * listaRetas, Matriz3Por3 * matrizEscalarReta)
{
    // Se a lista de retas estiver vazia ou a quantidade de retas for zero
	if (listaRetas == NULL || listaRetas->qtdRetas == 0) {
		printf("Lista de retas nao foi criada ou nao ha retas! Nao e possivel escalar a reta!\n");
		return 0;
	}
	// Escalar reta
	else {
		// Criar a matriz3Por3 para auxiliar nos cálculos
        // Primeiramente, a matriz contêm o resultado das multiplicações necessárias para a escalar
        Matriz3Por3 * matrizCompostaReta = multiplicarMatrizComposta(
			listaRetas->retas[chave].central.x, 
			listaRetas->retas[chave].central.y, 
			matrizEscalarReta
        );

        // Criar duas matriz3Por1 para auxiliar nos cálculos
        // Primeiramente, as matrizes contêm as coordenadas originais dos pontos inicial, central e final
		Matriz3Por1 * matrizICompostaInicial = criarMatriz3Por1(listaRetas->retas[chave].inicial.x, listaRetas->retas[chave].inicial.y);
		Matriz3Por1 * matrizCompostaFinal = criarMatriz3Por1(listaRetas->retas[chave].final.x, listaRetas->retas[chave].final.y);

		// Realizar a multiplicação gerando as matrizes rotacionando os pontos inicial, central e final da reta
		matrizICompostaInicial = multiplicarMatriz3Por3PorMatriz3Por1(matrizCompostaReta, matrizICompostaInicial);
		matrizCompostaFinal = multiplicarMatriz3Por3PorMatriz3Por1(matrizCompostaReta, matrizCompostaFinal);

		// Atualizar a posição dos pontos inicial, central e final a partir do resultado do cálculo da transformação
		listaRetas->retas[chave].inicial.x = matrizICompostaInicial->matriz[0][0];
		listaRetas->retas[chave].inicial.y = matrizICompostaInicial->matriz[0][1];
		listaRetas->retas[chave].final.x = matrizCompostaFinal->matriz[0][0];
		listaRetas->retas[chave].final.y = matrizCompostaFinal->matriz[0][1];

		return 1;
	}
}

/*
 * FUNÇÃO PARA REFLETIR UMA RETA
 */
int refletirReta(int chave, ListaRetas * listaRetas, Matriz3Por3 * matrizReflexaoReta)
{
    // Se a lista de retas estiver vazia ou a quantidade de retas for zero
	if (listaRetas == NULL || listaRetas->qtdRetas == 0) {
		printf("Lista de retas nao foi criada ou nao ha retas! Nao e possivel refletir a reta!\n");
		return 0;
	}
	// Refletir reta
	else {
        // Criar matrizes de ponto para auxiliar nos cálculos
        // Primeiramente, as matrizes contêm as coordenadas originais dos pontos da reta
		Matriz3Por1 * matrizCompostaInicial = criarMatriz3Por1(listaRetas->retas[chave].inicial.x, listaRetas->retas[chave].inicial.y);
		Matriz3Por1 * matrizCompostaCentral = criarMatriz3Por1(listaRetas->retas[chave].central.x, listaRetas->retas[chave].central.y);
		Matriz3Por1 * matrizCompostaFinal = criarMatriz3Por1(listaRetas->retas[chave].final.x, listaRetas->retas[chave].final.y);

		// Realizar a multiplicação transformação de cada um dos pontos inicial, central e final
		matrizCompostaInicial = multiplicarMatriz3Por3PorMatriz3Por1(matrizReflexaoReta, matrizCompostaInicial);
		matrizCompostaCentral = multiplicarMatriz3Por3PorMatriz3Por1(matrizReflexaoReta, matrizCompostaCentral);
		matrizCompostaFinal = multiplicarMatriz3Por3PorMatriz3Por1(matrizReflexaoReta, matrizCompostaFinal);

		// Atualizar a posição do ponto inicial a partir do resultado do cálculo da transformação
		listaRetas->retas[chave].inicial.x = matrizCompostaInicial->matriz[0][0];
		listaRetas->retas[chave].inicial.y = matrizCompostaInicial->matriz[0][1];

		// Atualizar a posição do ponto central a partir do resultado do cálculo da transformação
		listaRetas->retas[chave].central.x = matrizCompostaCentral->matriz[0][0];
		listaRetas->retas[chave].central.y = matrizCompostaCentral->matriz[0][1];

		// Atualizar a posição do ponto final a partir do resultado do cálculo da transformação
		listaRetas->retas[chave].final.x = matrizCompostaFinal->matriz[0][0];
		listaRetas->retas[chave].final.y = matrizCompostaFinal->matriz[0][1];

		return 1;
	}
}