/*
** Author: Soham Kar
** License: GNU General Public License
** Description: A lightweight #include file
**           that provides functionality similar to
**           a C++ STL Vector, or a dynamically
**           allocated array of integers
*/

#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdio.h>
#include <stdlib.h>

/*
** Struct definition of Vector
** Can be used as a type
*/

typedef struct
{
    int size;
    int curr_size;
    int* pool_addr;

} Vector;


// Allocates memory and returns address of vector
Vector* vect_createVector() {
    Vector* v = (Vector*)malloc(sizeof(Vector));
    v->size = 8;
    v->curr_size = 0;
    v->pool_addr = (int*)calloc(v->size, sizeof(int));
    if(v->pool_addr == NULL)
        printf("Warning: Memory not allocated.");
    return v;
}

// Allocates specified size of memory pool and returns address of vector
Vector* vect_createVectorWithSize(int size) {
    if(size <= 0) {
        printf("Warning: Size is invalid. Allocating standard memory.");
        return vect_createVector();
    }
    Vector* v = (Vector*)malloc(sizeof(Vector));
    v->size = size;
    v->curr_size = 0;
    v->pool_addr = (int*)calloc(v->size, sizeof(int));
    if(v->pool_addr == NULL)
        printf("Warning: Memory not allocated.");
    return v;
}

// Inserts element at end, if full, reallocates to double the size
void vect_insert(Vector* v, int data) {
    if(v->curr_size < v->size) {
        *(v->pool_addr + v->curr_size) = data;
        v->curr_size++;
    }
    else {
        v->size = v->size * 2;
        v->pool_addr = realloc(v->pool_addr, sizeof(int) * v->size);
        *(v->pool_addr + v->curr_size) = data;
        v->curr_size++;
    }
}

// Returns value at position passed as argument; prints error to console
// if position is invalid
int vect_at(Vector* v, int pos) {
    if(pos >= v->curr_size) {
        printf("Warning: Position invalid\n");
        return -1;
    }
    return *(v->pool_addr + pos);
}

// Frees space allocated to the vector
void vect_clear(Vector* v) {
    free(v->pool_addr);
    free(v);
}

// Prints contents of vector, space-separated
void vect_print(Vector* v) {
    for(int i = 0; i < v->curr_size; i++) {
        printf("%d ", *(v->pool_addr + i));
    }
    printf("\n");
}

void DEBUG_printMemAddr(Vector* v) {
    printf("Memory address of starting block: %p\n", v->pool_addr);
}

void DEBUG_printMemAlloc(Vector* v) {
    printf("Memory allocated in bytes: %lu\n", sizeof(int) * v->size);
}

void DEBUG_printSize(Vector* v) {
    printf("Size of vector is: %d\n", v->size);
}

void DEBUG_printCurrentSize(Vector* v) {
    printf("Length of vector is: %d\n", v->curr_size);
}

#endif
