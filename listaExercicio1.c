//Questão 1: R= c
//Questão 2: R= b   
//Questão 3: R= c
//Questão 4: R= c
//Questão 5: R= b
//Questão 6: R= a
//Questão 7: R= d
//Questão 8: R= a
//Questão 9: R= A arvore e uma estrutura de dados, que organizar dados de forma ordenada, fazendo com que o tempo de buscar seja diminuido significativamente
//Questão 10: R= No raiz e o primeiro no que comeca a arvore, os nos folhas sao os nos que nao tem filhos, e os nos internos sao os nos que tem filhos, mas nao sao a raiz
//Questão 11: R= Ancestrais sao os nos que estao acima do no em questao, e descendentes sao os nos que estao abaixo do no em questao
//Questão 12: R= A profundidade de um no e a distancia entre o no e a raiz
//Questão 13: R= Grau do no se refere a quantidade de filhos que o no tem, grau da arvore e a mesma coisa que o no com maior grau ou seja, o no que tem mais filhos
//Questão 14: R= As arvores sao importantes pois se bem utilizadas, podem diminuir o tempo de busca de um elemento
//Questão 15: R= No raiz(10), No folha(1), Grau Arvore(2) Altura(3) Nos(10, 5, 15, 3, 7, 12, 20, 1)
                 10
                /  \
               /    \
              5      15
             / \    /  \
            3   7  12   20
           /
          1

//Questão 16: R= 
def struct No{
    int dado;
    struct No *direita;
    struct No *esquerda;
} No;