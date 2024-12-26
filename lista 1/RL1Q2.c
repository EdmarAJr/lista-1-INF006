/**
 *  Implemente uma pilha de texto todos os elementos estao sempre ordenados alfabeticamente sem ferir
 *  a politica LIFO (las-in rst-out).
                                 |---------|
    |---------|                  | Walter  |
    | Walter  |                  | Dani    |
    | Daniele |                  | Carla   |
    | Carla   |                  | Bruno   |
    | Bruno   |  >(push Antonia) | Antonia |
    |---------|                  |---------|
 
 *  Assim para push Antonia e preciso executar: pop, pop, pop, pop, push Antonia, push Bruno, push
 *  Dani, push Walter.
                            L1Q2.in
             |----------------------------------|
             |  Bruno Dani Carla Antonia Walter |
             |  Maria Joao                      | 
             |----------------------------------|
    
                            L1Q2.out
 |-------------------------------------------------------------------------------------------------------------------|
 |  push Bruno push Dani 1x pop push Carla push Dani 3x pop push Antonia push Bruno push Carla push Dani push Walter |
 |  push Maria 1x pop push Joao push Maria                                                                           |
 |-------------------------------------------------------------------------------------------------------------------| 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Definições de tipos e variáveis de pré-processamento */
#define LINE_SIZE 1000
#define STACK_SIZE 100

typedef struct {
    char* stack[STACK_SIZE];//para modificar essa linha precisamos pensar em como inicializar a stack
    int top;
    int size;
} SortedStack;

int start();
void initStack(SortedStack* stack, int size);
void clearStack(SortedStack* stack);
bool isEmpty(SortedStack* stack);
bool isFull(SortedStack *stack);
void push(SortedStack* stack, char* name);
char* pop(SortedStack* stack);
void printStack(SortedStack* stack);

int main() {
    start();
    return 0;
}

int start() {
    FILE *input = fopen("L1Q2.in", "r");
    FILE *output = fopen("L1Q2.out", "w");
    
    /* Verifica se os ponteiros foram iniciados com sucesso*/
    if (!input || !output) {
        printf("Error opening files.\n");
        return EXIT_FAILURE;
    }

    /* Cria uma nova linha */
    char *line = malloc(LINE_SIZE * sizeof(char));
    /* Separador dos itens da linha */
    char split[] = " ";
    /* Ponteiro para salvar os dados separados da função strtok_r (thread-safe) */
    char *outer;

    /* Cria uma nova pilha a cada nova linha */
    SortedStack *stack = malloc(sizeof(SortedStack));
    SortedStack *stack_aux = malloc(sizeof(SortedStack));
    
    /* Inicializa a pilha a cada nova linha */
    initStack(stack, STACK_SIZE);
    initStack(stack_aux, STACK_SIZE);

    /* Copia cada linha do input no comprimento de 1000 caracteres para line */
    /* Percorre a linha enquanto existir caractere válido */
    while (fgets(line, LINE_SIZE, input) != NULL) {
        /* Limpa as pilhas antes de processar uma nova linha */
        clearStack(stack);
        clearStack(stack_aux);
         
         /*Copia a primeira ocorrência de cada linha do input antes do espaco e salva em token o reto da linha fica salva em outer*/
        char* token = strtok_r(line, split, &outer);

        /* Inicializa a contagem de pops */
        int counterPop = 0;
        
        /* Percorre o token enquanto existir caractere valido */
        while (token != NULL) {
            /* Remove o caractere de nova linha, se existir */
            token[strcspn(token, "\n")] = 0;

            /* Move elementos da pilha principal para a auxiliar enquanto necessário */
            while (!isEmpty(stack) && strcmp(token, stack->stack[stack->top]) < 0) {
                push(stack_aux, pop(stack));
                counterPop++;
            }

            /* Registra o numero de pops realizados */
            if (counterPop > 0) {
                fprintf(output, "%dx-pop ", counterPop);
                counterPop = 0;
            }
            /*empilha os nomes que não cairam no laço anterio*/
            push(stack, token);
            /* Escreve no output*/
            fprintf(output, "push-%s ", token);

            /* Reinsere os elementos da pilha auxiliar de volta na pilha principal */
            while (!isEmpty(stack_aux)) {
                char* auxTop = pop(stack_aux);
                push(stack, auxTop);
                fprintf(output, "push-%s ", auxTop);
            }

            /* Avança para o próximo token */
            token = strtok_r(NULL, split, &outer);
        }
        /*salta uma linha apos o procesamento da linha atual*/
        fprintf(output, "\n");
    }

    /*Libera a memoria alocada*/
    free(stack);
    free(stack_aux);
    free(line);
    fclose(input);
    fclose(output);

    return 0;
}

void initStack(SortedStack* stack, int size) {
    stack->top = -1;
    stack->size = size;
}

void clearStack(SortedStack* stack) {
    while (!isEmpty(stack)) {
        free(pop(stack));
    }
    stack->top = -1;
}

bool isEmpty(SortedStack* stack) {
    return stack->top == -1;
}

bool isFull(SortedStack *stack) {
    return stack->top == stack->size - 1;
}

void push(SortedStack* stack, char* name) {
    /* Verifica se a pilha está cheia */
    if (isFull(stack)) {
        printf("Error: stack full!\n");
        return;
    }
    /* Aloca memória para o novo nome e coloca-o na pilha */
    stack->stack[++stack->top] = strdup(name);
}

char* pop(SortedStack* stack) {
    /* Verifica se a pilha esta vazia */
    if (isEmpty(stack)) {
        printf("Error: stack empty!\n");
        return NULL;
    }
    return stack->stack[stack->top--];
}

void printStack(SortedStack* stack) {
    for (int i = 0; i <= stack->top; i++) {
        printf("%s ", stack->stack[i]);
    }
    printf("\n");
}