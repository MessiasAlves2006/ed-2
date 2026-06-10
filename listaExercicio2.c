#include <stdlib.h>
#include <stdio.h>

char resposta() {
    printf("1-B, 2-C, 3-C, 4-B, 5-A, 6-B. \n");
    printf("7- Uma arvore binaria cheia possui apenas nos com dois filhos ou folhas. Já uma arvore completa possui todos os niveis preenchidos exceto possivelmente o ultimo. \n");
    printf("8- Pre-ordem: visita a raiz primeiro depois as subarvores comecando da esquerda para a direita, Em-Ordem: visita as subarvores da esquerda para a raiz e depois a direita, Pos-Ordem: visita as subarvores da esquerda para a direita e depois a raiz. \n");
    printf("9- inserção e remoção frequentes em vetores ordenados, inserir exige deslocar elementos O(n), enquanto numa BST balanceada é O(log n): busca em dados dinâmicos quando os dados mudam constantemente, manter um vetor ordenado é caro: dados hierárquicos quando a estrutura em si é uma hierarquiia. \n");
    printf("!0-");
    printf("                5                  ");
    printf("        |               |          ");
    printf("        3               8          ");
    printf("    |       |       |       |      ");
    printf("    2       4       7       9      ");
    printf(" |              |               |  ");
    printf(" 1              6               10 ");
    printf("Pré-ordem: 5, 3, 2, 1, 4, 8, 7, 6, 9, 10 \n");
    printf("Em-ordem: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 \n");
    printf("Pós-ordem: 1, 2, 4, 3, 6, 7, 10, 9, 8, 5, \n");
}

// Q36
typedef struct Arvore {
    int dado;
    struct Arvore *direita;
    struct Arvore *esquerda;
} Arvore;

Arvore* CriarArvore() {
    return NULL;
}

int ArvoreVazia(Arvore *raiz) {
    return raiz == NULL;
}

//Q37
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

void adicionarValor(Arvore **raiz) {
    char res = 'S';
    int valor;
    printf("Deseja adicionar um valor a arvore? (S/N): ");
    scanf(" %c", &res);
    while (res == 'S') {
        printf("Digite o valor a ser adicionado: ");
        scanf("%d", &valor);
        inserirArvore(raiz, valor);
        printf("Deseja adicionar um valor a arvore? (S/N): ");
        scanf(" %c", &res);
    }
}    

//Q38
void preOrdem(Arvore *raiz) {
    if (raiz == NULL) return;
    printf("%d ", raiz->dado);
    preOrdem(raiz->esquerda);      
    preOrdem(raiz->direita);        
}

//Q39
void emOrdem(Arvore *raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esquerda);      
    printf("%d ", raiz->dado);  
    emOrdem(raiz->direita);         
}

//Q40
void posOrdem(Arvore *raiz) {
    if (raiz == NULL) return;
    posOrdem(raiz->esquerda);       
    posOrdem(raiz->direita);        
    printf("%d ", raiz->dado);  
}

//Q41
int quantidadeNos(Arvore *raiz) {
    if (ArvoreVazia(raiz)) {
        return 0;
    } else {
        return 1 + quantidadeNos(raiz->esquerda) + quantidadeNos(raiz->direita);
    }
}

//Q42
int alturaArvore(Arvore *raiz) {
    if (ArvoreVazia(raiz)) {
        return -1;
    } else {
        int alturaEsquerda = alturaArvore(raiz->esquerda);
        int alturaDireita = alturaArvore(raiz->direita);
        return 1 + (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita);
    }
}

//Q43
int quantidadeFolhas(Arvore *raiz) {
    if (ArvoreVazia(raiz)) {
        return 0;
    } else if (ArvoreVazia(raiz->esquerda) && ArvoreVazia(raiz->direita)) {
        return 1;
    } else {
        return quantidadeFolhas(raiz->esquerda) + quantidadeFolhas(raiz->direita);
    }
}

//Q44
void espelhar(Arvore *raiz) {
    if (raiz == NULL) return;
    Arvore *temp  = raiz->esquerda;
    raiz->esquerda = raiz->direita;
    raiz->direita = temp;
    espelhar(raiz->esquerda);
    espelhar(raiz->direita);
}

//Q45
int saoIguais(Arvore *a, Arvore *b) {
    if (a == NULL && b == NULL) return 1; 
    if (a == NULL || b == NULL) return 0; 
    return (a->dado == b->dado)
        && saoIguais(a->esquerda, b->esquerda)
        && saoIguais(a->direita, b->direita);
}

void mostrarArvore(Arvore *raiz) {
    if (!ArvoreVazia(raiz)) {
        printf("%d ", raiz->dado);
        mostrarArvore(raiz->esquerda);
        mostrarArvore(raiz->direita);
    }
}

int main() {
    Arvore *raiz = CriarArvore();
    adicionarValor(&raiz);
 

    printf("Quantidade de nos: %d\n", quantidadeNos(raiz));
    printf("Altura da arvore: %d\n", alturaArvore(raiz));
    printf("Quantidade de folhas: %d\n", quantidadeFolhas(raiz));
    printf("mostrando a arvore ");
    mostrarArvore(raiz);
    printf("\n");
    printf("mostrando a arvore em pre-ordem: ");
    preOrdem(raiz);
    printf("\n");
    printf("Mostrando a arvore em em-ordem: ");
    emOrdem(raiz);
    printf("\n");
    printf("Mostrando a arvore em pos-ordem: ");
    posOrdem(raiz);
    printf("\n");

    resposta();
    return 0;
}