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
    scanf(" %[^\n]", cpf_temp);
    limpar_buffer();

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
            printf("Novo email: (atual: %s)", cliente_alvo->email);
            scanf(" %[^\n]", cliente_alvo->email);
            limpar_buffer();
            printf("Email atualizado com sucesso!\n");
            break;

        case 3:
            printf("Novo telefone: (atual: %s)", cliente_alvo->telefone);
            scanf(" %[^\n]", cliente_alvo->telefone);
            limpar_buffer();
            printf("Numero de telefone atualizado com sucesso!\n");
            break;

        case 4:
            printf("Nova data de nascimento: (atual: %s)", cliente_alvo->data_nascimento);
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
        if( cliente_excluido->carrinho != NULL)
            apagar_lista_produtos(cliente_excluido->carrinho);

        free(cliente_excluido);
    }
    free(cabeca);

    *cabeca_main = NULL;
    printf("Memoria do sistema limpa com sucesso!\n");
}

void adiciona_ao_carrinho(Cliente *cliente_alvo, Produto *produto, int qtd)
{
    if (cliente_alvo == NULL)
        return;

    Produto *cabeca_carrinho = cliente_alvo->carrinho;
    Produto *item_no_carrinho = procurar_produto(cabeca_carrinho, produto->codigo_produto);
    if (item_no_carrinho != NULL)
    {
        printf("\nProduto adicionado com sucesso!\n");
        item_no_carrinho->quantidade += qtd;
        cabeca_carrinho->quantidade += qtd;
        return;
    }

    adiciona_produto(cabeca_carrinho, produto);
    cabeca_carrinho->quantidade += qtd;
    printf("\nProduto adicionado com sucesso!\n");
}