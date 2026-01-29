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
    scanf("%d", &novo_produto->codigo_produto);
    if (procurar_produto(cabeca, novo_produto->codigo_produto) != NULL) // Usa a função de busca para ver se o código já está cadastrado
    {
        printf("\nUm produto com esse código já está cadastrado!");
        free(novo_produto);
        return;
    }
    printf("\nDigte o nome do produto: ");
    novo_produto->nome = ler_texto(); // Chama a função ler_texto() criada em utils.c

    printf("\nDigite o preço do produto: ");
    scanf("%f", &novo_produto->preco_produto);

    // Lógica de inserção na lista
    novo_produto->prox = cabeca->prox; // Insere o novo produto entre a cabeça e o antigo primeiro produto
    cabeca->prox = novo_produto;       // remove o link entre a cabeça e o antigo primeiro produto, agora o primeiro é o novo
    /**
     * cabeca.prox -> primeiro_produto (Antes de adicionar o novo)
     * novo_produto.prox -> primeiro_produto
     * cabeca.prox -> novo_produto
     * Estrutura final: cabeca -> novo_produto -> primeiro_produto (O novo produto foi inserido no começo da lista)
     * O novo_produto vira o primeiro produto
     */
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
        produto_editado->nome = ler_texto(); // Chama a função do utils para ler o nome
    }

    if (opcao == 2)
    {
        float novo_preco;
        printf("\nDigite o novo preço para o produto: ");
        scanf("%f", &novo_preco);
        produto_editado->preco_produto = novo_preco;
    }
}
