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

/* Definicoes de tipos e variaveis de pre-processamento */
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
} D_NODE;

typedef struct doublyLinkedList {
    D_NODE *head;
    D_NODE *tail;
} D_List;

/* protótipos de funcoes */
int start();
D_NODE *create_Dnode(int key);
S_NODE *create_Snode(float value);
void init_Clist(C_List *CL);
void init_Dlist(D_List *DL);
D_NODE *search_Dlist(D_List *DL, int value);
void insert_Dlist(D_List *DL, D_NODE *newNode);
void insert_Clist(C_List *CL, float newValue);
void print_Dlist(D_List *DL, FILE *output);

int main() {
    start();
    return 0;
}

int start() {
    FILE *input = fopen("L1Q3.in", "r");
    FILE *output = fopen("L1Q3.out", "w");

    if (!input || !output) {
        printf("Error opening files.\n");
        return EXIT_FAILURE;
    }

    /* cria uma nova linha */
    char *line = malloc(LINE_SIZE * sizeof(char));
    /* separador dos itens da linha */
    char split[] = " ";
    /* ponteiro para salvar os dados separados da funcao strtok_r (thread-safe) */
    char *outer;
    /*linha atual*/
    while (fgets(line, LINE_SIZE, input) != NULL) {
        D_List *DL = malloc(sizeof(D_List));
        init_Dlist(DL);
        char *token = strtok_r(line, split, &outer);
        /*cada item da linha atual*/
        while (token != NULL) {
            if (strcmp(token, "LE") == 0) {
                /*retira o LE da linha atual*/
                token = strtok_r(NULL, split, &outer);
                /*percorre cada item da linha atual sem LE ate chegar ao LI*/
                while (token != NULL && strcmp(token, "LI") != 0) {
                    /*cria um novo no duplo convertendo o token para int*/
                    D_NODE *current = create_Dnode(atoi(token));
                    /*insere o novo no na lista dupla*/
                    insert_Dlist(DL, current);
                    /*define o item atual como nulo e segue para o proximo item da linha*/
                    token = strtok_r(NULL, split, &outer);
                }
            } else {
                /*retira o LI da linha atual*/
                //token = strtok_r(NULL, split, &outer);
                /*percorre cada item da linha atual sem LI ate chegar ao final*/
                while (token != NULL) {
                    /*converte o token atual para float*/
                    float value = atof(token);
                    /*converte o token para int para separar a parte inteira*/
                    int key = (int)value;
                    /*procura o no duplo com o valor igual a key para depois inserir a lista circular*/
                    D_NODE *current = search_Dlist(DL, key);
                   /*se o no encontrado nao for nulo segue para a etapa seguinte*/
                    if (current != NULL) {
                        /*verifica se existe  lista circular (key) em em current (no duplo)*/
                        if (current->key == NULL) {
                            /*se a lista circular (key) nao estiver criada em current (no duplo), cria uma nova lista*/
                            current->key = malloc(sizeof(C_List));
                            /*inicia uma nova lista circular*/
                            init_Clist(current->key);
                        }
                        /*chama a funcao para inserir o no na lista circular*/
                        insert_Clist(current->key, value);
                    }
                    /*define o item atual como nulo e segue para a proxima linha*/
                    token = strtok_r(NULL, split, &outer);
                }
            }
            /*segue para a proxima linha*/
            token = strtok_r(NULL, split, &outer);
        }
        /*chama a funcao para imprimir a lista dupla*/
        print_Dlist(DL, output);
        /*libera a lista dupla*/
        free(DL);
    }
    /*libera a linha atual*/
    free(line);
    /*fecha os arquivos de entrada e saida*/
    fclose(input);
    fclose(output);
    /*retorna sucesso*/
    return EXIT_SUCCESS;
}
/* funcao para criar um novo no duplo */
D_NODE *create_Dnode(int value) {
    D_NODE *node = malloc(sizeof(D_NODE));
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    node->key = NULL;
    return node;
}
/* funcao para criar um novo no simples */
S_NODE *create_Snode(float value) {
    S_NODE *node = malloc(sizeof(S_NODE));
    node->value = value;
    node->next = NULL;
    return node;
}

/* funcao para inicializar a lista circular */
void init_Clist(C_List *CL) {
    CL->head = NULL;
    CL->tail = NULL;
}

/* funcao para inicializar a lista dupla */
void init_Dlist(D_List *DL) {
    DL->head = NULL;
    DL->tail = NULL;
}

/* funcao para buscar um no duplo na lista dupla */
D_NODE *search_Dlist(D_List *DL, int value) {
    /*cria o no-atual para receber o valor da cabeca da lista*/
    D_NODE *current = DL->head;
    /*busca na lista um primeiro informado na busca*/
    while (current != NULL) {
        if (current->value == value) {
            return current;
        }
        current = current->next;
    } 
    /*Retorna NULL se o valor nao for encontrado ou se o valor no nó for maior que o procurado*/    
    return NULL;
}

void insert_Dlist(D_List *DL, D_NODE *newNode) {
    // Se a lista estiver vazia, inicializa a cabeca e a cauda
    if (DL->head == NULL) {
        DL->head = newNode;
        DL->tail = newNode;
    } else {/*caso ja existam nos na lista dupla*/
        /*cria o no-atual para receber o valor da cabeca da lista*/
        D_NODE *current = DL->head;
        /*busca na lista um primeiro valor maior que o valor informado na busca*/
        while (current != NULL && current->value < newNode->value) {
            current = current->next;
        }
        /* se o novo-no for menor que o atual, insere antes, no início da lista */
        if (current == DL->head) {
            newNode->next = DL->head; /* novo-no-proximo recebe da cabeca da lista */
            DL->head->prev = newNode;/* atualiza o valor da cabeca-anterior que aponta para o novo-no*/
            DL->head = newNode; /* atualiza o valor da cabeca recebe o novo-no*/
        } else if (current == NULL) {
            DL->tail->next = newNode;
            newNode->prev = DL->tail;
            DL->tail = newNode;
        } else {
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;
        }
    }
}

void insert_Clist(C_List *CL, float newValue) {
    /*inicia um novo no simples*/
    S_NODE *newNode = create_Snode(newValue);
    /* se a lista estiver vazia, insere o novo valor na primeira posicao atualizando a cabeca, a cauda e o próximo item da lista circular */
    if (CL->head == NULL) {
        CL->head = newNode;  /* atualiza a cabeca que aponta para novo-no se for o primeiro item */
        CL->tail = newNode;  /* atualiza a cauda que aponta para novo-no se for o primeiro item */
        newNode->next = newNode; /* novo no proximo recebe o novo-no se for o primeiro item */
    } else { /*caso ja existam nos na lista circular, busca pelo valor maior que o novo-no para ser inserido em ordem*/
        S_NODE *current = CL->head;
        S_NODE *prev = NULL;
        do {
            if (current->value > newValue) {
                if (prev == NULL) {
                    newNode->next = CL->head;
                    CL->tail->next = newNode;
                    CL->head = newNode;
                } else {
                    newNode->next = current;
                    prev->next = newNode;
                }
                return;
            }
            prev = current;
            current = current->next;
        } while (current != CL->head);
        prev->next = newNode;
        newNode->next = CL->head;
        CL->tail = newNode;
    }
}

/* funcao para imprimir a lista circular */
void print_Clist(C_List *CL, FILE *output) {
    if (CL == NULL || CL->head == NULL) {
        return;
    }

    S_NODE *current = CL->head;
    do {
        fprintf(output, "%.2f", current->value);
        current = current->next;
        if (current != CL->head) {
            fprintf(output, "->");
        }
    } while (current != CL->head);
}

/* funcao para imprimir a lista dupla */
void print_Dlist(D_List *DL, FILE *output) {
    if (DL == NULL || DL->head == NULL) {
        fprintf(stderr, "Error: DL or DL->head is NULL.\n");
        return;
    }

    D_NODE *current = DL->head;
    while (current != NULL) {
        fprintf(output, "[%d(", current->value);
        if (current->key != NULL && current->key->head != NULL) {
            print_Clist(current->key, output);
        }
        fprintf(output, ")]");
        if (current->next != NULL) {
            fprintf(output, "->");
        }
        current = current->next;
    }
    fprintf(output, "\n");
}

