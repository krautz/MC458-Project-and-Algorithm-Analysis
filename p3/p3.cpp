/* Caio Krauthamer
 * Ra 165457
 * O programa primeiramente encontra cada separador, para isso ele procura o separador do vetor original a partir do selectNL visto em sala
 * entao ele coloca este separador em um vetor auxiliar e particiona o vetor original em funcao deste separador binario 
 * (metade menor ficará a esquerda e maior a direita).
 * Entao os proximos separadores binarios estao nos 2 subvetores:
 * inicio ate meio e meio ate fim
 * assim,  chama-se a mesma funcao rescursiva para os subvetores da direita e da esquerda, esta funcao tem
 * como caso base o numero de separadores chegar a 0.
 * como para cada subvetor gastamos no maximo O(n) (particiona aleatorio tem caso medio O(n) e particiona e O(n))
 * e a altura da arvore de recorrencia é O(log k) temos uma complexidade total
 * O(n * log k)
 * apos a funcao que acha os separadores retorna para main, ordenamos o vetor com os separadores atraves do heap sort.
 * (para imprimir o vetor ordenado fazemos um heap sort que custa O(k*log k) < O (n * log k), entao mantemos a complexidade O(n * log k)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdlib.h>

using namespace std;

void encontra_separadores (vector <long int> &vetor, vector<long int> &separadores, long int qtd_separadores, long int inicio, long int fim, long int &pos_separador);
void particiona (vector<long int> &vetor, long int n_esimo, long int inicio, long int fim);
long int particiona_aleatorio (vector<long int> &vetor, long int inicio, long int fim);
long int encontra_n_esimo (vector<long int> &vetor, long int inicio, long int fim, long int n_esimo);

int main () {
    long int tamanho_vetor, qtd_separadores, pos_separador = 0;
    int i;    
    
    cin >> tamanho_vetor;
    cin >> qtd_separadores;
    
    vector<long int> vetor(tamanho_vetor);
    vetor.reserve(tamanho_vetor);
    vector<long int> separadores(qtd_separadores);
    separadores.reserve(qtd_separadores);
    
    for (i = 0; i < tamanho_vetor; i++) {
        cin >> vetor[i];
    }

    encontra_separadores (vetor, separadores, qtd_separadores, 0, tamanho_vetor - 1, pos_separador);
    make_heap(separadores.begin(), separadores.end());
    sort_heap(separadores.begin(), separadores.end());
    for (i = 0; i < qtd_separadores; i++)
        cout << separadores[i] << " ";
    cout << "\n";
    
    return 0;
}

void encontra_separadores (vector <long int> &vetor, vector<long int> &separadores, long int qtd_separadores, long int inicio, long int fim, long int &pos_separador) {
    long int n_esimo, prox_separador, meio;
    
    if (qtd_separadores == 0)
        return;
        
    meio = ((fim - inicio) + 1) / 2;
    n_esimo = encontra_n_esimo (vetor, inicio, fim, meio);
    separadores[pos_separador++] = vetor[n_esimo];
    
    particiona(vetor, n_esimo, inicio, fim);

    prox_separador = (qtd_separadores - 1) / 2;
    meio += inicio;
    encontra_separadores (vetor, separadores, prox_separador, inicio, meio - 1, pos_separador);
    encontra_separadores (vetor, separadores, prox_separador, meio + 1, fim, pos_separador);
}

void particiona (vector<long int> &vetor, long int n_esimo, long int inicio, long int fim) {
    long int i, j, aux;
    i = inicio - 1;
    aux = vetor[fim];
    vetor[fim] = vetor[n_esimo];
    vetor[n_esimo] = aux;
    for (j = inicio; j < fim; j++) {
        if (vetor[j] <= vetor[fim]) {
            i++;
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
        }
    }
    i++;
    aux = vetor[i];
    vetor[i] = vetor[fim];
    vetor[fim] = aux;
}

long int particiona_aleatorio (vector<long int> &vetor, long int inicio, long int fim) {
    srand(0);
    long int i = rand() % (fim - inicio + 1), aux, j;
    i += inicio;
    aux = vetor[i];
    vetor[i] = vetor[fim];
    vetor[fim] = aux;
    i = inicio - 1;
    for (j = inicio; j < fim; j++) {
        if (vetor[j] <= vetor[fim]) {
            i++;
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
        }
    }
    i++;
    aux = vetor[i];
    vetor[i] = vetor[fim];
    vetor[fim] = aux;
    return i;
}

long int encontra_n_esimo (vector<long int> &vetor, long int inicio, long int fim, long int n_esimo) {
    long int pos, k;
    
    if (inicio == fim) {
        return inicio;
    }
    pos = particiona_aleatorio (vetor, inicio, fim);
    k = pos - inicio;
    if (k == n_esimo)
        return pos;
    if (n_esimo < k)
        return encontra_n_esimo (vetor, inicio, pos - 1, n_esimo);
    else
        return encontra_n_esimo (vetor, pos + 1, fim, n_esimo - k - 1);
}