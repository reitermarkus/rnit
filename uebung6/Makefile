SERVER = HAbwA
CLIENT = Heiner

PROGRAM = $(SERVER) $(CLIENT)

OBJ = $(patsubst %.c, %.o, $(filter-out $(addsuffix .c, $(PROGRAM)), $(wildcard *.c */*.c)))

CFLAGS = -g -O2 -Wall -Werror -Wextra -std=c11 "-I$(CURDIR)" -D_BSD_SOURCE -D_XOPEN_SOURCE=600


$(PROGRAM): $(OBJ)
	$(CC) -o $@ $@.c $^ $(CFLAGS)


.DEFAULT_GOAL = all
all: $(PROGRAM)

default: all

.PHONY: clean
clean:
	$(RM) $(OBJ)
	$(RM) $(PROGRAM)

.PHONY: run
run: $(PROGRAM)
	./test.sh $(SERVER) $(CLIENT)
