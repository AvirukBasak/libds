#include "../include/tlib/stack.h"

STACK_DECLARE(int);
STACK_DEFINE(int);

int main() {
    Stack(int) st = StackFn(int, new)();
    st->push(st, 56);
    st->push(st, 38);
    st->push(st, 90);
    st->push(st, 23);
    st->push(st, 14);
    printf("len = %zu\n", st->length(st));
    while (!st->isempty(st)) {
        printf("st = { ");
        STACK_FOREACH(st, printf("%d ", *value));
        printf("}; ");
        printf("pop = %d\n", st->pop(st));
    }
    st->free(&st);
    return 0;
}
