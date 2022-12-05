#include <stdio.h>
#include <ctype.h>
#include "advent.h"

int get_pri(char ch) {
  return isupper(ch) ? ch - 38 : ch - 96;
}

char compare(char line[], int length) {
  for (int i = 0; i < length / 2; i++) {
    for (int j = length / 2; j < length; j++) {
      if (line[i] == line[j])
        return line[i];
    }
  }
  return 0;
}

int calc(void) {
  int match, result;
  result = 0;
  for (int i = 0; i < height; i++) {
    if ((match = compare(buf[i], length[i]))) {
      result += get_pri(match);
    }
  }
  return result;
}

int main() {
  readbuf(); // read in buffer
  printf("Sum of matches is %d\n", calc());
  return 0;
}
