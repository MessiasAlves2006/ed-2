#include <stdlib.h>
#include <stdio.h>
 
// Q16
typedef struct Arvore {
    int dado;
    struct Arvore *direita;
    struct Arvore *esquerda;
} Arvore;

//Q17
Arvore* CriarArvore() {
    return NULL;
}

int ArvoreVazia(Arvore *raiz) {
    return raiz == NULL;
}

//Q18
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

//Q19
int quantidadeNos(Arvore *raiz) {
    if (ArvoreVazia(raiz)) {
        return 0;
    } else {
        return 1 + quantidadeNos(raiz->esquerda) + quantidadeNos(raiz->direita);
    }
}

//Q20
int alturaArvore(Arvore *raiz) {
    if (ArvoreVazia(raiz)) {
        return -1;
    } else {
        int alturaEsquerda = alturaArvore(raiz->esquerda);
        int alturaDireita = alturaArvore(raiz->direita);
        return 1 + (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita);
    }
}

//Q21
int quantidadeFolhas(Arvore *raiz) {
    if (ArvoreVazia(raiz)) {
        return 0;
    } else if (ArvoreVazia(raiz->esquerda) && ArvoreVazia(raiz->direita)) {
        return 1;
    } else {
        return quantidadeFolhas(raiz->esquerda) + quantidadeFolhas(raiz->direita);
    }
}

//Q22
int estaNaArvore(Arvore *raiz, int valor) {
    if (ArvoreVazia(raiz)) {
        return 0;
    } else {
        if (valor == raiz->dado) {
            return 1;
        } else if (valor < raiz->dado) {
            return estaNaArvore(raiz->esquerda, valor);
        } else {
            return estaNaArvore(raiz->direita, valor);
        }
    }
}

//Q23
void mostrarArvore(Arvore *raiz) {
    if (!ArvoreVazia(raiz)) {
        printf("%d ", raiz->dado);
        mostrarArvore(raiz->esquerda);
        mostrarArvore(raiz->direita);
    }
}

//Q25 
void liberarArvore(Arvore *raiz) {
    if (!ArvoreVazia(raiz)) {
        liberarArvore(raiz->esquerda);
        liberarArvore(raiz->direita);
        free(raiz);
    }
}

char resposta () {
    printf("1-C, 2-B, 3-C, 4-c, 5-B, 6-A, 7-D, 8-A, \n 9-Uma árvore é uma estrutura de dados não linear formada por nós, organizados de forma hierárquica. Existe um nó raiz, que não possui pai. Cada nó pode ter zero ou mais nós filhos, formando subárvores, \n 10-Nó raiz: nó de topo da árvore, sem pai. Ponto de entrada de toda a estrutura. Existe somente um, Nó folha: nó sem filhos. Representa o fim de um ramo. Uma árvore pode ter muitas folhas, Nó interno: qualquer nó que não é raiz nem folha. Possui ao menos um filho e ao menos um pai. Serve de 'intermediário' na hierarquia, \n 11-Ancestral de um nó N é qualquer nó no caminho da raiz até N. Em outras palavras, são o pai, o avô, o bisavô de N, Descendente de um nó N é qualquer nó que pode ser alcançado a partir de N descendo pela árvore. São todos os filhos, netos, bisnetos de N, \n 12-A profundidade de um nó é o número de arestas no caminho da raiz até esse nó. A raiz tem profundidade 0. Seus filhos têm profundidade 1, os netos profundidade 2, e assim por diante, \n 13-Grau de um nó: quantidade de filhos daquele nó específico. Exemplo: um nó com 3 filhos tem grau 3; uma folha tem grau 0, Grau de uma árvore: o maior grau encontrado entre todos os nós da árvore. Representa a 'capacidade máxima de ramificação' da estrutura. Exemplo: se o nó com mais filhos tem 4 filhos, o grau da árvore é 4, \n 14-Busca eficiente: árvores binárias de busca permitem localizar dados em O(log n) no caso médio,");
    printf("\n Q15-");
    printf("\n                20                ");
    printf("\n       |        |         |       ");
    printf("\n      10       25        30       ");
    printf("\n    |    |   |    |    |    |     ");
    printf("\n    5   11  19   27   29   32     ");
    printf("\n folhas: 5, 11, 19, 27, 29, 32. Quantidade de folhas: 6. Altura da árvore: 2. Grau da árvore: 3. "); 

}


int main () {
    Arvore *raiz = CriarArvore();
    inserirArvore(&raiz, 10);
    inserirArvore(&raiz, 5);
    inserirArvore(&raiz, 15);
    inserirArvore(&raiz, 3);
    inserirArvore(&raiz, 7);
    inserirArvore(&raiz, 12);
    inserirArvore(&raiz, 18);

    printf("Quantidade de nos: %d\n", quantidadeNos(raiz));
    printf("Altura da arvore: %d\n", alturaArvore(raiz));
    printf("Quantidade de folhas: %d\n", quantidadeFolhas(raiz));
    printf("Valor 7 esta na arvore? %s\n", estaNaArvore(raiz, 7) ? "Sim" : "Nao");
    printf("Valor 20 esta na arvore? %s\n", estaNaArvore(raiz, 20) ? "Sim" : "Nao");

    printf("Mostrando a arvore: ");
    mostrarArvore(raiz);
    printf("\n");

    liberarArvore(raiz);
    resposta();
    return 0;
}

