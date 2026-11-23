CC ?= gcc
CFLAGS ?= -O2 -Wall -Wextra -std=c11
SRC = src/histograma.c src/forca_bruta.c
BIN = build

all: $(BIN)/testes $(BIN)/benchmark

$(BIN):
	mkdir -p $(BIN)

$(BIN)/testes: $(SRC) testes/testes.c src/histograma.h src/forca_bruta.h | $(BIN)
	$(CC) $(CFLAGS) -o $@ $(SRC) testes/testes.c

$(BIN)/benchmark: $(SRC) benchmark/benchmark.c src/histograma.h src/forca_bruta.h | $(BIN)
	$(CC) $(CFLAGS) -o $@ $(SRC) benchmark/benchmark.c

test: $(BIN)/testes
	./$(BIN)/testes

bench: $(BIN)/benchmark
	./$(BIN)/benchmark

run: test bench

clean:
	rm -rf $(BIN)

.PHONY: all test bench run clean
