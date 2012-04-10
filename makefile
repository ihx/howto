CFLAGS = -ansi -pedantic -Wall -Werror -o3
CFLAGS += -I$(IH) -L$(IH)
LDFLAGS = -lih

SOURCES = $(shell ls *.c)
PROGRAMS = $(SOURCES:.c=)

tests: $(PROGRAMS)

clean:
	rm -f *~ .*~ $(PROGRAMS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
