#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

char resposta() {
    printf("1-C, 2-C, 3-B, 4-B. \n");
    printf("5- A inserção começa na raiz. O valor a inserir é comparado com o nó atual: se for menor, desce para a subárvore esquerda; se for maior, desce para a direita. Isso se repete recursivamente até encontrar um ponteiro NULL, onde o novo nó é criado e anexado. Caso o valor já exista, a ABB ignora a inserção. \n");
    printf("6- Partindo da raiz, o valor buscado é comparado com o nó atual. Se igual, o nó foi encontrado. Se menor, busca-se na subárvore esquerda; se maior, na direita. Repete até encontrar o valor ou atingir NULL. Em uma ABB balanceada isso custa O(log n); em uma degenerada, O(n). \n");
    printf("7- Remoção de folha: o nó não tem filhos. Basta liberar o nó e colocar NULL no ponteiro do pai. Remoção com um filho: o nó tem exatamente um filho. O pai passa a apontar diretamente para esse filho, e o nó é liberado. Remoção com dois filhos: o nó não pode ser simplesmente removido. Encontra-se o sucessor em ordem (menor valor da subárvore direita) ou o predecessor em ordem (maior da esquerda), copia seu valor para o nó a remover, e então remove-se o sucessor/predecessor que terá no máximo um filho. \n");
    printf("8- A ABB impõe uma propriedade de ordem: para todo nó, todos os valores da subárvore esquerda são menores e todos da direita são maiores. Isso permite busca, inserção e remoção em O(log n) numa árvore balanceada, em vez de O(n) numa busca linear. Também permite obter os elementos em ordem crescente simplesmente realizando o percurso em ordem. \n");
    printf("9- Se os dados forem inseridos em ordem crescente ou decrescente, cada novo nó vai sempre para o mesmo lado, gerando uma árvore degenerada — semelhante a uma lista encadeada com altura n. Nesse caso, a complexidade de busca cai de O(log n) para O(n). Para evitar isso, usam árvores auto-balanceadas como Rubro-Negra, que realizam rotações para manter a altura próxima de log n após cada inserção ou remoção. \n");
}

// Q10
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

//Q11 
Arvore* buscar(Arvore *raiz, int valor) {
    if (raiz == NULL || raiz->dado == valor)
        return raiz;
    if (valor < raiz->dado)
        return buscar(raiz->esquerda, valor);
    return buscar(raiz->direita, valor);
}

//Q12 
void emOrdem(Arvore *raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esquerda);      
    printf("%d ", raiz->dado);  
    emOrdem(raiz->direita);         
}

//Q13
Arvore* removerFolha(Arvore *raiz, int valor) {
    if (raiz == NULL) return NULL;
    if (valor < raiz->dado) {
        raiz->esquerda = removerFolha(raiz->esquerda, valor);
    } else if (valor > raiz->dado) {
        raiz->direita = removerFolha(raiz->direita, valor);
    } else {
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        }
    }
    return raiz;
}

//Q14
Arvore* removerFilho(Arvore *raiz, int valor) {
    if (raiz == NULL) return NULL;
    if (valor < raiz->dado) {
        raiz->esquerda = removerFilho(raiz->esquerda, valor);
    } else if (valor > raiz->dado) {
        raiz->direita = removerFilho(raiz->direita, valor);
    } else {
        if (!raiz->esquerda && !raiz->direita) { free(raiz); return NULL; }

        if (raiz->esquerda == NULL) {
            Arvore *tmp = raiz->direita; free(raiz); return tmp;
        }
        if (raiz->direita == NULL) {
            Arvore *tmp = raiz->esquerda; free(raiz); return tmp;
        }
    }
    return raiz;
}

//Q15
Arvore* minNo(Arvore *n) {
    while (n->esquerda) n = n->esquerda;
    return n;
}

Arvore* removerDoisFilhosOrdem(Arvore *raiz, int v) {
    if (raiz == NULL) return NULL;
    if (v < raiz->dado)      raiz->esquerda = removerDoisFilhosOrdem(raiz->esquerda, v);
    else if (v > raiz->dado) raiz->direita = removerDoisFilhosOrdem(raiz->direita, v);
    else {
        if (!raiz->esquerda) { Arvore *t = raiz->direita; free(raiz); return t; }
        if (!raiz->direita) { Arvore *t = raiz->esquerda; free(raiz); return t; }

        Arvore *suc = minNo(raiz->direita);      
        raiz->dado = suc->dado;          
        raiz->direita  = removerDoisFilhosOrdem(raiz->direita, suc->dado); 
    }
    return raiz;
}

//Q16
int menorValor(Arvore *raiz) {
    if (raiz == NULL) { puts("Árvore vazia"); return -1; }
    while (raiz->esquerda) raiz = raiz->esquerda;
    return raiz->dado;
}

int maiorValor(Arvore *raiz) {
    if (raiz == NULL) { puts("Árvore vazia"); return -1; }
    while (raiz->direita) raiz = raiz->direita;
    return raiz->dado;
}

//Q17
int _validar(Arvore *n, int min, int max) {
    if (n == NULL) return 1;
    if (n->dado <= min || n->dado >= max) return 0;
    return _validar(n->esquerda, min, n->dado)
        && _validar(n->direita, n->dado, max);
}

int ehABB(Arvore *raiz) {
    return _validar(raiz, INT_MIN, INT_MAX);
}

//Q18
int altura(Arvore *raiz) {
    if (raiz == NULL) return 0;  
    int he = altura(raiz->esquerda);
    int hd = altura(raiz->direita);
    return 1 + (he > hd ? he : hd);
}

int main() {
    Arvore *raiz = NULL;
    int op, valor;
    do {
        printf("\n1-Inserir 2-Buscar 3-Remover 4-Em ordem 5-Altura 0-Sair\n> ");
        scanf("%d", &op);
        switch(op) {
            case 1: 
                printf("Valor: "); 
                scanf("%d",&valor); 
                inserirArvore(&raiz,valor); 
                break;
            case 2: 
                printf("Valor: "); 
                scanf("%d",&valor); 
                printf(buscar(raiz,valor)?"Encontrado\n":"Não encontrado\n"); 
                break;
            case 3: 
                printf("Valor: "); 
                scanf("%d",&valor); 
                raiz=removerDoisFilhosOrdem(raiz,valor); 
                break;
            case 4: 
                emOrdem(raiz); 
                puts(""); 
                break;
            case 5: 
                printf("Altura: %d\n", altura(raiz)); 
                break;
        }
    } while(op != 0);
    return 0;
}

