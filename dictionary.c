#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<math.h>
#include<time.h>

typedef struct no{
    char dado[50];
    char significado[300];
    int fatorB;
    struct no* pai;
    struct no* esq;
    struct no* dir;
}No;

typedef struct arvore {
    No *raiz;
} Arvore;

No* criaNo(char* palavra, char* significado){
    No* no = (No*)malloc(sizeof(No));
    strcpy(no->dado, palavra);
    strcpy(no->significado, significado);
    no->fatorB = 0;
    no->dir = NULL;
    no->esq = NULL;
    no->pai = NULL;
    return no;
}

 //enunciado pede criar árvore vazia
Arvore *criaArvore(){
    Arvore *novaArvore = (Arvore*)malloc(sizeof(Arvore));
    novaArvore->raiz = NULL;
    printf("Arvore criada com sucesso\n");
    return novaArvore;
}

int calcularAltura(No* no) {
    if (no == NULL) return 0;
    int alturaEsq = calcularAltura(no->esq);
    int alturaDir = calcularAltura(no->dir);
    return 1 + (alturaEsq > alturaDir ? alturaEsq : alturaDir);
}

void atualizarFB(No *no) {
    if (no == NULL) return;
    int alturaEsq = calcularAltura(no->esq);
    int alturaDir = calcularAltura(no->dir);
    no->fatorB = alturaEsq - alturaDir;
}

No* LL(No* no){
    No *aux;
    aux = no->dir;
    if(aux->esq!=NULL) aux->esq->pai = no;
    no->dir = aux->esq;
    aux->esq = no;
    aux->pai = no->pai;
    no->pai = aux;
    no=aux;
    atualizarFB(no);
    atualizarFB(aux);
    return no;
}


No* RR(No* no){
    No *aux;
    aux = no->esq;
    if(aux->dir!=NULL) aux->dir->pai = no;
    no->esq = aux->dir;
    aux->dir = no;
    aux->pai = no->pai;
    no->pai = aux;
    no=aux;
    atualizarFB(no);
    atualizarFB(aux);
    return no;
}

No* RL(No *no){
    no->dir = RR(no->dir);
    return LL(no);
}

No* LR(No *no){
    no->esq = LL(no->esq);
    return RR(no);
}

No* balancear(No* no) {
    if(no->fatorB>1 && no->esq->fatorB==-1){ //caso LR
        no = LR(no);
    } else if(no->fatorB>1) {
        no = RR(no); //caso RR
    }

    if(no->fatorB<-1 && no->dir->fatorB==1){ //caso RL
        no = RL(no);
    } else if(no->fatorB<-1) {
        no = LL(no); //caso LL
    }

    return no;
}

No* inserir(No* raiz, char* palavra, char* significado) {
    if (raiz == NULL){
        printf("\nPalavra %s inserida com sucesso!\n", palavra);
        return criaNo(palavra, significado);
    } 
    
    int valor = strcmp(palavra, raiz->dado);

    if (valor < 0){
        raiz->esq = inserir(raiz->esq, palavra, significado);
    }
    else if (valor > 0){
        raiz->dir = inserir(raiz->dir, palavra, significado);
    }
    else {
        printf("\nOperacao de insercao sem sucesso. Palavra %s já existe no dicionário\n", palavra);
        return raiz;
    }
    atualizarFB(raiz);
    return balancear(raiz);
}

No* encontrarAntecessor(No* raiz) {
    No* atual = raiz;
    while (atual && atual->dir != NULL) {
        atual = atual->dir;
    }
    return atual;
}

No* remover(No* raiz, char* palavra) {
    if (raiz == NULL) {
        printf("Remocao invalida\n");
        return NULL;
    }

    int valor = strcmp(palavra, raiz->dado);

    if (valor < 0) {
        raiz->esq = remover(raiz->esq, palavra);
    } else if (valor > 0) {
        raiz->dir = remover(raiz->dir, palavra);
    } else { // Encontrou o nó a ser removido
        if (raiz->esq == NULL && raiz->dir == NULL) { // Caso 1: Nó folha
            free(raiz);
            printf("Remoção bem sucedida!\n");
            return NULL;
        } else if (raiz->esq == NULL) { // Caso 2: Nó com apenas filho direito
            No* temp = raiz->dir;
            temp->pai = raiz->pai; // Atualiza o ponteiro pai
            free(raiz);
            printf("Remoção bem sucedida!\n");
            return temp;
        } else if (raiz->dir == NULL) { // Caso 2: Nó com apenas filho esquerdo
            No* temp = raiz->esq;
            temp->pai = raiz->pai; // Atualiza o ponteiro pai
            free(raiz);
            printf("Remoção bem sucedida!\n");
            return temp;
        } else { // Caso 3: Nó com dois filhos
            No* antecessor = encontrarAntecessor(raiz->esq);
            strcpy(raiz->dado, antecessor->dado);
            strcpy(raiz->significado, antecessor->significado);
            raiz->esq = remover(raiz->esq, antecessor->dado);
        }
    }
    atualizarFB(raiz);

    // Rebalanceia o nó atual
    return balancear(raiz);
}

No* busca(No *raiz, char palavra[], int altura){
    altura+=1;
    if(raiz == NULL){
        printf("\nPalavra nao encontrada!\n");
        return NULL;
    }
    int cmp = strcmp(raiz->dado, palavra);
    if(cmp<0){
        return busca(raiz->dir, palavra, altura);
    }
    else if(cmp>0){
    return busca(raiz->esq, palavra, altura);
    }
    else {
        printf("\nPalavra encontradada! h=%d\n%s: %s\n", altura, raiz->dado,raiz->significado);
        return raiz;
    } 
}

void percursoEmOrdem(No* no, int altura){
    if(no == NULL) return;
    percursoEmOrdem(no->esq, ++altura);
    printf("%s: h=%d\n ",no->dado, altura);
    percursoEmOrdem(no->dir, ++altura);
}

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    Arvore* arvore;
    char palavra[50], significado[256];
    int opcao;

    time_t inicioExecPrograma = time(NULL); 
    time_t fimExecInserir = time(NULL);
    time_t inicioExecBusca = time(NULL); 
    time_t fimExecBusca = time(NULL); 

    //main limpo para testes
    while(opcao != 6){
        scanf("%d", &opcao);
        switch(opcao){
        case 1:
            //cria árvore vazia
            arvore = criaArvore();
            break;
        case 2:
            // remover palavra
            scanf("%s",palavra);
            arvore->raiz = remover(arvore->raiz, palavra);
            break;
        case 3:
            //insere palavra
            scanf("%s",palavra);
            scanf(" %[^\n]", significado);
            getchar();
            arvore->raiz = inserir(arvore->raiz, palavra, significado);         
            break;
        case 4:
            //busca
            scanf("%s",palavra);
            busca(arvore->raiz, palavra, 0);
            break;
        case 5:
            // imprimir arvore
            printf("\n");
            percursoEmOrdem(arvore->raiz, 0);
            printf("\n");
            break;
        case 6:
            printf("\nEncerrando!");
            break;
        default:
            printf("Opçao invalida, tente novamente");
        }
    }
    return 0;
}
