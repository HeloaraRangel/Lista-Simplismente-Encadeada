//Desenvolvido por: Heloara Rangel Teixeira
typedef struct tipoElemento 
{
    int valor;
    struct tipoElemento *prox;
}TElemento;

typedef struct tipoLista 
{
    TElemento *inicio;
    TElemento *fim;
    int total;

}TLista;

TLista lista; //variavel global

FILE *abrirArquivo(char *nomeArq, char *modo);
void inicializa(TLista *L);
int menu();
int main();
void inserir_matriculas_existentes(TLista *lista, char *nomeArq);
void inserir_nova_matricula(TLista *lista);
void inserir_matricula(TLista *lista, int numero);
void excluir_matricula(TLista *lista);
TElemento *pesquisar_matriculas(TLista *lista, int numero_matricula);
void verificar_matricula(TLista *lista);
void total_matriculas(TLista lista);
void imprimir_lista_matriculas(TLista lista);
void gravar_matricula_na_lista(TLista *lista, char* nomeArq);