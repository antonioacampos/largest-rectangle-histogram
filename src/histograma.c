/*
 * Largest Rectangle in Histogram.
 *
 * A pilha guarda indices com altura crescente. Quando chega uma barra menor que o
 * topo, a barra do topo nao cresce mais para a direita: calculamos a area dela e
 * desempilhamos.
 *
 * O limite esquerdo de uma barra e o indice que fica no topo depois do pop, e nao
 * o indice que saiu. Se a pilha esvazia, o limite e -1.
 *
 * Cada indice entra e sai da pilha uma vez, entao o tempo e O(n). A memoria da
 * pilha e O(n).
 */

#include "histograma.h"

#include <stdlib.h>

int largestRectangleArea(const int *heights, int n) {
    return largestRectangleComPosicao(heights, n, NULL, NULL);
}

/*
 * Mesma solucao, devolvendo tambem onde o retangulo comeca e termina (indices no
 * vetor). Se a entrada for vazia, devolve -1 nas duas posicoes.
 */
int largestRectangleComPosicao(const int *heights, int n, int *inicio, int *fim) {
    if (heights == NULL || n <= 0) {
        if (inicio != NULL) *inicio = -1;
        if (fim != NULL) *fim = -1;
        return 0;
    }

    /* n + 1 posicoes: a ultima guarda o indice da sentinela. */
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
        /* Sentinela: em i == n a altura e 0, o que desempilha o que sobrou. Sem
         * ela, um vetor crescente terminaria sem calcular area nenhuma. */
        int alturaAtual = (i == n) ? 0 : heights[i];

        /* Usei >= e nao >: com empate, desempilhar agora ja fecha a area da barra
         * anterior corretamente, porque as duas tem a mesma altura. */
        while (topo >= 0 && heights[pilha[topo]] >= alturaAtual) {
            /* A barra desempilhada define a altura do retangulo. */
            int indice = pilha[topo--];
            long long altura = heights[indice];

            /* Limite esquerdo: o topo depois do pop. Se vazio, o retangulo comeca em 0. */
            int esquerda = (topo >= 0) ? pilha[topo] : -1;

            /* Largura entre os dois limites. */
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
