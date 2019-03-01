PROGRAMS = example1 example2 example3
SOURCES = $(patsubst %, %.c, $(PROGRAMS))
TARGETS = example4 example5
MIDDLEFILE = $(patsubst %, %.tab.c, $(TARGETS))
RESOURCES = $(patsubst %, %.c, $(TARGETS))

CC = gcc
LIBS = -lfl 
YACC = bison -y -d
RM = rm -f
LEX = flex
MV = mv -f
CFLAGS = -w

all: $(PROGRAMS) $(TARGETS)

$(PROGRAMS): %: %.c
	$(CC) -o $@ $< $(LIBS)

$(TARGETS): %: %.tab.c %.c
	$(MV) $@.tab.h y.tab.h
	$(CC) -o $@ $^ $(CFLAGS)
	$(RM) y.tab.h

$(MIDDLEFILE): %.tab.c: %.y
	$(YACC) -o $@ $<

$(RESOURCES) $(SOURCES): %.c: %.l 
	$(LEX) -o $@ $<

.PHONY: clean

clean:
	for filename in $(PROGRAMS) $(TARGETS) $(wildcard *.c) $(wildcard *.h);do \
		if [ -e $$filename ]; then \
			$(RM) $$filename; \
		fi \
	done

