#ifndef RETA_H
#define RETA_H

#define MAX_RETAS 1000

/*
 * ESTRUTURA PARA A RETA
 */
typedef struct
{
    Ponto inicio;   // Estrutura do ponto do início da reta
    Ponto centro;   // Estrutura do ponto do centro da reta
    Ponto fim;   // Estrutura do ponto no fim da reta
} Reta;

/*
 * ESTRUTURA PARA LISTA DE RETAS
 */
typedef struct
{
    int qtdRetas;    		  // Quantidade de retas na lista
    Reta retas[MAX_PONTOS];   // Dados das retas na lista de retas
} ListaRetas;

///////////////////////////////////////////////////////////////////

/*
 * DECLARAÇÃO DAS FUNÇÕES
 */

#endif // RETA_H