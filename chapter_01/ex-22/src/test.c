#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "lib.h"

// ####################
// string_length
// ####################
Test(string_length, pass) {
  int result = string_length("");
  cr_assert_eq(result, 0);

  result = string_length("a");
  cr_assert_eq(result, 1);

  result = string_length("abc");
  cr_assert_eq(result, 3);
}

// ####################
// space
// ####################
Test(space, yes) {
  char c = ' ';
  cr_assert_eq(space(c), true);
}

Test(space, no) {
  char c = '\t';
  cr_assert_eq(space(c), false);
}

// ####################
// tab
// ####################
Test(tab, yes) {
  char c = '\t';
  cr_assert_eq(tab(c), true);
}

Test(tab, no) {
  char c = ' ';
  cr_assert_eq(tab(c), false);
}

// ####################
// blank
// ####################
Test(blank, yes) {
  char c = ' ';
  cr_assert_eq(blank(c), true);

  c = '\t';
  cr_assert_eq(blank(c), true);
}

Test(blank, no) {
  char c = 'a';
  cr_assert_eq(blank(c), false);

  c = 'z';
  cr_assert_eq(blank(c), false);
}

// ####################
// blank_sequence
// ####################
Test(blank_sequence, yes) {
  char prev = 'a', cur = ' ';
  cr_assert_eq(blank_sequence(prev, cur), true);

  prev = '\t', cur = ' ';
  cr_assert_eq(blank_sequence(prev, cur), true);
}

Test(blank_sequence, no) {
  char prev, cur = 'a';
  cr_assert_eq(blank_sequence(prev, cur), false);

  prev = ' ', cur = 'a';
  cr_assert_eq(blank_sequence(prev, cur), false);

  prev = 'a', cur = 'b';
  cr_assert_eq(blank_sequence(prev, cur), false);
}

// ####################
// fold
// ####################
Test(fold, _1) {
  char str[] = "This is a sentence. It needs to be folded.";
  char buffer[1024] = {};
  
  fold(str, buffer, 10);

  char expected[] = "This is a\nsentence.\nIt needs\nto be\nfolded.";
  cr_assert_eq(strcmp(buffer, expected), 0);
}

Test(fold, _2) {
  char str[] = "This is a realy long sentence... You Understand? So, it needs to be folded into lines 20 chars long at most. Now do, bitch! Yeeeeeeeaaaaaah!";
  char buffer[1024] = {};
  
  fold(str, buffer, 15);

  char expected[] = "This is a realy\nlong\nsentence... You\nUnderstand? So,\nit needs to be\nfolded into\nlines 20 chars\nlong at most.\nNow do, bitch!\nYeeeeeeeaaaaaah!";
  cr_assert_eq(strcmp(buffer, expected), 0);
}

Test(fold, _3) {
  char str[] = "This is a realy long sentence... You Understand? So, it needs to be folded into lines 20 chars long at most. Now do, bitch! Yeeeeeeeaaaaaah!";
  char buffer[1024] = {};
  
  fold(str, buffer, 30);

  char expected[] = "This is a realy long\nsentence... You Understand?\nSo, it needs to be folded into\nlines 20 chars long at most.\nNow do, bitch!\nYeeeeeeeaaaaaah!";
  cr_assert_eq(strcmp(buffer, expected), 0);
}
