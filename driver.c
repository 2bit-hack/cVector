#include "vector.h"

int main() {
    Vector* v = vect_createVector();
    Vector* u = vect_createVectorWithSize(10);

    for(int i = 0; i < 10; i++) {
        //DEBUG_printMemAlloc(u);
        //DEBUG_printMemAlloc(v);
        vect_insert(u, i+1);
        vect_insert(v, i+1);
    }

    vect_print(v);
    vect_print(u);
    
    int x = vect_at(v, 8);
    printf("%d\n", x);

    vect_clear(u);
    vect_clear(v);

    return 0;
}