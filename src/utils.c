#include <stdio.h>
#include "advent.h"

char buf[MAXLEN][BUFSIZE];
int length[MAXLEN];
int height;

// Read line by line from stdin
int get_line(char s[]) {
  int c, i;
  c = getchar();
  for (i = 0; i < BUFSIZE - 1 && c != EOF && c != '\n'; ++i, c = getchar()) {
    s[i] = c;
  }
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return i;
}

// Reads standard in into buffer, storing total height and length of each line
void readbuf(void) {
  for (height = 0; (length[height] = get_line(buf[height])) > 0; height++)
    ;
}

void printb(unsigned int number) {
  printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(number));
  printf("\n");
}

void strcopy(char to[], char from[]) {
   int i;
   i = 0;
   while ((to[i] = from[i]) != '\0')
      ++i;
}
