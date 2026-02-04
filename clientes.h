#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"
#include "utils.h"

typedef struct ItemCarrinho
{
    Produto *produto;
    int quantidade;
    struct ItemCarrinho *prox;
} ItemCarrinho;

typedef struct _Cliente
{
    char cpf[15];
    char *nome;
    char email[50];
    char telefone[20];
    char data_nascimento[12];

    ItemCarrinho *carrinho;
    struct _Cliente *prox;
} Cliente;

// funções de cliente
Cliente *criarListaComCabeca();
void cadastrarCliente(Cliente *head);
void listarClientes(Cliente *head);
void editarCliente(Cliente *head);
void removerCliente(Cliente *head);
Cliente *encontrar_cliente_por_cpf(Cliente *cabeca, char *cpf);
void liberaMemoriaTotal(Cliente **head);

// funções de carrinho
ItemCarrinho *cria_lista_carrinho();
void listar_carrinho(ItemCarrinho *cabeca);
float calcular_total_carrinho(ItemCarrinho *cabeca);
void adiciona_ao_carrinho(Cliente *cliente_alvo, Produto *cabeca, int codigo_produto, int qtd);
void remover_do_carrinho(ItemCarrinho *cabeca_carrinho, Produto *cabeca_produto, int codigo_produto);

#endif