BIN = ./bin
SRC = ./src
PROGRAMS = $(BIN)/example1 $(BIN)/example2 $(BIN)/example3
TARGETS = $(BIN)/example4 $(BIN)/example5 $(BIN)/example6
SOURCES = $(patsubst $(BIN)/%, $(SRC)/%.c, $(PROGRAMS))
MIDDLEFILES = $(patsubst $(BIN)/%, $(SRC)/%.tab.c, $(TARGETS))
RESOURCES = $(patsubst $(BIN)/%, $(SRC)/%.c, $(TARGETS))
BINARY = $(patsubst $(BIN)/%,%,$(PROGRAMS) $(TARGETS))

CC = gcc
CP = cp -f
LIBS = -lfl 
YACC = bison -y -d
RM = rm -f
LEX = flex
MV = mv -f
CFLAGS = -Wall

$(shell test -d $(BIN) || mkdir -p $(BIN))
$(shell test -d $(SRC) || mkdir -p $(SRC))
$(shell test -e $(BIN)/Makefile || $(CP) Makefile.bin $(BIN)/Makefile)

ifeq ($(shell uname), Darwin)
	LIBS = -ll
endif

.PHONY: clean $(BINARY)

all: $(PROGRAMS) $(TARGETS)

$(BINARY): %: $(BIN)/%

$(PROGRAMS): $(BIN)/%: $(SRC)/%.c
	$(CC) -o $@ $< $(LIBS) $(CFLAGS)

$(TARGETS): $(BIN)/%: $(SRC)/%.tab.c $(SRC)/%.c
	$(MV) $(subst tab.c,tab.h, $<) $(SRC)/y.tab.h
	$(CC) -o $@ $^ $(LIBS) $(CFLAGS)
	$(RM) $(SRC)/y.tab.h

$(MIDDLEFILES): $(SRC)/%.tab.c: %.y
	$(YACC) -o $@ $<

$(RESOURCES) $(SOURCES): $(SRC)/%.c: %.l 
	$(LEX) -o $@ $<

clean:
	for filename in $(PROGRAMS) $(TARGETS);do \
		if [ -e $$filename ]; then \
			$(RM) $$filename; \
		fi \
	done
	$(RM) $(SRC)/*.c $(SRC)/*.h
