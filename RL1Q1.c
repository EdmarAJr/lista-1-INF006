#include <stdio.h>
#include <stdlib.h>

/*definições de tipos e variáveis de pré-processamento*/
# define lineMaxSize 1000
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
    int start();

    return 0;
}

int start(){
    FILE *input = "L1Q1.in";
    FILE *output = "L1Q1.out";
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