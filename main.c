#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "produto.h"
#include "utils.h"

int main()
{
    int opcao_principal, opcao_sub;
    int codigo_temp;
    Produto *cabeca_lista_produtos = cria_lista_produto();
    Cliente *cabeca_lista_clientes = criarListaComCabeca();

    carregar_produtos(cabeca_lista_produtos);
    carregar_clientes(cabeca_lista_clientes,cabeca_lista_produtos);

    do
    {
        printf("\n=== SISTEMA DE GESTAO ===\n");
        printf("1. Gerenciamento de Produtos\n");
        printf("2. Gerenciamento de Clientes\n");
        printf("3. Modo Compra (Carrinho)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: \n");
        scanf("%d", &opcao_principal);

        switch (opcao_principal)
        {

        // gerenciamento de produtos
        case 1:
            do
            {
                printf("\n--- MENU PRODUTOS ---\n");
                printf("1. Cadastrar Produto\n");
                printf("2. Listar Produtos\n");
                printf("3. Buscar Produto por Código\n");
                printf("4. Editar Produto\n");
                printf("5. Remover Produto\n");
                printf("0. Voltar\n");
                printf("Opção: \n");
                scanf("%d", &opcao_sub);

                switch (opcao_sub)
                {
                case 1:
                    cria_produto(cabeca_lista_produtos);
                    break;

                case 2:
                    listar_produtos(cabeca_lista_produtos);
                    break;

                case 3:
                    imprime_um_produto(cabeca_lista_produtos);
                    break;

                case 4:
                    editar_produto(cabeca_lista_produtos);
                    break;

                case 5:
                    remover_produto(cabeca_lista_produtos);
                    break;

                case 0:
                    printf("Voltando ao menu principal...\n");
                    break;

                default:
                    printf("Opcao invalida!\n");
                }
            } while (opcao_sub != 0);
            break;

            // MODULO DE CLIENTE
        case 2:
            do
            {
                printf("\n--- MENU CLIENTES ---\n");
                printf("1. Cadastrar Cliente\n");
                printf("2. Listar Clientes\n");
                printf("3. Buscar Cliente por CPF\n");
                printf("4. Editar Cliente\n");
                printf("5. Remover Cliente\n");
                printf("0. Voltar\n");
                scanf("%d", &opcao_sub);
                limpar_buffer();

                switch (opcao_sub)
                {
                case 1:
                    cadastrarCliente(cabeca_lista_clientes);
                    break;
                case 2:
                    listarClientes(cabeca_lista_clientes);
                    break;
                case 3:
                    buscarClientePorCPF(cabeca_lista_clientes);
                    break;
                case 4:
                    editarCliente(cabeca_lista_clientes);
                    break;
                case 5:
                    removerCliente(cabeca_lista_clientes);
                    break;
                case 0:
                    break;
                default:
                    printf("Opcao invalida\n");
                }
            } while (opcao_sub != 0);
            break;

        case 3:
        {
            char cpf_cliente[15];
            printf("Digite o CPF do cliente: ");
            scanf(" %[^\n]", cpf_cliente);
            limpar_buffer();
            Cliente *cliente = encontrar_cliente_por_cpf(cabeca_lista_clientes, cpf_cliente);
            if (cliente == NULL)
            {
                printf("Cliente não encontrado.\n");
                break;
            }
            do
            {
                printf("\n--- CARRINHO DE %s ---\n", cliente->nome);
                printf("1. Adicionar Produto ao Carrinho\n");
                printf("2. Listar Carrinho\n");
                printf("3. Remover Produto do Carrinho\n");
                printf("0. Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcao_sub);
                limpar_buffer();

                switch (opcao_sub)
                {
                case 1:
                    printf("Digite o código do produto: ");
                    scanf("%d", &codigo_temp);
                    limpar_buffer();

                    int qtd;
                    printf("Digite a quantidade: ");
                    scanf("%d", &qtd);
                    limpar_buffer();
                    adiciona_ao_carrinho(cliente, cabeca_lista_produtos, codigo_temp, qtd);

                    break;

                case 2:
                    listar_carrinho(cliente->carrinho);
                    break;

                case 3:
                    printf("Digite o código do produto para remover: ");
                    scanf("%d", &codigo_temp);
                    limpar_buffer();
                    remover_do_carrinho(cliente->carrinho, cabeca_lista_produtos, codigo_temp);
                    break;

                case 0:
                    printf("Voltando ao menu principal...\n");
                    break;

                default:
                    printf("Opcao invalida!\n");
                }
            } while (opcao_sub != 0);
        }
        break;

        case 0:
            printf("Saindo do sistema...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao_principal != 0);

    salvar_produtos(cabeca_lista_produtos);
    salvar_clientes(cabeca_lista_clientes);

    apagar_lista_produtos(cabeca_lista_produtos);
    liberaMemoriaTotal(&cabeca_lista_clientes);
    return 0;
}