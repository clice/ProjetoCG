#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#include "poligono.h"

/*
 * DECLARAÇÃO DAS CORES FIXAS
 */
Cor verde = { 0.0, 1.0, 0.0 };
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
	// Imprimir polígonos
	else {
		printf("Quantidade de poligonos: %d\n", listaPoligonos->qtdPoligonos);

		for (int i = 0; i < listaPoligonos->qtdPoligonos; i++) {
			printf("Poligono %d\n", i + 1);
			printf("Quantidade de lados: %d\n", listaPoligonos->poligonos[i].qtdLados);
			imprimirPontosPoligono(listaPoligonos->poligonos[i].inicial);
		}
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
		novoPontoPoligono->ponto.cor = verde;
		novoPontoPoligono->prox = NULL;
	}

	// Retornar ponto do polígono
	return novoPontoPoligono;
}

/*
 * FUNÇÃO PARA IMPRIMIR A LISTA DE PONTOS DOS POLÍGONOS
 */
void imprimirPontosPoligono(PontoPoligono * pontoInicial)
{
	// Checar se a variável para o ponto passada ainda é nula
	if (pontoInicial == NULL) {
		return NULL;
	}

	// Laço para percorrer a lista encadeada dos pontos pertencentes ao polígono
	// A variável do pontoInicial na iteração vai apontando para o próximo ponto até encontrar um ponteiro nulo
	int i = 0;
	while (pontoInicial->prox != NULL) {
		printf("Ponto %d: x: %.1f, y: %.1f\n",
			i + 1,
			pontoInicial->ponto.x,
			pontoInicial->ponto.y
		);
		
		pontoInicial = pontoInicial->prox;
		i++;
	}
}

/*
 * FUNÇÃO PARA RETORNAR O ÚLTIMO PONTO DO POLÍGONO
 */
PontoPoligono * ultimoPontoPoligono(PontoPoligono * pontoInicial)
{
	// Checar se a variável para o ponto passada ainda é nula
	if (pontoInicial == NULL) {
		return NULL;
	}

	// Laço para percorrer a lista encadeada dos pontos pertencentes ao polígono
	// A variável do pontoInicial na iteração vai apontando para o próximo ponto até encontrar um ponteiro nulo
	while (pontoInicial->prox != NULL) {
		pontoInicial = pontoInicial->prox;
	}

	// Retorna o último elemento da lista de pontos do polígono
	return pontoInicial;
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA ADICIONAR UM POLÍGONO A TELA
 */
int adicionarPoligono(float mouseX, float mouseY, int statusObjeto, ListaPoligonos * listaPoligonos)
{
	// Se a lista de polígonos não foi criada ou está cheia, não é possível adicionar mais polígonos
	if (listaPoligonos == NULL || listaPoligonos->qtdPoligonos == MAX_POLIGONOS) {
		printf("Lista de poligonos nao foi criada ou esta cheia! Nao e possivel adicionar o poligono!\n");
		return 0;
	}
	//
	else {
		printf("listaPoligonos->qtdPoligonos: %d\n", listaPoligonos->qtdPoligonos);

		// Se o polígono está sendo inicializado (primeiro ponto do polígono)
		if (statusObjeto == -1) {
			// Criando o ponto inicial do polígono
			PontoPoligono * pontoInicial = criarPontoPoligono(mouseX, mouseY);

			// Inicializando a lista de polígonos com o primeiro ponto
			listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].inicial = pontoInicial;

			// Adicionando mais um quantidade de lados do polígono
			listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].qtdLados++;

			// Retornar para continuar a adição de pontos ao polígono
			printf("statusObjeto: %d!\n", statusObjeto);
			printf("qtdLados: %d!\n", listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].qtdLados);
			return 1;
		}
		// Se o polígono está sendo desenhando (adicionando outros pontos ao polígono)
		else if (statusObjeto == 1) {
			// Criando uma variável ponto para auxílio na manipulação dos dados
			PontoPoligono * auxPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

			// Recebe os mesmos dados do ponto inicial para manipulação
			auxPontoPoligono = listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].inicial;

			// Recebe o último ponto da lista depois que percorre toda a lista
			auxPontoPoligono = ultimoPontoPoligono(auxPontoPoligono);

			// Criando o ponto do final do polígono
			PontoPoligono * pontoFinal = criarPontoPoligono(mouseX, mouseY);

			// Adicionando o ponteiro para o próximo ponto
			auxPontoPoligono->prox = pontoFinal;

			// Adicionando mais um quantidade de lados do polígono
			listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].qtdLados++;

			// Retornar o status que o objeto ainda terá mais pontos
			printf("statusObjeto: %d!\n", statusObjeto);
			printf("qtdLados: %d!\n", listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].qtdLados);
			return 1;
		} 
		// Se for finalizar o polígono
		else {
			// Se o polígono tem 3 ou mais lados
			if (listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].qtdLados > 2) {
				// Criando uma variável ponto para auxílio na manipulação dos dados
				PontoPoligono * auxPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

				// Recebe os mesmos dados do ponto inicial para manipulação
				auxPontoPoligono = listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].inicial;

				// // Laço para percorrer toda a lista de pontos do polígono
				// while (listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].inicial != NULL) {
				// 	// Movendo para o próximo ponto da lista de pontos para pegar o ponto final
				// 	auxPontoPoligono = auxPontoPoligono->prox;

				// 	// Calcular o ponto central das "retas" que compoem o polígono
				// 	listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].central.x = (listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].inicial->ponto.x + auxPontoPoligono->ponto.x) / 2;
				// 	listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].central.y = (listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].inicial->ponto.y + auxPontoPoligono->ponto.y) / 2;

				// 	// Adicionando a cor do ponto central da "reta"
				// 	listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].central.cor = magenta;

				// 	// Movendo para o próximo ponto da lista de pontos
				// 	listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].inicial = listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].inicial->prox;
				// }
							
				printf("statusObjeto: %d!\n", statusObjeto);
				printf("qtdLados: %d!\n", listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].qtdLados);

				// Acrescentando um polígono a lista
				listaPoligonos->qtdPoligonos++;

				// Retornar ao status inicial para finalizar o polígono	
				return -1;
			}

			// Se não tem lados o suficiente para montar um polígono
            printf("Nao ha lados suficientes para montar o poligono!\n");
            return 1;
		}
	}
}

/*
 * FUNÇÃO PARA EXCLUIR UM POLÍGONO DA TELA
 */
int excluirPoligono(int chave, ListaPoligonos * listaPoligonos)
{
	// Se a lista de polígonos não foi criada ou a quantidade de polígonos for zero
	if (listaPoligonos == NULL || listaPoligonos->qtdPoligonos == 0) {
		printf("Lista de poligonos nao foi criada ou nao ha poligonos! Nao e possivel excluir o poligono!\n");
		return 0;
	}
	// Remover um polígono
	else {
		// Laço para percorrer a lista de polígonos a partir da chave do polígono até o final da lista
        // Para não quebrar a integridade da lista
		for (int i = chave; i < listaPoligonos->qtdPoligonos; i++) {
			listaPoligonos->poligonos[i] = listaPoligonos->poligonos[i + 1];
		}

		// Diminuir uma unidade da quantidade de polígonos
		listaPoligonos->qtdPoligonos--;

		printf("Poligono excluido com sucesso!\n");
		return 1;
	}
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
