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

// void push(STACK *stack, char* value){
//     if (!isFull(stack)){
//         stack->top = stack->top + 1;
//         stack->STK[stack->top] = value;
//     }
//     else
//         printf("Stack is full!\n");
// }

// char *pop(STACK *stack){
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


// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <string.h>

// #define lineSize 1000
// #define stack_length 50
// #define MAX_NAME_LENGTH 100

// typedef struct {
//     char **STK;
//     int top;
//     int length;
// } STACK;

// bool isEmpty(STACK *stack);
// bool isFull(STACK *stack);
// void create(STACK *stack, int size);
// void push(STACK *stack, const char *value, FILE *output);
// char* pop(STACK *stack, FILE *output);
// void printStack(STACK *stack);
// void handlePushOperation(STACK *stack, STACK *stack_aux, const char *token, FILE *output);

// int main() {
//     FILE *input = fopen("L1Q2.in", "r");
//     FILE *output = fopen("L1Q2.out", "w");

//     if (!input || !output) {
//         printf("Error opening files.\n");
//         return EXIT_FAILURE;
//     }

//     char line[lineSize];
//     char split[] = " ";
//     char *outer;

//     while (fgets(line, lineSize, input) != NULL) {
//         STACK stack;
//         STACK stack_aux;
//         create(&stack, stack_length);
//         create(&stack_aux, stack_length);

//         char *token = strtok_r(line, split, &outer);

//         while (token) {
//             handlePushOperation(&stack, &stack_aux, token, output);
//             token = strtok_r(NULL, split, &outer);
//         }

//         fprintf(output, "\n");

//         // Liberar a memória alocada para as pilhas
//         for (int i = 0; i < stack.length; ++i) {
//             free(stack.STK[i]);
//             free(stack_aux.STK[i]);
//         }
//         free(stack.STK);
//         free(stack_aux.STK);
//     }

//     fclose(input);
//     fclose(output);
//     return 0;
// }

// void create(STACK *stack, int size) {
//     stack->STK = (char **)malloc(size * sizeof(char *));
//     for (int i = 0; i < size; ++i) {
//         stack->STK[i] = (char *)malloc(MAX_NAME_LENGTH * sizeof(char));
//     }
//     stack->top = -1;
//     stack->length = size;
// }

// void push(STACK *stack, const char *value, FILE *output) {
//     if (!isFull(stack)) {
//         stack->top++;
//         strncpy(stack->STK[stack->top], value, MAX_NAME_LENGTH);
//         fprintf(output, "push-%s ", value);
//     } else {
//         printf("Stack is full!\n");
//     }
// }

// char* pop(STACK *stack, FILE *output) {
//     if (!isEmpty(stack)) {
//         fprintf(output, "1x-pop ");
//         return stack->STK[stack->top--];
//     } else {
//         printf("Stack is empty!\n");
//         return NULL;
//     }
// }

// bool isEmpty(STACK *stack) {
//     return stack->top == -1;
// }

// bool isFull(STACK *stack) {
//     return stack->top == stack->length - 1;
// }

// void handlePushOperation(STACK *stack, STACK *stack_aux, const char *token, FILE *output) {
//     int pops = 0;

//     // Desempilhar até encontrar a posição correta para o novo token
//     while (!isEmpty(stack) && strcmp(stack->STK[stack->top], token) > 0) {
//         push(stack_aux, pop(stack, output), output);
//         pops++;
//     }

//     // Empilhar o novo token na posição correta
//     push(stack, token, output);

//     // Reempilhar os elementos desempilhados
//     while (!isEmpty(stack_aux)) {
//         push(stack, pop(stack_aux, output), output);
//     }
// }

// void printStack(STACK *stack) {
//     printf("Stack:\n");
//     for (int i = 0; i <= stack->top; i++) {
//         printf("%s\n", stack->STK[i]);
//     }
//     printf("\n");
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define LINE_SIZE 1000
#define STACK_SIZE 10
#define MAX_NUMS 100

typedef struct {
    char* stack[STACK_SIZE];//para modificar essa linha precisamos pensar em como inicializar a stack
    int top;
    int length;
} SortedStack;

int start();
void initStack(SortedStack* stack, int size);
bool isEmpty(SortedStack* stack);
bool isFull(SortedStack *stack);
void removeLineBreak(char * str);
void push(SortedStack* stack, char* name);
char* pop(SortedStack* stack);
void printStack(SortedStack* stack);

int main(){
    start();
    return 0;
}

int start(){
    //printf("inicio da função start\n\n");
    FILE *input = fopen("L1Q2.in", "r");
    FILE *output = fopen("L1Q2.out", "w");
    
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
    int counterPop=0;

//teste para aferir se este é o local correto para inicializar a pilha
    /*cria uma nova pilha a cada nova linha*/
    SortedStack *stack=malloc(sizeof(SortedStack));
    SortedStack *stack_aux=malloc(sizeof(SortedStack));
    /*inicializa a pilha a cada nova linha*/
    initStack(stack, STACK_SIZE);
    initStack(stack_aux, STACK_SIZE);

    /*copia cada linha do input no comprimento de 1000 caracteres para line*/
	//fgets(line, LINE_SIZE, input);
    /*percorre a linha enquanto existir caractere válido*/  
    while(fgets(line, LINE_SIZE, input) != NULL){
        //printf("Primeiro while\n");
        // /*cria uma nova pilha a cada nova linha*/
        // SortedStack *stack=malloc(sizeof(SortedStack));
        // SortedStack *stack_aux=malloc(sizeof(SortedStack));
        // /*inicializa a pilha a cada nova linha*/
        // initStack(stack, STACK_SIZE);
        // initStack(stack_aux, STACK_SIZE);
        
        char *token = strtok_r(line, split, &outer);
        //printf("token : %s\n", token);
        //removeLineBreak(token);
        push(stack, token);//insere o primeiro elemento da linha na pilha
        fprintf(output, "%s%s", "push-", token);
        token = strtok_r(NULL, split, &outer); // Em seguida, passa para o proximo elemento, que sera testado
        while(token !=NULL){ //verifica se há mais elementos na linha
            //printf("segundo while\n");
            fputc(32, output);
            char strTmp[strlen(token) + 1];
			strcpy(strTmp, token);
            //printf("token : %s\n", token);
            //if(!isFull(stack)){
                //printf("Entrou no if do segundo while\n");
                //printf("outer : %s\n", outer);
                
                //printf("length : %d\n", stack->length);
                /*Verifica se o elemento atual vem antes do elemento no topo da piha*/
                if(!isEmpty(stack) && strcmp(strTmp, stack->stack[stack->top]) < 0){
                    // printf("Entrou no segundo if do segundo while\n");
                    // printf("token : %s\n", token);
                    // printf("nome na pilha : %s\n", stack->stack[stack->top]);
                    // //printf("outer : %s\n", outer);
                    // printf("strTmp : %s\n", strTmp);
                    while (strcmp(strTmp, stack->stack[stack->top])<0){
                        //printf("top : %d\n", stack->top);
                        counterPop++;
                        push(stack_aux,  pop(stack));//insere o elemento maior na pilha auxiliar
                        printf("counter pop : %d\n", counterPop);
                        if (counterPop > 0) {
                            fprintf(output, "%dx-pop ", counterPop);
                        }
                    }
                    //push(stack, strTmp);//insere o novo elemento menor na pilha principal
                } else if (!isEmpty(stack_aux) && strcmp(stack_aux->stack[stack_aux->top], stack->stack[stack->top]) > 0) {
                    while (strcmp(stack_aux->stack[stack_aux->top], stack->stack[stack->top])>0){
                        push(stack,  pop(stack_aux));//insere maior elemento da pilha auxiliar na pilha principal
                        fprintf(output, "%s%s", "push-", token);  
                    }
                }else{
                    push(stack, token);//insere o novo elemento menor na pilha principal
                    fprintf(output, "%s%s", "push-", token);  
                }


                // if(isEmpty(stack)){
                //     strcpy(stack[stack->top++].STK, token);
                //     //fprintf(output,"push-%s ",token);
                // }
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
            //}
            //counterPop = 0;
            token = strtok_r(NULL, split, &outer);
        }
    }
    fclose(input);
    fclose(output);
}


void initStack(SortedStack* stack, int size) {
    //printf("Inicializar stack: foi\n");
    //stack->stack = malloc((char) size*sizeof(char));
    stack->top=-1;
    stack->length = size;
}

void removeLineBreak(char * str) {
	for(int i = 0; str[i] != '\0'; i++ ) {
		if(str[i] == '\n') {
			str[i] = '\0';
			break;
		}
	}
}

bool isEmpty(SortedStack* stack) {
    return stack->top == -1;
}

bool isFull(SortedStack *stack){
    return stack->top==stack->length-1;
}

void push(SortedStack* stack, char* name) {
    //printf("Nome : %s\n", name);
    if (isFull(stack)) {
        printf("Erro: Pilha cheia!\n");
        return; // Verifica se a pilha está cheia
    }

    printf("push: foi\n");
    char* temp[STACK_SIZE];      // Vetor temporário
    int tempTop = -1;            // Índice do topo da pilha temporária

    // Mover os elementos da pilha para a pilha temporária até encontrar a posição correta
    while (!isEmpty(stack) && strcmp(stack->stack[stack->top], name) > 0) {
        temp[++tempTop] = stack->stack[stack->top--]; // Mover o topo da pilha para a pilha temporária
    }

    // Alocar memória para o novo nome e colocá-lo na pilha
    stack->stack[++stack->top] = strdup(name);
    if (stack->stack[stack->top] == NULL) {
        printf("Erro ao alocar memória para o nome!\n");
        return; // Se a alocação falhar, retornamos
    }

    // Restaurar os elementos da pilha temporária de volta à pilha original
    while (tempTop >= 0) {
        stack->stack[++stack->top] = temp[tempTop--];
    }
}

char* pop(SortedStack* stack) {
    printf("pop: foi\n");

    if (isEmpty(stack)) {
        printf("Erro: Pilha vazia!\n");
        return NULL; // Verifica se a pilha está vazia
    }
    return stack->stack[stack->top--];
}

void printStack(SortedStack* stack) {
    for (int i = 0; i <= stack->top; i++) {
        printf("%s ", stack->stack[i]);
    }
    printf("\n");
}