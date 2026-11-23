/*
 * Forca bruta O(n^2), usada so como referencia nos testes.
 *
 * Para cada barra, estende para a direita guardando a menor altura do trecho. A area
 * do trecho [i, j] e (menor altura) * (j - i + 1).
 *
 * Com 100 mil barras sao cerca de 5 bilhoes de pares, entao nao serve para o limite do
 * problema: so para conferir a solucao O(n) com vetores pequenos.
 */

#include "forca_bruta.h"

int largestRectangleForcaBruta(const int *heights, int n) {
    long long melhor = 0;

    for (int i = 0; i < n; i++) {
        long long menor = heights[i];
        for (int j = i; j < n; j++) {
            if (heights[j] < menor) menor = heights[j];
            long long area = menor * (long long)(j - i + 1);
            if (area > melhor) melhor = area;
        }
    }

    return (int)melhor;
}
