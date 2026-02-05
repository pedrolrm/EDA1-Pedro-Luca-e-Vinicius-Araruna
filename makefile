CC = gcc
CFLAGS = -I include -Wall
SRC = src/main.c src/clientes.c src/produto.c src/utils.c
TARGET = bin/sistema

all:
	@mkdir -p bin
	@mkdir -p data
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f bin/sistema