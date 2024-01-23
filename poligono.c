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
			printf("Poligono: %d\n", i + 1);
			printf("Quantidade de lados: %d\n", listaPoligonos->poligonos[i].qtdLados);
			printf("Centroide: (%.1f, %.1f)\n", listaPoligonos->poligonos[i].centroide.x, listaPoligonos->poligonos[i].centroide.y);
			imprimirPontosPoligono(listaPoligonos->poligonos[i].inicial);
		}
	}
}

/*
 * FUNÇÃO PARA LIBERAR O ESPAÇO DE MEMÓRIA USADO PARA ARMAZENAR A LISTA DE POLÍGONOS
 */
void liberarListaPoligonos(ListaPoligonos * listaPoligonos)
{

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
 * FUNÇÃO PARA INSERIR UM PONTO DO POLÍGONO NA LISTA DE POLÍGONOS
 */
void inserirPontoPoligono(PontoPoligono ** pontoPoligonoInicial, float mouseX, float mouseY)
{
	// Criando o novo ponto
	PontoPoligono * novoPontoPoligono = criarPontoPoligono(mouseX, mouseY);

	// Se a lista estiver vazia, o novo ponto vira o ponto inicial da lista
	if (*pontoPoligonoInicial == NULL) {
		*pontoPoligonoInicial = novoPontoPoligono;
		return;
	}

	// Variável recebe o ponteiro para o último elemento da lista
	PontoPoligono * ultimoPontoPoligono = buscarUltimoPontoPoligono(*pontoPoligonoInicial);

	// Inserir o novo ponto do polígono no último lugar da lista
	ultimoPontoPoligono->prox = novoPontoPoligono;
}

/*
 * FUNÇÃO PARA IMPRIMIR A LISTA DE PONTOS DOS POLÍGONOS
 */
void imprimirPontosPoligono(PontoPoligono * pontoPoligonoInicial)
{
	// Laço para percorrer a lista encadeada dos pontos pertencentes ao polígono
	// A variável do pontoPoligonoInicial na iteração vai apontando para o próximo ponto até encontrar um ponteiro nulo
	int i = 0;
	while (pontoPoligonoInicial->prox != NULL) {
		printf("Ponto %d: x: %.1f, y: %.1f, cor: { %.1f, %.1f, %.1f }\n",
			i + 1,
			pontoPoligonoInicial->ponto.x,
			pontoPoligonoInicial->ponto.y,
            pontoPoligonoInicial->ponto.cor.red,
            pontoPoligonoInicial->ponto.cor.green,
            pontoPoligonoInicial->ponto.cor.blue
		);

		pontoPoligonoInicial = pontoPoligonoInicial->prox;
		i++;
	}
}

/*
 * FUNÇÃO PARA BUSCAR O ÚLTIMO PONTO DO POLÍGONO
 */
PontoPoligono * buscarUltimoPontoPoligono(PontoPoligono * pontoPoligonoInicial)
{
	// Checar se a variável para o ponto passada ainda é nula
	if (pontoPoligonoInicial == NULL) {
		return NULL;
	}

	// Laço para percorrer a lista encadeada dos pontos pertencentes ao polígono
	// A variável do pontoPoligonoInicial na iteração vai apontando para o próximo ponto até encontrar um ponteiro nulo
	while (pontoPoligonoInicial->prox != NULL) {
		pontoPoligonoInicial = pontoPoligonoInicial->prox;
	}

	// Retorna o último elemento da lista de pontos do polígono
	return pontoPoligonoInicial;
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
	// Adicionar polígono
	else {
		// Se o polígono está sendo inicializado (primeiro ponto do polígono)
		if (statusObjeto == -1) {
			// Inserir o ponto do polígono no próximo ponteiro da lista
			inserirPontoPoligono(&listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].inicial, mouseX, mouseY);

			// Adicionando mais um quantidade de lados do polígono
			listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].qtdLados = 0;

			// Retornar para continuar a adição de pontos ao polígono
			return 1;
		}
		// Se o polígono está sendo desenhando (adicionando outros pontos ao polígono)
		else if (statusObjeto == 1) {
			// Inserir o ponto do polígono no próximo ponteiro da lista
			inserirPontoPoligono(&listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].inicial, mouseX, mouseY);

			// Adicionando mais um quantidade de lados do polígono
			listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].qtdLados++;

			// Retornar o status que o objeto ainda terá mais pontos
			return 1;
		}
		// Se for finalizar o polígono e ele tiver 3 ou mais lados
		else if (statusObjeto == 2 && listaPoligonos->poligonos[listaPoligonos->qtdPoligonos].qtdLados > 2) {
			// Calcular o centróide do polígono
			calcularCentroidePoligono(listaPoligonos->qtdPoligonos, listaPoligonos);

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

/*
 * FUNÇÃO PARA CALCULAR O CENTRÓIDE DO POLÍGONO
 */
void calcularCentroidePoligono(int chave, ListaPoligonos * listaPoligonos)
{
	float centroideX = 0.0, centroideY = 0.0, areaPoligono = 0.0, auxPoligono = 0.0;

	// Variáveis para iterar a lista de polígonos e fazer o cálculo do centroide do polígono
	PontoPoligono * inicialPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));
	PontoPoligono * finalPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

	// Inicializando as variáveis com o primeiro ponto e com o próximo ponto, respectivamente inicialPontoPoligono e finalPontoPoligono
	inicialPontoPoligono = listaPoligonos->poligonos[chave].inicial;
	finalPontoPoligono = listaPoligonos->poligonos[chave].inicial->prox;

	// Se a quantidade de lados do polígono for 3
	if (listaPoligonos->poligonos[chave].qtdLados == 3) {
		// Laço para percorrer toda a lista de pontos do polígono
		// Utilizando também a fórmula do cálculo do centróide de um triângulo
		while (inicialPontoPoligono != NULL) {
			// Somatório para o cálculo do centróide
			// Sendo Cx = soma(xI)
			centroideX += inicialPontoPoligono->ponto.x;
			// Sendo Cy = soma(yI)
			centroideY += inicialPontoPoligono->ponto.y;

			// Passando para os próximos pontos da lista
			inicialPontoPoligono = inicialPontoPoligono->prox;
		}

		// Atribuindo o valor do cálculo do centróide a variável referente a ele na lista de polígonos
		listaPoligonos->poligonos[chave].centroide.x = centroideX / 3;
		listaPoligonos->poligonos[chave].centroide.y = centroideY / 3;
	}
	// Se a quantidade de lados do polígono for 4 ou mais
	else if (listaPoligonos->poligonos[chave].qtdLados >= 4) {
		// Laço para percorrer toda a lista de pontos do polígono
		// Utilizando o finalPontoPoligono como condição de parada (já que ele está mais a frente na iteração)
		// Utilizando também a fórmula do cálculo do centróide de um polígono
		while (finalPontoPoligono != NULL) {
			// Variável auxiliar para o cálculo da área e do centróide do polígono
			// Realizando a subtração das variáveis que serão utilizadas nos cálculos necessários
			auxPoligono = (inicialPontoPoligono->ponto.x * finalPontoPoligono->ponto.y) - (finalPontoPoligono->ponto.x * inicialPontoPoligono->ponto.y);

			// Somatório para o cálculo do centróide
			// Sendo Cx = soma((xI + xImais1) * (xI * yImais1 - yI * xImais1)) / (6 * A)
			centroideX += (inicialPontoPoligono->ponto.x + finalPontoPoligono->ponto.x) * auxPoligono;
			// Sendo Cy = soma((yI + yImais1) * (xI * yImais1 - yI * xImais1)) / (6 * A)
			centroideY += (inicialPontoPoligono->ponto.y + finalPontoPoligono->ponto.y) * auxPoligono;

			// Sendo a área A = soma(xI * yImais1 - yI * xImais1) / 2, onde i é igual a quantidade de ponto de um polígono
			areaPoligono += auxPoligono;

			// Passando para os próximos pontos da lista
			inicialPontoPoligono = inicialPontoPoligono->prox;
			finalPontoPoligono = finalPontoPoligono->prox;
		}

		// Atribuindo a variável finalPontoPoligono com o último ponto que está na inicialPontoPoligono
		finalPontoPoligono = inicialPontoPoligono;
		inicialPontoPoligono = listaPoligonos->poligonos[chave].inicial;

		// Atribuindo o valor para finalizar a soma do cálculo da área do polígono
		auxPoligono = (finalPontoPoligono->ponto.x * inicialPontoPoligono->ponto.y) - (inicialPontoPoligono->ponto.x * finalPontoPoligono->ponto.y);
		areaPoligono += auxPoligono;
		areaPoligono = areaPoligono / 2;

		// Atribuindo o valor para finalizar a soma do cálculo do centróide
		centroideX += (inicialPontoPoligono->ponto.x + finalPontoPoligono->ponto.x) * auxPoligono;
		centroideY += (inicialPontoPoligono->ponto.y + finalPontoPoligono->ponto.y) * auxPoligono;

		// Atribuindo o valor do cálculo do centróide a variável referente a ele na lista de polígonos
		listaPoligonos->poligonos[chave].centroide.x = centroideX / (6 * areaPoligono);
		listaPoligonos->poligonos[chave].centroide.y = centroideY / (6 * areaPoligono);
	}

	printf("Centroide: (%.1f, %.1f)\n", listaPoligonos->poligonos[chave].centroide.x, listaPoligonos->poligonos[chave].centroide.y);
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
    // Se a lista de polígonos não foi criada ou a quantidade de polígonos for zero
	if (listaPoligonos == NULL || listaPoligonos->qtdPoligonos == 0) {
		printf("Lista de poligonos nao foi criada ou nao ha poligonos! Nao e possivel selecionar o poligono!\n");
		return 0;
	}
	// Remover um polígono
	else {
		// Variável para manipular os dados da lista
		Poligono * poligonos = (Poligono *)malloc(sizeof(Poligono));

		// Laço para percorrer a lista de polígonos
		for (int i = 0; i < listaPoligonos->qtdPoligonos; i++) {
			// Inicializar com os pontos do polígono sendo verificado
			poligonos[i] = listaPoligonos->poligonos[i];

			// Se o ponto passado pertencer ao poligono, retornar a chave da lista de polígonos referente ao polígono
			if (verificarPontoPoligono(mouseX, mouseY, &poligonos[i])) {
				return i;
			}
		}

		return 0;
	}
}

/*
 * FUNÇÃO PARA VERIFICAR SE O PONTO PERTENCE AO POLÍGONO
 */
bool verificarPontoPoligono(float mouseX, float mouseY, Poligono * poligono)
{
	// Se a lista de polígonos não foi criada ou a quantidade de polígonos for zero
	if (poligono == NULL) {
		printf("Lista de poligonos nao foi criada ou nao ha poligonos! Nao e possivel verificar o ponto no poligono!\n");
		return false;
	}
	// Verificar ponto no polígono
	else {
		// Variável para registrar caso o ponto faz parte do polígono
		bool dentroPoligono = false;

		// Variáveis para auxiliar a manipulação dos dados
		PontoPoligono * atualPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));
		PontoPoligono * anteriorPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

		// Inicializando as variáveis para manipulação
		atualPontoPoligono = poligono->inicial;
		anteriorPontoPoligono = NULL;

		// Laço para percorrer todos os pontos do polígono
		while (atualPontoPoligono != NULL) {
			// Conferindo se os pontos do polígono são maiores que os que foram passados
			// Os pontos do eixo Y devem estar em diferentes lados do eixo X (horizontal)
			// A expressão é usado para detectar se o raio horizontal se extende a partir do ponto passado com a
			// coordenada Y, intersectando com a borda definida pelos vertices (pontos) que compoem o polígono
			// E o ponto passado no eixo X for também menor que a coordenada X
			// Se ambas as condições forem verdadeiras, significa que o ponto está dentro do polígono

			// Checar se os raios se intersectam com a borda entre o ponto anterior e o atual
			if (anteriorPontoPoligono != NULL &&
				(anteriorPontoPoligono->ponto.y > mouseY) != (atualPontoPoligono->ponto.y > mouseY) &&
				(mouseX < (atualPontoPoligono->ponto.x - anteriorPontoPoligono->ponto.x) * (mouseY - anteriorPontoPoligono->ponto.y) / (atualPontoPoligono->ponto.y - anteriorPontoPoligono->ponto.y) + anteriorPontoPoligono->ponto.x)) {
				dentroPoligono = !dentroPoligono;
			}

			anteriorPontoPoligono = atualPontoPoligono;
			atualPontoPoligono = atualPontoPoligono->prox;
		}

		// Chechar se os raios intesectam com as bordas entre o último e primeiro pontos
		// Isso é necessário porque o laço não dá a volta para o início, então é necessa'rio pegar o último ponto e comparar com o primeiro
		if (poligono->qtdLados >= 2 &&
			(anteriorPontoPoligono->ponto.y > mouseY) != (poligono->inicial->ponto.y > mouseY) &&
			(mouseX < (poligono->inicial->ponto.x - anteriorPontoPoligono->ponto.x) * (mouseY - anteriorPontoPoligono->ponto.y) / (poligono->inicial->ponto.y - anteriorPontoPoligono->ponto.y) + anteriorPontoPoligono->ponto.x)) {
			dentroPoligono = !dentroPoligono;
		}

		return dentroPoligono;
	}
}

/*
 * FUNÇÃO PARA DESENHAR OS POLÍGONOS NA TELA
 */
void desenharPoligonos(ListaPoligonos * listaPoligonos)
{
	// Criando uma variável ponto para auxílio na manipulação dos dados
	PontoPoligono * auxPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

	glLineWidth(6.0);

	// Laço para percorrer toda a lista de polígonos
    for (int i = 0; i < listaPoligonos->qtdPoligonos; i++) {
		glBegin(GL_POLYGON);

		// Recebe os mesmos dados do ponto inicial para manipulação
		auxPontoPoligono = listaPoligonos->poligonos[i].inicial;

		// Laço para percorrer toda a lista de pontos do polígono
		while (auxPontoPoligono->prox != NULL) {
			// Imprimindo os valores e intensidades de cores RGB
			glColor3f(auxPontoPoligono->ponto.cor.red, auxPontoPoligono->ponto.cor.green, auxPontoPoligono->ponto.cor.blue);
			// Posicionando o ponto na largura e altura corretas do mouse
			glVertex2f(auxPontoPoligono->ponto.x, auxPontoPoligono->ponto.y);

			// Iteração para o próximo ponto da lista
			auxPontoPoligono = auxPontoPoligono->prox;
		}

		glEnd();
    }
}

///////////////////////////////////////////////////////////////////

/*
 * FUNÇÃO PARA TRANSLADAR UM POLÍGONO (ARRASTAR E SOLTAR)
 */
int transladarPoligono(int chave, ListaPoligonos * listaPoligonos, Matriz3Por3 * matrizTranslacaoPoligono)
{
    // Se a lista de polígonos não foi criada ou a quantidade de polígonos for zero
	if (listaPoligonos == NULL || listaPoligonos->qtdPoligonos == 0) {
		printf("Lista de poligonos nao foi criada ou nao ha poligonos! Nao e possivel transladar o poligono!\n");
		return 0;
	}
	// Transladar um polígono
	else {
		// Variável para a lista de polígonos auxiliando a manipulação de dados
		PontoPoligono * atualPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

		// Recebendo os dados do ponto inicial do polígono
		atualPontoPoligono = listaPoligonos->poligonos[chave].inicial;

		// Laço para percorrer toda a lista de pontos do polígono
		while (atualPontoPoligono->prox != NULL) {
			// Criar matriz de ponto para auxiliar nos cálculos
       		// Primeiramente, a matriz contêm as coordenadas originais do ponto atual
			Matriz3Por1 * matrizPontoPoligono = criarMatriz3Por1(atualPontoPoligono->ponto.x, atualPontoPoligono->ponto.y);

			// Realizar a multiplicação para a transformação
			matrizPontoPoligono = multiplicarMatriz3Por3PorMatriz3Por1(matrizTranslacaoPoligono, matrizPontoPoligono);

			// Atualizar a posição do ponto a partir do resultado do cálculo da transformação
			atualPontoPoligono->ponto.x = matrizPontoPoligono->matriz[0][0];
			atualPontoPoligono->ponto.y = matrizPontoPoligono->matriz[0][1];

			// Iteração para o próximo ponto da lista
			atualPontoPoligono = atualPontoPoligono->prox;
		}

		// Calcular o centróide do novo lugar para o polígono
		calcularCentroidePoligono(chave, listaPoligonos);

		return 1;
	}
}

/*
 * FUNÇÃO PARA ROTACIONAR UM POLÍGONO
 */
int rotacionarPoligono(int chave, ListaPoligonos * listaPoligonos, Matriz3Por3 * matrizRotacaoPoligono)
{
    // Se a lista de polígonos não foi criada ou a quantidade de polígonos for zero
	if (listaPoligonos == NULL || listaPoligonos->qtdPoligonos == 0) {
		printf("Lista de poligonos nao foi criada ou nao ha poligonos! Nao e possivel rotacionar o poligono!\n");
		return 0;
	}
	// Rotacionar um polígono
	else {
		// Criar a matriz3Por3 para auxiliar nos cálculos
        // Primeiramente, a matriz contêm o resultado das multiplicações necessárias para a rotação
        Matriz3Por3 * matrizCompostaPoligono = multiplicarMatrizComposta(
			listaPoligonos->poligonos[chave].centroide.x, 
			listaPoligonos->poligonos[chave].centroide.y, 
			matrizRotacaoPoligono
        );

        // Variável para a lista de polígonos auxiliando a manipulação de dados
		PontoPoligono * atualPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

		// Recebendo os dados do ponto inicial do polígono
		atualPontoPoligono = listaPoligonos->poligonos[chave].inicial;

		// Laço para percorrer toda a lista de pontos do polígono
		while (atualPontoPoligono->prox != NULL) {
			// Criar matriz de ponto para auxiliar nos cálculos
       		// Primeiramente, a matriz contêm as coordenadas originais do ponto atual
			Matriz3Por1 * matrizPontoPoligono = criarMatriz3Por1(atualPontoPoligono->ponto.x, atualPontoPoligono->ponto.y);

			// Realizar a multiplicação para a transformação
			matrizPontoPoligono = multiplicarMatriz3Por3PorMatriz3Por1(matrizCompostaPoligono, matrizPontoPoligono);

			// Atualizar a posição do ponto a partir do resultado do cálculo da transformação
			atualPontoPoligono->ponto.x = matrizPontoPoligono->matriz[0][0];
			atualPontoPoligono->ponto.y = matrizPontoPoligono->matriz[0][1];

			// Iteração para o próximo ponto da lista
			atualPontoPoligono = atualPontoPoligono->prox;
		}

		// Calcular o centróide do novo lugar para o polígono
		calcularCentroidePoligono(chave, listaPoligonos);
		
		return 1;
	}
}

/*
 * FUNÇÃO PARA ESCALAR UM POLÍGONO
 */
int escalarPoligono(int chave, ListaPoligonos * listaPoligonos, Matriz3Por3 * matrizEscalarPoligono)
{
    // Se a lista de polígonos não foi criada ou a quantidade de polígonos for zero
	if (listaPoligonos == NULL || listaPoligonos->qtdPoligonos == 0) {
		printf("Lista de poligonos nao foi criada ou nao ha poligonos! Nao e possivel rotacionar o poligono!\n");
		return 0;
	}
	// Escalar um polígono
	else {
		// Criar a matriz3Por3 para auxiliar nos cálculos
        // Primeiramente, a matriz contêm o resultado das multiplicações necessárias para a rotação
        Matriz3Por3 * matrizCompostaPoligono = multiplicarMatrizComposta(
			listaPoligonos->poligonos[chave].centroide.x, 
			listaPoligonos->poligonos[chave].centroide.y, 
			matrizEscalarPoligono
        );

        // Variável para a lista de polígonos auxiliando a manipulação de dados
		PontoPoligono * atualPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

		// Recebendo os dados do ponto inicial do polígono
		atualPontoPoligono = listaPoligonos->poligonos[chave].inicial;

		// Laço para percorrer toda a lista de pontos do polígono
		while (atualPontoPoligono->prox != NULL) {
			// Criar matriz de ponto para auxiliar nos cálculos
       		// Primeiramente, a matriz contêm as coordenadas originais do ponto atual
			Matriz3Por1 * matrizPontoPoligono = criarMatriz3Por1(atualPontoPoligono->ponto.x, atualPontoPoligono->ponto.y);

			// Realizar a multiplicação para a transformação
			matrizPontoPoligono = multiplicarMatriz3Por3PorMatriz3Por1(matrizCompostaPoligono, matrizPontoPoligono);

			// Atualizar a posição do ponto a partir do resultado do cálculo da transformação
			atualPontoPoligono->ponto.x = matrizPontoPoligono->matriz[0][0];
			atualPontoPoligono->ponto.y = matrizPontoPoligono->matriz[0][1];

			// Iteração para o próximo ponto da lista
			atualPontoPoligono = atualPontoPoligono->prox;
		}

		// Calcular o centróide do novo lugar para o polígono
		calcularCentroidePoligono(chave, listaPoligonos);
		
		return 1;
	}
}

// /*
//  * FUNÇÃO PARA TRANSLADAR UM POLÍGONO (ARRASTAR E SOLTAR)
//  */
// int transladarPoligono(int chave, ListaPoligonos * listaPoligonos, Matriz3Por3 * matrizTranslacaoPoligono)
// {
//     // Se a lista de polígonos não foi criada ou a quantidade de polígonos for zero
// 	if (listaPoligonos == NULL || listaPoligonos->qtdPoligonos == 0) {
// 		printf("Lista de poligonos nao foi criada ou nao ha poligonos! Nao e possivel transladar o poligono!\n");
// 		return 0;
// 	}
// 	// Transladar um polígono
// 	else {
// 		// Variável para a lista de polígonos auxiliando a manipulação de dados
// 		PontoPoligono * atualPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

// 		// Recebendo os dados do ponto inicial do polígono
// 		atualPontoPoligono = listaPoligonos->poligonos[chave].inicial;

// 		// Laço para percorrer toda a lista de pontos do polígono
// 		while (atualPontoPoligono->prox != NULL) {
// 			// Criar matriz de ponto para auxiliar nos cálculos
//        		// Primeiramente, a matriz contêm as coordenadas originais do ponto atual
// 			Matriz3Por1 * matrizPontoPoligono = criarMatriz3Por1(atualPontoPoligono->ponto.x, atualPontoPoligono->ponto.y);

// 			// Realizar a multiplicação para a transformação
// 			matrizPontoPoligono = multiplicarMatriz3Por3PorMatriz3Por1(matrizTranslacaoPoligono, matrizPontoPoligono);

// 			// Atualizar a posição do ponto a partir do resultado do cálculo da transformação
// 			atualPontoPoligono->ponto.x = matrizPontoPoligono->matriz[0][0];
// 			atualPontoPoligono->ponto.y = matrizPontoPoligono->matriz[0][1];

// 			// Iteração para o próximo ponto da lista
// 			atualPontoPoligono = atualPontoPoligono->prox;
// 		}

// 		// Calcular o centróide do novo lugar para o polígono
// 		calcularCentroidePoligono(chave, listaPoligonos);

// 		return 1;
// 	}
// }

// /*
//  * FUNÇÃO PARA TRANSLADAR UM POLÍGONO (ARRASTAR E SOLTAR)
//  */
// int transladarPoligono(int chave, ListaPoligonos * listaPoligonos, Matriz3Por3 * matrizTranslacaoPoligono)
// {
//     // Se a lista de polígonos não foi criada ou a quantidade de polígonos for zero
// 	if (listaPoligonos == NULL || listaPoligonos->qtdPoligonos == 0) {
// 		printf("Lista de poligonos nao foi criada ou nao ha poligonos! Nao e possivel transladar o poligono!\n");
// 		return 0;
// 	}
// 	// Transladar um polígono
// 	else {
// 		// Variável para a lista de polígonos auxiliando a manipulação de dados
// 		PontoPoligono * atualPontoPoligono = (PontoPoligono *)malloc(sizeof(PontoPoligono));

// 		// Recebendo os dados do ponto inicial do polígono
// 		atualPontoPoligono = listaPoligonos->poligonos[chave].inicial;

// 		// Laço para percorrer toda a lista de pontos do polígono
// 		while (atualPontoPoligono->prox != NULL) {
// 			// Criar matriz de ponto para auxiliar nos cálculos
//        		// Primeiramente, a matriz contêm as coordenadas originais do ponto atual
// 			Matriz3Por1 * matrizPontoPoligono = criarMatriz3Por1(atualPontoPoligono->ponto.x, atualPontoPoligono->ponto.y);

// 			// Realizar a multiplicação para a transformação
// 			matrizPontoPoligono = multiplicarMatriz3Por3PorMatriz3Por1(matrizTranslacaoPoligono, matrizPontoPoligono);

// 			// Atualizar a posição do ponto a partir do resultado do cálculo da transformação
// 			atualPontoPoligono->ponto.x = matrizPontoPoligono->matriz[0][0];
// 			atualPontoPoligono->ponto.y = matrizPontoPoligono->matriz[0][1];

// 			// Iteração para o próximo ponto da lista
// 			atualPontoPoligono = atualPontoPoligono->prox;
// 		}

// 		// Calcular o centróide do novo lugar para o polígono
// 		calcularCentroidePoligono(chave, listaPoligonos);

// 		return 1;
// 	}
// }
