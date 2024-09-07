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