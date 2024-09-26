//include de bibliotecas
#include <stdio.h>
//definição de variaveis  
char nome [55];
char cpf [55];
char email[55];
//CRUD create(criar o cadastro do aluno), read(ver alunos cadastrados), update(modificar cadastro do aluno), delete(deletar o cadasto do aluno) 
void create();
void read();
void update();
void delete();
//menu customizável 
void divisoria(char simbolo){
    for (int i=0;i <40;i++){

    printf("%c",simbolo);
    }
    printf("\n");
    }
void titulo()
    {
        for (int i = 0; i < 13; i++)
        {
            printf(" ");
        }   
    printf("%s","UniCad em Video\n");  }
void conteudo(){
printf("1-Criar cadastro de aluno\n");
printf("2-Exibir lista de cadastro\n");
printf("3-Modificar cadatro\n");
printf("4-Deletar cadastro \n");
}

//inicio do codigo
int main(){
//menu
    divisoria('=');
    titulo();
    divisoria('-');
    conteudo();
    divisoria('=');
    printf("%s","digite o numero da tarefa:");
//seleção de funções
int opcao;
do {
    scanf("%d",&opcao);
    switch(opcao){
        case 1:
        create();
        break;
        case 2:
        read();
        break;
        
        case 3:
        update();
        break;

        case 4:
        delete();
        break;

        default:
        return 0;
        break;
    }
}
 while (opcao<4);

}

// função read (ler)
void read (){
    FILE *file;
    char linha [1501;
    int 1=0;
    file = fopen ("dados.txt","r");//coloquei o nosso arquivo txt que está guardando as informações de cadastro
    if (file ==NULL){
        printf("Erro no Arquivo de dados!");
        return;
    }
    char t[50] = "ARQUIVO ALUNO.CSV";//mudar o nome da variável se for usar outra
    cabecalho (t);
    char *result;
    while (!feof (file))
    {
        if ((result = fgets (Linha, 150, file)) != NULL){
            printf( "Linha %s", linha);
}
    }
    fclose (file);
    do{
        printf("\n\rPara voltar ao menu precione a tecla 1 ");
        scanf ("&d", &l);
        }while (l!=1);
        menu ();
}
