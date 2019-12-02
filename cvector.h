/*

Name :        cVector
Author :      Soham Kar
License :     GNU General Public License
Description : A lightweight implementation of the C++ STL vector for integers

*/

#ifndef CVECTOR_H_
#define CVECTOR_H_

#define DEFAULT_CAPACITY 4
#define GROWTH_FACTOR 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _cVector {
    int* m_data;
    int m_size;
    int m_capacity;
} cVector;

// utility functions
int UTIL_get_new_cap(int capacity);
cVector* UTIL_allocate(int capacity);
cVector* UTIL_reallocate(cVector* v, int new_capacity);
void UTIL_print_cVector(cVector* v);
void UTIL_debug_cVector(cVector* v);
// capacity functions
int size(cVector* v);
int capacity(cVector* v);
bool empty(cVector* v);
void resize(cVector* v, int n);
void resize_val(cVector* v, int n, int val);
void reserve(cVector* v, int n);
// iterators
int* begin(cVector* v);
int* end(cVector* v);
int* at_iter(cVector* v, int n);
// element access functions
int at(cVector* v, int n);
int front(cVector* v);
int back(cVector* v);
int* data(cVector* v);
// modifiers
int* insert(cVector* v, int* pos, int val);
int* push_back(cVector* v, int val);
void pop_back(cVector* v);
cVector* clear(cVector* v);
// constructors
cVector* new_cVector();
cVector* new_cVector_with_cap(int cap);

int UTIL_get_new_cap(int capacity) {
    int new_cap = 1;
    while (new_cap < capacity) {
        new_cap = (int)(new_cap * GROWTH_FACTOR);
    }
    return new_cap;
}

cVector* UTIL_allocate(int capacity) {
    cVector* v = (cVector*)malloc(sizeof(cVector));
    v->m_size = 0;
    v->m_capacity = capacity;
    v->m_data = (int*)calloc(v->m_capacity, sizeof(int));
    if (v->m_data == NULL) {
        free(v);
        return NULL;
    }
    return v;
}

cVector* UTIL_reallocate(cVector* v, int new_capacity) {
    v->m_capacity = new_capacity;
    v->m_data = (int*)realloc(v->m_data, v->m_capacity * sizeof(int));
    return v;
}

void UTIL_print_cVector(cVector* v) {
    for (int* i = begin(v); i < end(v); i++) {
        printf("%d ", *i);
    }
    printf("\n");
}

void UTIL_debug_cVector(cVector* v) {
    printf("Size: %d\n", v->m_size);
    printf("Capacity: %d\n", v->m_capacity);
    printf("Data pointer: %p\n", v->m_data);
}

int size(cVector* v) { return v->m_size; }

int capacity(cVector* v) { return v->m_capacity; }

bool empty(cVector* v) { return (v->m_size == 0 ? true : false); }

int* begin(cVector* v) { return v->m_data; }

int* end(cVector* v) { return (v->m_data + v->m_size); }

int at(cVector* v, int n) {
    if (n < 0 || n > v->m_size - 1) {
        fprintf(stderr, "ERROR: Index Out Of Bounds\n");
        return -1;
    } else {
        return *(v->m_data + n);
    }
}

int* at_iter(cVector* v, int n) {
    if (n < 0 || n > v->m_size - 1) {
        fprintf(stderr, "ERROR: Index Out Of Bounds\n");
        return NULL;
    } else {
        return (v->m_data + n);
    }
}

int front(cVector* v) { return *(v->m_data); }

int back(cVector* v) { return *(v->m_data + v->m_size); }

int* data(cVector* v) { return v->m_data; }

cVector* new_cVector() {
    return UTIL_allocate(UTIL_get_new_cap(DEFAULT_CAPACITY));
}

cVector* new_cVector_with_cap(int cap) {
    if (cap > 0)
        return UTIL_allocate(UTIL_get_new_cap(cap));
    else {
        fprintf(stderr, "ERROR: Capacity must be 1 or greater\n");
        return NULL;
    }
}

cVector* new_cVector_with_cap_val(int cap, int val) {
    if (cap > 0) {
        cVector* v = UTIL_allocate(UTIL_get_new_cap(cap));
        for (int* i = begin(v); i < (begin(v) + cap); i++) {
            *(i) = val;
        }
        return v;
    } else {
        fprintf(stderr, "ERROR: Capacity must be 1 or greater\n");
        return NULL;
    }
}

int* insert(cVector* v, int* pos, int val) {
    if (pos >= begin(v) && pos <= end(v)) {
        int pos_dist = (pos - begin(v));
        v->m_size++;
        if (v->m_size > v->m_capacity) {
            v = UTIL_reallocate(v, UTIL_get_new_cap(v->m_capacity + 1));
        }
        pos = begin(v) + pos_dist;
        for (int* i = (end(v) - 1); i > pos; i--) {
            *(i) = *(i - 1);
        }
        *(pos) = val;
        return pos;
    } else {
        fprintf(stderr, "ERROR: Iterator Out Of Bounds\n");
        return NULL;
    }
}

int* push_back(cVector* v, int val) { return insert(v, end(v), val); }

void pop_back(cVector* v) {
    if (!empty(v)) {
        *(at_iter(v, size(v) - 1)) = 0;
        v->m_size--;
    }
}

void resize(cVector* v, int n) {
    if (n > capacity(v)) {
        v = UTIL_reallocate(v, UTIL_get_new_cap(n));
        for (int* i = end(v); i < (begin(v) + n); i++) {
            *(i) = 0;
        }
        v->m_size = n;
    } else if (n > size(v)) {
        for (int* i = end(v); i < (begin(v) + n); i++) {
            *(i) = 0;
        }
        v->m_size = n;
    } else if (n < size(v)) {
        for (int* i = (begin(v) + n); i < end(v); i++) {
            *(i) = 0;
        }
        v->m_size = n;
    } else if (n == 0) {
        int cap = capacity(v);
        v = clear(v);
        v = UTIL_allocate(cap);
    } else {
        fprintf(stderr, "ERROR: Cannot resize\n");
    }
}

void resize_val(cVector* v, int n, int val) {
    if (n > capacity(v)) {
        v = UTIL_reallocate(v, UTIL_get_new_cap(n));
        for (int* i = end(v); i < (begin(v) + n); i++) {
            *(i) = val;
        }
        v->m_size = n;
    } else if (n > size(v)) {
        for (int* i = end(v); i < (begin(v) + n); i++) {
            *(i) = val;
        }
        v->m_size = n;
    } else if (n < size(v)) {
        for (int* i = (begin(v) + n); i < end(v); i++) {
            *(i) = 0;
        }
        v->m_size = n;
    } else if (n == 0) {
        int cap = capacity(v);
        v = clear(v);
        v = UTIL_allocate(cap);
    } else {
        fprintf(stderr, "ERROR: Cannot resize\n");
    }
}

void reserve(cVector* v, int n) {
    if (n > capacity(v)) {
        v = UTIL_reallocate(v, UTIL_get_new_cap(n));
    }
}

cVector* clear(cVector* v) {
    free(v->m_data);
    v->m_capacity = 0;
    v->m_size = 0;
    free(v);
    return NULL;
}

#endif // CVECTOR_H_