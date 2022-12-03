#include <stdio.h>
#include <stdlib.h>
#include "advent.h"

enum point {
  LOSE = 0,
  DRAW = 3,
  WIN = 6
};

enum move { ROCK, PAPER, SCISSOR };

char lchars[3] = { 'A', 'B', 'C' };
char rchars[3] = { 'X', 'Y', 'Z' };

// Assign rock/paper/scissor given an input array of values and a target char.
int assign(char vals[], char ch) {
  if (vals[0] == ch) {
    return ROCK;
  } else if (vals[1] == ch) {
    return PAPER;
  } else {
    return SCISSOR;
  }
}

// Translate rchars to point values
int trans(char ch) {
  if (rchars[0] == ch) {
    return LOSE;
  } else if (rchars[1] == ch) {
    return DRAW;
  } else {
    return WIN;
  }
}

// Tally score
// Use bitwise opeations to determine which move should be played based on
// which result we want (rch) + the point value for the move picked
// returning score
int vs_b(char lch, char rch) {
  enum move op;
  enum move me;
  enum point p;
  op = assign(lchars, lch);
  p = trans(rch);
  if (p == DRAW) {
    me = op;
  } else if (p == WIN) {
    me = ((op << 2) + 1) % 3;
  } else {
    me = (op + 2) % 3;
  };
  return p + me + 1;
}

// Part one
// Determine score by comparing moves played (move enum)
// Returning a score value based on who won plus the movement point
int vs_a(char lch, char rch) {
  enum move op;
  enum move me;
  int movep, result;
  op = assign(lchars, lch);
  me = assign(rchars, rch);
  movep = me + 1;
  if (me == op) {
    result = DRAW;
  } else if (op - (me | 1 << 2) % 3) {
    result = WIN;
  } else {
    result = LOSE;
  }
  return result + movep;
}

// Move through input
void total(void) {
  char lch, rch;
  int result_a, result_b;
  result_a = result_b = 0;
  for (int i = 0; i < height; i++) {
    lch = buf[i][0];
    rch = buf[i][2];
    result_a += vs_a(lch, rch);
    int val = vs_b(lch, rch);
    result_b += val;
  }
  printf("Score total for part 1 is %d\n", result_a);
  printf("Score total for part 2 is %d\n", result_b);
}

int main() {
  readbuf(); // read in buffer
  total();
  return 0;
}
