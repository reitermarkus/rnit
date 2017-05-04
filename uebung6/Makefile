PROGRAM = HAbwA

OBJ = $(patsubst %.c, %.o, $(wildcard *.c */*.c))

CFLAGS = -g -O2 -Wall -Werror -Wextra -std=c11 "-I$(CURDIR)"

$(PROGRAM): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: all
all: $(PROGRAM)

.PHONY: clean
clean:
	$(RM) $(PROGRAM)

.PHONY: run
run: $(PROGRAM)
	./$(PROGRAM) cities.txt
