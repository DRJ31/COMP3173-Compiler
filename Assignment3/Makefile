CC = gcc
LEX = flex
CFLAGS = -Wall
LEXSRC = lex.yy.c
SRC = $(wildcard *.c) $(LEXSRC)
BIN = hw03

all: $(BIN)

clean:
	$(RM) $(BIN) $(LEXSRC)

$(BIN): $(SRC)
	$(CC) -o $@ $^

$(LEXSRC): lexer.l
	$(LEX) $<
