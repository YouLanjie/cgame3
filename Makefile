#!/usr/bin/make

CC = gcc
BIN = ./bin
SRC = $(shell find ./src/ -name "*.c")
incl = $(shell find ./include/ -name "*.h")
OBJ = $(SRC:%.c=%.o)
prom = cgame3

all: cgame3

$(prom): $(OBJ)
	@rm -rf $(BIN)
	$(CC) $(OBJ) -o $(prom)
	@mkdir bin
	@mv $(prom) $(BIN)/cgame3

%.o: %.c $(incl)
	$(CC) -c $< -o $@

clean:
	@rm -rf $(OBJ) $(prom).deb

