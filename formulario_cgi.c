#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

// Função para decodificar caracteres especiais de URL (como %40 para @)
void url_decode(char *src, char *dest) {
    char hex[3];
    while (*src) {
        if (*src == '%') {
            hex[0] = *(src + 1);
            hex[1] = *(src + 2);
            hex[2] = '\0';
            *dest = (char) strtol(hex, NULL, 16);  // Converte de hexadecimal para caractere
            src += 3;
        } else if (*src == '+') {
            *dest = ' ';  // '+' em URL encoding vira espaço
            src++;
        } else {
            *dest = *src;
            src++;
        }
        dest++;
    }
    *dest = '\0';  // Finaliza a string
}

// Função para decodificar os dados enviados pelo formulário
void decode_form_data(char *data, char *nome, char *cpf, char *email, char *matricula) {
    char decoded_data[1024];  // Buffer temporário para dados decodificados
    url_decode(data, decoded_data);  // Decodifica a string inteira

    // Agora podemos usar sscanf nos dados já decodificados
    sscanf(decoded_data, "nome=%[^&]&cpf=%[^&]&email=%[^&]&matricula=%s", nome, cpf, email, matricula);
}

// Função para salvar os dados no arquivo .txt
void salvar_dados(const char *nome, const char *cpf, const char *email, const char *matricula) {
    FILE *arquivo = fopen("dados.txt", "a");
    if (arquivo == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Erro ao abrir o arquivo!</body></html>\n");
        return;
    }

    fprintf(arquivo, "Nome: %s\n", nome);
    fprintf(arquivo, "CPF: %s\n", cpf);
    fprintf(arquivo, "Email: %s\n", email);
    fprintf(arquivo, "Matrícula: %s\n\n", matricula);
    fclose(arquivo);

    printf("Content-Type: text/html\n\n");
    printf("<html><body>Dados salvos com sucesso!</body></html>\n");
}
// Função para decodificar os dados enviados pelo formulário
//void decode_form_data(char *data, char *nome, char *cpf, char *email, char *matricula) {
  //  sscanf(data, "nome=%[^&]&cpf=%[^&]&email=%[^&]&matricula=%s", nome, cpf, email, matricula);
//}

// Função para salvar os dados no arquivo .txt
//void salvar_dados(const char *nome, const char *cpf, const char *email, const char *matricula) {
//    FILE *arquivo = fopen("dados.txt", "a");
//    if (arquivo == NULL) {
 //       printf("Content-Type: text/plain\n\n");
 //       printf("Erro ao abrir o arquivo!\n");
 //       return;
 //   }

//    fprintf(arquivo, "Nome: %s\n", nome);
//    fprintf(arquivo, "CPF: %s\n", cpf);
//    fprintf(arquivo, "Email: %s\n", email);
//    fprintf(arquivo, "Matrícula: %s\n\n", matricula);
//    fclose(arquivo);

//    // Envia uma resposta simples ao frontend
//    printf("Content-Type: text/plain\n\n");
//    printf("Dados salvos com sucesso!\n");
//}


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
