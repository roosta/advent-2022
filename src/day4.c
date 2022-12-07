#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "advent.h"
#include <string.h>


long parse(char* token) {
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

void part1(void) {
  long l1, l2, r1, r2;
  int result = 0;
  for (int i = 0; i < height; i++) {
    char s[length[i]];
    char* ltok;
    char* rtok;
    strcopy(s, buf[i]);
    ltok = strtok(s, ",");
    rtok = strtok(NULL, ",");

    l1 = parse(strtok(ltok, "-"));
    l2 = parse(strtok(NULL, "-"));

    r1 = parse(strtok(rtok, "-"));
    r2 = parse(strtok(NULL, "-"));

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
