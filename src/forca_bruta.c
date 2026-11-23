/* Forca bruta O(n^2), so como referencia para conferir a solucao O(n). */

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
