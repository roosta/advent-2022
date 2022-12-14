#include <stdio.h>
#include "advent.h"
#include <ctype.h>
#include <stdlib.h>

#define MAXSTACK 52
#define WIDTH 10
#define MAXWIDTH 35

/* Globals */
int sp[MAXSTACK];
char diagram[WIDTH][MAXSTACK];
int cols[MAXWIDTH];
int maxcol = 0;
enum move { MOVE, FROM, TO };

/* Setup diagram array with spaces, aids in printing via print_diagram, reset
 * stack positions, and clear cols */
void setup() {
  for (int i = 0; i < MAXSTACK; i++)
    sp[i] = 0;
  for (int i = 0; i < MAXWIDTH; i++)
    cols[i] = 0;

  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < MAXSTACK; j++) {
      diagram[i][j] = ' ';
    }
  }
}

/* push: push f onto value stack */
void push(int col, char f) {
  if (sp[col] < MAXSTACK)
    diagram[col][sp[col]++] = f;
  else
    printf("error: stack %d full, can't push %c\n", col, f);
}

/* pop: pop and return top value from stack */
double pop(int col) {
  char prev;
  int i;
  if (sp[col] > 0) {
    sp[col]--;
    i = sp[col];
    prev = diagram[col][i];
    diagram[col][i] = ' ';
    return prev;
  } else {
    printf("error: stack %d empty\n", col);
    return 0.0;
  }
}

/* Parse column notation at the bottom of diagram */
/* Doesn't handle indexs beyond 9
 * Returns the last number registered, so we know how many columns to pop
 * from*/
int parse_cols(char line[], int idx) {
  int j = 1;
  for (int i = 0; i < length[idx]; i++) {
    if (isdigit(line[i])) {
      cols[i] = j++;
    }
  }
  return j;
}

/* Parse number as long */
long parse_n(char str[]) {
  char *endptr;
  long result = strtol(str, &endptr, 10);
  if (endptr == str) {
    printf("Failed to parse '%s'", str);
    return 0;
  } else {
    return result;
  }
}

void parse_move(char line[], int idx, long ret[]) {
  int i, j, nc;
  nc = 0;
  char str[4];
  for (i = 0, j = 0; i < length[idx]; i++) {
    while (isdigit(line[i])) {
      str[j++] = line[i++];
    }
    if (j > 0) {
      str[j] = '\0';
      j = 0;
      if (nc == 0) {
        ret[MOVE] = parse_n(str);
      } else if (nc == 1) {
        ret[FROM] = parse_n(str);
      } else if (nc == 2) {
        ret[TO] = parse_n(str);
      }
      nc++;
    }
  }
}

void transfer(int move, int from, int to) {
  if (move == 0) return;
  char ch = pop(from);
  transfer(move - 1, from, to);
  push(to, ch);
}

// print diagram
void print_diagram(void) {
  char ch;
  int max = 0;
  int j, i, idx;

  /* find tallest column */
  for (i = 0; i < maxcol; i++) {
    for (j = 0, idx = 0; j < MAXSTACK; j++) {
      if (isalpha(diagram[i][j])) {
        idx++;
        if (idx > max) max = idx;
      }
    }
  }

  /* print diagram tilted 90 degrees, so it matches input */
  for (i = max - 1; i >= 0; i--) {
    for (j = 1; j < maxcol; j++) {
      ch = diagram[j][i];
      printf("[%c]", ch);
    }
    printf("\n");
  }
  printf("\n");
}

/* Parse diagram in input data, store in global diagram array Return index for
 * remaining data */
int parse_diagram() {
  char ch;
  int idx;

  // Isolate the diagram index
  for (idx = 0; buf[idx][0] != '\n' && buf[idx][1] != '\0'; idx++)
    ;

  // parse columns, push to stack
  for (int i = idx; i >= 0; i--) {
    if (i == idx - 1)
      maxcol = parse_cols(buf[i], idx - 1); // save maxcol in global

    // Push diagram to stack
    for (int j = 0; j < length[i]; j++) {
      ch = buf[i][j];
      if (isalpha(ch) && buf[i][j - 1] == '[' && buf[i][j + 1] == ']') {
        push(cols[j], ch);
      }
    }
  }
  idx++; // skip empty line
  return idx;
}
/* After the rearrangement procedure completes, what crate ends up on top of
 * each stack? */
void part1(void) {
  char ch;
  int idx;
  long ldmove[3] = { 0, 0, 0 };

  setup();
  idx = parse_diagram();

  for (int i = idx; i < height; i++) {
    parse_move(buf[i], i, ldmove);
    for (int j = ldmove[MOVE]; j > 0; j--) {
      ch = pop(ldmove[FROM]);
      push(ldmove[TO], ch);
    }
  }

  printf("The top of the stacks in part 1 is: ");

  // Pop the top of diagram
  for (int j = 1; j < maxcol; j++) {
    ch = pop(j);
    printf("%c", ch);
  }
  printf("\n");
}

/* Stack based approach */
void part2(void) {
  char ch;
  int idx;
  long ldmove[3] = { 0, 0, 0 };

  setup();
  idx = parse_diagram();

  for (int i = idx; i < height; i++) {
    parse_move(buf[i], i, ldmove);
    transfer(ldmove[MOVE], ldmove[FROM], ldmove[TO]);
    /* print_diagram(); */
  }

  printf("The top of the stacks in part 2 is: ");

  for (int j = 1; j < 10; j++) {
    ch = pop(j);
    printf("%c", ch);
  }
  printf("\n");
}

int main() {
  readbuf(); // read in buffer
  part1();
  part2();
  return 0;
}
