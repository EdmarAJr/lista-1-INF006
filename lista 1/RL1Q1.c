#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*definições de tipos e variáveis de pré-processamento*/
# define lineSize 1000
# define MAX_ListS 50
# define MAX_NUMBERS 100

typedef struct list {
	int sum;
	int index;
	int numberList[MAX_NUMBERS];
} List;



/*protótipos de funções*/
int start();
void insertionSort(List * input, int listSize);


int main() {
    start();
    return 0;
}

int start(){
    FILE *input = fopen("L1Q1.in", "r");
    FILE *output = fopen("L1Q1.out", "w");
	char line[lineSize];
	char split[] = " ";
	char *outer;
	/*contador dos itens da lista*/
	int count = 0;
	
	if (!input || !output) {
        printf("Erro ao abrir os arquivos.\n");
        exit;
    }

	/*copia cada linha do input no comprimento de 1000 caracteres para line*/
	while(fgets(line, lineSize, input) != NULL){ /*enquanto existir carater válido na linha*/
		/*cópia auxiliar de cada linha*/
		char *token = strtok_r(line, split, &outer);
		
		/*nova lista sem o start*/
		List lineList[MAX_ListS] = {0};

		while (token != NULL) {
			if (strcmp(token, "start") == 0) {
        		token = strtok_r(NULL, " ", &outer);
				while(strcmp(token, "start") != 0) { 
				printf("%s\n", token);
                	lineList[count].numberList[lineList[count].index] = atoi(token);
					lineList[count].sum += lineList[count].numberList[lineList[count].index] ;
					lineList[count].index ++;
					token = strtok_r(NULL, split, &outer);
					if(token == NULL) break;
            	}
        		count++;
        	}	
		}
		// if(fgets(line, lineSize, input) != NULL) {
		// 	save(lineList, count, output, 0);
		// }
		// else {
		// 	save(lineList, count, output, 1);
		// 	break;
		// }
		count = 0;
	}

	fclose(input);
	fclose(output);
	EXIT_SUCCESS;
}

void insertionSort(List * input, int listSize) {
	for (int i = 1; i < listSize; i++) {
		List key = input[i];
		int j = i - 1;

		while (j >= 0 && key.sum < input[j].sum) {
			input[j + 1] = input[j];
			j--;
		}
		input[j + 1] = key;
	}
}