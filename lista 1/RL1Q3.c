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
# include <math.h>
# define LINE_SIZE 1000

typedef struct simple_node {
	float key;
	struct simple_node * next;
} simple_node;


typedef struct circular_linked_list {
	simple_node * head;
	simple_node * tail;
} circular_linked_list;


typedef struct doubly_linked_node {
	float range;
	struct doubly_linked_node *next;
	struct doubly_linked_node *prev;
	circular_linked_list *key;
} doubly_linked_node;


typedef struct doubly_linked_list {
	doubly_linked_node * head;
	doubly_linked_node * tail;
} doubly_linked_list;

int start();
void initCL(circular_linked_list *CL);
void insertCL(circular_linked_list *CL, float new);
void freeCL(circular_linked_list *CL);
void initDL(doubly_linked_list *DL);
void insertDL(doubly_linked_list *DL, float newValue);
void insertKey(doubly_linked_list *DL, float newValue);
void freeLists(doubly_linked_list *DL);
void saveToFile(doubly_linked_list *DL, FILE * output, int isLast);
float decimalPlaces(char* str, int places);

int main() {
	start();
	return EXIT_SUCCESS;
}

int start() {
	FILE * input = fopen("L1Q3.in", "r");
	FILE * output = fopen("L1Q3.out", "w");
	char * line = (char*) malloc(LINE_SIZE * (sizeof(char)));
	char * split = " ";
	char * token;

    if (!input || !output) {
        printf("Error opening files.\n");
        return EXIT_FAILURE;
    }

	doubly_linked_list *dl = malloc(sizeof(doubly_linked_list));
	initDL(dl);

	fgets(line, LINE_SIZE, input);
	while(line != NULL) {
		token = strtok(line, split);
		while(token != NULL) {
			if(strcmp(token, "LE") == 0) {
				token = strtok(NULL, split);
				while((strcmp(token, "LI") != 0) && token != NULL) {
					// float tmp = decimalPlaces(token, 2);
                    float tmp = atof(token);
					insertDL(dl, tmp);
					token = strtok(NULL, split);
				}
			}
			if(strcmp(token, "LI") == 0) {
				token = strtok(NULL, split);
				while((strcmp(token, "LE") != 0)) {
					// float tmp = decimalPlaces(token, 2);
                    float tmp = atof(token);
					insertKey(dl, tmp);
					token = strtok(NULL, split);
					if(token == NULL) {
						break;
					}
				}
			}
			token = strtok(NULL, split);
		}
		if(fgets(line, LINE_SIZE, input) != NULL) {
			saveToFile(dl, output, 0);
			freeLists(dl);
		} else {
			saveToFile(dl, output, 1);
			freeLists(dl);
			break;
		}
	}
	fclose(input);
	fclose(output);
	free(line);
	free(dl);
}

void freeCL(circular_linked_list * CL) {
	if (CL == NULL) return; 
	
	simple_node *current = CL->head;
	//simple_node *temp;
	while (current != NULL) {
		//temp = current;
		current = current->next;
		//free(temp);
		if (current == CL->head) {
			break; // Para evitar um loop infinito se a lista for circular
		}
	}
	CL->head = NULL; // Define o ponteiro da lista como NULL no final da funcao
	CL->tail = NULL;
}

void freeLists(doubly_linked_list *DL) {
	doubly_linked_node *current = DL->tail;
	//doubly_linked_node *temp;
	while (current != NULL) {
		//temp = current;
		//freeCL(temp -> key);
		current = current->prev;
		//free(temp);
	}
	DL->head = NULL;
	DL->tail = NULL;
}

void initCL(circular_linked_list *CL) {
	CL->head = NULL;
	CL->tail = NULL;
}

void initDL(doubly_linked_list *DL) {
	DL->head = NULL;
	DL->tail = NULL;
}

void insertCL(circular_linked_list * CL, float new) {
	simple_node * newNode = (simple_node *)malloc(sizeof(simple_node));
	newNode -> key = new;
	simple_node * current = CL -> head;
	if(current == NULL) {
		CL->head = newNode;
		CL->tail = newNode;
		newNode -> next = newNode;
	} else {
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

void insertKey(doubly_linked_list *DL, float newValue) {
    // printf("%f\n", newValue);
	doubly_linked_node *current = DL->head;
	if(current == NULL) {
		return;
	}
	while(current != NULL) {
		float difference = 0.0f;
		if((newValue - current -> range) <= 0.99f &&  newValue > current->range - 1) {
			insertCL(current -> key, newValue);
			break;
		}
		else if((current->range - newValue) <= 0.99f && newValue > current->range - 1 && newValue < current-> range + 1) {
			insertCL(current -> key, newValue);
			break;
		}
		current = current -> next;
	}
}

void insertDL(doubly_linked_list * DL, float newValue) {
	doubly_linked_node *newNode = (doubly_linked_node *)malloc(sizeof(doubly_linked_node));
	newNode->range = newValue;
	newNode->key = (circular_linked_list*)malloc(sizeof(circular_linked_list));
	initCL(newNode -> key);
	doubly_linked_node * tmp = DL->head;
	if(tmp == NULL) {
		newNode->prev = NULL;
		newNode->next = NULL;
		DL->head = newNode;
		DL->tail = newNode;
	} else {
		if(newValue < tmp->range) {
			newNode->next = tmp;
			newNode->prev = NULL;
			tmp->prev = newNode;
			DL->head = newNode;
		} else {
			while(newValue > tmp->range && tmp->next != NULL) {
				if(tmp->range == newValue) {
					free(newNode->key);
					free(newNode);
					return;
				}
				tmp = tmp->next;
			}
			newNode->next = tmp;
			newNode->prev = tmp->prev;
			if(tmp->next == NULL) {
				newNode->prev = tmp;
				newNode->next = NULL;
				tmp -> next = newNode;
			} else {
				tmp -> prev->next = newNode;
				tmp ->prev = newNode;
			}
		}
	}
}

void saveToFile(doubly_linked_list *DL, FILE *output, int isLast) {
	doubly_linked_node *tmp = DL->head;
	//simple_node *end;
	fprintf(output, "[");
	while(tmp != NULL) {
		fprintf(output, "%g", tmp -> range );
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
