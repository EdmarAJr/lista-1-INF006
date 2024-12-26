/**
 *  Considere uma lista duplamente ligada nao-circular onde cada elemento possui uma chave inteira.
 *  Cada elemento dessa lista pode ter associado a ele uma outra lista simplesmente ligada circular
 *  tambem de valores reais que diferem deste por no maximo 0,99; Todas as listas devem estar ordenadas.
                
 *                        L1Q3.in
  |----------------------------------------------------------|
  |   LE 10 9 6 4 LI 4.11 10.1 6.88 4.99 9.3 9.2 6.15 4.33   |
  |----------------------------------------------------------|
 *                        L1Q3.out
  |--------------------------------------------------------------|
  |  [4(4.11 >4.33 >4.99) >6(6.15 >6.88) >9(9.2 >9.3) >10(10.1)  | 
  |--------------------------------------------------------------| 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definições de tipos e variáveis de pré-processamento */
#define LINE_SIZE 1000
typedef struct simpleNode {
	float value;
	struct simpleNode *next;
} S_NODE;

typedef struct circularLinkedList {
	S_NODE *head;
	S_NODE *tail;
} C_List;

typedef struct doublyNode {
    int value;
    struct doublyNode *next;
    struct doublyNode *prev;
    C_List *key;
    float range;
} D_NODE;

typedef struct doublyLinkedList{
    D_NODE *head;
    D_NODE *tail;
} D_List;

/*protótipos de funções*/
int start();
D_NODE *create_Dnode(int key);
S_NODE *create_Snode(int value);
void init_Clist(C_List * CL);
void init_Dlist(D_List * DL);
D_NODE *search_Dlist(D_List *list, int value);
void insert_Dlist(D_List *list, D_NODE *current);
void insert_Clist(C_List *CL, float newValue);

int main(){
    start();
    return 0;
}

int start(){
    FILE *input = fopen("L1Q3.in", "r");
    FILE *output = fopen("L1Q3.out", "w");
    
    if (!input || !output) {
        printf("Error opening files.\n");
        return EXIT_FAILURE;
    }
    /*cria uma nova linha*/	
	char * line = malloc(LINE_SIZE * sizeof(char));
	/*separador dos itens da linha*/
	char split[] = " ";
	/*ponteiro para salvar os dados separados da função strtok_r (thread-safe)*/
	char *outer;

    while(fgets(line, LINE_SIZE, input) != NULL){
        D_List *DL = malloc(sizeof(D_List));
        init_Dlist(DL);
        char *token = strtok_r(line, split, &outer);
         while(token != NULL){
             if(strcmp(token, "LE") == 0){
                token = strtok_r(NULL, split, &outer);
                //printf("token: %s\n", token);
                D_NODE *current = create_Dnode(atoi(token));
                insert_Dlist(DL, current);
            } else if(strcmp(token, "LI") == 0){
                token = strtok_r(NULL, split, &outer);
                D_NODE *current = search_Dlist(DL, atoi(token));
                if(current != NULL){
                    C_List *CL = malloc(sizeof(C_List));
                    init_Clist(CL);
                    token = strtok_r(NULL, split, &outer);
                    while(token != NULL){
                        insert_Clist(CL, atof(token));
                        token = strtok_r(NULL, split, &outer);
                    }
                    current->key = CL;
                }
            }
            token = strtok_r(NULL, split, &outer);
        }
        // if (DL == NULL || DL->head == NULL) {
        //     fprintf(stderr, "Erro: DL ou DL->head é nulo.\n");
        //     return EXIT_FAILURE;
        // }
        // D_NODE *current = DL->head;
        // while(current != NULL){
        //     fprintf(output, "[%d(", current->value);
        //     if (current->key == NULL || current->key->head == NULL) {
        //         fprintf(stderr, "Error: current->key or current->key->head is NULL.\n");
        //         return EXIT_FAILURE;
        //     }
        //     S_NODE *currentCL = current->key->head;
        //     while(currentCL != NULL){
        //         fprintf(output, "%.2f", currentCL->value);
        //         if(currentCL->next != NULL){
        //             fprintf(output, " >");
        //         }
        //         currentCL = currentCL->next;
        //     }
        //     fprintf(output, ")");
        //     if(current->next != NULL){
        //         fprintf(output, " >");
        //     }
        //     current = current->next;
        // }
        // fprintf(output, "\n");
    }
    free(line);
    EXIT_SUCCESS;
}

D_NODE *create_Dnode(int value){
    printf("create duplo value: %d\n", value);
    D_NODE *node = malloc(sizeof(D_NODE));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

S_NODE *create_Snode(int value){
    printf("create simple value: %d\n", value);
    S_NODE *node = malloc(sizeof(S_NODE));
    node->value = value;
    node->next = NULL;
    return node;
}

void init_Clist(C_List * CL) {
	CL->head = NULL;
	CL->tail = NULL;
}

void init_Dlist(D_List * DL) {
	DL->head = NULL;
	DL->tail = NULL;
}

// D_NODE *search_Dlist(D_List *list, int value){
//     D_NODE *current = list->head;
//     while (current != NULL && current->value != value) {
//         current = current->next;
//     }
//     return current;
// }

// void insert_Dlist(D_List *list, D_NODE *current){
//     current->next = list->head;
//     if (list->head != NULL){
//         list->head->prev = current;
//     }
//     list->head = current;
//     current->prev = NULL;
// }

D_NODE *search_Dlist(D_List *list, int value) {
    D_NODE *current = list->head;
    while (current != NULL && current->value != value) {
        current = current->next;
    }
    return current;
}

void insert_Dlist(D_List *list, D_NODE *newNode) {
    // Se a lista estiver vazia, inicializa a cabeça e a cauda
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        newNode->next = NULL;
        newNode->prev = NULL;
    } else {
        // Insere o novo nó no início da lista
        newNode->next = list->head;
        newNode->prev = NULL;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

S_NODE *search_Clist(C_List *list, float value){
    /*Lista vazia*/ 
    if (list->head == NULL) { 
        return NULL;
    }
    /*cria o no-atual para receber o valor da cabeca da lista*/
    S_NODE *current = list->head;
    /*busca na lista um primeiro valor maior que o valor informado na busca*/
    // while (current != list->tail && current->value < value) {
    //     current = current->next;
    // }

    do {
        if (current->value == value) {
            return current;
        }
        if (current->value > value) {
            break;
        }
        current = current->next;
    } while (current != list->head);

    // Retorna NULL se o valor não for encontrado ou se o valor no nó for maior que o procurado
    return NULL;
}

void insert_Clist(C_List *CL, float newValue) {
    /*inicia um novo no*/
    S_NODE *newNode = malloc(sizeof(S_NODE));
    newNode->value = newValue;

    /* no atual recebe o início da lista*/
    S_NODE *current = CL->head;

    /* se a lista estiver vazia, insere o novo valor na primeira posição atualizando a cabeça, a cauda e o próximo item da lista circular */
    if (current == NULL) {
        CL->head = newNode;  /* atualiza a cabeça que aponta para novo-no se for o primeiro item */
        CL->tail = newNode;  /* atualiza a cauda que aponta para novo-no se for o primeiro item */
        newNode->next = newNode;  /* novo no proximo recebe o novo-no se for o primeiro item */
    } else {/*caso ja existam nos na lista circular, busca pelo valor maior que o novo-no para ser inserido em ordem*/
        if (newValue < current->value) {
            /* se o novo-no for menor que o atual, insere antes */
            newNode->next = current;  /* novo nó próximo recebe o atual */
            CL->head = newNode;  /* atualiza a cabeça que aponta para novo nó */
            CL->tail->next = newNode;  /* atualiza a cauda que aponta para novo nó */
        } else {/* se o novo nó for maior que o atual, busca um valor maior e insere antes */
            S_NODE *search = search_Clist(CL, newValue);  /* chama a função search_Clist */
            if (search == CL->head) { /* Se o no encontrado for a cabeça, o novo-no será inserido antes da cabeça */
                newNode->next = CL->head;
                CL->head = newNode;
                CL->tail->next = newNode;
            } else { /*insere o novo no antes do no encontrado */
                S_NODE *prev = CL->head;
                while (prev->next != search) {
                    prev = prev->next;
                }
                prev->next = newNode;
                newNode->next = search;
                if (search == CL->tail) {
                    /*atualiza a cauda se o no encontrado for a cauda*/
                    CL->tail = newNode;
                }
            }
        }
    }
}

// void insertCL(C_List * CL, float newValue) {
//     /*incia um novo no*/
// 	S_NODE *newNode = malloc(sizeof(S_NODE));
// 	newNode->value = newValue;
//     /*no atual recebe o inicio da lista*/
// 	S_NODE *current = CL->head;
//     /*se a lista estiver vazia insere o novo valor na primeira posicao atualizando a cabeca , a cauda e o proximo item da lista circular*/
// 	if(current == NULL) {
// 		CL->head = newNode; /*atualiza a cabeca que aponta para novo-no se for o primeiro item*/
// 		CL->tail = newNode; /*atualiza a cauda que aponta para novo-no se for o primeiro item*/
// 		newNode->next = newNode; /*novo-no-proximo recebe o novo-no se for o primeiro item*/
// 	} else { /*caso ja existam nos na lista circular, busca pelo valor maior que o novo-no para ser inserido em ordem*/
//         if(newValue < current->value) { /*se o novo-no for menor que atual, insere antes*/
// 			newNode->next = current;/*novo-no-proximo recebe o atual */
// 			CL->head = newNode; /*atualiza a cabeca que aponta para novo-no*/
// 			CL->tail->next = newNode; /*atualiza a cauda que aponta para novo-no*/
// 		} else {/*se o novo-no for maior que atual, busca um valor maior e insere antes*/
//             S_NODE *search = malloc(sizeof(S_NODE)); /*cria um novo no bara armazenar a busca*/
//             search = search_Clist(CL, current->value); /*chama a funcao search_Clist que retorna current->next*/
// 		    newNode->next = search;/*atualiza o valor de novo-no-proximo*/
// 			search = newNode;/*atualiza o valor de de atual-proximo para novo-no*/
// 			if (search == CL->tail) { /*atualiza o valor da causa se atual-proximo for igual a cauda*/
// 				CL->tail = newNode;
// 			}
// 		}
// 	}
// }
