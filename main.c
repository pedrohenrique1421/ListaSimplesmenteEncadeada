#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variaveis globais

int ids = 0;

// Defini��o do n� da lista
struct Node {
	int id;
    char marca[50]; // Defina um tamanho fixo para a string
    char tipo;
	float preco;
    struct Node* next;
};

// Fun��o para criar um novo n�
struct Node* criarNo(int id, const char *marca, char tipo, float preco) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = id;
    newNode->tipo = tipo;
    newNode->preco = preco;
    strcpy(newNode->marca, marca);
    newNode->next = NULL;
    return newNode;
}

// Fun��o para imprimir a lista
void listarElementos(struct Node* head) {
    struct Node* current = head;
    printf("\n----------\n- HEAD -\n");
    while (current != NULL) {
        printf("--> | id: %i, tipo: %c, marca: %s, preco = %.2f | -->\n", current->id, current->tipo, current->marca, current->preco);
        current = current->next;
    }
    printf("- TAIL -");
}

// Fun��o para adicionar um n� no in�cio da lista
void inserirElemento(struct Node** head_ref, const char *nova_marca, const char tipo, float preco) {
    struct Node* new_node = criarNo(ids, nova_marca, tipo, preco);
    ids++;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

struct Node* getNoById(struct Node** head, int id) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->id == id) {
            return current; // Retorna o n� se o ID for encontrado
        }
        current = current->next; // Avan�a para o pr�ximo n�
    }
    return NULL; // Retorna NULL se o n� n�o for encontrado
}

void inserirElementoID(struct Node** head_ref, int id, const char *nova_marca, const char tipo, float preco) {
	struct Node* prev_node = getNoById(*head_ref, id);
	if (prev_node == NULL) {
        printf("O n� anterior n�o pode ser NULL.\n");
        return;
    }
    struct Node* new_node = criarNo(id, nova_marca, tipo, preco);
    new_node->next = prev_node->next; // O novo n� aponta para o pr�ximo n�
    prev_node->next = new_node; // O n� anterior aponta para o novo n�
    
    // reformando os ids dos outros elementos
    struct Node* current = *head_ref;
    int new_id;
    while (current->id != id) {
    	new_id = current->id + 1;
        current->id = new_id;
        current = current->next; // Avan�a para o pr�ximo n�
    }
    new_id = current->id + 1;
	current->id = new_id;
	ids++;
}

void removerNo(struct Node** head_ref, int position) {
    struct Node* temp = *head_ref;

    // Encontra o n� anterior ao n� a ser removido
    int i, real_position = (ids -1) - position;
    for (i = 0; temp != NULL && i < real_position - 1; i++) {
        temp = temp->next;
    }

    // Se a posi��o � maior que o n�mero de n�s
    if (temp == NULL || temp->next == NULL) {
        printf("Posi��o %d n�o � v�lida.\n", position);
        return;
    }

    // N� temp->next � o n� a ser removido
    struct Node* next = temp->next->next; // Armazena o pr�ximo n�
    free(temp->next); // Libera o n� a ser removido
    temp->next = next; // Ajusta o ponteiro para ignorar o n� removido
}

int main() {
    struct Node* head = NULL; // Inicializa a lista vazia

    // Adiciona elementos � lista
    inserirElemento(&head, "caloi", 'E', 1299.90);// E = ergometrica, S = Spining
    inserirElemento(&head, "zummi", 'S', 2499.90);
    inserirElemento(&head, "mormaii", 'E', 5199.90);
    inserirElemento(&head, "ogs", 'E', 1299.90);// E = ergometrica, S = Spining
    inserirElemento(&head, "bike soul", 'S', 2499.90);
    inserirElemento(&head, "bike and cia s.a.", 'E', 5199.90);

    // Imprime a lista
    listarElementos(head);
    
    inserirElementoID(&head, 1, "tsw", 'S', 999.99);
    
    listarElementos(head);
    
    removerNo(&head, 0);
    
    listarElementos(head);

    // Libera a mem�ria (n�o implementado para simplicidade)

    return 1;
}
