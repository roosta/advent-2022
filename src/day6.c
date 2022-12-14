#include <stdio.h>
#include "advent.h"
#include <ctype.h>

#define QSIZE 4

char que[QSIZE] = { 0 };

void push(char ch) {
  for (int i = 0; i < QSIZE - 1; i++) {
    que[i] = que[i + 1];
  }
  que[QSIZE - 1] = ch;
}

void part1() {
  char ch;
  while ((ch = getchar()) != EOF) {
    push(ch);
    for (int i = 0; i < QSIZE; i++) {
      int alpha = isalpha(que[i]);
      printf("[%c]", alpha ? que[i] : ' ');
    }
    printf("\n");
  }
}

int main() {
  part1();
  return 0;
}
