#include "vector.h"

int main() {
    //Vector* v = vect_createVector();
    Vector* u = vect_createVectorWithSize(5);
    DEBUG_printSize(u);
    DEBUG_printCurrentSize(u);
    printf("***\n");
    for(int i = 0; i < 10; i++) {
        //DEBUG_printMemAlloc(v);
        vect_insert(u, i+1);
        DEBUG_printSize(u);
        DEBUG_printCurrentSize(u);
        printf("%d\n", vect_at(u, i));
        //vect_insert(v, i+1);
    }

    //vect_print(v);
    vect_print(u);
    
    //int x = vect_at(v, 8);
    //printf("%d\n", x);

    vect_clear(u);
    //vect_clear(v);

    return 0;
}
