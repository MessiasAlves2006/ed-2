#include <stdlib.h>
#include <stdio.h>

typedef struct Arvore {
    int dado;
    struct Arvore *direita;
    struct Arvore *esquerda;
} Arvore;

Arvore* CriarArvore() {
    Arvore *novo = (Arvore *) malloc(sizeof(Arvore));
    if (novo == NULL) {
        fprintf(stderr, "Erro: nao foi possivel alocar memoria para um novo no\n");
        exit(EXIT_FAILURE);
    }
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

int ArvoreVazia(Arvore *raiz) {
    return raiz == NULL;
}

Arvore* inserirIter(Arvore *raiz, int valor) {
    Arvore *novo = CriarArvore();
    novo->dado = valor;
    novo->esquerda = NULL;
    novo->direita = NULL;
    if (raiz == NULL) return novo;
    Arvore *atual = raiz, *pai = NULL;
    while (atual) {
        pai = atual;
        if (valor < atual->dado)     
            atual = atual->esquerda;
        else if (valor > atual->dado) 
            atual = atual->direita;
        else { free(novo); return raiz; } 
    }
    if (valor < pai->dado) 
        pai->esquerda = novo;
    else                   
        pai->direita = novo;
    return raiz;
}

Arvore* buscarIter(Arvore *raiz, int valor) {
    while (raiz && raiz->dado != valor)
        raiz = (valor < raiz->dado) ? raiz->esquerda : raiz->direita;
    return raiz;
}

void liberarArvore(Arvore *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

void espelhar(Arvore *raiz) {
    if (raiz == NULL) return;
    /* Troca os ponteiros esquerdo e direito */
    Arvore *tmp   = raiz->esquerda;
    raiz->esquerda = raiz->direita;
    raiz->direita = tmp;
    espelhar(raiz->esquerda);
    espelhar(raiz->direita);
}

int altura(Arvore *n) {
    if (n == NULL) return 0;
    int he = altura(n->esquerda);
    if (he == -1) return -1;         
    int hd = altura(n->direita);
    if (hd == -1) return -1;
    int diff = he - hd;
    if (diff < -1 || diff > 1) return -1;
    return 1 + (he > hd ? he : hd);
}

int eBalanceada(Arvore *raiz) {
    return altura(raiz) != -1;
}

void imprimirEmOrdem(Arvore *raiz) {
    if (raiz == NULL) return;
    imprimirEmOrdem(raiz->esquerda);
    printf("%d ", raiz->dado);
    imprimirEmOrdem(raiz->direita);
}

void imprimirPreOrdem(Arvore *raiz) {
    if (raiz == NULL) return;
    printf("%d ", raiz->dado);
    imprimirPreOrdem(raiz->esquerda);
    imprimirPreOrdem(raiz->direita);
}

int main(void) {
    Arvore *raiz = CriarArvore();

    int valores[] = {10, 5, 15, 3, 7, 12, 18};
    int tamanho = sizeof(valores) / sizeof(valores[0]);
    for (int i = 0; i < tamanho; i++) {
        raiz = inserirIter(raiz, valores[i]);
    }

    printf("Arvore apos insercoes (em ordem): ");
    imprimirEmOrdem(raiz);
    printf("\n");

    printf("Arvore vazia apos insercoes? %s\n", ArvoreVazia(raiz) ? "sim" : "nao");

    int buscaExistente = 7;
    int buscaInexistente = 20;
    printf("Buscar %d: %s\n", buscaExistente,
           buscarIter(raiz, buscaExistente) ? "encontrado" : "nao encontrado");
    printf("Buscar %d: %s\n", buscaInexistente,
           buscarIter(raiz, buscaInexistente) ? "encontrado" : "nao encontrado");

    printf("Altura da arvore: %d\n", altura(raiz));
    printf("Arvore balanceada? %s\n", eBalanceada(raiz) ? "sim" : "nao");

    printf("Estrutura antes de espelhar (pre-ordem): ");
    imprimirPreOrdem(raiz);
    printf("\n");

    espelhar(raiz);
    printf("Estrutura apos espelhar (pre-ordem): ");
    imprimirPreOrdem(raiz);
    printf("\n");

    printf("Altura apos espelhar: %d\n", altura(raiz));
    printf("Arvore balanceada apos espelhar? %s\n", eBalanceada(raiz) ? "sim" : "nao");

    liberarArvore(raiz);
    raiz = NULL;
    printf("Arvore liberada. Vazia? %s\n", ArvoreVazia(raiz) ? "sim" : "nao");

    return 0;
}
