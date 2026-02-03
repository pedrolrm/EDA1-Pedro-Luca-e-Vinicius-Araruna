#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

char *ler_texto()
{
    char temp[100];
    scanf(" %[^\n]", temp);

    char *nome = (char *)malloc((strlen(temp) + 1) * sizeof(char)); // Aloca a quantidade exata de memória para o ponteiro nome
    if (nome == NULL)
    {
        printf("\nFalha ao alocar memória\n");
        exit(EXIT_FAILURE);
    }
    strcpy(nome, temp); // Copia para nome o texto salvo na variável temporaria

    return nome;
}

void limpar_buffer(){
    int c;
    while((c = getchar()) != '\n' &&  c != EOF); // c!= EOF para nao entrar em loop infinito
}