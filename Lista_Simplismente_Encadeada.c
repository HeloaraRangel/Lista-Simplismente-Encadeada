//Desenvolvido por: Heloara Rangel Teixeira
 
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "Lista_Simplismente_Encadeada.h"

void inicializa(TLista *L) {
    L->inicio = NULL;
    L->fim = NULL;
    L->total = 0;
}

int menu () {
    int opcao;
    
    printf("\n\t\t====| MENU |=====\n");
    printf("\t0 - Sair (Encerrar a Aplicação).\n");
    printf("\t1 - Inserir Nova Matrícula.\n");
    printf("\t2 - Cancelar Matrícula (ou Remover Matrícula).\n");
    printf("\t3 - Pesquisar Matrícula.\n");
    printf("\t4 - Total de Matrículas.\n");
    printf("\t5 - Imprimir Matrículas.\n");
    
    printf("\n\tInsira a opção desejada: ");
    fflush(stdin);
    scanf("%d", &opcao);
  
    if ((opcao < 0) || (opcao > 5))
    {
        printf("Opção Inválida!\n");
    }

    return opcao;
}

int main () {
    SetConsoleOutputCP(65001);
    int op;
    TLista lista;
    inicializa(&lista);
    
    inserir_matriculas_existentes(&lista,"lista_matricula.txt");

    do {
        op = menu();
        switch (op)
        {
            case 0:
                // Fechar o programa
                break;
            case 1:
                inserir_nova_matricula(&lista);
                gravar_matricula_na_lista(&lista,"lista_matricula.txt");
                break;
        
            case 2:
                excluir_matricula(&lista);
                gravar_matricula_na_lista(&lista,"lista_matricula.txt");
                break;

            case 3:
                verificar_matricula(&lista);
                break;

            case 4:
                total_matriculas(lista);
                break;

            case 5:
                imprimir_lista_matriculas(lista);
                break;
    
            default:
                break;
        }

    } while (op != 0);
    
    return 0;
}

//Função para abir o arquivo texto
FILE *abrirArquivo (char *nomeArq, char *modo) {
    FILE *arq;
    arq = fopen(nomeArq, modo);
    if (arq == NULL) 
    {
        printf("ERRO ao abrir o arquivo! .\n");
        exit(-1);
    }
    return arq;
}

//Após as inserções, as matrículas são gravadas no arquivo texto
void gravar_matricula_na_lista(TLista *lista, char* nomeArq) {
    FILE *arquivo = abrirArquivo(nomeArq, "w");
    TElemento *atual = lista->inicio;

    while (atual != NULL) {
        fprintf(arquivo, "%d\n", atual->valor);
        atual = atual->prox;
    }
    fclose(arquivo);
}

//Função para ler e inserir as matrículas do arquivo texto na lista
void inserir_matriculas_existentes(TLista *lista, char *nomeArq) {
    FILE *arquivo = abrirArquivo(nomeArq,"rw");
    int matricula;

        while (fscanf(arquivo, "%d", &matricula) == 1 ) {
            inserir_matricula(lista, matricula);
        }
        fclose(arquivo);
        printf("Matrículas lidas e inseridas na lista com sucesso! \n");
}

//O usuário fornece uma nova matrícula e essa função é responsável por inserir na lista e no arquivo texto,
//além disso, faz a verificação para não permitir numero de matrículas repetidas, chamando a função pesquisar.
void inserir_nova_matricula(TLista *lista){
    int numero_matricula;
    TElemento *encontrar;

    printf("Digite o código da matrícula: ");
    scanf("%d", &numero_matricula);

    encontrar = pesquisar_matriculas(lista, numero_matricula );

    if (encontrar == NULL) {
        inserir_matricula(lista, numero_matricula);
    }

    else {
        printf("A matrícula %d ja foi inserida na lista! .", numero_matricula);
    }
}

//Função para inserir matriculas na lista
void inserir_matricula(TLista *lista, int numero_matricula) {

    //Validação para não inserir matrículas repetidas na lista
    TElemento *encontrar = pesquisar_matriculas(lista, numero_matricula);
    if (encontrar != NULL) {
    return; // Se a matrícula já existir, não faz a inserção
    }

    TElemento *novo = (TElemento *)malloc(sizeof(TElemento));
    int inseriu = 0;
    novo->valor = numero_matricula;
    novo->prox = NULL;

    // Lista está vazia e vai inserir o primeiro elemento
    if (lista->inicio == NULL) {
        lista->inicio = novo;
        lista->fim = novo;
        lista->total = 1;
        inseriu = 1;
    } else {
        // A lista possui pelo menos um elemento
        TElemento *atual = lista->inicio;
        TElemento *anterior = NULL;

        while (atual != NULL) {
            if (atual->valor >= novo->valor) {
                if (anterior == NULL) {
                    // Inserir novo antes do primeiro da lista
                    novo->prox = atual;
                    lista->inicio = novo;
                } else {
                    // Inserir no meio da lista
                    novo->prox = atual;
                    anterior->prox = novo;
                }
                inseriu = 1;
                lista->total++;
                break;
            }
            anterior = atual;
            atual = atual->prox; // Move para o próximo elemento
        }
    }

    if (!inseriu) {
        // Insere elemento no fim da lista
        lista->fim->prox = novo;
        lista->fim = novo;
        lista->total++;
    }

}

//Função para excluir a matrícula não permitindo a exclusão de uma matrícula que não existe
void excluir_matricula(TLista *lista) {
    TElemento *atual = lista->inicio;
    TElemento *anterior = NULL;
    int numero_matricula;

    printf("Digite o código da matricula que deseja excluir: ");
    scanf("%d", &numero_matricula);

    TElemento *encontrar;
    encontrar = pesquisar_matriculas(lista, numero_matricula);

    if (encontrar == NULL) {
        printf("A matrícula a ser excluída não existe na lista!. \n");
    }
    
    else {
            while(atual != NULL) {
            if (atual->valor == numero_matricula) {
                // Encontrado elemento a ser excluído!
                printf("Encontrada a matrícula a ser excluida!. \n");
                
                if (lista->inicio == lista->fim) {
                    // Exclusão do único elemento da Lista.
                    lista->inicio = NULL;
                    lista->fim = NULL;     
                } else if (atual == lista->inicio) {
                    // Exclusão do primeiro elemento da Lista.
                    lista->inicio = atual->prox;
                } else if (atual == lista->fim) {
                    // Exclusão do último elemento da Lista.
                    lista->fim = anterior;
                    lista->fim->prox = NULL;    
                } else {
                    // Exclusão de Elemento intermediário.
                    anterior->prox = atual->prox;
                }
                
                printf("Excluindo a matrícula %d ...\n", atual->valor);
                free(atual);
                lista->total--;
                break;
            }
            
            anterior = atual;
            atual = atual->prox; // move para o próximo elemento.
        }
    }

}

//Função que faz a pesquisa de uma matrícula na lista
TElemento *pesquisar_matriculas(TLista *lista, int numero_matricula) {
    TElemento *atual = lista->inicio;
    while (atual != NULL) {
        if (atual->valor == numero_matricula) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

//Função que desempenha o papel de pesquisa na matrícula, mostrano ao usuário
void verificar_matricula(TLista *lista) {
    int numero_matricula;
    TElemento *encontrar;

    printf("Digite o código da matrícula que deseja verificar: ");
    scanf("%d", &numero_matricula);

    encontrar = pesquisar_matriculas(lista, numero_matricula);

    // Verificando se a matrícula foi encontrada
    if (encontrar != NULL) {
        printf("Matrícula %d encontrada na lista.\n", numero_matricula);
    } else {
        printf("Matrícula %d não existe na lista.\n", numero_matricula);
    }
}

//Função que retorna o total de matriculas cadastradas na lista.
void total_matriculas(TLista lista) {
    printf("Total de matrículas: %d\n", lista.total);
}

//Função responsável de fazer a impressão a lista
void imprimir_lista_matriculas(TLista lista) {
    TElemento *atual = lista.inicio;
    int cont = 0;
    
    printf("\n\n\t\t===| EXIBE LISTA COMPLETA |===\n\n");
    printf("Total de matriculas: %d\n", lista.total);
    
    while (atual != NULL){
        printf("(%d) - %d.\n", ++cont, atual->valor);
        atual = atual->prox;
    }
    
}