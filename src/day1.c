#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define BUFSIZE 16
#define MAXLINE 16

int get_line(char s[]) {
  int c, i;
  for (i = 0, c = getchar(); i < BUFSIZE - 1 && c != EOF && c != '\n'; ++i, c = getchar()) {
    s[i] = c;
  }
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return i;
}

int main() {
  char buf[MAXLINE];
  long number, high;
  long result = high = 0;
  char *endptr;
  while (get_line(buf) > 0) {
    number = strtol(buf, &endptr, 10);
    result += number;
    if (endptr == buf) {
      if (result > high) high = result;
      result = 0;
      continue;
    };
  }
  printf("result: %ld\n", high);
}
