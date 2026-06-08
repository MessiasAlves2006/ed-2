#include <stdlib.h>
#include <stdio.h>
 
typedef struct Arvore {
    int dado;
    struct Arvore *direita;
    struct Arvore *esquerda;
} Arvore;

Arvore* CreateArvore() {
    return NULL;
}

int ArvoreVazia(Arvore *raiz) {
    return raiz == NULL;
}

void mostrarArvore(Arvore *raiz) {
    if (!ArvoreVazia(raiz)) {
        printf("%d ", raiz->dado);
        mostrarArvore(raiz->esquerda);
        mostrarArvore(raiz->direita);
    }
}

void inserirArvore(Arvore **raiz, int valor) {
    if (ArvoreVazia(*raiz)) {
        *raiz = (Arvore*)malloc(sizeof(Arvore));
        (*raiz)->dado = valor;
        (*raiz)->direita = NULL;
        (*raiz)->esquerda = NULL;
    } else {
        if (valor < (*raiz)->dado) {
            inserirArvore(&(*raiz)->esquerda, valor);
        } else {
            inserirArvore(&(*raiz)->direita, valor);
        }
    }
}

int estaNaArvore(Arvore *raiz, int valor) {
    if (ArvoreVazia(raiz)) {
        return 0;
    } else {
        if (valor == raiz->dado) {
            return 1;
        } else if (valor < raiz->dado) {
            return estahNaArvore(raiz->esquerda, valor);
        } else {
            return estahNaArvore(raiz->direita, valor);
        }
    }
}

