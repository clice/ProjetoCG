#ifndef PONTO_H
#define PONTO_H

#define MAX_PONTOS 1000

/*
 * ESTRUTURA PARA AS CORES
 */
struct Cor
{
    float red;     // Valor da cor vermelha
    float green;   // Valor da cor verde
    float blue;    // Valor da cor azul
};

/*
 * ESTRUTURA PARA O PONTO
 */
struct Ponto
{
    float x;   // Posição na largura
    float y;   // Posição na altura
    struct Cor cor;   // Estrutura das cores
};

/*
 * ESTRUTURA PARA LISTA DE PONTOS
 */
struct ListaPontos
{
    int qtdPontos;    			// Quantidade de pontos na lista
    struct Ponto pontos[MAX_PONTOS];   // Dados dos pontos da lista de pontos
};

///////////////////////////////////////////////////////////////////

/*
 * DECLARAÇÕES DAS FUNÇÕEES
 */
struct ListaPontos * criarListaPontos();

int adicionarPonto(float x, float y, struct ListaPontos * listaPontos);
int removerPonto(int ponto, struct ListaPontos * listaPontos);
int selecionarPonto(float pontoX, float pontoY, float mouseX, float mouseY, int aux);

void desenharPontos(int ponto, struct ListaPontos * listaPontos);
void imprimirListaPontos(struct ListaPontos * listaPontos);

int transladarPonto(int ponto, struct ListaPontos * listaPontos);
int rotacionarPonto(int ponto, struct ListaPontos * listaPontos);

#endif // PONTO_H