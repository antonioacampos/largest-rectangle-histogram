/*
 * Benchmark: mostra na pratica que a solucao e linear e que a forca bruta nao
 * aguenta o limite do problema.
 *
 * Cada linha roda a funcao varias vezes ate somar pelo menos ~50 ms, e divide
 * pelo numero de execucoes. Sem isso o cronometro de Windows (resolucao de 1 ms)
 * reporta 0.000 para os casos pequenos.
 *
 * Compilar: gcc -O2 -std=c11 src/histograma.c src/forca_bruta.c benchmark/benchmark.c -o benchmark
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/forca_bruta.h"
#include "../src/histograma.h"

typedef int (*Solver)(const int *, int);

/*
 * Roda f(v, n) entre 1 e maxExecucoes vezes, parando quando acumular ~50 ms.
 * Devolve o tempo medio em milissegundos e o numero de execucoes feitas.
 */
static double medirMs(Solver f, const int *v, int n, int maxExecucoes, int *execucoes) {
    clock_t inicio = clock();
    int feitas = 0;
    volatile int resultado = 0;

    while (feitas < maxExecucoes) {
        resultado = f(v, n);
        feitas++;
        if (feitas >= 3) {
            double decorrido = (double)(clock() - inicio) / (double)CLOCKS_PER_SEC;
            if (decorrido >= 0.05) break;
        }
    }

    clock_t fim = clock();
    (void)resultado;
    *execucoes = feitas;
    return ((double)(fim - inicio) / (double)CLOCKS_PER_SEC) * 1000.0 / (double)feitas;
}

int main(void) {
    const int tamanhos[] = {1000, 10000, 50000, 100000, 200000};
    const int total = (int)(sizeof(tamanhos) / sizeof(tamanhos[0]));

    printf("%9s | %10s %8s | %13s %8s | %10s\n",
           "barras", "O(n) ms", "exec", "forca bruta ms", "exec", "aceleracao");
    printf("%9s-+-%10s-%8s-+-%13s-%8s-+-%10s\n",
           "---------", "----------", "--------", "-------------", "--------", "----------");

    for (int t = 0; t < total; t++) {
        int n = tamanhos[t];
        int *v = malloc((size_t)n * sizeof(int));
        if (v == NULL) {
            printf("sem memoria para %d barras\n", n);
            continue;
        }
        for (int i = 0; i < n; i++) {
            v[i] = (int)(rand() % 10001);
        }

        int execRapida = 0;
        double msRapida = medirMs(largestRectangleArea, v, n, 5000, &execRapida);

        /* a forca bruta so roda ate 50 mil barras; acima disso levaria horas */
        double msBruta = -1.0;
        int execBruta = 0;
        if (n <= 1000) {
            msBruta = medirMs(largestRectangleForcaBruta, v, n, 200, &execBruta);
        } else if (n <= 10000) {
            msBruta = medirMs(largestRectangleForcaBruta, v, n, 10, &execBruta);
        } else if (n <= 50000) {
            msBruta = medirMs(largestRectangleForcaBruta, v, n, 2, &execBruta);
        }

        if (msBruta > 0) {
            printf("%9d | %10.4f %8d | %13.2f %8d | %9.0fx\n",
                   n, msRapida, execRapida, msBruta, execBruta, msBruta / msRapida);
        } else {
            printf("%9d | %10.4f %8d | %13s %8s | %10s\n",
                   n, msRapida, execRapida, "n/a", "-", "n/a");
        }

        free(v);
    }

    puts("");
    puts("Na coluna O(n): o tempo praticamente dobra quando o numero de barras dobra.");
    puts("Na coluna da forca bruta: quadruplica. E com 100 mil barras seriam ~5 bilhoes");
    puts("de pares (i, j), o que estoura qualquer limite de tempo de juiz online.");
    return 0;
}
