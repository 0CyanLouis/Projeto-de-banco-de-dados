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
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Erro ao abrir o arquivo!</body></html>\n");
        return;
    }

    fprintf(arquivo, "Nome: %s\n", nome);
    fprintf(arquivo, "CPF: %s\n", cpf);
    fprintf(arquivo, "Email: %s\n", email);
    fprintf(arquivo, "Matrícula: %s\n\n", matricula);
    fclose(arquivo);

//redirecionamento dps de 10 sec para a pagina de cadastro 
    printf("Content-Type: text/html\n\n");
    printf("<html>\n");
    printf("<head>\n");
    printf("<title>Redirecionando...</title>\n");
    printf("</head>\n");
    printf("<body>\n");
    printf("<p>Dados salvos com sucesso!</p>\n");
    printf("<p>Você será redirecionado para a página de cadastro em breve.</p>\n");
    printf("<script>\n");
    printf("    setTimeout(function() {\n");
    printf("        window.location.href = 'http://localhost:8080/formulario/index.html';\n");
    printf("    }, 10000); // Tempo de atraso em milissegundos\n");
    printf("</script>\n");
    printf("</body>\n");
    printf("</html>\n");

}

int main(void) {
    setlocale(LC_ALL,"portuguese.UTF-8");
    char *data;
    char nome[100], cpf[15], email[100], matricula[20];

    // Obtém o comprimento dos dados enviados pelo formulário
    int content_length = atoi(getenv("CONTENT_LENGTH"));

    // Aloca espaço para os dados recebidos
    data = (char *)malloc(content_length + 1);
    if (data == NULL) {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Erro de alocação de memória!</body></html>\n");
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
