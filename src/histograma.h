#ifndef HISTOGRAMA_H
#define HISTOGRAMA_H

/*
 * Largest Rectangle in Histogram.
 *
 * heights: vetor de alturas, cada barra tem largura 1.
 * n: numero de barras.
 *
 * Devolve a area do maior retangulo contido no histograma.
 */
int largestRectangleArea(const int *heights, int n);

/*
 * Mesma conta, devolvendo tambem o intervalo [inicio, fim] do retangulo vencedor.
 * Inicio e fim sao indices inclusivos nas barras; se n <= 0, devolve 0 e -1 em ambos.
 */
int largestRectangleComPosicao(const int *heights, int n, int *inicio, int *fim);

#endif
