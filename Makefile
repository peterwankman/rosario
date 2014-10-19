SRC=fons
BIN=destinatum
CC=gcc

CFLAGS=-O0 -ggdb

$(BIN)/rosario: $(SRC)/rosario.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f $(BIN)/*
