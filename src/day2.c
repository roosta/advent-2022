#include <stdio.h>
#include <stdlib.h>
#include "advent.h"

enum points {
  LOSE = 0,
  DRAW = 3,
  WIN = 6
};

enum move { ROCK, PAPER, SCISSOR };

char lchar[3] = { 'A', 'B', 'C' };
char rchar[3] = { 'X', 'Y', 'Z' };

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

// Chech who wins for a given row of moves
int vs(char lch, char rch) {
  enum move op;
  enum move me;
  int movep, result;
  op = assign(lchar, lch);
  me = assign(rchar, rch);
  movep = me + 1; // move point value
  if (me == op) {
    result = DRAW;
  } else if ((op | 0 << 2) - (me | 1 << 2) % 3) {
    result = WIN;
  } else {
    result = LOSE;
  }
  return result + movep;
}

// Move through input
void total(void) {
  char lch, rch;
  int result = 0;
  for (int i = 0; i < height; i++) {
    lch = buf[i][0];
    rch = buf[i][2];
    result += vs(lch, rch);
  }
  printf("Score total is %d\n", result);
}

int main() {
  readbuf(); // read in buffer
  total();
  return 0;
}
