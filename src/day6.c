#include <stdio.h>
#include "advent.h"
#include <ctype.h>

#define QSIZE 4

char que[QSIZE] = { 0 };
int idx = 0;

/* Shift que array to the left */
void shift(char ch) {
  for (int i = 0; i < QSIZE - 1; i++) {
    que[i] = que[i + 1];
  }
  que[QSIZE - 1] = ch;
  idx++;
}

/* Check for unique characters in que, if the que isn't full return false */
int uniq(void) {
  if (que[0] == 0) return 0;
  for (int i = 0; i < QSIZE - 1; i++) {
    for (int j = i + 1; j < QSIZE; j++) {
      if (que[i] == que[j])
        return 0;
    }
  }
  return 1;
}

/* output que, useful in debugging */
void print_que() {
  for (int i = 0; i < QSIZE; i++) {
    int alpha = isalpha(que[i]);
    printf("[%c]", alpha ? que[i] : ' ');
  }
  printf("\n");
}

/* How many characters need to be processed before the first start-of-packet
 * marker is detected? */
void part1(void) {
  char ch;
  while ((ch = getchar()) != EOF) {
    shift(ch);
    if (uniq()) break;

    /* print_que(); */

  }
  printf("Result: %d\n", idx);
}

int main() {
  part1();
  return 0;
}
