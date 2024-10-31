#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variaveis globais

int ids = 0;

// Defini��o do n� da lista
struct Node {
	int id;
    int data;
    char funcionario[50]; // Defina um tamanho fixo para a string
    struct Node* next;
};

// Fun��o para criar um novo n�
struct Node* criarNo(int data, const char *str) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = ids;
    newNode->data = data;
    strcpy(newNode->funcionario, str); // Copia a string para o n�
    newNode->next = NULL;
    ids++;
    return newNode;
}

// Fun��o para imprimir a lista
void printLista(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("| %i, %d, %s | --> ", current->id, current->data, current->funcionario);
        current = current->next;
    }
    printf("NULL\n");
}

// Fun��o para adicionar um n� no in�cio da lista
void inserirElemento(struct Node** head_ref, int new_data, const char *new_str) {
    struct Node* new_node = criarNo(new_data, new_str);
    new_node->next = *head_ref;
    *head_ref = new_node;
}

void inserirElementoID(struct Node* prev_node, int new_data, const char *new_str) {
    if (prev_node == NULL) {
        printf("O n� anterior n�o pode ser NULL.\n");
        return;
    }

    struct Node* new_node = criarNo(new_data, new_str);
    new_node->next = prev_node->next; // O novo n� aponta para o pr�ximo n�
    prev_node->next = new_node; // O n� anterior aponta para o novo n�
}

int main() {
    struct Node* head = NULL; // Inicializa a lista vazia

    // Adiciona elementos � lista
    inserirElemento(&head, 10, "Pedro");
    inserirElemento(&head, 20, "Maria");
    inserirElemento(&head, 30, "Victor");

    // Imprime a lista
    printLista(head);

    // Libera a mem�ria (n�o implementado para simplicidade)

    return 0;
}
