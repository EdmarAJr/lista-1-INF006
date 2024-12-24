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
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <string.h>
// #define lineSize 1000
// #define stack_length 50

// typedef struct node {
// 	struct node * prev;
// 	struct node * next;
// 	char * key;
// } NODE;


// typedef struct stack{
//     char *STK;
//     int top;
//     int length;
// } STACK;


// int start();
// bool isEmpty(STACK *stack);
// bool isFull(STACK *stack);
// void create(STACK *stack, int size);
// void push(STACK *stack, int value);
// int pop(STACK *stack);

// int main(){
//     start();
//     return 0;
// }

// int start(){
//     FILE *input = fopen("L1Q2.in", "r");
//     FILE *output = fopen("L1Q2.out", "w");
    
//     if (!input || !output) {
//         printf("Error opening files.\n");
//         return EXIT_FAILURE;
//     }
// 	/*cria uma nova linha*/	
// 	char * line = malloc(lineSize * sizeof(char));
// 	/*separador dos itens da linha*/
// 	char split[] = " ";
// 	/*ponteiro para salvar os dados separados da função strtok_r (thread-safe)*/
// 	char *outer;
//     /*copia cada linha do input no comprimento de 1000 caracteres para line*/
// 	fgets(line, lineSize, input);
//     /*percorre a linha enquanto existir caractere válido*/    
//     while(line != NULL){
//         STACK *stack=malloc(sizeof(STACK));
//         STACK *stack_aux=malloc(sizeof(STACK));
//         create(stack, stack_length);
//         create(stack_aux, stack_length);
        
//         char *token = strtok_r(line, split, &outer);
        
//         // printf("token : %s\n", token);
//         while(token){
//             if(stack->top < stack_length){
//                 printf("token : %s\n", token);
//                 printf("top : %d\n", stack->top);
//                 printf("length : %d\n", stack->length);
                
//                 if(isEmpty(stack)){
//                     strcpy(stack[stack->top++].STK, token);
//                     //fprintf(output,"push-%s ",token);
//                 }
//     //             else{
//     //                 int i=stack->top;
//     //                 while(strcmp(token,stack[i].STK) <= 0 && i >- 1){
//     //                     i--;
//     //                 }
//     //                 if(i==stack->top){
//     //                     strcpy(stack[stack->top++].STK, token);
//     //                     fprintf(output,"push-%s ",token);
//     //                 }
//     //                 else if(i<stack->top){
//     //                     int pop =0;
//     //                     while(stack->top>i){
//     //                         strcpy(stack_aux[stack_aux->top++].STK, stack[stack->top--].STK);
//     //                         pop++;
//     //                     }
//     //                     fprintf(output,"%dx-pop ",pop);
//     //                     strcpy(stack[stack->top++].STK, token);
//     //                     fprintf(output,"push-%s ",token);
//     //                     while(isEmpty(stack_aux)){
//     //                         strcpy(stack[stack->top++].STK, stack_aux[stack_aux->top--].STK);
//     //                         fprintf(output,"push-%s ",stack[stack->top].STK);
//     //                     }
//     //                 }
//     //             }
//             }
//             token = strtok_r(NULL, split, &outer);
//         }
//     }
//     fclose(input);
//     fclose(output);
// }

// void create(STACK *stack, int size){
//     stack->STK = malloc((char) size*sizeof(char));
//     stack->top=-1;
//     stack->length = size;
// }

// void push(STACK *stack, int value){
//     if (!isFull(stack)){
//         stack->top = stack->top + 1;
//         stack->STK[stack->top] = value;
//     }
//     else
//         printf("Stack is full!\n");
// }

// int pop(STACK *stack){
//     if (!isEmpty(stack)) {
//         stack->top = stack->top - 1;
//         return stack->STK[stack->top + 1];
//     }else{
//         printf("Stack is empty!\n");
//         return EXIT_FAILURE;
//     }
// }

// bool isEmpty(STACK *stack){
//     return stack->top==-1;
// }

// bool isFull(STACK *stack){
//     return stack->top==stack->length-1;
// }


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define lineSize 1000
#define stack_length 50
#define MAX_NAME_LENGTH 100

typedef struct {
    char **STK;
    int top;
    int length;
} STACK;

bool isEmpty(STACK *stack);
bool isFull(STACK *stack);
void create(STACK *stack, int size);
void push(STACK *stack, const char *value, FILE *output);
char* pop(STACK *stack, FILE *output);
void printStack(STACK *stack);
void handlePushOperation(STACK *stack, STACK *stack_aux, const char *token, FILE *output);

int main() {
    FILE *input = fopen("L1Q2.in", "r");
    FILE *output = fopen("L1Q2.out", "w");

    if (!input || !output) {
        printf("Error opening files.\n");
        return EXIT_FAILURE;
    }

    char line[lineSize];
    char split[] = " ";
    char *outer;

    while (fgets(line, lineSize, input) != NULL) {
        STACK stack;
        STACK stack_aux;
        create(&stack, stack_length);
        create(&stack_aux, stack_length);

        char *token = strtok_r(line, split, &outer);

        while (token) {
            handlePushOperation(&stack, &stack_aux, token, output);
            token = strtok_r(NULL, split, &outer);
        }

        fprintf(output, "\n");

        // Liberar a memória alocada para as pilhas
        for (int i = 0; i < stack.length; ++i) {
            free(stack.STK[i]);
            free(stack_aux.STK[i]);
        }
        free(stack.STK);
        free(stack_aux.STK);
    }

    fclose(input);
    fclose(output);
    return 0;
}

void create(STACK *stack, int size) {
    stack->STK = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; ++i) {
        stack->STK[i] = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
    }
    stack->top = -1;
    stack->length = size;
}

void push(STACK *stack, const char *value, FILE *output) {
    if (!isFull(stack)) {
        stack->top++;
        strncpy(stack->STK[stack->top], value, MAX_NAME_LENGTH);
        fprintf(output, "push-%s ", value);
    } else {
        printf("Stack is full!\n");
    }
}

char* pop(STACK *stack, FILE *output) {
    if (!isEmpty(stack)) {
        fprintf(output, "1x-pop ");
        return stack->STK[stack->top--];
    } else {
        printf("Stack is empty!\n");
        return NULL;
    }
}

bool isEmpty(STACK *stack) {
    return stack->top == -1;
}

bool isFull(STACK *stack) {
    return stack->top == stack->length - 1;
}

void handlePushOperation(STACK *stack, STACK *stack_aux, const char *token, FILE *output) {
    int pops = 0;

    // Desempilhar até encontrar a posição correta para o novo token
    while (!isEmpty(stack) && strcmp(stack->STK[stack->top], token) > 0) {
        push(stack_aux, pop(stack, output), output);
        pops++;
    }

    // Empilhar o novo token na posição correta
    push(stack, token, output);

    // Reempilhar os elementos desempilhados
    while (!isEmpty(stack_aux)) {
        push(stack, pop(stack_aux, output), output);
    }
}

void printStack(STACK *stack) {
    printf("Stack:\n");
    for (int i = 0; i <= stack->top; i++) {
        printf("%s\n", stack->STK[i]);
    }
    printf("\n");
}
