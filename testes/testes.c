/* Casos fixos e comparacao com a forca bruta em vetores aleatorios. */

#include <stdio.h>
#include <stdlib.h>

#include "../src/forca_bruta.h"
#include "../src/histograma.h"

static int falhas = 0;
static int total = 0;

static void confere(const char *nome, int esperado, int obtido) {
    total++;
    if (esperado != obtido) {
        falhas++;
        printf("FALHOU %-34s esperado %d, obtido %d\n", nome, esperado, obtido);
    }
}

static void confereAnimal(const char *nome, const int *v, int n, int esperado) {
    int obtido = largestRectangleArea(v, n);
    confere(nome, esperado, obtido);

    /* a versao com posicao precisa concordar com a area */
    int inicio = -1, fim = -1;
    int area = largestRectangleComPosicao(v, n, &inicio, &fim);
    total++;
    if (area != obtido) {
        falhas++;
        printf("FALHOU %-34s area com posicao %d != %d\n", nome, area, obtido);
        return;
    }
    if (area > 0) {
        long long menor = v[inicio];
        for (int i = inicio; i <= fim; i++) {
            if (v[i] < menor) menor = v[i];
        }
        long long recomputada = menor * (long long)(fim - inicio + 1);
        total++;
        if (recomputada != area) {
            falhas++;
            printf("FALHOU %-34s posicao [%d,%d] nao reproduz a area %d\n", nome, inicio, fim, area);
        }
    }
}

int main(void) {
    puts("== casos fixos ==");

    const int exemplo[] = {2, 1, 5, 6, 2, 3};
    confereAnimal("exemplo do enunciado -> 10", exemplo, 6, 10);

    const int dois[] = {2, 4};
    confereAnimal("[2,4] -> 4", dois, 2, 4);

    const int uma[] = {7};
    confereAnimal("[7] -> 7", uma, 1, 7);

    const int zero[] = {0};
    confereAnimal("[0] -> 0", zero, 1, 0);

    const int iguais[] = {5, 5, 5, 5};
    confereAnimal("barras iguais -> 20", iguais, 4, 20);

    const int crescente[] = {1, 2, 3, 4, 5};
    confereAnimal("crescente -> 9", crescente, 5, 9);

    const int decrescente[] = {5, 4, 3, 2, 1};
    confereAnimal("decrescente -> 9", decrescente, 5, 9);

    const int vale[] = {2, 1, 2};
    confereAnimal("[2,1,2] -> 3", vale, 3, 3);

    const int misto[] = {4, 2, 0, 3, 2, 5};
    confereAnimal("[4,2,0,3,2,5] -> 6", misto, 6, 6);

    const int zeros[] = {0, 0, 0};
    confereAnimal("so zeros -> 0", zeros, 3, 0);

    puts("== teste diferencial (20.000 vetores aleatorios) ==");

    srand(20261119u);
    int divergencias = 0;
    for (int caso = 0; caso < 20000; caso++) {
        int n = 1 + rand() % 64;
        int v[64];
        int alturaMaxima = 1 + rand() % 10;
        for (int i = 0; i < n; i++) {
            v[i] = rand() % alturaMaxima;
        }

        int rapida = largestRectangleArea(v, n);
        int bruta = largestRectangleForcaBruta(v, n);
        if (rapida != bruta) {
            divergencias++;
            if (divergencias <= 5) {
                printf("divergencia no caso %d: rapida %d, bruta %d, vetor:", caso, rapida, bruta);
                for (int i = 0; i < n; i++) printf(" %d", v[i]);
                printf("\n");
            }
        }
    }
    total++;
    if (divergencias != 0) {
        falhas++;
        printf("FALHOU teste diferencial: %d divergencias em 20.000 casos\n", divergencias);
    } else {
        printf("ok: 20.000 casos, 0 divergencias\n");
    }

    printf("\n%d verificacoes, %d falhas\n", total, falhas);
    return falhas == 0 ? 0 : 1;
}
