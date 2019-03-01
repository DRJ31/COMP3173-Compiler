SOURCE = $(wildcard *.l)
PROGRAMS = $(patsubst %.l, %, $(SOURCE))
CC = gcc
LIBS = -lfl
YACC = bison -y -d

all: $(PROGRAMS)

example1: example1.c
	$(CC) -o $@ $< $(LIBS)

example2: example2.c
	$(CC) -o $@ $< $(LIBS)

example3: example3.c
	$(CC) -o $@ $< $(LIBS)

example4: example4.c y.tab.c
	$(CC) -o $@ $^ $(LIBS)

.l.c: 
	flex -o $*.c $<

y.tab.c: example4.y
	$(YACC) $<

.PHONY: clean

clean:
	for filename in $(PROGRAMS) $(wildcard *.c) $(wildcard *.h);do \
		if [ -e $$filename ]; then \
			rm $$filename; \
		fi \
	done
