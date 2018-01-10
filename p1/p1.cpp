#include <iostream>
#include <cstdlib>

/* Este e um algoritimo padrao de MergeSort(ordena em ordem decrescente), porem, alem de passar como parametro o inicio e fim dos vetores, 
 * tambem passo um ponteiro que armazena o numero de inversoes feitas.
 * o calculo das inversoes eh bem simples:
 * como esta ordenado em forma decrescente, sei que caso eu escolha o primeiro elemento do atual vetor que vai de inicio a meio (i)
 * significa que ele eh maior que todos elementos a partir do inidice atual (j) do vetor meio+1 ate fim, ja que ambos estao ordenados de forma descrescente.
 * Entao o numero de inversoes que faço eh o numero de elementos restantes no vetor meio+1 ate fim, ja que meu elemento do vetor
 * inicio ate meio tem indice menor e eh maior que todos elementos restantes do vetor meio+1 ate fim.
 * (caso o elemento escolhido seja do vetor inicio ate meio, entao somo em inversoes o tamanho restante do vetor meio+1 ate fim, que eh
 * fim - j + 1, onde j indica a posicao atual no vetor meio+1 ate fim)
 * O algoritimo esta correto e para, pois eh apenas um MergeSort em ordem descrescente com uma linha a mais para indicar o numero de inversoes feitas
 */

void MergeSort (int *vetor,int inicio,int fim, unsigned long long int *inversoes);
void Intercala (int *vetor, int inicio, int meio, int fim, unsigned long long int *inversoes);

int main () {
	int tamanho, *vetor, i;
        unsigned long long int inversoes = 0;

	std::cin >> tamanho;

	vetor = (int *)  malloc (tamanho * sizeof(int));

	for (i = 0; i < tamanho; i++)
		std::cin >> vetor[i];

	MergeSort(vetor, 0, tamanho - 1, &inversoes);

         std::cout << inversoes << "\n";
	
	return 0;
}

void MergeSort (int *vetor,int inicio,int fim, unsigned long long int *inversoes) {
	int meio;
	if (inicio < fim) {
		meio = (fim + inicio) / 2;
		MergeSort (vetor, inicio, meio, inversoes);
		MergeSort (vetor, meio + 1, fim, inversoes);
		Intercala (vetor, inicio, meio, fim, inversoes);
	}
}

void Intercala (int *vetor, int inicio, int meio, int fim, unsigned long long int *inversoes) {
	int *aux = (int *) malloc (((fim - inicio) + 1) * sizeof (int));
	int i = inicio, j = meio + 1, indice_aux = 0;
        
	while (i != (meio + 1) || j != (fim + 1)) {
		if (i == (meio + 1)) {
			aux[indice_aux++] = vetor[j++];
		} else if (j == (fim + 1)) {
			aux[indice_aux++] = vetor[i++];
		} else if (vetor[i] > vetor[j]) {
			aux[indice_aux++] = vetor[i++];
                        *inversoes += (fim - j + 1);
		} else {
			aux[indice_aux++] = vetor[j++];
		}
	}
	for (i = inicio, indice_aux = 0; i <= fim; i++, indice_aux++) {
		vetor[i] = aux[indice_aux];
	}
}
