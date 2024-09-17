#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Função para decodificar os dados enviados pelo formulário
void decode_form_data(char *data, char *nome, char *cpf, char *email, char *matricula) {
    sscanf(data, "nome=%[^&]&cpf=%[^&]&email=%[^&]&matricula=%s", nome, cpf, email, matricula);
}

// Função para salvar os dados no arquivo .txt
void salvar_dados(const char *nome, const char *cpf, const char *email, const char *matricula) {
    FILE *arquivo = fopen("dados.txt", "a");
    if (arquivo == NULL) {
        printf("Content-Type: text/plain\n\n");
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fprintf(arquivo, "Nome: %s\n", nome);
    fprintf(arquivo, "CPF: %s\n", cpf);
    fprintf(arquivo, "Email: %s\n", email);
    fprintf(arquivo, "Matrícula: %s\n\n", matricula);
    fclose(arquivo);

    // Envia uma resposta simples ao frontend
    printf("Content-Type: text/plain\n\n");
    printf("Dados salvos com sucesso!\n");
}

int main(void) {
    setlocale(LC_ALL, "portuguese.UTF-8");
    char *data;
    char nome[100], cpf[15], email[100], matricula[20];

    // Obtém o comprimento dos dados enviados pelo formulário
    char *content_length_str = getenv("CONTENT_LENGTH");
    if (content_length_str == NULL) {
        printf("Content-Type: text/plain\n\n");
        printf("Nenhum dado recebido!\n");
        return 1;
    }

    int content_length = atoi(content_length_str);
    if (content_length <= 0) {
        printf("Content-Type: text/plain\n\n");
        printf("Comprimento do conteúdo inválido!\n");
        return 1;
    }

    // Aloca espaço para os dados recebidos
    data = (char *)malloc(content_length + 1);
    if (data == NULL) {
        printf("Content-Type: text/plain\n\n");
        printf("Erro de alocação de memória!\n");
        return 1;
    }

    // Lê os dados enviados pelo formulário
    fread(data, 1, content_length, stdin);
    data[content_length] = '\0';  // Adiciona o terminador de string

    // Decodifica os dados do formulário
    decode_form_data(data, nome, cpf, email, matricula);

    // Salva os dados no arquivo
    salvar_dados(nome, cpf, email, matricula);

    free(data);
    return 0;
}
