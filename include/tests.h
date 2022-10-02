#ifndef TESTS_H
#define TESTS_H

#include <assert.h>
#include "shell.h"

void test_run_all();

void test_split_good_string1();
void test_split_good_string2();

void test_split_string_with_spaces1();
void test_split_string_with_spaces2();

void test_split_string_with_other_symbols1();
void test_split_string_with_other_symbols2();
void test_split_string_with_other_symbols3();

void test_split_empty_string1();
void test_split_empty_string2();

#endif