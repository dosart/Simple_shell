#ifndef TESTS_H
#define TESTS_H

#include "shell.h"
#include "utils.h"

#include <assert.h>

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

// =============================================
void test_search_success1();
void test_search_success2();
void test_search_success3();
void test_search_success4();

void test_search_bad1();

void test_search_error1();
void test_search_error2();
void test_search_error3();

#endif