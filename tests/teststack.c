#include "ctl/stack.h"

STACK_DECLARE(int);
STACK_DEFINE(int);

typedef struct {
    int m;
    char *n;
} Person;

STACK_DECLARE(Person);
STACK_DEFINE(Person);

void teststack() {
    Stack(int) st1 = StackFn(int, new)();
    st1->push(st1, 56)
       ->push(st1, 38)
       ->push(st1, 90)
       ->push(st1, 23)
       ->push(st1, 14);
    printf("len = %zu\n", len(st1));
    while (!st1->isempty(st1)) {
        printf("st1 = { ");
        STACK_FOREACH(st1, printf("%d ", *value));
        printf("}; ");
        printf("pop = %d\n", st1->pop(st1));
    }
    st1->free(&st1);
    Stack(Person) st2 = StackFn(Person, new)();
    st2->push(st2, (Person) { 56, "Bob"   })
       ->push(st2, (Person) { 21, "Nana"  })
       ->push(st2, (Person) { 12, "Joe"   })
       ->push(st2, (Person) { 34, "Peter" })
       ->push(st2, (Person) { 17, "Lily"  })
       ->push(st2, (Person) { 67, "Jenny" });
    while (!st2->isempty(st2)) {
        printf("st2 = { ");
        STACK_FOREACH(st2, printf("%s ", value->n));
        printf("}; ");
        printf("pop = %s\n", st2->pop(st2).n);
    }
    st2->free(&st2);
}
