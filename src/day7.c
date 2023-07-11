#include <stdio.h>
#include "advent.h"
#include <string.h>
/* #include <ctype.h> */
/* #include <stdlib.h> */

#define MAXCMD 24
#define MAXPATH 16

/* next free stack position */
int sp = 0;

/* stack for paths */
char path[MAXCMD][MAXPATH];

enum Command { ERR, CD, LS };

/* push: push f onto value stack */
void push(char f[]) {
  if (sp < MAXCMD)
    strcopy(path[sp++], f);
  else
    printf("error: stack full, can't push %s\n", f);
}

/* pop: pop and return top value from stack */
void pop(char to[]) {
  if (sp > 0) {
    strcopy(to, path[--sp]);
  }
  else {
    printf("error: stack empty\n");
  }
}

/* look at top element of stack without popping it */
void peek(char to[]) {
  if (sp > 0) {
    strcopy(to, path[sp]);
  } else {
    printf("error: stack empty\n");
  }
}

int parse_cmd(char line[], int idx) {
  char cmd[MAXCMD];
  char pt[MAXPATH];
  int i = 2;
  int j = 0;
  for (; i < 4; i++, j++)
    cmd[j] = line[i];
  cmd[j] = '\0';

  if (strcmp(cmd, "ls") == 0)
    return LS;

  if (strcmp(cmd, "cd") == 0) {
    i++; // skip space
    for (j = 0; line[i] != '\n' && line[i] != '\0'; i++, j++)
      pt[j] = line[i];
    pt[j] = '\0';
    if (strcmp(pt, "..") == 0) {
      char r[MAXPATH];
      pop(r);
    } else {
      push(pt);
    }
    return CD;
  }
  return ERR;
}

void printerr(char line[]) {
  printf("Error parsing command \"");
  for (int i = 0; line[i] != '\n'; i++) {
    putchar(line[i]);
  }
  printf("\"\n");
}

void part1(void) {
  int cmd;
  for (int i = 0; i < height; i++) {
    if (buf[i][0] == '$') {
      cmd = parse_cmd(buf[i], i);
      if (cmd == ERR)
        printerr(buf[i]);
      if (cmd == LS) {

      }
    }
  }
  /* char result[MAXPATH]; */
  /* while (sp > 0) { */
  /*   pop(result); */
  /*   printf("{%s}\n", result); */
  /* } */
}

int main() {
  readbuf(); // read in buffer
  part1();
  return 0;
}
