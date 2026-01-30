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

