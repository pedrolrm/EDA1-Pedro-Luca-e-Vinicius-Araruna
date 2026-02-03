#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produto.h"
#include "utils.h"

typedef struct _Cliente
{
    char cpf[15];
    char *nome;
    char email[50];
    char telefone[20];
    char data_nascimento[12];

    Produto *carrinho;
    struct _Cliente *prox;
} Cliente;

Cliente *criarListaComCabeca();

void cadastrarCliente(Cliente *head);
void listarClientes(Cliente *head);
void editarCliente(Cliente *head);
void removerCliente(Cliente *head);
void adiciona_ao_carrinho(Cliente *cliente_alvo, Produto *produto, int qtd);
Cliente *encontrar_cliente_por_cpf(Cliente *cabeca, char *cpf);
void liberaMemoriaTotal(Cliente **head);

#endif