
/*
 *  1. Considere as seguintes entrada e sada abaixo:
 *                   L1Q1.in
   |---------------------------------------------|
   |  start 3 1 2 0 start 4 2 5 1 0 start 2 1 3  | 
   |  start 6 8 15 0 start 5 1 3 2               |
   |---------------------------------------------|
   
 arnce
                     L1Q1.out  
   |---------------------------------------------|
   |  start 3 1 2 start 1 0 2 3 start 0 1 2 4 5  | 
   |  start 1 2 3 5 start 8 0 6 15               |
   |---------------------------------------------|
 
*  A cada linha um start marca o incio de uma lista de numeros naturais que acaba na ocorrencia do
*  proximo start ou na quebra de linha. No arquivo de sada devem aparecer todas as listas em ordem
*  crescente. As listas deverao tambem ser ordenadas entre si conforme a soma de seus elementos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*definições de tipos e variáveis de pré-processamento*/
# define lineSize 1000
# define MAX_ListS 50
# define MAX_NUMBERS 100

typedef struct list {
	int numberList[MAX_NUMBERS];
	int itemCount;
	int sum;/*serve para verificar quem tem o maior somatório e assim organiza as células*/
} List;

/*protótipos de funções*/
int start();
void save(List * input, int listSize, FILE * fileOut, int isLast);
void insertionSortCells(List * input, int listSize);

int main() {
    start();
    return 0;
}

int start(){
    FILE *input = fopen("L1Q1.in", "r");
    FILE *output = fopen("L1Q1.out", "w");
	
	if (!input || !output) {
        printf("Error opening files.\n");
        return EXIT_FAILURE;
    }
	/*cria uma nova linha*/	
	char * line = malloc(lineSize * sizeof(char));
	/*separador dos itens da linha*/
	char split[] = " ";
	/*ponteiro para salvar os dados separados da função strtok_r (thread-safe)*/
	char *outer;
	/*contador dos itens da lista*/
	int cellCounter = 0;
	

	/*copia cada linha do input no comprimento de 1000 caracteres para line*/
	fgets(line, lineSize, input);
	/*percorre a linha enquanto existir caractere válido*/
	while(line != NULL){ 
		/*cópia auxiliar de cada linha*/
		char *token = strtok_r(line, split, &outer);
		
		/*nova lista sem o start*/
		List currentLine[MAX_ListS] = {0};
		/*percorre o dado enquanto existir caractere válido*/
		while (token != NULL) {
			/*remove o start de cada novo dado. Ex: 3 -1 2 0 start 4 2 5 1 0 start 2 1 -3 start 2 1 100 -3 start 2 101 -3*/
			if (strcmp(token, "start") == 0) { 
				/*copia o dado para o ponteiro outer. thread-safe permite a tokenização de múltiplas strings simultaneamente sem interferência entre elas.*/
        		token = strtok_r(NULL, " ", &outer); 
				/*percorre o dado sem start enquanto for diferente de start Ex: 3 -1 2 0 start*/
				while(strcmp(token, "start") != 0) { 
					/*insere os dados de token na linha atual[contador de células].lista de números[linha atual[contador de células].contagem de itens]*/
                	currentLine[cellCounter].numberList[currentLine[cellCounter].itemCount] = atoi(token);
					//salva a soma para organizar a células
					currentLine[cellCounter].sum += currentLine[cellCounter].numberList[currentLine[cellCounter].itemCount];
					/*atualiza o valor do contador de itens armazenadas em cada célula*/
					currentLine[cellCounter].itemCount++; 
					/*atualiza o valor do token para inicar novamente*/
					token = strtok_r(NULL, split, &outer); 
					/*caso chegue ao final da linha ou encontre um valor nulo, interrompe o loop*/
					if(token == NULL) break; 
            	}
				/*atualiza o valor do contado de células e vai para a próxima célula na linha*/
        		cellCounter++; 
        	}	
		}
		
		if(fgets(line, lineSize, input) != NULL) 
			save(currentLine, cellCounter, output, 0);
		else {
			save(currentLine, cellCounter, output, 1);
			break;
		}
		cellCounter = 0;
	}

	free(line);
	fclose(input);
	fclose(output);
	EXIT_SUCCESS;
}

/*ordena os itens das células*/
void insertionSortItems(List * input) {
	for (int i = 1; i < input->itemCount; i++) {
		int key = input->numberList[i];
		int j = i - 1;
		while (j >= 0 && key < input->numberList[j]) {
			input->numberList[j + 1] = input->numberList[j];
			j--;
		}
		input->numberList[j + 1] = key;
	}
}

/*ordena as células pelo valor da soma*/
void insertionSortCells(List * input, int listSize) {
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

void save(List * input, int listSize, FILE * fileOut, int isLast) {
	insertionSortCells(input, listSize);
	int j = 0;
	for(int i = 0; i < listSize; i++) {
		fprintf(fileOut, "%s", "start ");
		insertionSortItems(&input[i]);
		for(j = 0; j < input[i].itemCount - 1; j++) {
			fprintf(fileOut, "%d ", input[i].numberList[j]);
		}
		if(i < listSize - 1) {
			fprintf(fileOut, "%d ", input[i].numberList[j]);
		}
		else {
			fprintf(fileOut, "%d", input[i].numberList[j]);
		}
	}
	if(!isLast) {
		fputc('\n', fileOut);
	}
}