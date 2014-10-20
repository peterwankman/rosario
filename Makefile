SRC=fons
BIN=destinatum
CC=gcc

CFLAGS=-O0 -ggdb
OPTS=-DCUM_RETICULUM

$(BIN)/rosario: $(SRC)/rosario.c
	$(CC) $(CFLAGS) $(OPTS)  -o $@ $^

.PHONY: clean

clean:
	rm -f $(BIN)/*
