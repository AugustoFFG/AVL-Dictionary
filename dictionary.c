#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct no{
    char dado[50];
    char signigicado[300];
    int fatorB;
    struct no* pai;
    struct no* esq;
    struct no* dir;
}No;

typedef struct arvore {
    No *raiz;
    int numNos;
} Arvore;

No* CriaNo(char* palavra, char* significado){
    No* no = (No*)malloc(sizeof(No));
    strcpy(no->dado, palavra);
    strcpy(no->signigicado, significado);
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
    return n->esq->fatorB - n->esq->alturaDir; 
}
*/

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

void balancear(No* no) {
    if(no->fatorB==2){
        if(no->esq->fatorB==-1){
            LL(no->esq);
            RR(no);
        }
    } else if(no->fatorB == -2){
        if(no->dir->fatorB==1){
            RR(no->dir);
            LL(no);
        }
    }
}

No* inserir(No* raiz, char* palavra, char* significado) {
    if (raiz == NULL) return criarNo(palavra, significado);
    
    int valor = strcmp(palavra, raiz->dado);

    if (valor < 0){
        raiz->esq = inserir(raiz->esq, palavra, significado);
        raiz->esq->pai = raiz;
        raiz->esq->fatorB -= 1;
        balancear(raiz->esq);
    }
    else if (valor > 0){
        raiz->dir = inserir(raiz->dir, palavra, significado);
        raiz->dir->pai = raiz;
        raiz->dir->fatorB += 1;
        balancear(raiz->dir);
    }
    else {
        printf("Palavra já existe no dicionário\n");
        return NULL;
    }
}

//falta fazer
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
            No* antecessor = encontrarMaximo(raiz->esq);
            strcpy(raiz->dado, antecessor->dado);
            strcpy(raiz->signigicado, antecessor->signigicado);
            raiz->esq = remover(raiz->esq, antecessor->dado);
        }
        //for de todo no z na subarvore de r
        //atualizaFb(z);
        //balancear(z)
    }
    
  //return balancear(raiz);
}

No* busca(No *raiz, char palavra[]){
    int cmp = strcmp(raiz->dado, palavra);
    if(raiz == NULL || cmp==0) return raiz;
    if(cmp>0) busca(raiz->dir, palavra);
    else busca(raiz->esq, palavra);
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
