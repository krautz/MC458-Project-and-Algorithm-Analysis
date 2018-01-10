/* Caio Krauthamer
 * Ra 165457
 * 
 * O programa le todas as especies e as armazena em uma matriz especies.
 * Constroi-se 2 vetores, um contendo os elementos da posicao 60% e outro com os maximos.
 * Transformamos ambos os vetores em heaps.
 * O padrao de corte sera o primeiro elemendo o heap com maximos.
 * Funcao recursiva corta_arvores:
 * Sempre que a o primeiro elemento do heap de 60% precisar ser podado, entao o podamos, 
 * guardamos a especie podada e fazemos um heapify removendo esse elemento do heap e chamamos a funcao novamente.
 * Ela para quando a raiz nao precisa ser podada ou o vetor estiver vazio (todas especies podadas).
 * Retornando o fluxo para main:
 * Computamos os cortes na variavel corte.
 * Para cada especie podada, podamos de fato a especie removendo o ultimo elemendo de cada especie podada da matriz especies.
 * Re-inserimos no heap de 60% as especies podadas agora com a nova posicao 60%.
 * Analisamos o heap de maximo e vemos se precisa ser atualizado, se sim, vamos o atualizando de acordo com  a matriz especies
 * atualizada ate chegarmos a um ponto que o heap fique consistente.
 * Repetimos tal processo ate todas especies serem jovens ou todas arvores serem completamente podadas
 */

// Funcoes da std::vector
// Declarar vetor -> std::vector<int> myvector (tamanho, valor inicializado em cada posicao(padrao 0));
// Adds a new element at the end of the vector -> myvector.push_back (valor);
// Removes the last element in the vector -> myvector.pop_back();
// Returns the number of elements in the vector -> myvector.size();
// Acess element -> Operator[];
// Returns a reference to the last element in the vector -> myvector.back();
// Returns a reference to the first element in the vector -> myvector.front();

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

typedef struct Esp {
    int especie;
    int idade;
} esp;

struct ordena{
    bool operator()( esp &a, esp &b) const{
        return a.idade < b.idade;
    }
};


int corta_arvores (vector<esp> &pct_60, int arvore_mais_velha, vector<int> &especies_podadas) {
    if (pct_60.size() == 0 || pct_60.front().idade <= 0.6 * arvore_mais_velha) {
        return 0;
    } else {
        pop_heap(pct_60.begin(), pct_60.end(), ordena());
        especies_podadas.push_back(pct_60.back().especie);
        pct_60.pop_back();
        return 1 + corta_arvores (pct_60, arvore_mais_velha, especies_podadas);
    }
}


int main () {
    int numero_especies, tamanho_especie, i, j, elemento, cortes = 0;
    esp aux;
    
    cin >> numero_especies;
    vector<vector<int> > especies(numero_especies,vector<int>());
    vector<esp> max_idade(numero_especies);
    vector<esp> pct_60(numero_especies);
    vector<int> especies_podadas(numero_especies);
    
    //lendo entradas e armazenando na matriz de especies
    for (i = 0; i < numero_especies; i++) {
        cin >> tamanho_especie;
        especies[i].reserve(tamanho_especie);
        for (j = 0; j < tamanho_especie; j++) {
            cin >> elemento;
            especies[i].push_back(elemento);
        }
    }
    
    pct_60.erase(pct_60.begin(), pct_60.end());
    //criando o heap da posicao 60 porcento
    for (i = 0; i < numero_especies; i++) {
        aux.especie = i;
        aux.idade = especies[i][ceil(especies[i].size() * 0.6) - 1];
        pct_60.push_back(aux);
    }
    make_heap(pct_60.begin(), pct_60.end(), ordena());
    
    max_idade.erase(max_idade.begin(), max_idade.end());
    //criando o heap dos valores mais velhos
    for (i = 0; i < numero_especies; i++) {
        aux.especie = i;
        aux.idade = especies[i].back();
        max_idade.push_back(aux);
    }
    make_heap(max_idade.begin(), max_idade.end(), ordena());

    while (j && (0.6 * max_idade.front().idade) < pct_60.front().idade) {
        if (especies_podadas.size() > 0)
            especies_podadas.erase(especies_podadas.begin(), especies_podadas.end());
        cortes += corta_arvores (pct_60, max_idade.front().idade, especies_podadas);
        j = especies_podadas.size();
        for (i = 0; i < j; i++) {
            especies[especies_podadas[i]].pop_back();
            if (especies[especies_podadas[i]].size() > 0) {
                aux.especie = especies_podadas[i];
                aux.idade = especies[especies_podadas[i]][ceil(especies[especies_podadas[i]].size() * 0.6) - 1];
                pct_60.push_back(aux);
                push_heap (pct_60.begin(), pct_60.end(), ordena());
            }
        }
        while (max_idade.size() > 0 && max_idade.front().idade != especies[max_idade.front().especie].back()) {
            pop_heap(max_idade.begin(), max_idade.end(), ordena());
            elemento = max_idade.back().especie;
            max_idade.pop_back();
            if (especies[elemento].size() > 0) {
                aux.especie = elemento;
                aux.idade = especies[elemento].back();
                max_idade.push_back(aux);
                push_heap(max_idade.begin(), max_idade.end(), ordena());
            }
        }
    }
    cout << cortes << "\n";
    return 0;
}