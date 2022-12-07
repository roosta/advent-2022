#include <stdio.h>
#include <ctype.h>
#include "advent.h"

// Return character priority
int get_pri(char ch) {
  return isupper(ch) ? ch - 38 : ch - 96;
}

// Compare two halves of a string for matching char
char compare(char line[], int length) {
  for (int i = 0; i < length / 2; i++) {
    for (int j = length / 2; j < length; j++) {
      if (line[i] == line[j])
        return line[i];
    }
  }
  return 0;
}

// Looks for target in a given line[idx]
int seek(char target, int idx) {
  char active;
  for (int i = 0; i < length[idx]; i++) {
    active = buf[idx][i];
    if (active == target) return active;
  }
  return 0;
}

// Checks each char in first position against two more lines
int compare3(int i) {
  for (int j = 0; j < length[i]; j++) {
    if (seek(buf[i][j], i + 1) && seek(buf[i][j], i + 2)) {
      return buf[i][j];
    }
  }
  return 0;
}

// Sum of badges priority
int part2(void) {
  int match, result;
  result = 0;
  for (int i = 0; i < height; i += 3) {
    if ((match = compare3(i))) {
      result += get_pri(match);
    }
  }
  return result;
}

// Sum of matching item in line
int part1(void) {
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
  printf("Part one: sum of matches is %d\n", part1());
  printf("Part two: sum of badges is %d\n", part2());
  return 0;
}
