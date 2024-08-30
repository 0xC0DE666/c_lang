#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include "lib.h"

int read_line(char buffer[], int size) {
  int i, c;
  for (i = 0; i < size - 1 && (c = getchar()) != '\n' && c != EOF; ++i) {
    buffer[i] = c;
  }
  buffer[i] = '\0';
  return i;
}

int string_length(char buffer[]) {
  int i = 0;
  while (buffer[i]) {
    ++i;
  }
  return i;
}

bool space(char c) {
  return c == ' ';
}

bool tab(char c) {
  return c == '\t';
}

bool blank(char c) {
  return space(c) || tab(c);
}

bool blank_sequence(char prev, char cur) {
  int one = !blank(prev) && blank(cur);
  int two = blank(prev) && blank(cur);
  return one || two;
}

void fold(char from[], char to[], int max_line_length) {
  int idx = 0, c, count = 0;
  int last_blank_idx;

  while(c = from[idx]) {
    if (blank(c) && count <= max_line_length) {
      last_blank_idx = idx;
    }
    if (count == max_line_length + 1) {
      // printf("last_blank_idx = %d idx = %d c = '%c'\n", last_blank_idx, idx, c);
      if (blank(c)) {
        // printf("\nblank fold -> %d\n", idx);
        c = '\n';
        count = 0;
      }
      else {
        // printf("\nlast blank fold -> %d %d\n", last_blank_idx, idx);
        // printf("cut on %d\n", last_blank_idx);
        to[last_blank_idx] = '\n';
        count = idx - last_blank_idx;
      }
    }

    to[idx] = c;
    ++idx;
    ++count;
  }
  to[idx] = '\0';
  // debug(to);
}

void debug(char buffer[]) {
  int c, idx = 0, count = 0, length = string_length(buffer);
  while (idx < length) {
    c = buffer[idx];

    if (c != '\n')
      printf("%c", c);

    if (c == '\n' || idx == length - 1) {
      printf("<<%d\n", count);
      count = 0;
    }
    ++count;
    ++idx;
  }
}
