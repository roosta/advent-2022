#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "advent.h"
#include <string.h>


// Parsed input
long l1, l2, r1, r2;

// Parse a variable length number from a given token (strtok)
long parse_n(char* token) {
  int i = 0;
  char snum[BUFSIZE];
  char *endptr;
  while (isdigit(token[i])) {
    snum[i] = token[i];
    i++;
  }
  snum[i] = '\0';
  return strtol(snum, &endptr, 10);
}

// Parse a line of input, storing result in l1, l2, r1, r2
void parse_line(char line[], int idx) {
  char s[length[idx]];
  char* ltok;
  char* rtok;
  strcopy(s, line);
  ltok = strtok(s, ",");
  rtok = strtok(NULL, ",");

  // left
  l1 = parse_n(strtok(ltok, "-"));
  l2 = parse_n(strtok(NULL, "-"));

  // right
  r1 = parse_n(strtok(rtok, "-"));
  r2 = parse_n(strtok(NULL, "-"));
}

/* In how many assignment pairs does one range fully contain the other? */
void part1() {
  int result = 0;

  for (int i = 0; i < height; i++) {
    parse_line(buf[i], i);
    if ((r1 >= l1 && r2 <= l2) || (l1 >= r1 && l2 <= r2)) {
      result++;
    }
  }
  printf("Part one: number of overlapping pairs %d\n", result);
}

int main() {
  readbuf(); // read in buffer
  part1();
  return 0;
}
