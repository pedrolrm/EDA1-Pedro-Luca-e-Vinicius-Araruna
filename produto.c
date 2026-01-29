#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"

Produto *cria_lista_produto()
{
    Produto *cabeca = (Produto *)malloc(sizeof(Produto));
    if (cabeca == NULL)
    {
        printf("Falha ao alocar memória para a cabeça da lista de produtos.");
        exit(EXIT_FAILURE);
    }

    cabeca->prox = NULL; // começando a lsita vazia
    cabeca->nome = NULL; // Começando o ponteiro para nome vazio para evitar problema

    return cabeca; // retorna o endereço da primeira célula da lista
}

void listar_produtos(Produto *cabeca)
{
    Produto *atual = cabeca->prox; // começa apontando para a próxima struct de produto depois da cabeça
    while (atual != NULL)
    {
        printf("Código: %d | Nome: %s | Preço: R$ %.2f \n", atual->codigo_produto, atual->nome, atual->preco_produto);

        atual = atual->prox; // Pula para a próxima
    }
}