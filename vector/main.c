//
//  main.c
//  vector
//
//  Created by Gurankio on 15/08/2020.
//  Copyright © 2020 Gurankio. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

#include <string.h>

int test_resize() {
    char * v = vector_create();
    for (int i = 0; i < 15; i++) vector_insert(v, i, (char)'a');
    vector_resize(v, 255);
    unsigned long length = vector_length(v);
    for (int i = 0; i < 15; i++) if (v[i] != 'a') return 0;
    for (int i = 15; i < length; i++) if (v[i] != 0) return 0; // Checks all zeros
    vector_destroy(v);
    return length == 255; // Checks length
}

int test_insert() {
    char * v = vector_create();
    for (char i = 'a'; i <= 'z'; i++) vector_insert(v, 0, i);
    for (int i = 0; i <= 'z' - 'a'; i++) if (v[i] != 'z' - i) return 0;
    vector_destroy(v);
    return 1;
}

int test_remove() {
    char * v = vector_create();
    for (char i = 'a'; i <= 'z'; i++) vector_insert(v, 0, i);
    unsigned long length = vector_length(v);
    for (int i = 0; i < 10; i++) vector_remove(v, 0);
    for (int i = 0; i <= 'z' - 'a' - 10; i++) if (v[i] != 'z' - i - 10) return 0;
    vector_destroy(v);
    return length == vector_length(v) + 10;
}

// Capacity and Length aren't copied, but are the minimum to hold the source vector.
int test_copy() {
    char * v = vector_create();
    for (char i = 'a'; i <= 'z'; i++) vector_insert(v, 0, i);
    char * t = vector_copy(v);
    for (int i = 0; i <= 'z' - 'a'; i++) if (v[i] != t[i]) return 0;
    vector_destroy(v);
    vector_destroy(t);
    return 1;
}

int test_concat() {
    long long * v = vector_create();
    for (long long i = 0; i < 15; i++) vector_insert(v, i, i);
    long long * t = vector_create();
    for (long long i = 0; i < 15; i++) vector_insert(t, i, i);
    vector_concat(t, v);
    if (vector_length(t) != 30) return 0;
    for (int i = 15; i < 30; i++) if (t[i] != t[i-15] || t[i] != v[i-15]) return 0;
    vector_destroy(v);
    vector_destroy(t);
    return 1;
}

int test_stack() {
    int * v = vector_create();
    vector_push(v, 1);
    vector_push(v, 2);
    vector_push(v, 3);
    vector_push(v, 4);
    if (vector_top(v) != 4) return 0;
    vector_pop(v);
    if (vector_top(v) != 3) return 0;
    vector_destroy(v);
    return 1;
}

int main(int argc, const char * argv[]) {
    fprintf(stdout, "Test vector_resize(): %s\n", test_resize() ? "Passed" : "Failed");
    fprintf(stdout, "Test vector_insert(): %s\n", test_insert() ? "Passed" : "Failed");
    fprintf(stdout, "Test vector_remove(): %s\n", test_remove() ? "Passed" : "Failed");
    fprintf(stdout, "Test vector_copy(): %s\n", test_copy() ? "Passed" : "Failed");
    fprintf(stdout, "Test vector_concat(): %s\n", test_concat() ? "Passed" : "Failed");
    fprintf(stdout, "Test vector_stack(): %s\n", test_stack() ? "Passed" : "Failed");
    return 0;
}

