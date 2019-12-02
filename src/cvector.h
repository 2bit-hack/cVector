/*

Name :        cVector
Author :      Soham Kar (2bit-hack)
License :     GNU General Public License v3.0
Description : A lightweight implementation similar to
              the C++ STL vector for integers

*/

#ifndef CVECTOR_H_
#define CVECTOR_H_

#define DEFAULT_CAPACITY 4
#define GROWTH_FACTOR 2
#define ERR -1
#define ERR_PTR NULL

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
void shrink_to_fit(cVector* v);
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
int* erase(cVector* v, int* pos);
cVector* clear(cVector* v);
// constructors
cVector* new_cVector();
cVector* new_cVector_with_cap(int cap);
cVector* new_cVector_with_cap_val(int cap, int val);

/* gets new capacity of vector */
int UTIL_get_new_cap(int capacity) {
    int new_cap = 1;
    while (new_cap < capacity) {
        new_cap = (int)(new_cap * GROWTH_FACTOR);
    }
    return new_cap;
}

/* allocates an empty vector with some capacity */
cVector* UTIL_allocate(int capacity) {
    cVector* v = (cVector*)malloc(sizeof(cVector));
    v->m_size = 0;
    v->m_capacity = capacity;
    v->m_data = (int*)calloc(v->m_capacity, sizeof(int));
    if (v->m_data == NULL) {
        free(v);
        return ERR_PTR;
    }
    return v;
}

/* reallocates existing vector with new capacity */
cVector* UTIL_reallocate(cVector* v, int new_capacity) {
    v->m_capacity = new_capacity;
    v->m_data = (int*)realloc(v->m_data, v->m_capacity * sizeof(int));
    return v;
}

/* prints contents of vector, space separated */
void UTIL_print_cVector(cVector* v) {
    for (int* i = begin(v); i < end(v); i++) {
        printf("%d ", *i);
    }
    printf("\n");
}

/* prints size, capacity, and data pointer of vector */
void UTIL_debug_cVector(cVector* v) {
    printf("Size: %d\n", v->m_size);
    printf("Capacity: %d\n", v->m_capacity);
    printf("Data pointer: %p\n", v->m_data);
}

/* returns current size of vector */
int size(cVector* v) { return v->m_size; }

/* returns current capacity of vector */
int capacity(cVector* v) { return v->m_capacity; }

/* returns whether or not vector is empty */
bool empty(cVector* v) { return (v->m_size == 0 ? true : false); }

/* resizes vector and reallocates if larger than capacity
   does not reallocate if resized to smaller size than existing capacity
   destroys elements outside size range */
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

/* same as resize, with values to copy
   if size increases */
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

/* reallocates vector with specified capacity
   only if n > capacity(v)
   else does nothing */
void reserve(cVector* v, int n) {
    if (n > capacity(v)) {
        v = UTIL_reallocate(v, UTIL_get_new_cap(n));
    }
}

/* reallocates vector to fit according to size
   as given by the growth rate */
void shrink_to_fit(cVector* v) {
    v = UTIL_reallocate(v, UTIL_get_new_cap(size(v)));
}

/* returns iterator to beginning of vector
   (first element) */
int* begin(cVector* v) { return v->m_data; }

/* returns iterator to element past the end of the vector
   (next past last element) */
int* end(cVector* v) { return (v->m_data + v->m_size); }

/* returns iterator to element at index n */
int* at_iter(cVector* v, int n) {
    if (n < 0 || n > v->m_size - 1) {
        fprintf(stderr, "ERROR: Index Out Of Bounds\n");
        return ERR_PTR;
    } else {
        return (v->m_data + n);
    }
}

/* returns element at index n */
int at(cVector* v, int n) {
    if (n < 0 || n > v->m_size - 1) {
        fprintf(stderr, "ERROR: Index Out Of Bounds\n");
        return ERR;
    } else {
        return *(v->m_data + n);
    }
}

/* returns first element */
int front(cVector* v) {
    if (!empty(v)) {
        return *(v->m_data);
    } else {
        fprintf(stderr, "ERROR: Vector Empty");
        return ERR;
    }
}

/* returns last element */
int back(cVector* v) {
    if (!empty(v)) {
        return *(v->m_data + v->m_size - 1);
    } else {
        fprintf(stderr, "ERROR: Vector Empty");
        return ERR;
    }
}

/* returns reference to underlying array */
int* data(cVector* v) { return v->m_data; }

/* inserts value at given iterator */
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
        return ERR_PTR;
    }
}

/* inserts value at end */
int* push_back(cVector* v, int val) { return insert(v, end(v), val); }

/* removes value from end */
void pop_back(cVector* v) {
    if (!empty(v)) {
        *(at_iter(v, size(v) - 1)) = 0;
        v->m_size--;
    }
}

/* clears contents of vector and returns NULL */
cVector* clear(cVector* v) {
    free(v->m_data);
    v->m_capacity = 0;
    v->m_size = 0;
    free(v);
    return NULL;
}

/* removes element at given iterator and performs shifting as needed */
int* erase(cVector* v, int* pos) {
    if (pos >= begin(v) && pos < end(v)) {
        int pos_dist = (pos - begin(v));
        for (int* i = pos; i < end(v) - 1; i++) {
            *(i) = *(i + 1);
        }
        *(end(v) - 1) = 0;
        v->m_size--;
        return (begin(v) + pos_dist);
    } else if (pos == end(v)) {
        pop_back(v);
        return end(v);
    } else {
        fprintf(stderr, "ERROR: Iterator Out Of Bounds\n");
        return ERR_PTR;
    }
}

/* allocates vector with default capacity */
cVector* new_cVector() {
    return UTIL_allocate(UTIL_get_new_cap(DEFAULT_CAPACITY));
}

/* allocates vector with given capacity */
cVector* new_cVector_with_cap(int cap) {
    if (cap > 0)
        return UTIL_allocate(UTIL_get_new_cap(cap));
    else {
        fprintf(stderr, "ERROR: Capacity must be 1 or greater\n");
        return ERR_PTR;
    }
}

/* allocates vector with given capacity and value */
cVector* new_cVector_with_cap_val(int cap, int val) {
    if (cap > 0) {
        cVector* v = UTIL_allocate(UTIL_get_new_cap(cap));
        for (int* i = begin(v); i < (begin(v) + cap); i++) {
            *(i) = val;
        }
        return v;
    } else {
        fprintf(stderr, "ERROR: Capacity must be 1 or greater\n");
        return ERR_PTR;
    }
}

#endif // CVECTOR_H_