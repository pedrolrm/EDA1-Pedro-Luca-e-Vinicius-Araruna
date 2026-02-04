#include "clientes.h"
#include "utils.h"

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
    int cpf_valido = 0;
    printf("\n--- Novo Cadastro ---\n");
    do
    {
        printf("CPF: ");
        scanf(" %[^\n]", cpf_temp);
        limpar_buffer();

        if (!apenasNumeros(cpf_temp))
            printf("Erro: O CPF deve conter apenas numeros! Tente novamente!\n");
        else if (encontrar_cliente_por_cpf(cabeca, cpf_temp) != NULL)
        {
            printf("Erro: CPF ja cadastrado!");
            return;
        }
        else
        {
            cpf_valido = 1;
        }
    } while (!cpf_valido);

    Cliente *novo_cliente = calloc(1, sizeof(Cliente));

    if (!novo_cliente)
    {
        printf("Erro: falha ao alocar struct\n");
        return;
    }

    novo_cliente->carrinho = cria_lista_carrinho();
    novo_cliente->carrinho->quantidade = 0;
    strcpy(novo_cliente->cpf, cpf_temp);
    printf("Nome Completo: ");
    novo_cliente->nome = ler_texto();

    printf("Email: \n");
    scanf(" %[^\n]", novo_cliente->email);
    limpar_buffer();

    printf("Telefone: \n");
    scanf(" %[^\n]", novo_cliente->telefone);
    limpar_buffer();

    printf("Data de Nascimento: \n");
    scanf(" %[^\n]", novo_cliente->data_nascimento);
    limpar_buffer();

    novo_cliente->prox = cabeca->prox;
    cabeca->prox = novo_cliente;

    cabeca->total_clientes++;

    printf("Cliente cadastrado com sucesso!\n");
}

void listarClientes(Cliente *cabeca)
{
    if(cabeca->total_clientes == 0){
        printf("\n--- Lista de clientes vazia --\n");
        return;
    }

    printf("\n---Lista de Clientes (Total: %d) ---\n",cabeca->total_clientes);
    Cliente *cliente_atual = cabeca->prox;
    while (cliente_atual != NULL)
    {
        printf("CPF: %s  |  Nome: %s\n", cliente_atual->cpf, cliente_atual->nome);
        cliente_atual = cliente_atual->prox;
    }
    printf("----------------------------\n");
}

void buscarClientePorCPF(Cliente *cabeca)
{
    char cpf_busca[15];
    printf("\n--- Buscar Cliente por CPF ---\n");
    printf("Digite o CPF do cliente: ");
    scanf(" %[^\n]", cpf_busca);
    limpar_buffer();

    Cliente *cliente_encontrado = encontrar_cliente_por_cpf(cabeca, cpf_busca);

    if (cliente_encontrado == NULL)
    {
        printf("Cliente com CPF %s nao encontrado!\n", cpf_busca);
        return;
    }

    printf("\n--- Dados do Cliente ---\n");
    printf("CPF: %s\n", cliente_encontrado->cpf);
    printf("Nome: %s\n", cliente_encontrado->nome);
    printf("Email: %s\n", cliente_encontrado->email);
    printf("Telefone: %s\n", cliente_encontrado->telefone);
    printf("Data de Nascimento: %s\n", cliente_encontrado->data_nascimento);
    printf("------------------------\n");
}

void editarCliente(Cliente *cabeca)
{
    char busca_cpf[15];
    printf("\n Digite o CPF do cliente para editar: ");
    scanf(" %[^\n]", busca_cpf);
    limpar_buffer();

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
        limpar_buffer();

        switch (opcao)
        {
        case 1:
            printf("Novo nome: ");

            free(cliente_alvo->nome);
            cliente_alvo->nome = ler_texto();

            printf("Nome atualizado com sucesso!\n");
            break;

        case 2:
            printf("(atual: %s) Novo email: ", cliente_alvo->email);
            scanf(" %[^\n]", cliente_alvo->email);
            limpar_buffer();
            printf("Email atualizado com sucesso!\n");
            break;

        case 3:
            printf("(atual: %s) Novo telefone: ", cliente_alvo->telefone);
            scanf(" %[^\n]", cliente_alvo->telefone);
            limpar_buffer();
            printf("Numero de telefone atualizado com sucesso!\n");
            break;

        case 4:
            printf(" (atual: %s) Nova data de nascimento: ", cliente_alvo->data_nascimento);
            scanf(" %[^\n]", cliente_alvo->data_nascimento);
            limpar_buffer();
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
    if (cabeca->prox == NULL)
    {
        printf("\nErro: Nao ha clientes cadastrados no sistema!\n");
        return;
    }

    char busca_cpf[15];
    printf("\n CPF para remover: ");
    scanf(" %[^\n]", busca_cpf);
    limpar_buffer();
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

    cabeca->total_clientes--;

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

void remover_do_carrinho(ItemCarrinho *carrinho, Produto *cabeca, int codigo_produto)
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
    devolverEstoque(cabeca, codigo_produto, atual->quantidade);
    anterior->prox = atual->prox;
    free(atual);
    printf("Produto removido do carrinho.\n");
}

void adiciona_ao_carrinho(Cliente *cliente_alvo, Produto *cabeca, int codigo_produto, int qtd)
{
    Produto *produto = procurar_produto(cabeca, codigo_produto);

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
            baixarEstoque(cabeca, produto->codigo_produto, qtd);
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
    baixarEstoque(cabeca, produto->codigo_produto, qtd);
    printf("Produto adicionado ao carrinho!\n");
}