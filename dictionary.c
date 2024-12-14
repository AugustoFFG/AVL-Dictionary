#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
    int numNos;
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
    novaArvore->numNos=0;
    return novaArvore;
}
/*
int calcularAltura(No* n){
    if(n == NULL){
        return 0;
    }
    return n->altura;
}

int fb(No* n){
    if (n == NULL) return 0; 
    int alturaEsq = calcularAltura(n->esq);
    int alturaDir = calcularAltura(n->dir);
    return n->esq->altura - n->esq->alturaDir; 
}
*/

No* LL(No* no){
    No *aux;
    aux = no->dir;
    if(aux->esq!=NULL) aux->esq->pai = no;
    no->dir = aux->esq;
    aux->esq = no;
    aux->pai = no->pai;
    no->pai = aux;
    return aux;
}


No* RR(No* no){
    No *aux;
    aux = no->esq;
    if(aux->dir!=NULL) aux->dir->pai = no;
    no->esq = aux->dir;
    aux->dir = no;
    aux->pai = no->pai;
    no->pai = aux;
    return aux;
}

/*void RL(No *no){
    RR(no->dir);
    LL(no);
}

void LR(No *no){
    LL(no->esq);
    RR(no);
}*/

No* balancear(No* no) {
    if(no->fatorB>1 && no->esq->fatorB==-1){ //caso LR
        printf("LR(%s)\n", no->dado);
        no->esq = LL(no->esq);
        no = RR(no);
    } else if(no->fatorB>1) {
        printf("RR(%s)\n", no->dado);
        no = RR(no); //caso RR
    }

    if(no->fatorB<-1 && no->esq->fatorB==1){ //caso RL
        printf("RL(%s)\n", no->dado);
        no->dir = RR(no->dir);
        no = LL(no);
    } else if(no->fatorB<-1) {
        printf("LL(%s)\n", no->dado);
        no = LL(no); //caso LL
    }

    return no;
}

void atualizarFB(No *no){
    int valEsq=0, valDir=0;
    if (no->esq!=NULL) valEsq = no->esq->fatorB +1;
    if (no->dir!=NULL) valDir = no->dir->fatorB -1; 
    no->fatorB = valEsq + valDir;
}

void fbTudo(No *raiz){
    if(raiz==NULL) return;
    fbTudo(raiz->esq);
    fbTudo(raiz->dir);
    atualizarFB(raiz);
}

void balancearTudo(No *raiz){
    if(raiz==NULL) return;
    balancearTudo(raiz->esq);
    balancearTudo(raiz->dir);
    balancear(raiz);
}

No* inserir(No* raiz, char* palavra, char* significado) {
    if (raiz == NULL) return criaNo(palavra, significado);
    
    int valor = strcmp(palavra, raiz->dado);

    if (valor < 0){
        raiz->esq = inserir(raiz->esq, palavra, significado);
        if (raiz->esq != NULL) raiz->esq->pai = raiz;
    }
    else if (valor > 0){
        raiz->dir = inserir(raiz->dir, palavra, significado);
        if (raiz->dir != NULL) raiz->dir->pai = raiz;
    }
    else {
        printf("Palavra já existe no dicionário\n");
        return raiz;
    }
    fbTudo(raiz);
    return balancear(raiz);
}

No* encontrarAntecessor(No* raiz) {
    No* atual = raiz;
    while (atual && atual->dir != NULL) {
        atual = atual->dir;
    }
    return atual;
}

//falta fazer
No* remover(No* raiz, char* palavra) {
    if (raiz == NULL) {
        printf("Palavra nao encontrada.\n");
        return raiz;
    }

    int valor = strcmp(palavra, raiz->dado);

    if(valor < 0){
        raiz->esq = remover(raiz->esq, palavra);
    }
    else if(valor > 0){
        raiz->dir = remover(raiz->dir, palavra);
    }

    //encontrou
    else{ 
        if(raiz->esq == NULL && raiz->dir == NULL) { //folha
            free(raiz);
            return NULL;
        } 

        else if(raiz->esq == NULL){ //só tem 1 filho
            No* temp = raiz->dir;
            temp->pai = raiz->pai;
            free(raiz);
            return temp;
        } 
        else if(raiz->dir == NULL){ //só tem 1 filho
            No* temp = raiz->esq;
            temp->pai = raiz->pai;
            free(raiz);
            return temp;
        } 
        else{ //tem ambos os filhos
            No* antecessor = encontrarAntecessor(raiz->esq);
            strcpy(raiz->dado, antecessor->dado);
            strcpy(raiz->significado, antecessor->significado);
            raiz->esq = remover(raiz->esq, antecessor->dado);
        }
        //atualiza fatores de balanceamento e balanceia a árvore
        fbTudo(raiz);
        balancearTudo(raiz);
        printf("Palavra excluida com sucesso!");
    }
  //return balancear(raiz);
}

No* busca(No *raiz, char palavra[]){
    if(raiz == NULL){
        printf("Palavra nao encontrada!\n");
        return NULL;
    }
    int cmp = strcmp(raiz->dado, palavra);
    if(cmp<0){
        return busca(raiz->dir, palavra);
    }
    else if(cmp>0){
    return busca(raiz->esq, palavra);
    }
    else {
        printf("Palavra encontradada!\n%s: %s\n",raiz->dado,raiz->significado);
        return raiz;
    } 
}

void percursoEmOrdem(No* no){
    if(no == NULL) return;
    percursoEmOrdem(no->esq);
    printf("%s: %s ",no->dado, no->significado);
    percursoEmOrdem(no->dir);
}

int main() {
    Arvore* arvore;
    char palavra[50], significado[256];
    int opcao;
    while(opcao != 6){
        printf("\n----------------------------\n");
        printf("Escolha uma opcao\n");
        printf("[1] Criar arvore vazia\n");
        printf("[2] Remover uma palavra\n");
        printf("[3] Inserir uma palavra\n");
        printf("[4] Buscar palavra\n");
        printf("[5] Imprimir arvore\n");
        printf("[6] Sair\n");
        printf("----------------------------\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        switch(opcao){
        case 1:
            //cria árvore vazia
            arvore = criaArvore();
            printf("Arvore criada com sucesso\n");
            break;
        case 2:
            // remover palavra
            printf("Insira uma palavra para excluir: ");
            scanf("%s",palavra);
            remover(arvore->raiz, palavra);
            break;
        case 3:
            //insere palavra
            printf("Insira uma palavra: ");
            scanf("%s",palavra);
            printf("Insira o significado: ");
            scanf(" %[^\n]", significado);
            arvore->raiz = inserir(arvore->raiz, palavra, significado);         
            break;
        case 4:
            //busca
            printf("Insira uma palavra para buscar: ");
            scanf("%s",palavra);
            busca(arvore->raiz, palavra);
            break;
        case 5:
            // imprimir arvore
            percursoEmOrdem(arvore->raiz);
            break;
        case 6:
            printf("Encerrando!");
            break;
        default:
            printf("Opçao invalida, tente novamente");
        }
    }
    return 0;
}
