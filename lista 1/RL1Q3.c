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
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/* Definicoes de tipos e variaveis de pre-processamento */
# define LINE_SIZE 1000

typedef struct simple_node {
	float key;
	struct simple_node *next;
} simple_node;


typedef struct circular_linked_list {
	simple_node *head;
	simple_node *tail;
} circular_linked_list;

typedef struct doubly_linked_node {
	float keyRange;
	struct doubly_linked_node *next;
	struct doubly_linked_node *prev;
	circular_linked_list *key;
} doubly_linked_node;


typedef struct doubly_linked_list {
	doubly_linked_node *head;
	doubly_linked_node *tail;
} doubly_linked_list;

/* protótipos de funcoes */
int start();
void initCL(circular_linked_list *CL);
simple_node *createSimpleNode(float value);
void insertCL(circular_linked_list *CL, float new);
void freeCL(circular_linked_list *CL);
void initDL(doubly_linked_list *DL);
doubly_linked_node *createDoublyNode(float value);
void insertDL(doubly_linked_list *DL, float newValue);
void insertNodeIntoKey(doubly_linked_list *DL, float newValue);
void freeLists(doubly_linked_list *DL);
void printFile(doubly_linked_list *DL, FILE * output, int isLast);
//float decimalPlaces(char* str, int places);

int main() {
	start();
	return EXIT_SUCCESS;
}

int start() {
	FILE *input = fopen("L1Q3.in", "r");
	FILE *output = fopen("L1Q3.out", "w");
	
    if (!input || !output) {
        printf("Error opening files.\n");
        return EXIT_FAILURE;
    }

    /* cria uma nova linha */
    char *line = (char*) malloc(LINE_SIZE * (sizeof(char)));
    /* separador dos itens da linha */
	char split[] = " ";
    /* ponteiro para salvar os dados separados da funcao strtok_r (thread-safe) */
    char *outer;
	/*ponteiro para receber linha atual*/
    char *token;

	doubly_linked_list *dl = malloc(sizeof(doubly_linked_list));
	/*inicia a lista duplamente encadeada*/
    initDL(dl);
    /*linha atual*/
	fgets(line, LINE_SIZE, input);
    /*percorre cada linha do arquivo*/
	while(line != NULL) {
        /*retira o LE da linha atual*/
		token = strtok_r(line, split, &outer);
        /*percorre cada item da linha atual*/
		while(token != NULL) {
			if(strcmp(token, "LE") == 0) {
				token = strtok_r(NULL, split, &outer);
                /*percorre cada item da linha atual sem LE ate chegar ao LI*/
				while((strcmp(token, "LI") != 0) && token != NULL) {
					// float tmp = decimalPlaces(token, 2);
                    /*converte o token atual para float*/
                    float tmp = atof(token);
					insertDL(dl, tmp);
                    /*define o item atual como nulo e segue para o proximo item da linha*/
					token = strtok_r(NULL, split, &outer);
				}
			}                
			if(strcmp(token, "LI") == 0) {
                /*retira o LI da linha atual*/
				token = strtok_r(NULL, split, &outer);
				while((strcmp(token, "LE") != 0)) {
					// float tmp = decimalPlaces(token, 2);
                    /*converte o token atual para float*/
                    float tmp = atof(token);
					insertNodeIntoKey(dl, tmp);
					token = strtok_r(NULL, split, &outer);
                    /*se o no encontrado for nulo interrompre o laço e segue para a etapa seguinte*/
					if(token == NULL) {
						break;
					}
				}
			}
            /*define o item atual como nulo e segue para a proxima linha*/
			token = strtok_r(NULL, split, &outer);
		}
		if(fgets(line, LINE_SIZE, input) != NULL) {
			printFile(dl, output, 0);
			freeLists(dl);
		} else {
			printFile(dl, output, 1);
			freeLists(dl);
			break;
		}
	}
    /*fecha os arquivos*/
	fclose(input);
	fclose(output);
	/*libera a lista linha*/
    free(line);
    /*libera a lista dupla*/
	free(dl);
}

/* funcao para inicializar a lista circular */
void initCL(circular_linked_list *CL) {
	CL->head = NULL;
	CL->tail = NULL;
}

/* funcao para criar um novo no simples */
simple_node *createSimpleNode(float value) {
    simple_node *node = (simple_node *)malloc(sizeof(simple_node));
    node->key = value;
    node->next = NULL;
    return node;
}

/*funcao para inserir no na lista circular*/
void insertCL(circular_linked_list * CL, float new) {
	//simple_node * newNode = (simple_node *)malloc(sizeof(simple_node));
	//newNode->key = new;
    
    /*inicia um novo no simples*/
    simple_node *newNode = createSimpleNode(new);
    /*inicia um novo atual que recebe a cabeca da lista*/
	simple_node *current = CL->head;
    /* se a lista estiver vazia, insere o novo valor na primeira posicao atualizando a cabeca, a cauda e o próximo item da lista circular */
    if(current == NULL) {
		CL->head = newNode; /* atualiza a cabeca que aponta para novo-no se for o primeiro item */
		CL->tail = newNode; /* atualiza a cauda que aponta para novo-no se for o primeiro item */
		newNode -> next = newNode; /* novo no proximo recebe o novo-no se for o primeiro item */
	} else { /*caso ja existam nos na lista circular, busca pelo valor maior que o novo-no para ser inserido em ordem*/
		if(new < current -> key) {
			newNode -> next = current;
			CL->head = newNode;
			CL->tail->next = newNode;
		} else {
			while (current != CL->tail && new > current->next->key) {
				current = current -> next;
			}
			newNode->next = current->next;
			current->next = newNode;
			if (current == CL->tail) {
				CL->tail = newNode;
			}
		}
	}
}

/* funcao para inicializar a lista dupla */
void initDL(doubly_linked_list *DL) {
	DL->head = NULL;
	DL->tail = NULL;
}

/* funcao para criar um novo no duplo */
doubly_linked_node *createDoublyNode(float value) {
    doubly_linked_node *node = (doubly_linked_node *)malloc(sizeof(doubly_linked_node));
    node->keyRange = value;
    node->next = NULL;
    node->prev = NULL;
    node->key = NULL;
    return node;
}

/*funcao para inserir no na lista dupla*/
void insertDL(doubly_linked_list * DL, float newValue) {
	// doubly_linked_node *newNode = (doubly_linked_node *)malloc(sizeof(doubly_linked_node));
    doubly_linked_node *newNode = createDoublyNode(newValue);
	//newNode->keyRange = newValue;
	newNode->key = (circular_linked_list*)malloc(sizeof(circular_linked_list));
	initCL(newNode -> key);

    /*cria o no-atual para receber o valor da cabeca da lista*/       
	doubly_linked_node * current = DL->head;
    /*Se a lista estiver vazia, inicializa a cabeca e a cauda*/ 
	if(current == NULL) {
		newNode->prev = NULL;
		newNode->next = NULL;
		DL->head = newNode;
		DL->tail = newNode;
	} else {/*caso ja existam nos na lista dupla*/
		if(newValue < current->keyRange) {
			newNode->next = current;
			newNode->prev = NULL;
			current->prev = newNode;
			DL->head = newNode;
		} else {
            /*busca na lista um primeiro valor maior que o valor informado*/
			while(newValue > current->keyRange && current->next != NULL) {
				if(current->keyRange == newValue) {
					free(newNode->key);
					free(newNode);
					return;
				}
				current = current->next;
			}
			newNode->next = current;
			newNode->prev = current->prev;
			if(current->next == NULL) {
				newNode->prev = current;
				newNode->next = NULL;
				current->next = newNode;
			} else {
				current-> prev->next = newNode;
				current->prev = newNode;
			}
		}
	}
}

void insertNodeIntoKey(doubly_linked_list *DL, float newValue) {
	doubly_linked_node *current = DL->head;
	if(current == NULL) {
		return;
	}
	while(current != NULL) {
		float difference = 0.0f;
		if((newValue - current -> keyRange) <= 0.99f &&  newValue > current->keyRange - 1) {
			insertCL(current -> key, newValue);
			break;
		}
		else if((current->keyRange - newValue) <= 0.99f && newValue > current->keyRange - 1 && newValue < current-> keyRange + 1) {
			insertCL(current -> key, newValue);
			break;
		}
		current = current -> next;
	}
}

/* funcao para imprimir a lista dupla */
void printFile(doubly_linked_list *DL, FILE *output, int isLast) {
	doubly_linked_node *tmp = DL->head;
	//simple_node *end;
	fprintf(output, "[");
	while(tmp != NULL) {
		fprintf(output, "%g", tmp -> keyRange );
		simple_node *end = tmp->key->head;
		fputc('(',output);
		if(tmp -> key -> head != NULL) {
			while (end -> next != tmp -> key -> head) {
				fprintf(output, "%g->", end->key);
				end = end->next;
			}
			fprintf(output, "%g)", end->key);
		} else {
			fprintf(output, ")");
		}
		tmp = tmp -> next;
		if(tmp != NULL) {
			fprintf(output, "->");
		}
	}
	if(!isLast) {
		fprintf(output, "]\n");
	} else {
		fprintf(output, "]");
	}
}


// float decimalPlaces(char* str, int places) {
// 	float number = atof(str); 
// 	float power = 1;
// 	for (int i = 0; i < places; i++) {
// 		power *= 10;
// 	}
// 	return ((int)(number * power)) / power;
// }


void freeCL(circular_linked_list * CL) {
	if (CL == NULL) return; 
	
	simple_node *current = CL->head;
	simple_node *temp;
	while (current != NULL) {
		temp = current;
		current = current->next;
		free(temp);
		if (current == CL->head) {
			break; // Para evitar um loop infinito se a lista for circular
		}
	}
	CL->head = NULL; // Define o ponteiro da lista como NULL no final da funcao
	CL->tail = NULL;
}

void freeLists(doubly_linked_list *DL) {
	doubly_linked_node *current = DL->tail;
	doubly_linked_node *temp;
	while (current != NULL) {
		temp = current;
		freeCL(temp -> key);
		current = current->prev;
		free(temp);
	}
	DL->head = NULL;
	DL->tail = NULL;
}