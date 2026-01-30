#include "clientes.h"

Cliente *encontrar_cliente_por_cpf(Cliente *primeiro_cliente, char *cpf){
    Cliente *cliente_atual = primeiro_cliente;
    
    while(cliente_atual != NULL){
        if(strcmp(cliente_atual->cpf, cpf) == 0) return cliente_atual;

        cliente_atual = cliente_atual->prox;
    }

    return NULL;
}


