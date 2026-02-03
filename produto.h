#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct Produto
{
    int codigo_produto;
    int quantidade;
    char *nome;
    float preco_produto;
    struct Produto *prox;

} Produto;

Produto *cria_lista_produto();
Produto *procura_fim(Produto *inicio);
Produto *cria_produto(Produto *inicio);
void listar_produtos(Produto *inicio);
Produto *procurar_produto(Produto *inicio, int codigo_produto);
void editar_produto(Produto *inicio);
void remover_produto(Produto *inicio, int codigo_produto);
void apagar_lista_produtos(Produto *inicio);
void adiciona_produto(Produto *cabeca, Produto *novo_produto);

// Estoque de Produtos

int baixarEstoque(Produto *cabeca, int codigo, int qtd_requerida);
void devolverEstoque(Produto *cabeca, int codigo, int qtd_devolvida);



#endif