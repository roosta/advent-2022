#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define BUFSIZE 16
#define MAXLEN 2500

char buf[MAXLEN][BUFSIZE];
int length[MAXLEN];
int height;

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

void mostcal(void) {
  long number, high;
  long result = high = 0;
  char *endptr;
  char *str;
  for (int i = 0; i < height; i++) {
    str = buf[i];
    number = strtol(str, &endptr, 10);
    result += number;
    if (endptr == str) {
      if (result > high) high = result;
      result = 0;
      continue;
    };
  }
  printf("most calories: %ld\n", high);
}

int main() {
  for (height = 0; (length[height] = get_line(buf[height])) > 0; height++)
    ;

  mostcal();
}
