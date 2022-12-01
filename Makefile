# Create target directory
dir_guard=@mkdir -p $(@D)

bin/%.out: src/%.c
	$(dir_guard)
	@gcc -g -Wall -Wextra -O0 -std=c99 -pedantic -lm $< -o $@
