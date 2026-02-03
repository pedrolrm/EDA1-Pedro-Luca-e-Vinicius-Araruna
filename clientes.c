#include "clientes.h"

Cliente *criarListaComCabeca()
{
    Cliente *cabeca = calloc(1, sizeof(Cliente));
    if (cabeca == NULL)
    {
        printf("Erro ao criar a lista!\n");
        exit(EXIT_FAILURE);
    }
    return cabeca;
}

Cliente *encontrar_cliente_por_cpf(Cliente *cabeca, char *cpf)
{
    Cliente *cliente_atual = cabeca->prox;

    while (cliente_atual != NULL)
    {
        if (strcmp(cliente_atual->cpf, cpf) == 0)
            return cliente_atual;

        cliente_atual = cliente_atual->prox;
    }

    return NULL;
}

void cadastrarCliente(Cliente *cabeca)
{
    char cpf_temp[15];
    printf("\n--- Novo Cadastro ---\n");
    printf("CPF: ");
    scanf("%[^\n]", cpf_temp);

    if (encontrar_cliente_por_cpf(cabeca, cpf_temp) != NULL)
    {
        printf("Erro: CPF ja cadastrado!");
        return;
    }
    Cliente *novo_cliente = calloc(1, sizeof(Cliente));

    if (!novo_cliente)
    {
        printf("Erro: falha ao alocar struct\n");
        return;
    }

    novo_cliente->carrinho = cria_lista_produto();
    novo_cliente->carrinho->quantidade = 0;
    strcpy(novo_cliente->cpf, cpf_temp);
    printf("Nome Completo: ");
    novo_cliente->nome = ler_texto();

    printf("Email: \n");
    scanf("%[^\n]", novo_cliente->email);
    printf("Telefone: \n");
    scanf("%[^\n]", novo_cliente->telefone);
    printf("Data de Nascimento: \n");
    scanf("%[^\n]", novo_cliente->data_nascimento);

    novo_cliente->prox = cabeca->prox;
    cabeca->prox = novo_cliente;

    printf("Cliente cadastrado com sucesso!\n");
}

void listarClientes(Cliente *cabeca)
{

    Cliente *cliente_atual = cabeca->prox;

    if (cliente_atual == NULL)
    {
        printf("\n--- Lista de clientes vazia ---\n");
    }

    printf("\n---Lista de Clientes ---\n");
    while (cliente_atual != NULL)
    {
        printf("CPF: %s  |  Nome: %s\n", cliente_atual->cpf, cliente_atual->nome);
        cliente_atual = cliente_atual->prox;
    }
    printf("----------------------------\n");
}

void editarCliente(Cliente *cabeca)
{
    char busca_cpf[15];
    printf("\n Digite o CPF do cliente para editar: ");
    scanf("%[^\n]", busca_cpf);

    Cliente *cliente_alvo = encontrar_cliente_por_cpf(cabeca, busca_cpf);

    if (cliente_alvo == NULL)
    {
        printf("Cliente nao encontrado!\n");
        return;
    }

    int opcao;

    do
    {
        printf("\n Editando: %s\n", cliente_alvo->nome);
        printf("1. Alterar Nome\n");
        printf("2. Alterar Email\n");
        printf("3. Alterar Telefone\n");
        printf("4. Alterar Data de Nascimento\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha sua opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Novo nome: ");

            free(cliente_alvo->nome);
            cliente_alvo->nome = ler_texto();

            printf("Nome atualizado com sucesso!\n");
            break;

        case 2:
            printf("Novo email: (atual: %s)", cliente_alvo->email);
            scanf("%[^\n]", cliente_alvo->email);
            printf("Email atualizado com sucesso!\n");
            break;

        case 3:
            printf("Novo telefone: (atual: %s)", cliente_alvo->telefone);
            scanf("%[^\n]", cliente_alvo->telefone);
            printf("Numero de telefone atualizado com sucesso!\n");
            break;

        case 4:
            printf("Nova data de nascimento: (atual: %s)", cliente_alvo->data_nascimento);
            scanf("%[^\n]", cliente_alvo->data_nascimento);
            printf("Data de Nascimento atualizada com sucesso!\n");
            break;

        case 0:
            printf("Finalizando edicao!\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 0);
}

void removerCliente(Cliente *cabeca)
{
    char busca_cpf[15];
    printf("\n CPF para remover: ");
    scanf("%[^\n]", busca_cpf);
    Cliente *cliente_anterior = cabeca;
    Cliente *cliente_atual = cabeca->prox;

    while (cliente_atual != NULL && strcmp(cliente_atual->cpf, busca_cpf) != 0)
    {
        cliente_anterior = cliente_atual;
        cliente_atual = cliente_atual->prox;
    }

    if (cliente_atual == NULL)
    {
        printf("CPF nao encontrado!\n");
        return;
    }

    cliente_anterior->prox = cliente_atual->prox;

    if (cliente_atual->nome != NULL)
    {
        free(cliente_atual->nome);
    }
    free(cliente_atual);

    printf("Cliente removido com sucesso!\n");
}

void liberaMemoriaTotal(Cliente **cabeca_main)
{
    Cliente *cabeca = *cabeca_main;
    if (!cabeca)
        return;

    Cliente *cliente_atual = cabeca->prox;

    while (cliente_atual != NULL)
    {
        Cliente *cliente_excluido = cliente_atual;

        cliente_atual = cliente_atual->prox;

        if (cliente_excluido->nome)
            free(cliente_excluido->nome);
        ItemCarrinho *item_atual = cliente_excluido->carrinho->prox;
        while (item_atual != NULL)
        {
            ItemCarrinho *item_excluido = item_atual;
            item_atual = item_atual->prox;
            free(item_excluido);
        }
        free(cliente_excluido->carrinho);
        free(cliente_excluido);
    }
    free(cabeca);

    *cabeca_main = NULL;
    printf("Memoria do sistema limpa com sucesso!\n");
}

// Funções de carrinho

ItemCarrinho *cria_lista_carrinho()
{
    ItemCarrinho *cabeca = (ItemCarrinho *)malloc(sizeof(ItemCarrinho));
    if (cabeca == NULL)
    {
        printf("\nFalha ao alocar memória para o carrinho\n");
        exit(EXIT_FAILURE);
    }
    cabeca->prox = NULL;
    cabeca->produto = NULL;
    return cabeca;
}

void listar_carrinho(ItemCarrinho *cabeca)
{
    ItemCarrinho *atual = cabeca->prox;
    if (atual == NULL)
    {
        printf("\nCarrinho Vazio\n");
        return;
    }

    printf("\nProdutos no carrinho: \n");
    while (atual != NULL)
    {
        printf("\nCódigo: %d | Nome: %s | | Quantidade: %d | Preço (Unidade): R$ %.2f | Preço (Subtotal): R$ %.2f\n",
               atual->produto->codigo_produto, atual->produto->nome, atual->quantidade,
               atual->produto->preco_produto, atual->quantidade * atual->produto->preco_produto);
        atual = atual->prox;
    }
    printf("Total: %.2f\n", calcular_total_carrinho(cabeca));
}

float calcular_total_carrinho(ItemCarrinho *cabeca)
{
    float total = 0.0;
    ItemCarrinho *atual = cabeca->prox;
    while (atual != NULL)
    {
        total += atual->quantidade * atual->produto->preco_produto;
        atual = atual->prox;
    }
    return total;
}

void remover_do_carrinho(ItemCarrinho *carrinho, int codigo_produto)
{
    ItemCarrinho *anterior = carrinho;
    ItemCarrinho *atual = carrinho->prox;
    while (atual != NULL && atual->produto->codigo_produto != codigo_produto)
    {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL)
    {
        printf("Produto não encontrado no carrinho.\n");
        return;
    }
    anterior->prox = atual->prox;
    free(atual);
    printf("Produto removido do carrinho.\n");
}

void adiciona_ao_carrinho(Cliente *cliente_alvo, Produto *produto, int qtd)
{
    if (cliente_alvo == NULL || produto == NULL || qtd <= 0)
    {
        printf("\nFalha ao adicionar produto ao carrinho\n");
        return;
    }

    if (produto->quantidade < qtd)
    {
        printf("Sem capacidade no estoque para o produto %s", produto->nome);
        return;
    }

    ItemCarrinho *cabeca_carrinho = cliente_alvo->carrinho;
    ItemCarrinho *atual = cabeca_carrinho->prox;

    while (atual != NULL)
    {
        if (atual->produto->codigo_produto == produto->codigo_produto)
        {
            atual->quantidade += qtd;
            printf("\nProduto adicionado ao carrinho!\n");
            return;
        }
        atual = atual->prox;
    }

    ItemCarrinho *novo_item = (ItemCarrinho *)malloc(sizeof(ItemCarrinho));
    if (novo_item == NULL)
    {
        printf("Falha ao alocar memória para item do carrinho.\n");
        return;
    }
    novo_item->produto = produto;
    novo_item->quantidade = qtd;
    novo_item->prox = cabeca_carrinho->prox;
    cabeca_carrinho->prox = novo_item;
    printf("Produto adicionado ao carrinho!\n");
}