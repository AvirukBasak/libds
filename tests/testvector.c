#include "../include/tlib/vector.h"

VECTOR_DECLARE(int);
VECTOR_DEFINE(int);

int main() {
    Vector(int) vc1 = VectorFn(int, new)();
    vc1->push(vc1, 56);
    vc1->push(vc1, 38);
    vc1->push(vc1, 90);
    vc1->push(vc1, 23);
    vc1->push(vc1, 14);

    Vector(int) vc2 = vc1->clone(vc1);

    printf("vc2 = { ");
    VECTOR_FOREACH(vc2, printf("%d ", *value));
    printf("}\n");

    vc2->reverse(vc2);
    
    printf("vc2 = { ");
    VECTOR_FOREACH(vc2, printf("%d ", *value));
    printf("}\n");

    printf("len = %zu\n", vc1->length(vc1));
    while (!vc1->isempty(vc1)) {
        printf("vc1 = { ");
        VECTOR_FOREACH(vc1, printf("%d ", *value));
        printf("}; ");
        printf("pop = %d\n", vc1->pop(vc1));
    };

    vc1->free(&vc1);
    vc2->free(&vc2);
    return 0;
}
