#include <stdio.h>
#include <stdlib.h>
#include "advent.h"

void mostcal(void) {
  long number, high;
  long result = high = 0;
  char *endptr;
  for (int i = 0; i < height; i++) {
    number = strtol(buf[i], &endptr, 10);
    result += number;
    if (endptr == buf[i]) {
      if (result > high) high = result;
      result = 0;
      continue;
    };
  }
  printf("most calories: %ld\n", high);
}

void top3(void) {
  long number;
  long result = 0;
  long top[3] = { 0, 0, 0 };
  char *endptr;
  for (int i = 0; i <= height; i++) {
    number = strtol(buf[i], &endptr, 10);
    result += number;
    if (endptr == buf[i]) {
      if (result > top[0]) {
        top[2] = top[1];
        top[1] = top[0];
        top[0] = result;
      } else if (result > top[1] && result != top[0]) {
        top[2] = top[1];
        top[1] = result;
      } else if (result > top[2] && result != top[1]) {
        top[2] = result;
      }
      result = 0;
    };
  }
  result = 0;
  for (int i = 0; i < 3; i++) {
    result += top[i];
  }
  printf("sum of top 3 elves: %ld\n", result);
}

int main() {

  // Read buffer
  readbuf();

  // Solutions
  mostcal();
  top3();

  return 0;
}
