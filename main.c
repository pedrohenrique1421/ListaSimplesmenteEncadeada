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

void listarElemento(struct Node** head, int id){
	struct Node* current = getNoById(*head, id);
    printf("\n\n- --- -\n");
	printf("--> | id: %i, tipo: %c, marca: %s, preco = %.2f | -->\n", current->id, current->tipo, current->marca, current->preco);
	current = current->next;
    printf("- --- -");
}

// Fun��o para adicionar um n� no in�cio da lista
void inserirElemento(struct Node** head_ref, const char *nova_marca, const char tipo, float preco) {
    struct Node* new_node = criarNo(ids, nova_marca, tipo, preco);
    ids++;
    new_node->next = *head_ref;
    *head_ref = new_node;
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

void atualizarNo(struct Node** head, int id, const char *marca, char tipo, float preco){
	struct Node* no = getNoById(*head, id);
	if(no == NULL){
		printf("\n\nno nao encontrado para a atualizacao");
		return;
	}
	no->tipo = tipo;
    no->preco = preco;
    strcpy(no->marca, marca);
}

int getTamanho(struct Node* head){
	struct Node* current = head;
	int tamanho = 0;
    while (current != NULL) {
        tamanho++;
        current = current->next;
    }
    
    printf("\n\ntamanho = %i\n", tamanho);
    return tamanho;
}

struct Node* excluirLista(struct Node* head){
	struct Node* current = head;
	struct Node* back;
	while (current != NULL) {
        back = current;
		current = current->next;
  		free(back);
    }
    return NULL;
}

void salvarListaEmArquivo(struct Node* head, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w"); // Abre o arquivo para escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return;
    }

    struct Node* current = head;
    while (current != NULL) {
        // Grava cada n� no arquivo no formato desejado
        fprintf(arquivo, "%d;%c;%s;%.2f\n", current->id, current->tipo, current->marca, current->preco);
        current = current->next;
    }

    fclose(arquivo); // Fecha o arquivo
    printf("Lista salva no arquivo %s com sucesso!\n", nome_arquivo);
}

void carregarListaDeArquivo(struct Node** head, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r"); // Abre o arquivo para leitura
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return;
    }

    int id;
    char tipo;
    char marca[50];
    float preco;

    // L� cada linha do arquivo e insere os dados na lista
    while (fscanf(arquivo, "%d;%c;%49[^;];%f\n", &id, &tipo, marca, &preco) == 4) {
        struct Node* new_node = criarNo(id, marca, tipo, preco);
        new_node->next = *head; // Insere no in�cio
        *head = new_node; // Atualiza o head
    }

    fclose(arquivo); // Fecha o arquivo
    printf("Lista carregada do arquivo %s com sucesso!\n", nome_arquivo);
}

void salvarListaEmArquivoInvertido(struct Node* head, const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "w"); // Abre o arquivo para escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return;
    }

    // Cria um vetor para armazenar os n�s
    struct Node* nos[100]; // Supondo que a lista n�o ter� mais que 100 elementos
    int count = 0;

    struct Node* current = head;
    while (current != NULL) {
        nos[count++] = current; // Armazena o ponteiro do n�
        current = current->next;
    }

    // Grava os n�s na ordem inversa
    int i;
    for (i = count - 1; i >= 0; i--) {
        fprintf(arquivo, "%d;%c;%s;%.2f\n", nos[i]->id, nos[i]->tipo, nos[i]->marca, nos[i]->preco);
    }

    fclose(arquivo); // Fecha o arquivo
    printf("Lista salva no arquivo %s em ordem invertida com sucesso!\n", nome_arquivo);
}

int main() {
    struct Node* head = NULL; // Inicializa a lista vazia

    //Adiciona elementos � lista
    // inserirElemento(&head, "caloi", 'E', 1299.90);// E = ergometrica, S = Spining
    // inserirElemento(&head, "zummi", 'S', 2499.90);
    // inserirElemento(&head, "mormaii", 'E', 5199.90);
    // inserirElemento(&head, "ogs", 'E', 1299.90);
    // inserirElemento(&head, "bike soul", 'S', 2499.90);
    // inserirElemento(&head, "bike and cia s.a.", 'E', 5199.90);
// 
    //Imprime a lista
    // listarElementos(head);
    // 
    // inserirElementoID(&head, 1, "tsw", 'S', 999.99);
    // 
    // listarElementos(head);
    // 
    // removerNo(&head, 0);
    // 
    // listarElementos(head);
    // 
    // atualizarNo(&head, 3, "audax", 'E', 1799.90);
    // 
    // listarElementos(head);
    // 
    // atualizarNo(&head, 0, "abcd", 'E', 1799.90);
    // 
    // listarElementos(head);
    // 
    // listarElemento(&head, 5);
    // 
    // getTamanho(head);
    // 
    // salvarListaEmArquivo(head, "listaDebicicletas.txt");

    carregarListaDeArquivo(&head, "listaDebicicletas.txt");
    
    // salvarListaEmArquivoInvertido(head, "listaDebicicletas.txt");
    
    listarElementos(head);

    return 1;
}
