#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Função para decodificar os dados enviados pelo formulário
void decode_form_data(char *data, char *nome, char *cpf, char *email, char *matricula) {
    sscanf(data, "nome=%[^&]&cpf=%[^&]&email=%[^&]&matricula=%s", nome, cpf, email, matricula);
}


// Função para buscar dados no arquivo com base na matrícula e cpf
void buscar_dados(const char *cpf, const char *matricula) {
    FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Content-Type: text/plain\n\n");
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    char linha[200];
    char nome[100], cpf_arquivo[15], email[100], matricula_arquivo[20];
    int encontrou = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (sscanf(linha, "Nome: %[^\n]", nome) == 1 &&
            fgets(linha, sizeof(linha), arquivo) != NULL &&
            sscanf(linha, "CPF: %[^\n]", cpf_arquivo) == 1 &&
            fgets(linha, sizeof(linha), arquivo) != NULL &&
            sscanf(linha, "Email: %[^\n]", email) == 1 &&
            fgets(linha, sizeof(linha), arquivo) != NULL &&
            sscanf(linha, "Matrícula: %[^\n]", matricula_arquivo) == 1) {
            
            // Verifica se CPF e Matrícula correspondem
            if (strcmp(cpf, cpf_arquivo) == 0 && strcmp(matricula, matricula_arquivo) == 0) {
                printf("Content-Type: text/plain\n\n");
                printf("Dados encontrados:\n");
                printf("Nome: %s\n", nome);
                printf("CPF: %s\n", cpf_arquivo);
                printf("Email: %s\n", email);
                printf("Matrícula: %s\n", matricula_arquivo);
                encontrou = 1;
                break;
            }
        }
    }

    if (!encontrou) {
        printf("Content-Type: text/plain\n\n");
        printf("Nenhum dado encontrado para o CPF e Matrícula fornecidos.\n");
    }

    fclose(arquivo);
}


