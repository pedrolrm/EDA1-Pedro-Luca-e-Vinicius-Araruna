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
    if (atual == NULL) {
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

Produto *cria_produto(Produto *cabeca)
{
    Produto *novo_produto = (Produto *)(malloc(sizeof(Produto))); // Cria novo produto solto na memória
    if (novo_produto == NULL)
    {
        printf("\nFalha ao alocar memória para novo produto\n");
        exit(EXIT_FAILURE);
    }

    printf("\nDigite o código do produto: ");
    scanf("%d", &novo_produto->codigo_produto);
    limpar_buffer();
    if (procurar_produto(cabeca, novo_produto->codigo_produto) != NULL) // Usa a função de busca para ver se o código já está cadastrado
    {
        printf("\nUm produto com esse código já está cadastrado!");
        free(novo_produto);
        return NULL;
    }
    printf("\nDigte o nome do produto: ");
    novo_produto->nome = ler_texto();

    do {
        printf("Digite o preço do produto: ");
        scanf("%f", &novo_produto->preco_produto);
        limpar_buffer();

        if(novo_produto->preco_produto <= 0)
        printf("Erro: Preço deve ser positivo.\n");
        
    } while(novo_produto->preco_produto <= 0);
   

    do {
        printf("Digite a quantidade inicial em estoque: ");
        scanf("%d", &novo_produto->quantidade);
        limpar_buffer();

        if(novo_produto->quantidade < 0)
         printf("Erro: Quantidade não pode ser negativa.\n");

    } while(novo_produto->quantidade < 0);

    novo_produto->prox = NULL;

    return novo_produto;
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
    printf("Você deseja editar: \n(1): Nome do produto \n(2): Preço do produto\n");
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
        scanf("%f", &novo_preco);
        produto_editado->preco_produto = novo_preco;
    }
}

void remover_produto(Produto *cabeca, int codigo_produto)
{
    Produto *anterior = cabeca;
    Produto *atual = cabeca->prox;

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

Produto *procura_fim(Produto *cabeca)
{
    Produto *fim = cabeca;
    while (fim->prox != NULL)
    {
        fim = fim->prox;
    }
    return fim;
}

void adiciona_produto(Produto *cabeca, Produto *novo_produto)
{
    // Lógica de inserção na lista
    novo_produto->prox = cabeca->prox; // Insere o novo produto entre a cabeça e o antigo primeiro produto
    cabeca->prox = novo_produto;       // remove o link entre a cabeça e o antigo primeiro produto, agora o primeiro é o novo
}


// FUNCOES DE ESTOQUE

int baixarEstoque(Produto *cabeca, int codigo, int qtd_requerida){
    Produto *p = procurar_produto(cabeca,codigo);

    if(p == NULL || p->quantidade < qtd_requerida){
        printf("Estoque insuficiente ou produto nao encontrado.\n");
        return 0;
    }

    p->quantidade -= qtd_requerida;
    return 1;
}

void devolverEstoque(Produto *cabeca, int codigo, int qtd_devolvida){
    Produto *p = procurar_produto(cabeca,codigo);

    if(p != NULL){
        p->quantidade += qtd_devolvida;
    }
}