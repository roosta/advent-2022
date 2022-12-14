#include <stdio.h>
#include "advent.h"
#include <ctype.h>

#define P1Q 4
#define P2Q 14

char str[MAXLEN];

/* Shift que array to the left */
int shift(char ch, char que[], int max) {
  for (int i = 0; i < max - 1; i++) {
    que[i] = que[i + 1];
  }
  que[max - 1] = ch;
  return 1;
}

/* Check for unique characters in que, if the que isn't full return false */
int uniq(char que[], int max) {
  if (que[0] == 0) return 0;
  for (int i = 0; i < max - 1; i++) {
    for (int j = i + 1; j < max; j++) {
      if (que[i] == que[j])
        return 0;
    }
  }
  return 1;
}

/* output que, useful in debugging */
void print_que(char que[], int max) {
  for (int i = 0; i < max; i++) {
    int alpha = isalpha(que[i]);
    printf("[%c]", alpha ? que[i] : ' ');
  }
  printf("\n");
}

void readin(void) {
  int c, i;
  c = getchar();
  for (i = 0; i < MAXLEN - 1 && c != EOF; ++i, c = getchar())
    str[i] = c;

  str[i] = '\0';
}

/* How many characters need to be processed before the first start-of-message
 * marker is detected? */
void part2(void) {
  char ch;
  char que[P2Q] = { 0 };
  int idx, i;
  i = idx = 0;
  while ((ch = str[i++]) != '\0') {
    idx += shift(ch, que, P2Q);
    if (uniq(que, P2Q)) break;

    /* print_que(que, P1Q); */

  }
  printf("PART 2: %d\n", idx);
}

/* How many characters need to be processed before the first start-of-packet
 * marker is detected? */
void part1(void) {
  char ch;
  char que[P1Q] = { 0 };
  int idx, i;
  i = idx = 0;
  while ((ch = str[i++]) != '\0') {
    idx += shift(ch, que, P1Q);
    if (uniq(que, P1Q)) break;

    /* print_que(que, P1Q); */

  }
  printf("PART 1: %d\n", idx);
}

int main() {
  readin();
  part1();
  part2();
  return 0;
}
