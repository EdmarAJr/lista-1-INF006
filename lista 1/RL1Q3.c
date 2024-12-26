#include <stdio.h>
#include <stdlib.h>
# include <string.h>

/* Definições de tipos e variáveis de pré-processamento */

typedef struct node{
    int value;
    struct node *next;
    struct node *prev;
} Node;

typedef struct list{
    Node *head;
} List;


/*protótipos de funções*/
int start();
Node *create_node(int key);
Node *search_list(List *list, int value);
void insert_list(List *list, Node *current);

int main(){
    start();
    return 0;
}

int start(){
    printf("Hello World");
    EXIT_SUCCESS;
}

Node *create_node(int value){
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

Node *search_list(List *list, int value){
    Node *current = list->head;
    while (current != NULL && current->value != value) {
        current = current->next;
    }
    return current;
}

void insert_list(List *list, Node *current){
    current->next = list->head;
    if (list->head != NULL){
        list->head->prev = current;
    }
    list->head = current;
    current->prev = NULL;
}