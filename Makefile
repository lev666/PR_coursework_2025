CC=gcc
CFLAGS= -c -Wall -Wextra -Werror -g -MMD -MP
LDFLAGS=
SOURCES=$(wildcard src/*.c)
OBJ=$(SOURCES:.c=.o)
DEPENDS = $(OBJ:.o=.d)
EXEC=cw

.PHONY: all clean

all: $(SOURCES) $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

src/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) $(EXEC) $(DEPENDS)

-include $(DEPENDS)