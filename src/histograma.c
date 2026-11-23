#include "histograma.h"

#include <stdlib.h>

/*
 * Pilha de indices com altura crescente. Quando chega uma barra menor que o topo,
 * a barra do topo nao cresce mais para a direita: fecha a area dela e desempilha.
 * O limite esquerdo e o topo depois do pop, nao o indice que saiu.
 * Cada indice entra e sai uma vez, entao O(n) de tempo e O(n) de memoria.
 */

int largestRectangleArea(const int *heights, int n) {
    return largestRectangleComPosicao(heights, n, NULL, NULL);
}

int largestRectangleComPosicao(const int *heights, int n, int *inicio, int *fim) {
    if (heights == NULL || n <= 0) {
        if (inicio != NULL) *inicio = -1;
        if (fim != NULL) *fim = -1;
        return 0;
    }

    int *pilha = malloc((size_t)(n + 1) * sizeof(int));
    if (pilha == NULL) {
        if (inicio != NULL) *inicio = -1;
        if (fim != NULL) *fim = -1;
        return 0;
    }

    int topo = -1;
    long long melhor = 0;
    int melhorComeco = 0, melhorFim = -1;

    for (int i = 0; i <= n; i++) {
        /* i == n e uma sentinela de altura 0, que desempilha o que sobrou. */
        int alturaAtual = (i == n) ? 0 : heights[i];

        while (topo >= 0 && heights[pilha[topo]] >= alturaAtual) {
            int indice = pilha[topo--];
            long long altura = heights[indice];
            int esquerda = (topo >= 0) ? pilha[topo] : -1;
            long long largura = (long long)i - esquerda - 1;
            long long area = altura * largura;

            if (area > melhor) {
                melhor = area;
                melhorComeco = esquerda + 1;
                melhorFim = i - 1;
            }
        }

        pilha[++topo] = i;
    }

    free(pilha);

    if (inicio != NULL) *inicio = melhorComeco;
    if (fim != NULL) *fim = melhorFim;
    return (int)melhor;
}
