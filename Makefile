CC=gcc
CFLAGS=-g -Wall -Wextra -O0 -std=c99 -pedantic
dir_guard=@mkdir -p $(@D)

bin/%: %.o utils.o
	$(dir_guard)
	$(CC) $(CFLAGS) $^ -o $@

%.o: src/%.c src/advent.h
	$(CC) $(CFLAGS) -c $< -o $@
