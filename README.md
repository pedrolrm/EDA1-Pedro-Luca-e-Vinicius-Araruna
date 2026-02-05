# Sistema de Gestão de Vendas

Sistema desenvolvido em C para gerenciamento de clientes, produtos e operações de compra, utilizando Estruturas de Dados (Listas Encadeadas) e persistência de arquivos.

## Funcionalidades

- **Gerenciamento de Produtos:** Cadastro, listagem, busca, edição, remoção e controle de estoque.
- **Gerenciamento de Clientes:** Cadastro, listagem, busca por CPF, edição e remoção.
- **Carrinho de Compras:**
  - Adição de produtos com verificação de estoque em tempo real.
  - Remoção de itens com devolução ao estoque.
  - Persistência do carrinho vinculado ao cliente.
- **Persistência de Dados:** Carregamento e salvamento automático em arquivos `.txt` (pasta `data/`).

## Estrutura de Pastas

O projeto segue uma arquitetura modular:

- `src/`: Código fonte (`.c`)
- `include/`: Arquivos de cabeçalho (`.h`)
- `data/`: Banco de dados em texto (`.txt`)
- `bin/`: Executável compilado
- `Makefile`: Script de automação de compilação

## Como Compilar e Executar

Certifique-se de ter o compilador `gcc` e o `make` instalados.

### 1. Compilar o Projeto

No terminal, na raiz do projeto, execute:

```bash
make
```

Isso criará automaticamente as pastas necessárias (bin e data) e gerará o executável.

2. Rodar o Sistema
   Após a compilação, execute:

```Bash
./bin/sistema
```

Para remover o executável e limpar o projeto:

```Bash
make clean
```

👥 Autores:

Pedro Luca

Vinicius Araruna
