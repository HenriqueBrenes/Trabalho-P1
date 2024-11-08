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

void frequente(struct Node* head) {
    if (head == NULL) {
        printf("Não há\n");
        return;
    }

    int freq = head->data;
    int maxcount = 1;
    int prev = head->data;
    int count = 1;
    int countfreq = 1; //contador para verificar quantos números têm a maior frequência

    struct Node* atual = head->next;

    while (atual != NULL) {
        if (atual->data == prev) {
            count++;
        } else {
            if (count > maxcount) {
                maxcount = count;
                freq = prev;
                countfreq = 1;  //novo número com maior frequência
            } else if (count == maxcount) {
                countfreq++;  //outro número com a mesma frequência máxima
            }
            prev = atual->data;
            count = 1;
        }
        atual = atual->next;
    }

    //ultima verificação para o último elemento
    if (count > maxcount) {
        freq = prev;
        countfreq = 1;
    } else if (count == maxcount) {
        countfreq++;
    }

    if (countfreq > 1) {
        printf("Não há\n");
    } else {
        printf("O número que mais aparece é: %d\n", freq);
    }
}

int main() {
    // input do tipo head=[1,2,3]
    int dados[50];
    char input[50];
    int i = 0, n = 0;
    struct Node* head = initList();

    scanf("%s", input);
    while (input[i] != '\0') {
        //verifica se o caractere é um dígito entre '0' e '9'
        if (input[i] >= '0' && input[i] <= '9') {
            //converte o caractere para um número inteiro e armazena em dados
            dados[n] = input[i] - '0';
            inserir(&head, dados[n]);
            n++;
        }
        i++;
    }

    bubbleSort(head);
    frequente(head);
    return 0;
}
