#include "../include/tlib/vector.h"

VECTOR_DECLARE(int);
VECTOR_DEFINE(int);

int main() {
    Vector(int) vc = VectorFn(int, new)();
    vc->push(vc, 56);
    vc->push(vc, 38);
    vc->push(vc, 90);
    vc->push(vc, 23);
    vc->push(vc, 14);

    printf("vc = { ");
    VECTOR_FOREACH(vc, printf("%d ", *value));
    printf("}\n");

    vc->reverse(vc);
    
    printf("vc = { ");
    VECTOR_FOREACH(vc, printf("%d ", *value));
    printf("}\n");

    printf("len = %zu\n", vc->length(vc));
    while (!vc->isempty(vc)) {
        printf("vc = { ");
        VECTOR_FOREACH(vc, printf("%d ", *value));
        printf("}\n");
        printf("pop = %d\n", vc->pop(vc));
    };
    return 0;
}
