CC ?= gcc
CFLAGS ?= -O2 -Wall -Wextra -std=c11
SRC = src/histograma.c src/forca_bruta.c
BIN = build

all: test

$(BIN):
	mkdir -p $(BIN)

$(BIN)/testes: $(SRC) testes/testes.c src/histograma.h src/forca_bruta.h | $(BIN)
	$(CC) $(CFLAGS) -o $@ $(SRC) testes/testes.c

test: $(BIN)/testes
	./$(BIN)/testes

clean:
	rm -rf $(BIN)

.PHONY: all test clean
