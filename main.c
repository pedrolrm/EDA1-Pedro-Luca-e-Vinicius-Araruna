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

    do
    {
        printf("\n=== SISTEMA DE GESTAO ===\n");
        printf("1. Gerenciamento de Produtos\n");
        printf("2. Gerenciamento de Clientes\n");
        printf("3. Modo Compra (Carrinho)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
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
                printf("3. Buscar Produto por Codigo\n");
                printf("4. Editar Produto\n");
                printf("5. Remover Produto\n");
                printf("0. Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcao_sub);

                switch (opcao_sub)
                {
                case 1:
                    Produto *novo_produto = cria_produto(cabeca_lista_produtos);
                    if (novo_produto != NULL)
                    {
                        adiciona_produto(cabeca_lista_produtos, novo_produto);
                        break;
                    }
                    else
                    {
                        break;
                    }

                case 2:
                    listar_produtos(cabeca_lista_produtos);
                    break;

                case 3:
                    printf("Digite o Codigo: ");
                    scanf("%d", &codigo_temp);
                    Produto *produto_selecionado = procurar_produto(cabeca_lista_produtos, codigo_temp);

                    if (produto_selecionado)
                    {
                        printf("Produto: %s | Preco: %.2f\n", produto_selecionado->nome, produto_selecionado->preco_produto);
                    }
                    else
                    {
                        printf("Produto nao encontrado.\n");
                    }
                    break;

                case 4:
                    editar_produto(cabeca_lista_produtos);
                    break;

                case 5:
                    printf("Digite o Codigo para remover: ");
                    scanf("%d", &codigo_temp);
                    remover_produto(cabeca_lista_produtos, codigo_temp);
                    break;

                case 0:
                    printf("Voltando ao menu principal...\n");
                    break;

                default:
                    printf("Opcao invalida!\n");
                }
            } while (opcao_sub != 0);
            break;

            //MODULO DE CLIENTE
        case 2:
            do{
                printf("\n--- MENU CLIENTES ---\n");
                printf("1. Cadastrar Cliente\n");
                printf("2. Listar Clientes\n");
                printf("3. Editar Cliente\n");
                printf("0. Voltar\n");
                scanf("%d",opcao_sub);
                limpar_buffer();

                switch(opcao_sub){
                    case 1: cadastrarCliente(cabeca_lista_clientes); break;
                    case 2: listarClientes(cabeca_lista_clientes); break;
                    case 3: editarCliente(cabeca_lista_clientes); break;
                    case 4: removerCliente(cabeca_lista_clientes); break;
                    case 0: break;
                    default: printf("Opcao invalida\n");
                }
            } while(opcao_sub != 0);
            break;

        case 0:
            printf("Saindo do sistema...\n");
            break;

        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao_principal != 0);

    apagar_lista_produtos(cabeca_lista_produtos); 
    liberaMemoriaTotal(&cabeca_lista_clientes);
    return 0;
}