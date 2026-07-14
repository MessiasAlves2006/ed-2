#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

// --- ESTRUTURA DA ÁRVORE ---
typedef enum { RBT_RED, RBT_BLACK } NodeColor;

typedef struct Node {
    int data;
    NodeColor color; // Propriedade unificada como 'color'
    struct Node *left, *right, *parent;
} Node;

// --- ROTAÇÕES ---
void rotateLeft(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    
    if (y->left != NULL)
        y->left->parent = x;
        
    y->parent = x->parent;
    
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
        
    y->left = x;
    x->parent = y;
}

void rotateRight(Node **root, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    
    if (x->right != NULL)
        x->right->parent = y;
        
    x->parent = y->parent;
    
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
        
    x->right = y;
    y->parent = x;
}

// --- BALANCEAMENTO DA INSERÇÃO ---
void fixUp(Node **root, Node *z) {
    while (z != *root && z->parent->color == RBT_RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right; // Tio de z
            
            // Caso 1: O tio é Vermelho
            if (y != NULL && y->color == RBT_RED) {
                z->parent->color = RBT_BLACK;
                y->color = RBT_BLACK;
                z->parent->parent->color = RBT_RED;
                z = z->parent->parent;
            } else {
                // Caso 2: O tio é Preto e z é um filho à direita
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(root, z);
                }
                // Caso 3: O tio é Preto e z é um filho à esquerda
                z->parent->color = RBT_BLACK;
                z->parent->parent->color = RBT_RED;
                rotateRight(root, z->parent->parent);
            }
        } else {
            // Espelho do bloco acima (quando o pai de z é filho à direita)
            Node *y = z->parent->parent->left;
            
            if (y != NULL && y->color == RBT_RED) {
                z->parent->color = RBT_BLACK;
                y->color = RBT_BLACK;
                z->parent->parent->color = RBT_RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(root, z);
                }
                z->parent->color = RBT_BLACK;
                z->parent->parent->color = RBT_RED;
                rotateLeft(root, z->parent->parent);
            }
        }
    }
    (*root)->color = RBT_BLACK; // A raiz sempre deve ser preta
}

void insert(Node **root, int data) {
    Node *z = (Node*)malloc(sizeof(Node));
    z->data = data;
    z->left = z->right = z->parent = NULL;
    z->color = RBT_RED; // Sempre inserido como vermelho
    
    Node *y = NULL;
    Node *x = *root;
    
    // Caminha na árvore para achar a posição de inserção
    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    
    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;
        
    // Corrige as propriedades da árvore
    fixUp(root, z);
}

void inorder(Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d(%s) ", root->data, root->color == RBT_RED ? "V" : "P");
    inorder(root->right);
}

Node* search(Node *root, int key) {
    if (root == NULL || root->data == key)
        return root;
    
    if (key < root->data)
        return search(root->left, key);
        
    return search(root->right, key);
}

void destroyTree(Node *root) {
    if (root == NULL) return;
    
    destroyTree(root->left);
    destroyTree(root->right);
    free(root);
}

// --- BALANCEAMENTO DA REMOÇÃO ---
void deleteFixUp(Node **root, Node *x, Node *xParent) {
    while (x != *root && (x == NULL || x->color == RBT_BLACK)) {
        if (x == xParent->left) {
            Node *w = xParent->right; // Irmão de x
            
            // Caso 1: O irmão w é Vermelho
            if (w->color == RBT_RED) {
                w->color = RBT_BLACK;
                xParent->color = RBT_RED;
                rotateLeft(root, xParent);
                w = xParent->right;
            }
            
            // Caso 2: O irmão w é Preto e ambos os filhos de w são Pretos
            if ((w->left == NULL || w->left->color == RBT_BLACK) &&
                (w->right == NULL || w->right->color == RBT_BLACK)) {
                w->color = RBT_RED;
                x = xParent;
                xParent = x->parent;
            } else {
                // Caso 3: O irmão w é Preto, filho esquerdo de w é Vermelho e o direito é Preto
                if (w->right == NULL || w->right->color == RBT_BLACK) {
                    if (w->left != NULL) w->left->color = RBT_BLACK;
                    w->color = RBT_RED;
                    rotateRight(root, w);
                    w = xParent->right;
                }
                // Caso 4: O irmão w é Preto e o filho direito de w é Vermelho
                w->color = xParent->color;
                xParent->color = RBT_BLACK;
                if (w->right != NULL) w->right->color = RBT_BLACK;
                rotateLeft(root, xParent);
                x = *root; // Termina o loop
                break;
            }
        } else {
            // Espelho do bloco acima (quando x é o filho direito)
            Node *w = xParent->left;
            
            if (w->color == RBT_RED) {
                w->color = RBT_BLACK;
                xParent->color = RBT_RED;
                rotateRight(root, xParent);
                w = xParent->left;
            }
            
            if ((w->left == NULL || w->left->color == RBT_BLACK) &&
                (w->right == NULL || w->right->color == RBT_BLACK)) {
                w->color = RBT_RED;
                x = xParent;
                xParent = x->parent;
            } else {
                if (w->left == NULL || w->left->color == RBT_BLACK) {
                    if (w->right != NULL) w->right->color = RBT_BLACK;
                    w->color = RBT_RED;
                    rotateLeft(root, w);
                    w = xParent->left;
                }
                w->color = xParent->color;
                xParent->color = RBT_BLACK;
                if (w->left != NULL) w->left->color = RBT_BLACK;
                rotateRight(root, xParent);
                x = *root;
                break;
            }
        }
    }
    if (x != NULL) x->color = RBT_BLACK;
}

// Função auxiliar para encontrar o menor nó de uma subárvore
Node* minimum(Node *node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// --- REMOÇÃO ---
void deleteNode(Node **root, int key) {
    Node *z = search(*root, key);
    if (z == NULL) {
        printf("Elemento %d nao encontrado.\n", key);
        return;
    }

    Node *y = z;
    NodeColor y_original_color = y->color; // Ajustado de Color para NodeColor
    Node *x;
    Node *xParent;

    if (z->left == NULL) {
        x = z->right;
        xParent = z->parent;
        // Substituir z por x (transplante simples)
        if (z->parent == NULL) {
            *root = x;
        } else if (z == z->parent->left) {
            z->parent->left = x;
        } else {
            z->parent->right = x;
        }
        if (x != NULL) x->parent = z->parent;
    } 
    else if (z->right == NULL) {
        x = z->left;
        xParent = z->parent;
        if (z->parent == NULL) {
            *root = x;
        } else if (z == z->parent->left) {
            z->parent->left = x;
        } else {
            z->parent->right = x;
        }
        if (x != NULL) x->parent = z->parent;
    } 
    else {
        // Nó com dois filhos: acha o sucessor (mínimo da subárvore direita)
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        
        if (y->parent == z) {
            xParent = y; // Se o sucessor for filho direto de z
        } else {
            xParent = y->parent;
            // Desconecta y de sua posição original
            if (x != NULL) x->parent = y->parent;
            y->parent->left = x;
            y->right = z->right;
            y->right->parent = y;
        }
        
        // Substitui z por y na estrutura da árvore
        if (z->parent == NULL) {
            *root = y;
        } else if (z == z->parent->left) {
            z->parent->left = y;
        } else {
            z->parent->right = y;
        }
        y->parent = z->parent;
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    // Se a cor do nó removido/deslocado era preta, precisamos corrigir
    if (y_original_color == RBT_BLACK) {
        deleteFixUp(root, x, xParent);
    }
}

// --- FUNÇÕES DA INTERFACE GRÁFICA ---

// Função recursiva para desenhar as conexões (linhas) e depois os nós (círculos)
void DrawTree(Node *root, int x, int y, int hSpacing, int vSpacing) {
    if (root == NULL) return;

    // 1. Desenha as linhas primeiro para que fiquem por baixo dos círculos
    if (root->left != NULL) {
        DrawLine(x, y, x - hSpacing, y + vSpacing, GRAY);
        DrawTree(root->left, x - hSpacing, y + vSpacing, hSpacing / 1.8, vSpacing);
    }
    if (root->right != NULL) {
        DrawLine(x, y, x + hSpacing, y + vSpacing, GRAY);
        DrawTree(root->right, x + hSpacing, y + vSpacing, hSpacing / 1.8, vSpacing);
    }

    // 2. Determina a cor do nó (Mapeando NodeColor para Color da Raylib)
    Color color = (root->color == RBT_RED) ? RED : BLACK;
    Color border = (root->color == RBT_RED) ? MAROON : DARKGRAY;

    // 3. Desenha o círculo do nó e a borda
    DrawCircle(x, y, 22, border);
    DrawCircle(x, y, 20, color);

    // 4. Desenha o valor do nó centralizado
    char buffer[12];
    sprintf(buffer, "%d", root->data);
    int textWidth = MeasureText(buffer, 16);
    DrawText(buffer, x - textWidth / 2, y - 8, 16, WHITE);
}

int main() {
    // Inicialização da janela gráfica (Largura: 1000, Altura: 600)
    InitWindow(1000, 600, "Demonstrador de Arvore Rubro-Negra");
    SetTargetFPS(60);

    Node *root = NULL;
    char inputBuffer[16] = "\0";
    int letterCount = 0;

    // Inserindo alguns valores iniciais para demonstração
    insert(&root, 40);
    insert(&root, 20);
    insert(&root, 60);
    insert(&root, 10);
    insert(&root, 30);
    insert(&root, 50);
    insert(&root, 70);

    while (!WindowShouldClose()) {
        // --- 1. CAPTURA DE TECLADO (INPUT DO USUÁRIO) ---
        int key = GetCharPressed();
        while (key > 0) {
            // Permitir apenas números
            if ((key >= '0') && (key <= '9') && (letterCount < 5)) {
                inputBuffer[letterCount] = (char)key;
                inputBuffer[letterCount+1] = '\0';
                letterCount++;
            }
            key = GetCharPressed();
        }

        // Apagar caractere (Backspace)
        if (IsKeyPressed(KEY_BACKSPACE)) {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            inputBuffer[letterCount] = '\0';
        }

        // Confirmar inserção (Enter)
        if (IsKeyPressed(KEY_ENTER) && letterCount > 0) {
            int value = atoi(inputBuffer);
            insert(&root, value);
            inputBuffer[0] = '\0';
            letterCount = 0;
        }

        // Confirmar remoção (Delete)
        if (IsKeyPressed(KEY_DELETE) && letterCount > 0) {
            int value = atoi(inputBuffer);
            deleteNode(&root, value);
            inputBuffer[0] = '\0';
            letterCount = 0;
        }

        // --- 2. DESENHO NA TELA (RULER & RENDER) ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Painel de instruções superior esquerdo
        DrawRectangle(10, 10, 360, 140, Fade(SKYBLUE, 0.3f));
        DrawRectangleLines(10, 10, 360, 140, BLUE);
        DrawText("CONTROLES:", 20, 20, 16, DARKBLUE);
        DrawText("- Digite um numero e aperte ENTER para Inserir", 20, 45, 14, BLACK);
        DrawText("- Digite um numero e aperte DEL para Remover", 20, 65, 14, BLACK);
        DrawText("- Use Backspace para corrigir o texto", 20, 85, 14, BLACK);
        
        // Caixa de texto de Input
        DrawText("Valor atual: ", 20, 115, 16, BLACK);
        DrawRectangle(120, 110, 80, 25, LIGHTGRAY);
        DrawRectangleLines(120, 110, 80, 25, DARKGRAY);
        DrawText(inputBuffer, 125, 115, 16, RED);

        // Se a árvore estiver vazia, avisa o usuário
        if (root == NULL) {
            DrawText("A arvore esta vazia!", 400, 300, 20, DARKGRAY);
        } else {
            // Desenha a árvore de forma recursiva a partir do topo central
            DrawTree(root, 500, 100, 180, 80);
        }

        EndDrawing();
    }

    // Finalização e liberação de memória
    destroyTree(root);
    CloseWindow();

    return 0;
}