CC=gcc
CFLAGS=-Wall -Wextra -g -Iinclude
SRC=src/main.c src/elf_parser.c
OUT=elf_parser

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f elf_parser
