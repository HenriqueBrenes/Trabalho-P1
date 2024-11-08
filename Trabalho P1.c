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

void printList ( struct Node* node ){
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

void insertionSort(struct Node** head) {
    struct Node* ord = NULL;         //iniciar lista ordenada vazia
    struct Node* atual = *head;      //iniciar novo nó a partir da lista original

    while (atual != NULL) { //percorrer até que a lista original esteja vazia 
        struct Node* next = atual->next;

        if (ord == NULL || ord->data >= atual->data) {      //comparar os valores
            atual->next = ord;       //se o ordenado for maior que o atual, ele será o próximo
            ord = atual;
        } else {
            struct Node* temp = ord;        //percorrer a lista ordenada por valor temporário 
            while (temp->next != NULL && temp->next->data < atual->data) {      //encontrar o lugar correto na lista ordenada
                temp = temp->next;
            }
            atual->next = temp->next;
            temp->next = atual;         // inserir no lugar correto
        }
        atual = next;       //avança para o próximo elemento
    }
    *head = ord;        //atualiza o ponteiro da lista original para a lista ordenada
}

struct Node* merge(struct Node* primeira, struct Node* segunda){
    struct Node* ord = NULL;        //gera lista ordenada vazia
    struct Node** atual = &ord;         //marcador para os elemetos

    while (primeira != NULL || segunda != NULL) {       //define loop até o final das duas listas
        
        //se alguma lista tiver mais elementos, completar a ordenada com eles
        if (primeira == NULL) {
            *atual = segunda;
            segunda = segunda->next;  
        } else if (segunda == NULL) {
            *atual = primeira;
            primeira = primeira->next;
            }

        //tamanhos ainda iguais 
        else {
            if (primeira->data < segunda->data) {
                *atual = primeira;
                primeira = primeira->next;
            } else {
                *atual = segunda;
                segunda = segunda->next;
            }
        }
        atual = &((*atual)->next);
    }
    return ord;     //retorna lista ordenada
}

void split(struct Node* head, struct Node** primeira, struct Node** segunda){
    struct Node* metade = head;
    struct Node* final = head->next;
     while (final != NULL && final->next != NULL) {
        final = final->next->next;     //avança 2x mais rápido para chegar ao final
        metade = metade->next;
    }
    *primeira = head;
    *segunda = metade->next;
    metade->next = NULL;
}

void MergeSort(struct Node** head){
    struct Node* ref = *head;
    struct Node* a;
    struct Node* b;

    if ((ref == NULL) || (ref->next == NULL)) {     //caso base
        return;
    }

    split(ref,&a,&b);    //divide em 2

    //recursão para cada parte dividida
    MergeSort(&a);
    MergeSort(&b);

    *head = merge(a,b);     //altera o marcador da lista original para a ordenada
}


//função para concatenar três listas
struct Node* concatena(struct Node* esquerda, struct Node* meio, struct Node* direita) {
    struct Node* head = NULL;
    struct Node* temp = NULL;

    //conecta a lista esquerda ao meio
    if (esquerda) {
        head = esquerda;
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = meio;
    } else {
        head = meio;    //se a lista esquerda estiver vazia, começa com meio
    }

    //conecta o meio à lista direita
    if (meio) {
        temp = meio;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = direita;
    } else if (esquerda) {
        temp = esquerda;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = direita;
    } else {
        head = direita;     
    }

    return head;    //retorna a lista concatenada
}

void QuickSort(struct Node** head) {
    struct Node* ref = *head;

    if (ref == NULL || ref->next == NULL) {     //caso base
        return;
    }

    struct Node* pivo = ref;
    struct Node* esquerda = NULL;
    struct Node* direita = NULL;
    struct Node* atual = ref->next;

    //particiona a lista em duas sublistas
    while (atual != NULL) {
        struct Node* proximo = atual->next;
        if (atual->data < pivo->data) {
            atual->next = esquerda;  //adiciona à esquerda
            esquerda = atual;
        } else {
            atual->next = direita;  //adiciona à direita
            direita = atual;
        }
        atual = proximo;
    }
    QuickSort(&esquerda);
    QuickSort(&direita);

    *head = concatena(esquerda, pivo, direita);
}

int main(){
    struct Node* head = initList();
    int n;
    printf("Quantos elementos a lista terá?\n");
    scanf("%d", &n);
    for (int i=0; i<n; i++){
        int x;
        printf("Qual o %dº elemento?\n",i+1);
        scanf("%d", &x);
        inserir(&head, x);
    }
    printf("A lista é:\n");
    printList(head);

    printf("A lista ordenada é:\n");
    insertionSort(&head);
    printList(head);

    return 0;
}

