#include "clientes.h"

Cliente *encontrar_cliente_por_cpf(Cliente *primeiro_cliente, char *cpf){
    Cliente *cliente_atual = primeiro_cliente;
    
    while(cliente_atual != NULL){
        if(strcmp(cliente_atual->cpf, cpf) == 0) return cliente_atual;

        cliente_atual = cliente_atual->prox;
    }

    return NULL;
}

void cadastrarCliente(Cliente **head){
    char buffer_nome[256];
    char cpf_temp[15];
    printf("\n--- Novo Cadastro ---\n");
    printf("CPF: ");
    scanf("%[^\n]",cpf_temp);

    if(encontrar_cliente_por_cpf(*head, cpf_temp) !=NULL){
        printf("Erro: CPF ja cadastrado!");
        return;
    }
    Cliente *novo_cliente =  (sizeof(Cliente));

    if(!novo_cliente){
        printf("Erro: falha ao alocar struct\n");
        return;
    }
     strcpy(novo_cliente->cpf, cpf_temp);
     printf("Nome Completo: ");
     scanf("%[^\n]",buffer_nome);

     novo_cliente->nome = malloc((strlen(buffer_nome) + 1) *sizeof(char));
     
     if(novo_cliente->nome == NULL){
        printf("Erro: falha ao alocar nome\n");
        free(novo_cliente);
        return;
     }

     strcpy(novo_cliente->nome, buffer_nome);

     printf("Email: \n"); 
     scanf("%[^\n]", novo_cliente->email);
     printf("Telefone: \n");
     scanf("%[^\n]", novo_cliente->telefone);
     printf("Data de Nascimento: \n");
     scanf("%[^\n]", novo_cliente->data_nascimento);

     novo_cliente->car_cabeca = NULL;

     novo_cliente->prox = *head;
     *head = novo_cliente;

     printf("Cliente cadastrado com sucesso!\n");
}

void listarClientes(Cliente *head){
    if(head == NULL){
        printf("\n--- Lista de clientes vazia ---\n");
    }

    Cliente *cliente_atual = head;
    
    printf("\n---Lista de Clientes ---\n");
    while(cliente_atual != NULL){
        printf("CPF: %s  |  Nome: %s\n", cliente_atual->cpf, cliente_atual->nome);
        cliente_atual = cliente_atual->prox;
    }
    printf("----------------------------\n");

}

void editarCliente(Cliente *head){
    char busca_cpf[15];
    printf("\n Digite o CPF do cliente para editar: ");
    scanf("%[^\n]", busca_cpf);

    Cliente *cliente_alvo = encontrar_cliente_por_cpf(head,busca_cpf);

    if(cliente_alvo == NULL){
        printf("Cliente nao encontrado!\n");
        return;
    }

    int opcao;

    do{
        printf("\n Editando: %s\n", cliente_alvo->nome);
        printf("1. Alterar Nome\n");
        printf("2. Alterar Email\n");
        printf("3. Alterar Telefone\n");
        printf("4. Alterar Data de Nascimento\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha sua opcao: ");
        scanf("%d", &opcao);

        char buffer_temp[256];

        switch(opcao){
            case 1:
            printf("Novo nome: ");
            scanf("%[^\n]",buffer_temp);
            char *novoNome = realloc(cliente_alvo->nome, (strlen(buffer_temp) + 1) *sizeof(char));

            if(novoNome != NULL){
                cliente_alvo->nome = novoNome;
                strcpy(cliente_alvo->nome , buffer_temp);
                printf("Nome atualizado com sucesso!\n");
            } else {
                printf("Erro: falha ao alocar nome");
            } break;

            case 2:
            printf("Novo email: (atual: %s)",cliente_alvo->email);
            scanf("%[^\n]",cliente_alvo->email);
            printf("Email atualizado com sucesso!\n");
            break;

            case 3:
            printf("Novo telefone: (atual: %s)",cliente_alvo->telefone);
            scanf("%[^\n]", cliente_alvo->telefone);
            printf("Numero de telefone atualizado com sucesso!\n");
            break;

            case 4:
            printf("Nova data de nascimento: (atual: %s)", cliente_alvo->data_nascimento);
            scanf("%[^\n]",cliente_alvo->data_nascimento);
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


void removerCliente(Cliente **head){
    char busca_cpf[15];
    printf("\n CPF para remover: ");
    scanf("%[^\n]",busca_cpf);

    Cliente *cliente_atual = *head;
    Cliente *cliente_anterior = NULL;

    while(cliente_atual != NULL && strcmp(cliente_atual->cpf,busca_cpf) != 0 ){
        cliente_anterior = cliente_atual;
        cliente_atual = cliente_atual->prox;
    }

    if(cliente_atual == NULL){
        printf("CPF nao encontrado!\n");
        return;
    }

    if(cliente_anterior == NULL){
        *head = cliente_atual->prox;
    } else{
        cliente_anterior->prox = cliente_atual->prox;
    }

    if(cliente_atual->nome == NULL){
        free(cliente_atual->nome);
    }
    free(cliente_atual);
    
    printf("Cliente removido com sucesso!\n");
}
