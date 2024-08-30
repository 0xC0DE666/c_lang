#include <stdio.h>

#include "lib.h"

/*
 * Exercise 1-22. Write a program to "fold" long input lines into two or more
 * shorter lines after the last non-blank character that occurs before the n-th
 * column of input. Make sure your program does something intelligent with very
 * long lines, and if there are no blanks or tabs before the specified column. D
 */

int main() {
  char str[] = "This is a sentence. It needs to be folded.";
  char buffer[1024] = {};
  
  fold(str, buffer, 10);  
  printf("before: \"%s\"\nafter: \"%s\"\n", str, buffer);
  return 0;
}
