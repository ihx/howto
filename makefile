CFLAGS = -ansi -pedantic -Wall -Werror -o3 -D_BSD_SOURCE
CFLAGS += -I$(IH) -L$(IH)
CFLAGS += -g
LDFLAGS = -lih

SOURCES = $(shell ls *.c)
PROGRAMS = $(SOURCES:.c=)

tests: $(PROGRAMS)

clean:
	rm -f *~ .*~ .etags $(PROGRAMS)

stats:
	wc -l *.c

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
