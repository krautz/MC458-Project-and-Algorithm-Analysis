/* Caio Krauthamer
 * 165457
 * 
 * O programa le as entradas e entao precisa calcular o menor custo.
 * para isso ele calcula o preço de compra do ultimo dia e guarda no vetor melhor_compra[j] este valor
 * entao para todos os outros dias 0 ... n-2 calculamos todas opcoes possiveis (Comprar no 1o dia apenas para ele e somar o melhor resultado ate o 2o dia, 
 * comprar no 1o dia para o 1o e 2o dia e somar o melhor resultado até o 3o dia, 
 * comprar no 1o dia para o 1o, 2o e 3o dia e somar com o valor do 4o dia e por ai vai...)
 * apos fazer isso para todos n-1 elementos do vetor ou ate o custo de permanencia ser maior que o frete,
 * imprimimos melhor_compra[0], que e o menor valor de compra para todos os dias juntos.
 */

#include <iostream>
#include <vector>

using namespace std;

int main () {
    
    long int custo_manutencao, numero_dias, i, j, melhor;
    
    cin >> custo_manutencao;
    cin >> numero_dias;
    
    vector<long int> custo_compra(numero_dias);
    custo_compra.reserve(numero_dias);
    vector<long int> melhor_compra(numero_dias);
    melhor_compra.reserve(numero_dias);
    vector<long int> custo_itens(numero_dias);
    custo_itens.reserve(numero_dias);
    
    for (i = 0; i < numero_dias; i++) {
        cin >> custo_compra[i];
    }

    for (i = 0; i < numero_dias; i++) {
        cin >> j;
        custo_itens[i] = j * custo_manutencao;
    }
    
    melhor_compra[numero_dias - 1] = custo_compra [numero_dias - 1];
    for (i = numero_dias - 2; i >= 0; i--) {
        melhor = custo_compra[i];
        melhor_compra[i] = custo_compra[i] + melhor_compra[i + 1];
        for (j = i + 1; j < numero_dias - 1 && ((custo_compra[j] / custo_itens[j]) >= (j - i)); j++) {
                melhor += (j-i) * custo_itens[j];
                if (melhor + melhor_compra[j + 1] < melhor_compra[i]) {
                    melhor_compra[i] = melhor + melhor_compra[j + 1];
                }
        }
        melhor += (j-i) * custo_itens[j];
        if (melhor < melhor_compra[i] && j == numero_dias - 1) {
            melhor_compra[i] = melhor;
        }
    }
    cout << melhor_compra[0] << "\n";
    
    return 0;
}