#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "poligono.h"

/*
 * DECLARAÇÃO DAS CORES FIXAS
 */
Cor magenta = { 1.0, 0.0, 1.0 };

///////////////////////////////////////////////////////////////////

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
		printf("Lista de poligonos nao foi criada ou esta vazia! Nao e possivel imprimir poligonos!\n");
	}
	//
	else {

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
 * FUNÇÃO PARA CRIAR UM PONTO DO POLÍGONO
 */
PontoPoligono * criarPontoPoligono(float mouseX, float mouseY)
{
	PontoPoligono * novoPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

	// Checando se o novo ponto está vazio antes de inserir os dados
	if (novoPontoPoligono != NULL) {
		// Inicializando os valores do ponto do polígono
		novoPontoPoligono->ponto.x = mouseX;
		novoPontoPoligono->ponto.y = mouseY;
		novoPontoPoligono->ponto.cor = magenta;
		novoPontoPoligono->prox = NULL;
	}

	// Retornar ponto do polígono
	return novoPontoPoligono;
}

/*
 * FUNÇÃO PARA IMPRIMIR A LISTA DE PONTOS DOS POLÍGONOS
 */
// void imprimirPontosPoligono(ListaPoligonos * listaPoligonos)
// {
	// PontoPoligono * novoPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

	// Checando se o novo ponto está vazio antes de inserir os dados
	// if (novoPontoPoligono != NULL) {
	// 	// Inicializando os valores do ponto do polígono
	// 	novoPontoPoligono->ponto.x = mouseX;
	// 	novoPontoPoligono->ponto.y = mouseY;
	// 	novoPontoPoligono->ponto.cor = magenta;
	// 	novoPontoPoligono->prox = NULL;
	// }

	// Retornar ponto do polígono
	// return novoPontoPoligono;
// }

/*
 * FUNÇÃO PARA RETORNAR O ÚLTIMO PONTO DO POLÍGONO
 */
PontoPoligono * ultimoPontoPoligono(PontoPoligono * auxPontoPoligono)
{
	// Checar se a variável para o ponto passada ainda é nula
	if (auxPontoPoligono == NULL) {
		return NULL;
	}

	// Laço para percorrer a lista encadeada dos pontos pertencentes ao polígono
	// A variável do pontoInicial na iteração vai apontando para o próximo ponto até encontrar um ponteiro nulo
	while (auxPontoPoligono->prox != NULL) {
		auxPontoPoligono = auxPontoPoligono->prox;
	}

	// Retorna o último elemento da lista de pontos do polígono
	return auxPontoPoligono;
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA ADICIONAR UM POLÍGONO A TELA
 */
int adicionarPoligono(float mouseX, float mouseY, int statusObjeto, ListaPoligonos * listaPoligonos)
{
	// Se a lista de polígonos não foi criada ou está cheia, não é possível adicionar mais polígonos
	if (listaPoligonos == NULL || listaPoligonos->qtdPoligonos == MAX_POLIGONOS) {
		printf("Lista de poligonos nao foi criada ou esta cheia! Nao e possivel imprimir poligonos!\n");
		return 0;
	}
	//
	else {
		// Se o polígono está sendo inicializado (primeiro ponto do polígono)
		if (statusObjeto == -1) {
			// Criando o ponto inicial do polígono
			PontoPoligono * pontoInicial = criarPontoPoligono(mouseX, mouseY);

			// Inicializando a lista de polígonos com o primeiro ponto
			listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].tamanho = 1;
			listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].inicial = pontoInicial;
			printf("entrou -1!\n");
		}
		// Se o polígono está sendo desenhando (adicionando outros pontos ao polígono)
		else {
			// Criando uma variável ponto para auxílio na manipulação dos dados
			PontoPoligono * auxPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

			// Recebe os mesmos dados do ponto inicial para manipulação
			auxPontoPoligono = listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].inicial;

			// Recebe o último ponto da lista depois que percorre toda a lista
			auxPontoPoligono = ultimoPontoPoligono(auxPontoPoligono);

			// Criando o ponto do final do polígono
			PontoPoligono * pontoFinal = criarPontoPoligono(mouseX, mouseY);

			// Adicionando o ponteiro para do inicial para o próximo ponto
			auxPontoPoligono->prox = pontoFinal;

			// Adicionando mais um ponto ao tamanho do polígono
			listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].tamanho++;
			printf("entrou 1!\n");
		}

		return 1;
	}
}

/*
 * FUNÇÃO PARA EXCLUIR UM POLÍGONO DA TELA
 */
int excluirPoligono(int chave, ListaPoligonos * listaPoligonos)
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
