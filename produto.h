#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct Produto {
    int codigo_produto;
    char *nome;
    float preco_produto;
    struct Produto * prox;

} Produto;

// crud
void cria_produto(Produto **inicio); // create
void listar_produto(Produto *inicio); // read

// find one
Produto * procurar_produto(Produto * inicio, int codigo_produto); // Retorna o endereço do produto encontrado ou NULL

void editar_produto(Produto *inicio); // update
void remover_produto(Produto **inicio); // delete

#endif