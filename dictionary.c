#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct no{
    char dado[50];
    char signigicado[300];
    int altura;
    struct no* pai;
    struct no* esq;
    struct no* dir;
}No;

No* CriaNo(char* palavra, char* significado){
    No* no = (No*)malloc(sizeof(No));
    strcpy(no->dado, palavra);
    strcpy(no->signigicado, significado);
    no->altura = 1;
    no->dir = NULL;
    no->esq = NULL;
    no->pai = NULL;
    return no;
}

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
    return alturaEsq - alturaDir; 
}

void LL(No* no) {
    No *aux;
    aux = no->dir;
    if(aux->esq!=NULL) aux->esq->pai = no;
    no->dir = aux->esq;
    aux->esq = no;
    aux->pai = no->pai;
    no->pai = aux;
    no = aux; //if(no->pai==NULL) arv->raiz = aux;
}


void RR(No* no) {
    No *aux;
    aux = no->esq;
    if(aux->dir!=NULL) aux->dir->pai = no;
    no->esq = aux->dir;
    aux->dir = no;
    aux->pai = no->pai;
    no->pai = aux;
    no = aux; //if(no->pai==NULL) arv->raiz = aux;
}

void RL(No *no){
    RR(no->dir);
    LL(no);
}

void LR(No *no){
    LL(no->esq);
    RR(no);
}

//No* balancear(No* raiz)

No* inserir(No* raiz, char* palavra, char* significado) {
    if (raiz == NULL) return criarNo(palavra, significado);
    
    int valor = strcmp(palavra, raiz->dado);

    if (valor < 0){
        raiz->esq = inserir(raiz->esq, palavra, significado);
        raiz->esq->pai = raiz;
    }
    else if (valor > 0){
        raiz->dir = inserir(raiz->dir, palavra, significado);
        raiz->dir->pai = raiz;
    }
    else{
        printf("Palavra já existe no dicionário\n");
        return raiz;
    }
    raiz->altura = 1 + obterMaior(calcularAltura(raiz->esq), calcularAltura(raiz->dir));
    return balancear(raiz);
}

No* remover(No* raiz, char* palavra) {
    if (raiz == NULL) {
        printf("Palavra não encontrada.\n");
        return raiz;
    }

    int valor = strcmp(palavra, raiz->dado);

    if(valor < 0){
        raiz->esq = remover(raiz->esq, palavra);
    }
    else if(valor > 0){
        raiz->dir = remover(raiz->dir, palavra);
    }
    else{ 
        if(raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        } 
        else if(raiz->esq == NULL){
            No* temp = raiz->dir;
            temp->pai = raiz->pai;
            free(raiz);
            return temp;
        } 
        else if(raiz->dir == NULL){
            No* temp = raiz->esq;
            temp->pai = raiz->pai;
            free(raiz);
            return temp;
        } 
        else{
            No* antecessor = encontrarMaximo(raiz->esq);
            strcpy(raiz->dado, antecessor->dado);
            strcpy(raiz->signigicado, antecessor->signigicado);
            raiz->esq = remover(raiz->esq, antecessor->dado);
        }
    }
    
  //return balancear(raiz);
}

void percursoEmOrdem(No* no){
    if(no == NULL) return;
    percursoEmOrdem(no->esq);
    printf("%s ",no->dado); //por enquanto imprime só a palavra
    percursoEmOrdem(no->dir);
}

int main(){
    return 0;
}
