#ifndef PONTO_H
#define PONTO_H

#define MAX_PONTOS 1000

/*
 * ESTRUTURA PARA AS CORES
 */
typedef struct
{
    float red;     // Valor da cor vermelha
    float green;   // Valor da cor verde
    float blue;    // Valor da cor azul
} Cor;

/*
 * ESTRUTURA PARA O PONTO
 */
typedef struct
{
    float x;   // Posição na largura
    float y;   // Posição na altura
    Cor cor;   // Estrutura das cores
} Ponto;

/*
 * ESTRUTURA PARA LISTA DE PONTOS
 */
typedef struct
{
    int qtdPontos;    			// Quantidade de pontos na lista
    Ponto pontos[MAX_PONTOS];   // Dados dos pontos da lista de pontos
} ListaPontos;

///////////////////////////////////////////////////////////////////

/*
 * DECLARAÇÕES DAS FUNÇÕEES
 */
ListaPontos * criarListaPontos();

int adicionarPonto(float x, float y, ListaPontos * listaPontos);
int removerPonto(int ponto, ListaPontos * listaPontos);
int selecionarPonto(float pontoX, float pontoY, float mouseX, float mouseY, int aux);

void desenharPontos(int ponto, ListaPontos * listaPontos);
void imprimirListaPontos(ListaPontos * listaPontos);

int transladarPonto(int ponto, ListaPontos * listaPontos);
int rotacionarPonto(int ponto, ListaPontos * listaPontos);

#endif // PONTO_H
