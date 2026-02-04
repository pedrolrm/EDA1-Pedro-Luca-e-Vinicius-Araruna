#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"
#include "utils.h"

Produto *cria_lista_produto()
{
    Produto *cabeca = (Produto *)malloc(sizeof(Produto));
    if (cabeca == NULL)
    {
        printf("Falha ao alocar memória para a cabeça da lista de produtos.");
        exit(EXIT_FAILURE);
    }

    cabeca->prox = NULL;
    cabeca->nome = NULL;

    return cabeca;
}

void listar_produtos(Produto *cabeca)
{
    Produto *atual = cabeca->prox;
    if (atual == NULL)
    {
        printf("\n--- Lista de Produtos Vazia ---\n");
        return;
    }
    printf("\n--- Lista de Produtos ---\n");
    while (atual != NULL)
    {
        printf("Código: %d | Nome: %s | Preço: R$ %.2f | Estoque: %d\n", atual->codigo_produto, atual->nome, atual->preco_produto, atual->quantidade);

        atual = atual->prox;
    }
    printf("----------------------------\n");
}

Produto *procurar_produto(Produto *cabeca, int codigo)
{
    Produto *atual = cabeca->prox;
    while (atual != NULL && codigo != atual->codigo_produto)
    {
        atual = atual->prox;
    }
    return atual;
}

void cria_produto(Produto *cabeca)
{
    Produto *novo_produto = (Produto *)(malloc(sizeof(Produto))); // Cria novo produto solto na memória
    if (novo_produto == NULL)
    {
        printf("\nFalha ao alocar memória para novo produto\n");
        exit(EXIT_FAILURE);
    }

    printf("\nDigite o código do produto: ");
    while (scanf("%d", &novo_produto->codigo_produto) != 1)
    {
        printf("\nERRO: Digite um número inteiro para o código!\n");
        limpar_buffer();
        printf("\nDigite o código do produto: ");
    }

    if (procurar_produto(cabeca, novo_produto->codigo_produto) != NULL) // Usa a função de busca para ver se o código já está cadastrado
    {
        printf("\nUm produto com esse código já está cadastrado!\n");
        free(novo_produto);
        return;
    }
    printf("\nDigte o nome do produto: ");
    novo_produto->nome = ler_texto();

    printf("\nDigite o preço do produto: ");
    while (scanf("%f", &novo_produto->preco_produto) != 1 || novo_produto->preco_produto <= 0)
    {
        printf("\nERRO: Digite um valor válido!\n");
        printf("\nDigite o preço do produto: ");
        limpar_buffer();
    }

    printf("\nDigite a quantidade inicial em estoque: ");
    while (scanf("%d", &novo_produto->quantidade) != 1 || novo_produto->quantidade < 0)
    {
        printf("\nERRO: Digite um valor válido!\n");
        printf("\nDigite a quantidade inicial em estoque: ");
        limpar_buffer();
    }

    // Lógica de inserção na lista
    novo_produto->prox = cabeca->prox; // Insere o novo produto entre a cabeça e o antigo primeiro produto
    cabeca->prox = novo_produto;       // remove o link entre a cabeça e o antigo primeiro produto, agora o primeiro é o novo
    printf("\nProduto cadastrado com sucesso!\n");
}

void editar_produto(Produto *cabeca)
{
    int codigo;
    printf("\nDigite o código do produto: ");
    scanf("%d", &codigo);

    Produto *produto_editado = (procurar_produto(cabeca, codigo));

    if (produto_editado == NULL)
    {
        printf("\nProduto com o código %d não encontrado", codigo);
        return;
    }

    int opcao;
    printf("Você deseja editar: \n(1): Nome do produto \n(2): Preço do produto\n(3): Quantidade em estoque\n");
    scanf("%d", &opcao);
    if (opcao == 1)
    {
        free(produto_editado->nome); // limpa a memória do nome antigo
        printf("\nDigite o novo nome para o produto: ");
        produto_editado->nome = ler_texto();
    }

    if (opcao == 2)
    {
        float novo_preco;
        printf("\nDigite o novo preço para o produto: ");
        while (scanf("%f", &novo_preco) != 1 || novo_preco <= 0)
        {
            printf("\nDigite um valor válido para o preço!\n");
            printf("\nDigite o novo preço para o produto: ");
            limpar_buffer();
        }

        produto_editado->preco_produto = novo_preco;
    }

    if (opcao == 3)
    {
        int nova_quantidade;
        printf("\nDigite a nova quantidade em estoque: ");
        while (scanf("%d", &nova_quantidade) != 1 || nova_quantidade < 0)
        {
            printf("\nDigite uma quantidade válida para o estoque!\n");
            printf("\nDigite a nova quantidade em estoque: ");
            limpar_buffer();
        }

        produto_editado->quantidade = nova_quantidade;
    }
}

void remover_produto(Produto *cabeca)
{
    Produto *anterior = cabeca;
    Produto *atual = cabeca->prox;

    int codigo_produto;
    printf("Digite o código para remover: ");
    scanf("%d", &codigo_produto);

    while (atual != NULL && atual->codigo_produto != codigo_produto)
    {
        atual = atual->prox;
        anterior = anterior->prox;
    }

    if (atual == NULL)
    {
        printf("O produto de código %d não foi encontrado!", codigo_produto);
        return;
    }

    anterior->prox = atual->prox; // Salva o próximo como um depois do produto que vai ser excluido

    free(atual->nome);
    free(atual);
    printf("O produto de código %d foi excluido", codigo_produto);
}

void apagar_lista_produtos(Produto *cabeca)
{
    Produto *atual = cabeca->prox;
    Produto *proximo;

    while (atual != NULL)
    {
        proximo = atual->prox;
        free(atual->nome);
        free(atual);
        atual = proximo;
    }
    free(cabeca->nome); // apaga o inicio da lista
    free(cabeca);
    printf("\nLista apagada com sucesso!\n");
    return;
}

// FUNCOES DE ESTOQUE

int baixarEstoque(Produto *cabeca, int codigo, int qtd_requerida)
{
    Produto *p = procurar_produto(cabeca, codigo);

    if (p == NULL || p->quantidade < qtd_requerida)
    {
        printf("Estoque insuficiente ou produto nao encontrado.\n");
        return 0;
    }

    p->quantidade -= qtd_requerida;
    return 1;
}

void devolverEstoque(Produto *cabeca, int codigo, int qtd_devolvida)
{
    Produto *p = procurar_produto(cabeca, codigo);

    if (p != NULL)
    {
        p->quantidade += qtd_devolvida;
    }
}

void imprime_um_produto(Produto *cabeca)
{
    int codigo;
    printf("\nDigite o Codigo: ");
    scanf("%d", &codigo);
    limpar_buffer();
    Produto *produto_selecionado = procurar_produto(cabeca, codigo);

    if (produto_selecionado)
    {
        printf("\nProduto encontrado:\n");
        printf("Código: %d | Nome: %s | Preço: R$ %.2f | Estoque: %d\n", produto_selecionado->codigo_produto, produto_selecionado->nome, produto_selecionado->preco_produto, produto_selecionado->quantidade);
    }
    else
    {
        printf("Produto não encontrado.\n");
    }
}