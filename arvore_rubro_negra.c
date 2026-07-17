#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <raylib.h>

// --- ESTRUTURA DA ÁRVORE ---
typedef enum { VERMELHO, PRETO } Cor_Do_No;

typedef struct No {
    int chave;
    Cor_Do_No cor;
    struct No *esquerda, *direita, *pai;
} No;

// --- ROTAÇÕES ---
void rotateesquerda(No **raiz, No *x) {
    No *y = x->direita;
    x->direita = y->esquerda;
    
    if (y->esquerda != NULL)
        y->esquerda->pai = x;
        
    y->pai = x->pai;
    
    if (x->pai == NULL)
        *raiz = y;
    else if (x == x->pai->esquerda)
        x->pai->esquerda = y;
    else
        x->pai->direita = y;
        
    y->esquerda = x;
    x->pai = y;
}

void rotatedireita(No **raiz, No *y) {
    No *x = y->esquerda;
    y->esquerda = x->direita;
    
    if (x->direita != NULL)
        x->direita->pai = y;
        
    x->pai = y->pai;
    
    if (y->pai == NULL)
        *raiz = x;
    else if (y == y->pai->esquerda)
        y->pai->esquerda = x;
    else
        y->pai->direita = x;
        
    x->direita = y;
    y->pai = x;
}

// --- BALANCEAMENTO DA INSERÇÃO ---
void correcaoInsercao(No **raiz, No *z) {
    while (z != *raiz && z->pai->cor == VERMELHO) {
        if (z->pai == z->pai->pai->esquerda) {
            No *y = z->pai->pai->direita; 
            
            if (y != NULL && y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->direita) {
                    z = z->pai;
                    rotateesquerda(raiz, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotatedireita(raiz, z->pai->pai);
            }
        } else {
            No *y = z->pai->pai->esquerda;
            
            if (y != NULL && y->cor == VERMELHO) {
                z->pai->cor = PRETO;
                y->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esquerda) {
                    z = z->pai;
                    rotatedireita(raiz, z);
                }
                z->pai->cor = PRETO;
                z->pai->pai->cor = VERMELHO;
                rotateesquerda(raiz, z->pai->pai);
            }
        }
    }
    (*raiz)->cor = PRETO;
}

void insercao(No **raiz, int chave) {
    No *z = (No*)malloc(sizeof(No));
    z->chave = chave;
    z->esquerda = z->direita = z->pai = NULL;
    z->cor = VERMELHO;
    
    No *y = NULL;
    No *x = *raiz;
    

    while (x != NULL) {
        y = x;
        if (z->chave < x->chave)
            x = x->esquerda;
        else
            x = x->direita;
    }
    
    z->pai = y;
    if (y == NULL)
        *raiz = z;
    else if (z->chave < y->chave)
        y->esquerda = z;
    else
        y->direita = z;
        
    correcaoInsercao(raiz, z);
}

void inorder(No *raiz) {
    if (raiz == NULL) return;
    inorder(raiz->esquerda);
    printf("%d(%s) ", raiz->chave, raiz->cor == VERMELHO ? "V" : "P");
    inorder(raiz->direita);
}

No *buscarNo = NULL;

No* buscar(No *raiz, int key) {
    if (raiz == NULL || raiz->chave == key)
        return raiz;
    
    if (key < raiz->chave)
        return buscar(raiz->esquerda, key);
        
    return buscar(raiz->direita, key);
}

void destruirArvore(No *raiz) {
    if (raiz == NULL) return;
    
    destruirArvore(raiz->esquerda);
    destruirArvore(raiz->direita);
    free(raiz);
}

// --- BALANCEAMENTO DA REMOÇÃO ---
void correcaoRemocao(No **raiz, No *x, No *xpai) {
    while (x != *raiz && (x == NULL || x->cor == PRETO)) {
        if (x == xpai->esquerda) {
            No *w = xpai->direita;
            
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                xpai->cor = VERMELHO;
                rotateesquerda(raiz, xpai);
                w = xpai->direita;
            }
            
            if ((w->esquerda == NULL || w->esquerda->cor == PRETO) &&
                (w->direita == NULL || w->direita->cor == PRETO)) {
                w->cor = VERMELHO;
                x = xpai;
                xpai = x->pai;
            } else {
                if (w->direita == NULL || w->direita->cor == PRETO) {
                    if (w->esquerda != NULL) w->esquerda->cor = PRETO;
                    w->cor = VERMELHO;
                    rotatedireita(raiz, w);
                    w = xpai->direita;
                }
                w->cor = xpai->cor;
                xpai->cor = PRETO;
                if (w->direita != NULL) w->direita->cor = PRETO;
                rotateesquerda(raiz, xpai);
                x = *raiz; // Termina o loop
                break;
            }
        } else {
            No *w = xpai->esquerda;
            
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                xpai->cor = VERMELHO;
                rotatedireita(raiz, xpai);
                w = xpai->esquerda;
            }
            
            if ((w->esquerda == NULL || w->esquerda->cor == PRETO) &&
                (w->direita == NULL || w->direita->cor == PRETO)) {
                w->cor = VERMELHO;
                x = xpai;
                xpai = x->pai;
            } else {
                if (w->esquerda == NULL || w->esquerda->cor == PRETO) {
                    if (w->direita != NULL) w->direita->cor = PRETO;
                    w->cor = VERMELHO;
                    rotateesquerda(raiz, w);
                    w = xpai->esquerda;
                }
                w->cor = xpai->cor;
                xpai->cor = PRETO;
                if (w->esquerda != NULL) w->esquerda->cor = PRETO;
                rotatedireita(raiz, xpai);
                x = *raiz;
                break;
            }
        }
    }
    if (x != NULL) x->cor = PRETO;
}

No* minimo(No *No) {
    while (No->esquerda != NULL)
        No = No->esquerda;
    return No;
}

// --- REMOÇÃO ---
void removerNo(No **raiz, int key) {
    No *z = buscar(*raiz, key);
    if (z == NULL) {
        printf("Elemento %d nao encontrado.\n", key);
        return;
    }

    // Se o nó que estamos deletando for o destacado atualmente, limpamos o destaque
    if (z == buscarNo) {
        buscarNo = NULL;
    }

    No *y = z;
    Cor_Do_No y_original_cor = y->cor; 
    No *x;
    No *xpai;

    if (z->esquerda == NULL) {
        x = z->direita;
        xpai = z->pai;
        if (z->pai == NULL) {
            *raiz = x;
        } else if (z == z->pai->esquerda) {
            z->pai->esquerda = x;
        } else {
            z->pai->direita = x;
        }
        if (x != NULL) x->pai = z->pai;
    } 
    else if (z->direita == NULL) {
        x = z->esquerda;
        xpai = z->pai;
        if (z->pai == NULL) {
            *raiz = x;
        } else if (z == z->pai->esquerda) {
            z->pai->esquerda = x;
        } else {
            z->pai->direita = x;
        }
        if (x != NULL) x->pai = z->pai;
    } 
    else {
        y = minimo(z->direita);
        y_original_cor = y->cor;
        x = y->direita;
        
        if (y->pai == z) {
            xpai = y;
        } else {
            xpai = y->pai;
            if (x != NULL) x->pai = y->pai;
            y->pai->esquerda = x;
            y->direita = z->direita;
            y->direita->pai = y;
        }
        
        if (z->pai == NULL) {
            *raiz = y;
        } else if (z == z->pai->esquerda) {
            z->pai->esquerda = y;
        } else {
            z->pai->direita = y;
        }
        y->pai = z->pai;
        y->esquerda = z->esquerda;
        y->esquerda->pai = y;
        y->cor = z->cor;
    }

    free(z);

    if (y_original_cor == PRETO) {
        correcaoRemocao(raiz, x, xpai);
    }
}

// --- FUNÇÕES DA INTERFACE GRÁFICA ---

// Função recursiva para desenhar as conexões (linhas) e depois os nós (círculos)
void DrawTree(No *raiz, int x, int y, int hSpacing, int vSpacing) {
    if (raiz == NULL) return;

    // 1. Desenha as linhas primeiro para que fiquem por baixo dos círculos
    if (raiz->esquerda != NULL) {
        DrawLine(x, y, x - hSpacing, y + vSpacing, GRAY);
        DrawTree(raiz->esquerda, x - hSpacing, y + vSpacing, hSpacing / 1.8, vSpacing);
    }
    if (raiz->direita != NULL) {
        DrawLine(x, y, x + hSpacing, y + vSpacing, GRAY);
        DrawTree(raiz->direita, x + hSpacing, y + vSpacing, hSpacing / 1.8, vSpacing);
    }

    // 2. Determina a cor do nó (Mapeando Cor_Do_No para cor da Raylib)
    Color cor = (raiz->cor == VERMELHO) ? RED : BLACK;
    Color border = (raiz->cor == VERMELHO) ? MAROON : DARKGRAY;

    // --- DESTAQUE DA BUSCA ---
    // Se este nó for o procurado, desenhamos uma auréola amarela ao redor dele
    if (raiz == buscarNo) {
        DrawCircle(x, y, 28, YELLOW); // Círculo de destaque maior por trás
        border = GOLD;               // Altera a cor da borda do próprio nó para dourado
    }

    // 3. Desenha o círculo do nó e a borda
    DrawCircle(x, y, 22, border);
    DrawCircle(x, y, 20, cor);

    // 4. Desenha o valor do nó centralizado
    char buffer[12];
    sprintf(buffer, "%d", raiz->chave);
    int textWidth = MeasureText(buffer, 16);
    DrawText(buffer, x - textWidth / 2, y - 8, 16, WHITE);
}

int main() {
    // Inicialização da janela gráfica (Largura: 1600, Altura: 900)
    InitWindow(1600, 900, "Demonstrador de Arvore Rubro-Negra");
    SetTargetFPS(60);

    No *raiz = NULL;
    char inputBuffer[16] = "\0";
    int letterCount = 0;

    // Variável para exibir mensagem de status da busca (ex: "Nó encontrado!" ou "Não encontrado")
    char buscarStatus[32] = "\0"; 
    Color statusColor = GRAY;


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
            insercao(&raiz, value);
            inputBuffer[0] = '\0';
            letterCount = 0;
        }

        // Confirmar remoção (Delete)
        if (IsKeyPressed(KEY_DELETE) && letterCount > 0) {
            int value = atoi(inputBuffer);
            removerNo(&raiz, value);
            inputBuffer[0] = '\0';
            letterCount = 0;
        }

        // TECLA F: Buscar (Find)
        if (IsKeyPressed(KEY_F) && letterCount > 0) {
            int value = atoi(inputBuffer);
            buscarNo = buscar(raiz, value);
            
            if (buscarNo != NULL) {
                sprintf(buscarStatus, "Nó encontrado!");
                statusColor = GREEN;
            } else {
                sprintf(buscarStatus, "Nó não encontrado!");
                statusColor = RED;
            }
            
            inputBuffer[0] = '\0';
            letterCount = 0;
        }

        // --- 2. DESENHO NA TELA (RULER & RENDER) ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Painel de instruções superior esquerdo
        DrawRectangle(10, 10, 500, 200, Fade(SKYBLUE, 0.3f));
        DrawRectangleLines(10, 10, 500, 200, BLUE);
        DrawText("CONTROLES:", 20, 20, 30, DARKBLUE);
        DrawText("Digite um numero e aperte ENTER para Inserir", 20, 60, 20, BLACK);
        DrawText("Digite um numero e aperte DEL para Remover", 20, 90, 20, BLACK);
        DrawText("Digite um numero e aperte F para Buscar", 20, 120, 20, BLACK);
        DrawText("Use Backspace para corrigir o texto", 20, 150, 20, BLACK);
        
        // Caixa de texto de Input
        DrawText("Valor atual: ", 20, 180, 20, BLACK);
        DrawRectangle(150, 180, 130, 25, LIGHTGRAY);
        DrawRectangleLines(150, 180, 130, 25, DARKGRAY);
        DrawText(inputBuffer, 160, 184, 20, RED);

        // Status da Busca
        if (buscarStatus[0] != '\0') {
            DrawText(buscarStatus, 290, 184, 19, statusColor);
        }

        // Se a árvore estiver vazia, avisa o usuário
        if (raiz == NULL) {
            DrawText("A arvore esta vazia!", 700, 230, 20, DARKGRAY);
        } else {
            // Desenha a árvore de forma recursiva a partir do topo central
            DrawTree(raiz, 700, 250, 300, 80);
        }

        EndDrawing();
    }

    // Finalização e liberação de memória
    destruirArvore(raiz);
    CloseWindow();

    return 0;
}