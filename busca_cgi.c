#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Função para decodificar os dados enviados pelo formulário (CPF e Matrícula)
void decode_form_data(char *data, char *cpf, char *matricula) {
    sscanf(data, "cpf=%[^&]&matricula=%s", cpf, matricula);
}

// Função para buscar dados no arquivo com base no CPF ou matrícula
void buscar_dados(const char *cpf, const char *matricula) {
    FILE *arquivo = fopen("../htdocs/cgi-bin/dados.txt", "r");
    if (arquivo == NULL) {
        perror("<p>Erro ao abrir o arquivo!</p>");
        return;
    }

    char linha[300];
    char nome[100], cpf_arquivo[15], email[100], matricula_arquivo[20];
    int encontrou = 0;

    // Lê cada linha do arquivo e verifica se o CPF ou a Matrícula correspondem
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Usa sscanf para extrair os dados
        if (sscanf(linha, "Nome: %[^,], CPF: %[^,], Email: %[^,], Matrícula: %s", nome, cpf_arquivo, email, matricula_arquivo) == 4) {
            // Verifica se CPF ou Matrícula correspondem
            if ((cpf[0] != '\0' && strcmp(cpf, cpf_arquivo) == 0) ||
                (matricula[0] != '\0' && strcmp(matricula, matricula_arquivo) == 0)) {
                printf("<p>Dados encontrados:</p>");
                printf("<ul>");
                printf("<li>Nome: %s</li>", nome);
                printf("<li>CPF: %s</li>", cpf_arquivo);
                printf("<li>Email: %s</li>", email);
                printf("<li>Matrícula: %s</li>", matricula_arquivo);
                printf("</ul>");
                encontrou = 1;
                break;  // Interrompe a busca ao encontrar o primeiro resultado
            }
        }
    }

    if (!encontrou) {
        printf("<p>Nenhum dado encontrado para o CPF ou Matrícula fornecidos.</p>");
    }

    fclose(arquivo);
}

int main(void) {
    setlocale(LC_ALL, "portuguese.UTF-8");

    // Envia o cabeçalho HTTP para indicar que a resposta será HTML
    printf("Content-Type: text/html; charset=UTF-8\n\n");

    // Início da estrutura HTML
    printf("<html><head><title>Resultado da Busca</title></head><body>");

    // Verifica o método da requisição
    char *request_method = getenv("REQUEST_METHOD");

    if (request_method != NULL && strcmp(request_method, "POST") == 0) {
        // Método POST - obtem o comprimento do conteúdo
        char *content_length_str = getenv("CONTENT_LENGTH");
        int content_length = content_length_str ? atoi(content_length_str) : 0;

        if (content_length > 0) {
            // Lê os dados do corpo da requisição
            char *data = (char *)malloc(content_length + 1);
            fread(data, 1, content_length, stdin);
            data[content_length] = '\0';  // Termina a string

            // Variáveis para armazenar CPF e Matrícula
            char cpf[15] = "", matricula[20] = "";

            // Decodifica os dados do formulário
            decode_form_data(data, cpf, matricula);

            // Verifica se pelo menos um dos campos foi preenchido
            if (cpf[0] == '\0' && matricula[0] == '\0') {
                printf("<p>Por favor, forneça o CPF ou a Matrícula.</p>");
            } else {
                // Busca os dados no arquivo
                buscar_dados(cpf, matricula);
            }

            free(data);
        } else {
            printf("<p>Nenhum dado recebido!</p>");
        }
    } else {
        printf("<p>Este script suporta apenas o método POST.</p>");
    }

    // Fim da estrutura HTML
    printf("</body></html>");

    return 0;
}
