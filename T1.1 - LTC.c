#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct Node* initList(){
    return NULL;
}

void inserir(struct Node** head, int new_data){
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    if (*head == NULL) {
        *head = new_node;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void printList (struct Node* node ){
    while ( node != NULL ) {
        printf ("%d -> ", node->data ) ;
        node = node->next ;
    }
    printf (" NULL \n") ;
}

void bubbleSort (struct Node* head){ 
    struct Node *atual, *final=NULL;
    atual = head;
    int trocado;
    do {
        trocado = 0;        //se não houver troca, está ordenado
        atual = head;       //começa pelo primeiro

        while (atual->next != final) {      //continua até chegar ao fim
            if (atual->data > atual->next->data) {       //troca se necessário
                int temp = atual->data;
                atual->data = atual->next->data;
                atual->next->data = temp;
                trocado = 1;
            }
            atual = atual->next;
        }
        final = atual; 
    } while (trocado);      //repete até que não hajam trocas
}

void setlist(struct Node** head) {      //função para remover somente as cópias
    struct Node* atual = *head;
    
    //percorre a lista até o final
    while (atual != NULL && atual->next != NULL) {
        struct Node* ref = atual;    //ponteiro para o nó de comparação

        //percorre todos os nós para encontrar duplicados
        while (ref->next != NULL) {
            if (atual->data == ref->next->data) {
                //remover nó duplicado
                ref->next = ref->next->next;
            } else {
                ref = ref->next;
            }
        }
        atual = atual->next;
    }
}

void copias(struct Node** head) {       //função que remove números que possuam cópias
    struct Node* atual = *head;
    struct Node* prev = NULL;

    while (atual != NULL) {
        int duplicata = 0;

        // Verifica se há um valor duplicado
        while (atual->next != NULL && atual->data == atual->next->data) {
            duplicata = 1;
            struct Node* temp = atual->next;
            atual->next = atual->next->next;
        }

        // Se encontramos uma duplicata, removemos o valor atual também
        if (duplicata) {
            if (prev == NULL) {
                *head = atual->next;
                atual = *head;
            } else {
                prev->next = atual->next;
                atual = prev->next;
            }
        } else {
            // Avança o ponteiro prev apenas se não houve duplicatas
            prev = atual;
            atual = atual->next;
        }
    }
}


int main() {
    // input do tipo head=[1,2,3]
    int dados[10];
    char input[20];
    int i = 0, n = 0;
    struct Node* head = initList();

    scanf("%s", input);
    while (input[i] != '\0') {
        // Verifica se o caractere é um dígito entre '0' e '9'
        if (input[i] >= '0' && input[i] <= '9') {
            // Converte o caractere para um número inteiro e armazena em dados
            dados[n] = input[i] - '0';
            inserir(&head, dados[n]);
            n++;
        }
        i++;
    }   

    printList(head);
    bubbleSort(head);
    copias(&head);
    printList(head);

    return 0;
}
