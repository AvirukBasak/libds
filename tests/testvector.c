#include "ctl/vector.h"

VECTOR_DECLARE(int);
VECTOR_DEFINE(int);

// pointers need to be aliased before using in a vector type
typedef char* str_t;

typedef struct {
    int m;
    char *n;
} Person;

VECTOR_DECLARE(str_t);
VECTOR_DEFINE(str_t);

VECTOR_DECLARE(Person);
VECTOR_DEFINE(Person);

// comparator function: should take 2 vtype and return int
int int_asc_compfn(int a, int b) {
    return a - b;
}

// comparator function: should take 2 vtype and return int
int str_asc_compfn(str_t a, str_t b) {
    if (a == b) return 0;
    if (*a != *b) return *a - *b;
    return strcmp(a, b);
}

// comparator function: should take 2 vtype and return int
int persn_asc_compfn(Person a, Person b) {
    if (a.m == b.m) return 0;
    if (a.m != b.m) return a.m - b.m;
    return str_asc_compfn(a.n, b.n);
}

void teststack() {
    Vector(int) vc1 = VectorFn(int, new)();
    vc1->insert(vc1, 0, 45);
    vc1->push(vc1, 56);
    vc1->push(vc1, 38);
    vc1->push(vc1, 90);
    vc1->push(vc1, 23);
    vc1->push(vc1, 14);
    vc1->insert(vc1, 2, 45);
    vc1->insert(vc1, 0, 19);
    vc1->insert(vc1, 11, 38);

    Vector(int) vc2 = vc1->clone(vc1);

    printf("vc2 = { ");
    VECTOR_FOREACH(vc2, printf("%d ", *value));
    printf("}\n");

    vc2->reverse(vc2);
    vc2->erase(vc2, 4, 1);
    vc2->erase(vc2, 0, 1);
    vc2->erase(vc2, 2, 2);

    printf("vc2 = { ");
    VECTOR_FOREACH(vc2, printf("%d ", *value));
    printf("}\n");

    vc2->qsort(vc2, int_asc_compfn);

    printf("vc2 = { ");
    VECTOR_FOREACH(vc2, printf("%d ", *value));
    printf("}\n");

    printf("\nlen = %zu\n", vc1->length(vc1));
    while (!vc1->isempty(vc1)) {
        printf("vc1 = { ");
        VECTOR_FOREACH(vc1, printf("%d ", *value));
        printf("}; ");
        printf("pop = %d\n", vc1->pop(vc1));
    };

    int *n = vc2->find(vc2, 35, int_asc_compfn);
    if (n) printf("\nfound %d\n", *n);
    else printf("\nnot found 35\n");

    vc1->free(&vc1);
    vc2->free(&vc2);

    // creating a vector of Persons
    Vector(Person) vcp = VectorFn(Person, from)(6, (Person[6]) {
        (Person) { 56, "Bob"   },
        (Person) { 21, "Nana"  },
        (Person) { 12, "Joe"   },
        (Person) { 34, "Peter" },
        (Person) { 17, "Lily"  },
        (Person) { 67, "Jenny" },
    });
    printf("\nvector of structs\n");
    printf("vcp = {\n");
    VECTOR_FOREACH(vcp, printf("    %d, %s\n", value->m, value->n));
    printf("}\n");

    vcp->reverse(vcp);

    printf("vcp = {\n");
    VECTOR_FOREACH(vcp, printf("    %d, %s\n", value->m, value->n));
    printf("}\n");

    vcp->qsort(vcp, persn_asc_compfn);

    Person *p = vcp->find(vcp, (Person) { 17, "Lily" }, persn_asc_compfn);
    if (p) printf("\nfound %d, %s\n\n", p->m, p->n);

    printf("vcp = {\n");
    VECTOR_FOREACH(vcp, printf("    %d, %s\n", value->m, value->n));
    printf("}\n");

    vcp->free(&vcp);
}
