#include "cvector.h"

int main() {
    cVector* v = new_cVector_with_cap(1);
    push_back(v, 1);
    push_back(v, 2);
    push_back(v, 3);
    push_back(v, 4);
    push_back(v, 6);
    push_back(v, 7);
    push_back(v, 8);
    push_back(v, 9);
    push_back(v, 10);
    push_back(v, 11);
    push_back(v, 12);
    push_back(v, 13);
    push_back(v, 14);
    push_back(v, 15);
    push_back(v, 16);
    push_back(v, 17);
    UTIL_print_cVector(v);
    pop_back(v);
    pop_back(v);
    UTIL_print_cVector(v);
    push_back(v, 16);
    UTIL_print_cVector(v);
    insert(v, at_iter(v, 4), 5);
    UTIL_print_cVector(v);
    resize_val(v, 20, 100);
    UTIL_print_cVector(v);
    resize(v, 5);
    UTIL_print_cVector(v);
    erase(v, at_iter(v, 2));
    UTIL_print_cVector(v);
    v = clear(v);
}