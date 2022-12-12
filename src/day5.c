#include <stdio.h>
#include "advent.h"
#include <ctype.h>
#include <stdlib.h>

#define MAXSTACK 10

// Globals
int sp[MAXSTACK] = { 0 };
char diagram[MAXSTACK][MAXSTACK];
int cols[MAXSTACK] = { 0 };


void init() {
  for (int i = 0; i < MAXSTACK; i++) {
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

// Parse column notation at the bottom of diagram
// Doesn't handle indexs beyond 9
void parse_cols(char line[], int idx) {
  int j = 1;
  for (int i = 0; i < length[idx]; i++) {
    if (isdigit(line[i])) {
      cols[i] = j++;
    }
  }
}

// Parse diagram in input data, store in global diagram array
void parse_head(int max) {
  char ch;
  for (int i = max; i >= 0; i--) {
    if (i == max - 1)
      parse_cols(buf[i], max - 1);

    for (int j = 0; j < length[i]; j++) {
      ch = buf[i][j];
      if (isalpha(ch) && buf[i][j - 1] == '[' && buf[i][j + 1] == ']') {
        push(cols[j], ch);
      }
    }
  }
}

long parse_n(char cn) {
  char *endptr;
  char str[2] = { cn, '\0' };
  long result = strtol(str, &endptr, 10);
  if (endptr == str) {
    printf("Failed to parse '%c'", cn);
    return 0;
  } else {
    return result;
  }
}

// Parse a move line, doesn't handle indexes above 9
void parse_move(char line[], int idx) {
  int nc = 0;
  long move, from, to;
  char ch;
  move = from = to = 0;

  for (int i = 0; i < length[idx]; i++) {
    ch = line[i];
    if (isdigit(ch)) {
      if (nc == 0) {
        move = parse_n(ch);
      } else if (nc == 1) {
        from = parse_n(ch);
      } else if (nc == 2) {
        to = parse_n(ch);
      }
      nc++;
    }
  }

  for (int i = move; i > 0; i--) {
    ch = pop(from);
    push(to, ch);
  }
}

// print diagram
void pdiagram(void) {
  char ch;
  for (int i = 5; i >= 0; i--) {
    for (int j = 0; j < 5; j++) {
      ch = diagram[j][i];
      printf("[%c]", ch);
    }
    printf("\n");
  }
  printf("\n");
}

void part1(void) {
  int i;

  // Isolate the diagram
  for (i = 0; buf[i][0] != '\n' && buf[i][1] != '\0'; i++)
    ;
  parse_head(i);
  i++; // skip empty line

  pdiagram();
  for (; i < height; i++) {
    parse_move(buf[i], i);
  }

  /* printf("After\n"); */
  pdiagram();
}

int main() {
  readbuf(); // read in buffer

  init();
  part1();
  return 0;
}
