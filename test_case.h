#ifndef TEST_CASE_H
#define TEST_CASE_H
#include "nbtrees.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

void run_test_case();

// Fungsi untuk mencetak header test
void print_test_header(const char* test_name);

// Fungsi untuk mencetak hasil test
void test_result(const char* test_name, bool success);

// Test untuk create_tree dan is_empty_tree
void test_create_tree();

// Test untuk insert_node
void test_insert_node();

// Test sederhana
void test_simple_tree();


#endif // TEST_CASE_H
