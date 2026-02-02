#ifndef CLIENTES_H
#define CLIENTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _carrinho {
    int codigo_produto;
    int quantidade;
    struct _carrinho *prox;
} carrinho;

typedef struct _Cliente {
    char cpf[15];
    char *nome;
    char email[50];
    char telefone[20];
    char data_nascimento [12];

    carrinho *car_cabeca;
    struct _Cliente *prox;
} Cliente;

Cliente * criarListaComCabeca();


void cadastrarCliente(Cliente *head);
void listarClientes(Cliente *head);
void editarCliente(Cliente *head);
void removerCliente(Cliente *head);
void liberarMemoriaTotal(Cliente **head);

#endif