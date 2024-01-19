#ifndef RETA_H_INCLUDED
#define RETA_H_INCLUDED

#include "ponto.h"
#define MAX_RETAS 1000


/*
 * ESTRUTURA PARA A RETA
 */
typedef struct
{
    Ponto inicio;   // Estrutura do ponto do início da reta
    Ponto fim;   // Estrutura do ponto no fim da reta
} Reta;

/*
 * ESTRUTURA PARA LISTA DE RETAS
 */
typedef struct
{
    int qtdRetas;    		  // Quantidade de retas na lista
    Reta retas[MAX_RETAS];   // Dados das retas na lista de retas
} ListaRetas;

///////////////////////////////////////////////////////////////////

/*
 * DECLARAÇÃO DAS FUNÇÕES
 */


#endif // RETA_H_INCLUDED
