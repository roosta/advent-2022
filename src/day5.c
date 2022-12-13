#include <stdio.h>
#include "advent.h"
#include <ctype.h>
#include <stdlib.h>

#define MAXSTACK 52
#define WIDTH 10
#define MAXWIDTH 35

// Globals
int sp[MAXSTACK] = { 0 };
char diagram[WIDTH][MAXSTACK];
int cols[MAXWIDTH] = { 0 };


void init() {
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

void parse_move(char line[], int idx) {
  long move, from, to;
  int i, j, nc;
  char ch;
  move = from = to = 0;
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
        move = parse_n(str);
      } else if (nc == 1) {
        from = parse_n(str);
      } else if (nc == 2) {
        to = parse_n(str);
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
  for (int i = MAXSTACK - 1; i >= 0; i--) {
    for (int j = 1; j < WIDTH; j++) {
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

  /* pdiagram(); */
  for (; i < height; i++) {
    parse_move(buf[i], i);
  }

  char ch;
  for (int j = 1; j < 10; j++) {
    ch = pop(j);
    printf("%c", ch);
  }
  printf("\n");
  /* pdiagram(); */
}

int main() {
  readbuf(); // read in buffer

  init();
  part1();
  return 0;
}
