# Largest Rectangle in Histogram

Trabalho de Estruturas de Dados.

Entrada: um vetor de alturas, cada barra com largura 1.
Saida: a area do maior retangulo que cabe dentro do histograma.

Com `[2, 1, 5, 6, 2, 3]` a resposta e 10, que e o retangulo formado pelas barras de
altura 5 e 6 (largura 2).

## Como rodar

```
make        # compila os testes e o benchmark
make test   # roda os testes
make bench  # roda o benchmark
make clean  # apaga a pasta build
```

Precisa de um compilador C com suporte a C11. Testei com gcc 16 no Windows; no Linux
funciona com gcc ou clang sem mudar nada.

## Arquivos

| Arquivo | O que e |
|---|---|
| `src/histograma.c` | solucao O(n) com pilha monotona |
| `src/forca_bruta.c` | solucao O(n^2), so para comparar nos testes |
| `testes/testes.c` | casos fixos e comparacao com a forca bruta |
| `benchmark/benchmark.c` | tempo das duas solucoes |

## Como funciona

A pilha guarda indices, e as alturas desses indices ficam em ordem crescente.

Quando chega uma barra mais baixa que o topo da pilha, aquela barra do topo nao pode
mais crescer para a direita. Entao calculamos a area dela e desempilhamos. A largura e
a distancia entre a barra atual e o indice que sobrou no topo, menos 1. Se a pilha
ficar vazia, a barra vai desde o comeco do vetor.

No final do vetor entra uma barra de altura 0 so para esvaziar a pilha. Sem ela, um
vetor em ordem crescente nunca teria nenhuma area calculada.

Como cada indice entra e sai da pilha uma unica vez, o laco interno roda no maximo 2n
vezes no total. O tempo e O(n) e a memoria da pilha e O(n).

## Testes

`make test` roda dois tipos de verificacao:

1. dez casos fixos, com resposta conhecida, incluindo os que costumam quebrar a
   implementacao: vetor crescente, decrescente, todas as barras iguais e barras com
   altura zero;
2. vinte mil vetores aleatorios, comparando a resposta da solucao O(n) com a da forca
   bruta. Qualquer divergencia faz o programa falhar.

Tambem conferimos a versao que devolve a posicao do retangulo, recalculando a area a
partir do inicio e do fim informados.

Saida esperada:

```
29 verificacoes, 0 falhas
20000 casos aleatorios, 0 divergencias
```

## Benchmark

`make bench` mede o tempo das duas solucoes. A forca bruta fica limitada a 50 mil
barras porque acima disso leva mais de um segundo por execucao.

```
   barras |      O(n) | forca bruta | quantas vezes mais rapido
     1000 |  0.0025ms |     0.42ms  |  168x
    10000 |  0.0911ms |    35.03ms  |  384x
    50000 |  0.5437ms |   979.32ms  | 1801x
   100000 |  1.0000ms |         -   |    -
   200000 |  1.8276ms |         -   |    -
```

Os numeros variam de 10 a 20% entre execucoes, por causa da maquina. O que importa e o
crescimento: dobrando o tamanho, o tempo da O(n) dobra, enquanto o da forca bruta
quadruplica.
