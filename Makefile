#!/usr/bin/make

CC = gcc
BIN = ./bin
SRC = $(shell find ./ -name "*.c")
incl = $(shell find ./ -name "*.h")
OBJ = $(SRC:%.c=%.o)
prom = cgame3

all: cgame3

$(prom): $(OBJ)
	@rm -rf $(BIN)
	$(CC) $(OBJ) -L lib -ltools -o $(prom)
	@mkdir bin
	@mv $(prom) $(BIN)/main

%.o: %.c $(incl)
	$(CC) -g -Wall -c $< -o $@

clean:
	@rm -rf $(OBJ)

