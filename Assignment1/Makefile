SOURCE = $(wildcard *.l)
PROGRAMS = $(patsubst %.l, %, $(SOURCE))

%: %.c
	gcc -o $* $< -lfl

.l.c:
	flex -o $*.c $<

all: $(PROGRAMS)

.PHONY: clean

clean:
	for filename in $(PROGRAMS) $(wildcard *.c);do \
		if [ -e $$filename ]; then \
			rm $$filename; \
		fi \
	done
