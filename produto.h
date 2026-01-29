#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct Produto
{
    int codigo_produto;
    char *nome;
    float preco_produto;
    struct Produto *prox;

} Produto;

Produto *cria_lista_produto();
Produto *procura_fim(Produto *inicio);
void cria_produto(Produto *inicio);
void listar_produtos(Produto *inicio);
Produto *procurar_produto(Produto *inicio, int codigo_produto);
void editar_produto(Produto *inicio);
void remover_produto(Produto *inicio, int codigo_produto);
void apagar_lista_produtos(Produto *inicio);

#endif