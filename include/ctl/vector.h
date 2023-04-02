/**
 * header guards are not required as every macro
 * is undef-ed before defining
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#undef new
/**
 * new function: returns a pointer to a struct type passed by allocating
 * memory using calloc
 */
#define new(struct_t) ({                                                                              \
    struct struct_t *tmp = calloc(1, sizeof(struct struct_t));                                        \
    tmp;                                                                                              \
})

#undef delete
/**
 * delete function: frees pointer and sets it to null
 */
#define delete(ptr) ({                                                                                \
    if (ptr) {                                                                                        \
        free(ptr);                                                                                    \
        ptr = NULL;                                                                                   \
    }                                                                                                 \
})

#undef Vector
#undef VectorFn
#undef VectorCmpFnT

#define Vector(vtype) Vector_##vtype
#define VectorFn(vtype, func) Vector_##vtype##_##func
#define VectorCmpFnT(vtype) Vector_##vtype##_##cmpfunc_t

#undef len
/**
 * Return container length
 * @param o Container object
 */
#define len(o) (o->length(o))

#undef VECTOR_NOT_NULLPTR
/**
 * Return ptr if not null else abort
 * @param ptr Pointer to object
 * @param fn Name of caller function
 * @return ptr If not null
 */
#define VECTOR_NOT_NULLPTR(ptr, fn) ({                                                                \
    void *tmp = ptr;                                                                                  \
    if (!tmp) {                                                                                       \
        fprintf(stderr, "vector: %s(): null pointer\n", fn);                                          \
        abort();                                                                                      \
    }                                                                                                 \
    tmp;                                                                                              \
})

#undef VECTOR_FOREACH
/**
 * Iterate through the vector
 * @param vc The vector
 * @param action{int i, vtype *value} A code block
 */
#define VECTOR_FOREACH(vc, action) ({                                                                 \
    VECTOR_NOT_NULLPTR(vc, "FOREACH");                                                                \
    for (int _i = 0; _i < vc->_.len; _i++) {                                                          \
        typeof(vc->_.v) const value = &(vc->_.v[_i]); value;                                          \
        const int i = _i; i;                                                                          \
        const int _i = 0; _i;                                                                         \
        action;                                                                                       \
    }                                                                                                 \
})

#undef VECTOR_RFOREACH
/**
 * Iterate in reverse through the vector
 * @param vc The vector
 * @param action{int i, vtype *value} A code block
 */
#define VECTOR_RFOREACH(vc, action) ({                                                                \
    VECTOR_NOT_NULLPTR(vc, "RFOREACH");                                                               \
    for (int _i = vc->_.len -1; _i >= 0 ; _i--) {                                                     \
        typeof(vc->_.v) const value = &(vc->_.v[_i]); value;                                          \
        const int i = _i; i;                                                                          \
        const int _i = 0; _i;                                                                         \
        action;                                                                                       \
    }                                                                                                 \
})

#undef VECTOR_DECLARE
/**
 * Generates function prototype definitions and typedefs for the Vector.
 * vtype should be a primary datatype or typdefed (aliased) pointer/struct.
 * Format: VECTOR_DECLARE(vtype)
 * @param vtype
 */
#define VECTOR_DECLARE(vtype)                                                                         \
                                                                                                      \
typedef struct Vector(vtype) *Vector(vtype);                                                          \
typedef int (*VectorCmpFnT(vtype))(vtype a, vtype b);                                                 \
                                                                                                      \
struct Vector(vtype) {                                                                                \
    void          (*free)    (Vector(vtype) *vc_ptr);                                                 \
    size_t        (*length)  (const Vector(vtype) vc);                                                \
    bool          (*isempty) (const Vector(vtype) vc);                                                \
    vtype         (*at)      (const Vector(vtype) vc, int index);                                     \
    vtype*        (*getref)  (const Vector(vtype) vc, int index);                                     \
    vtype         (*front)   (const Vector(vtype) vc);                                                \
    vtype         (*back)    (const Vector(vtype) vc);                                                \
    vtype*        (*begin)   (const Vector(vtype) vc);                                                \
    vtype*        (*end)     (const Vector(vtype) vc);                                                \
    vtype*        (*rbegin)  (const Vector(vtype) vc);                                                \
    vtype*        (*next)    (const Vector(vtype) vc, vtype *curr);                                   \
    vtype*        (*rnext)   (const Vector(vtype) vc, vtype *curr);                                   \
    Vector(vtype) (*set)     (Vector(vtype) vc, int index, vtype val);                                \
    Vector(vtype) (*push)    (Vector(vtype) vc, vtype val);                                           \
    vtype         (*pop)     (Vector(vtype) vc);                                                      \
    Vector(vtype) (*insert)  (Vector(vtype) vc, int index, vtype val);                                \
    Vector(vtype) (*erase)   (Vector(vtype) vc, int from, int count);                                 \
    vtype*        (*find)    (const Vector(vtype) vc, vtype val, VectorCmpFnT(vtype) f);              \
    vtype*        (*rfind)   (const Vector(vtype) vc, vtype val, VectorCmpFnT(vtype) f);              \
    int           (*index)   (const Vector(vtype) vc, vtype val, VectorCmpFnT(vtype) f);              \
    int           (*rindex)  (const Vector(vtype) vc, vtype val, VectorCmpFnT(vtype) f);              \
    Vector(vtype) (*clone)   (const Vector(vtype) vc);                                                \
    Vector(vtype) (*qsort)   (Vector(vtype) vc, VectorCmpFnT(vtype) f);                               \
    Vector(vtype) (*reverse) (Vector(vtype) vc);                                                      \
    /** private data members, do not modify */                                                        \
    struct {                                                                                          \
        vtype *v;                                                                                     \
        size_t len;                                                                                   \
        size_t cap;                                                                                   \
    } _;                                                                                              \
};                                                                                                    \
                                                                                                      \
Vector(vtype) VectorFn(vtype, new)();                                                                 \
Vector(vtype) VectorFn(vtype, from)(int len, vtype arr[len]);                                         \
                                                                                                      \
void          VectorFn(vtype, free)    (Vector(vtype) *vc_ptr);                                       \
size_t        VectorFn(vtype, length)  (const Vector(vtype) vc);                                      \
bool          VectorFn(vtype, isempty) (const Vector(vtype) vc);                                      \
vtype         VectorFn(vtype, at)      (const Vector(vtype) vc, int index);                           \
vtype*        VectorFn(vtype, getref)  (const Vector(vtype) vc, int index);                           \
vtype         VectorFn(vtype, front)   (const Vector(vtype) vc);                                      \
vtype         VectorFn(vtype, back)    (const Vector(vtype) vc);                                      \
vtype*        VectorFn(vtype, begin)   (const Vector(vtype) vc);                                      \
vtype*        VectorFn(vtype, end)     (const Vector(vtype) vc);                                      \
vtype*        VectorFn(vtype, rbegin)  (const Vector(vtype) vc);                                      \
vtype*        VectorFn(vtype, next)    (const Vector(vtype) vc, vtype *curr);                         \
vtype*        VectorFn(vtype, rnext)   (const Vector(vtype) vc, vtype *curr);                         \
Vector(vtype) VectorFn(vtype, set)     (Vector(vtype) vc, int index, vtype val);                      \
Vector(vtype) VectorFn(vtype, push)    (Vector(vtype) vc, vtype val);                                 \
vtype         VectorFn(vtype, pop)     (Vector(vtype) vc);                                            \
Vector(vtype) VectorFn(vtype, insert)  (Vector(vtype) vc, int index, vtype val);                      \
Vector(vtype) VectorFn(vtype, erase)   (Vector(vtype) vc, int from, int count);                       \
vtype*        VectorFn(vtype, find)    (const Vector(vtype) vc, vtype val, VectorCmpFnT(vtype) f);    \
vtype*        VectorFn(vtype, rfind)   (const Vector(vtype) vc, vtype val, VectorCmpFnT(vtype) f);    \
int           VectorFn(vtype, index)   (const Vector(vtype) vc, vtype val, VectorCmpFnT(vtype) f);    \
int           VectorFn(vtype, rindex)  (const Vector(vtype) vc, vtype val, VectorCmpFnT(vtype) f);    \
Vector(vtype) VectorFn(vtype, clone)   (const Vector(vtype) vc);                                      \
Vector(vtype) VectorFn(vtype, qsort)   (Vector(vtype) vc, VectorCmpFnT(vtype) f);                     \
Vector(vtype) VectorFn(vtype, reverse) (Vector(vtype) vc);

#undef VECTOR_DEFINE
/**
 * Defines the chosen Vector from template: generates the necessary function definitions
 * vtype should be a primary datatype or typdefed (aliased) pointer/struct
 * Format: VECTOR_DEFINE(vtype)
 * Note: requires VECTOR_DECLARE(vtype)
 * @param vtype
 */
#define VECTOR_DEFINE(vtype)                                                                          \
                                                                                                      \
Vector(vtype) VectorFn(vtype, new)()                                                                  \
{                                                                                                     \
    Vector(vtype) vc = VECTOR_NOT_NULLPTR(new(Vector(vtype)), "new");                                 \
    vc->_.v = NULL;                                                                                   \
    vc->_.len = 0;                                                                                    \
    vc->_.cap = 0;                                                                                    \
    vc->free    = VectorFn(vtype, free);                                                              \
    vc->length  = VectorFn(vtype, length);                                                            \
    vc->isempty = VectorFn(vtype, isempty);                                                           \
    vc->at      = VectorFn(vtype, at);                                                                \
    vc->getref  = VectorFn(vtype, getref);                                                            \
    vc->front   = VectorFn(vtype, front);                                                             \
    vc->back    = VectorFn(vtype, back);                                                              \
    vc->begin   = VectorFn(vtype, begin);                                                             \
    vc->end     = VectorFn(vtype, end);                                                               \
    vc->rbegin  = VectorFn(vtype, rbegin);                                                            \
    vc->next    = VectorFn(vtype, next);                                                              \
    vc->rnext   = VectorFn(vtype, rnext);                                                             \
    vc->set     = VectorFn(vtype, set);                                                               \
    vc->push    = VectorFn(vtype, push);                                                              \
    vc->pop     = VectorFn(vtype, pop);                                                               \
    vc->insert  = VectorFn(vtype, insert);                                                            \
    vc->erase   = VectorFn(vtype, erase);                                                             \
    vc->find    = VectorFn(vtype, find);                                                              \
    vc->rfind   = VectorFn(vtype, rfind);                                                             \
    vc->index   = VectorFn(vtype, index);                                                             \
    vc->rindex  = VectorFn(vtype, rindex);                                                            \
    vc->clone   = VectorFn(vtype, clone);                                                             \
    vc->qsort   = VectorFn(vtype, qsort);                                                             \
    vc->reverse = VectorFn(vtype, reverse);                                                           \
    return vc;                                                                                        \
}                                                                                                     \
                                                                                                      \
Vector(vtype) VectorFn(vtype, from)(int len, vtype arr[len])                                          \
{                                                                                                     \
    Vector(vtype) vc = VectorFn(vtype, new)();                                                        \
    vc->_.v = malloc(len * sizeof(vtype));                                                            \
    memcpy(vc->_.v, arr, len * sizeof(vtype));                                                        \
    vc->_.len += len;                                                                                 \
    vc->_.cap += len;                                                                                 \
    return vc;                                                                                        \
}                                                                                                     \
                                                                                                      \
size_t VectorFn(vtype, length)(const Vector(vtype) vc)                                                \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "length");                                                                 \
    return vc->_.len;                                                                                 \
}                                                                                                     \
                                                                                                      \
bool VectorFn(vtype, isempty)(const Vector(vtype) vc)                                                 \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "isempty");                                                                \
    return !(vc->_.len);                                                                              \
}                                                                                                     \
                                                                                                      \
vtype VectorFn(vtype, at)(const Vector(vtype) vc, int index)                                          \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "at");                                                                     \
    if (index < 0 || index >= (int) vc->_.len) {                                                      \
        fprintf(stderr, "vector: at(): index out of bounds: %d\n", index);                            \
        abort();                                                                                      \
    }                                                                                                 \
    return vc->_.v[index];                                                                            \
}                                                                                                     \
                                                                                                      \
vtype *VectorFn(vtype, getref)(const Vector(vtype) vc, int index)                                     \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "getref");                                                                 \
    if (index < 0 || index >= (int) vc->_.len) {                                                      \
        fprintf(stderr, "vector: getref(): index out of bounds: %d\n", index);                        \
        abort();                                                                                      \
    }                                                                                                 \
    return &(vc->_.v[index]);                                                                         \
}                                                                                                     \
                                                                                                      \
vtype VectorFn(vtype, front)(const Vector(vtype) vc)                                                  \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "front");                                                                  \
    return *(vc->begin(vc));                                                                          \
}                                                                                                     \
                                                                                                      \
vtype VectorFn(vtype, back)(const Vector(vtype) vc)                                                   \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "back");                                                                   \
    return *(vc->rbegin(vc));                                                                         \
}                                                                                                     \
                                                                                                      \
vtype *VectorFn(vtype, begin)(const Vector(vtype) vc)                                                 \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "begin");                                                                  \
    if (0 >= vc->_.len) {                                                                             \
        fprintf(stderr, "vector: begin(): vector empty\n");                                           \
        abort();                                                                                      \
    }                                                                                                 \
    return &(vc->_.v[0]);                                                                             \
}                                                                                                     \
                                                                                                      \
vtype *VectorFn(vtype, end)(const Vector(vtype) vc)                                                   \
{                                                                                                     \
    return vc->begin(vc) + vc->_.len;                                                                 \
}                                                                                                     \
                                                                                                      \
vtype *VectorFn(vtype, rbegin)(const Vector(vtype) vc)                                                \
{                                                                                                     \
    int index = vc->_.len -1;                                                                         \
    VECTOR_NOT_NULLPTR(vc, "rbegin");                                                                 \
    if (index < 0) {                                                                                  \
        fprintf(stderr, "vector: rbegin(): vector empty\n");                                          \
        abort();                                                                                      \
    }                                                                                                 \
    return &(vc->_.v[index]);                                                                         \
}                                                                                                     \
                                                                                                      \
vtype *VectorFn(vtype, next)(const Vector(vtype) vc, vtype *curr)                                     \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "next");                                                                   \
    if (!curr) return vc->begin(vc);                                                                  \
    curr++;                                                                                           \
    if (vc->begin(vc) <= curr && curr <= vc->rbegin(vc))                                              \
        return curr;                                                                                  \
    return NULL;                                                                                      \
}                                                                                                     \
vtype *VectorFn(vtype, rnext)(const Vector(vtype) vc, vtype *curr)                                    \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "rnext");                                                                  \
    if (!curr) return vc->rbegin(vc);                                                                 \
    curr--;                                                                                           \
    if (vc->begin(vc) <= curr && curr <= vc->rbegin(vc))                                              \
        return curr;                                                                                  \
    return NULL;                                                                                      \
}                                                                                                     \
                                                                                                      \
Vector(vtype) VectorFn(vtype, set)(Vector(vtype) vc, int index, vtype val)                            \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "set");                                                                    \
    if (index < 0 || index >= (int) vc->_.len) {                                                      \
        fprintf(stderr, "vector: set(): index out of bounds: %d\n", index);                           \
        abort();                                                                                      \
    }                                                                                                 \
    vc->_.v[index] = val;                                                                             \
    return vc;                                                                                        \
}                                                                                                     \
                                                                                                      \
Vector(vtype) VectorFn(vtype, push)(Vector(vtype) vc, vtype val)                                      \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "push");                                                                   \
    if (vc->_.len >= vc->_.cap) {                                                                     \
        vc->_.cap = (int) (2 * vc->_.cap) +1;                                                         \
        vc->_.v = realloc(vc->_.v, sizeof(vtype) * vc->_.cap);                                        \
    }                                                                                                 \
    vc->_.v[vc->_.len++] = val;                                                                       \
    return vc;                                                                                        \
}                                                                                                     \
                                                                                                      \
vtype VectorFn(vtype, pop)(Vector(vtype) vc)                                                          \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "pop");                                                                    \
    vtype retv = *vc->rbegin(vc);                                                                     \
    vc->_.len--;                                                                                      \
    return retv;                                                                                      \
}                                                                                                     \
                                                                                                      \
Vector(vtype) VectorFn(vtype, insert)(Vector(vtype) vc, int index, vtype val)                         \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "insert");                                                                 \
    if (index >= (int) vc->_.len) {                                                                   \
        vc->push(vc, val);                                                                            \
        return vc;                                                                                    \
    }                                                                                                 \
    vc->push(vc, vc->back(vc));                                                                       \
    vtype *p = vc->begin(vc) + index;                                                                 \
    vtype *r = vc->rbegin(vc);                                                                        \
    while (r > p) {                                                                                   \
        vtype *tmp = vc->rnext(vc, r);                                                                \
        *r = *tmp;                                                                                    \
        r = tmp;                                                                                      \
    }                                                                                                 \
    *p = val;                                                                                         \
    return vc;                                                                                        \
}                                                                                                     \
                                                                                                      \
Vector(vtype) VectorFn(vtype, erase)(Vector(vtype) vc, int from, int count)                           \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "erase");                                                                  \
    if (from >= (int) vc->_.len) {                                                                    \
        fprintf(stderr, "vector: erase(): index out of bounds: %d\n", from);                          \
        abort();                                                                                      \
    }                                                                                                 \
    vtype *p = vc->getref(vc, from);                                                                  \
    if (p + count >= vc->end(vc)) {                                                                   \
        fprintf(stderr, "vector: erase(): count out of bounds: %d\n", count);                         \
        abort();                                                                                      \
    }                                                                                                 \
    vtype *q = p + count;                                                                             \
    while (p < q && q < vc->end(vc)) {                                                                \
        *p = *q;                                                                                      \
        p = vc->next(vc, p);                                                                          \
        q = vc->next(vc, q);                                                                          \
    }                                                                                                 \
    vc->_.len -= count;                                                                               \
    return vc;                                                                                        \
}                                                                                                     \
                                                                                                      \
vtype *VectorFn(vtype, find)(const Vector(vtype) vc, vtype val, VectorCmpFnT(vtype) f)                \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "find");                                                                   \
    VECTOR_FOREACH(vc, if (!f(val, *value)) return value);                                            \
    return NULL;                                                                                      \
}                                                                                                     \
vtype *VectorFn(vtype, rfind)(const Vector(vtype) vc, vtype val, VectorCmpFnT(vtype) f)               \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "rfind");                                                                  \
    VECTOR_RFOREACH(vc, if (!f(val, *value)) return value);                                           \
    return NULL;                                                                                      \
}                                                                                                     \
int VectorFn(vtype, index)(const Vector(vtype) vc, vtype val, VectorCmpFnT(vtype) f)                  \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "index");                                                                  \
    VECTOR_FOREACH(vc, if (!f(val, *value)) return value - vc->begin(vc));                            \
    return -1;                                                                                        \
}                                                                                                     \
int VectorFn(vtype, rindex)(const Vector(vtype) vc, vtype val, VectorCmpFnT(vtype) f)                 \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "rindex");                                                                 \
    VECTOR_RFOREACH(vc, if (!f(val, *value)) return value - vc->begin(vc));                           \
    return -1;                                                                                        \
}                                                                                                     \
                                                                                                      \
Vector(vtype) VectorFn(vtype, clone)(const Vector(vtype) vc)                                          \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "clone");                                                                  \
    Vector(vtype) vec = VectorFn(vtype, new)();                                                       \
    VECTOR_FOREACH(vc, vec->push(vec, *value));                                                       \
    return vec;                                                                                       \
}                                                                                                     \
                                                                                                      \
void VectorFn(vtype, swap)(vtype *x, vtype *y) {                                                      \
    void *tmp = malloc(sizeof(vtype));                                                                \
    memcpy(tmp, x, sizeof(vtype));                                                                    \
    memcpy(x, y, sizeof(vtype));                                                                      \
    memcpy(y, tmp, sizeof(vtype));                                                                    \
    free(tmp);                                                                                        \
}                                                                                                     \
                                                                                                      \
void VectorFn(vtype, qsort_generic)(vtype *base, size_t len, VectorCmpFnT(vtype) cmp) {               \
    if (len <= 1) return;                                                                             \
    vtype *pbase = base;                                                                              \
    int pivot_idx = rand() % len;                                                                     \
    vtype *pivot = pbase + pivot_idx;                                                                 \
    VectorFn(vtype, swap)(pivot, pbase + (len -1));                                                   \
    int i = 0, j = len -2;                                                                            \
    while (i <= j) {                                                                                  \
        while (i <= j && cmp(*(pbase +i), *(pbase + (len -1))) <= 0) {                                \
            i++;                                                                                      \
        }                                                                                             \
        while (j >= i && cmp(*(pbase +j), *(pbase + (len -1))) >= 0) {                                \
            j--;                                                                                      \
        }                                                                                             \
        if (i < j) {                                                                                  \
            VectorFn(vtype, swap)(pbase +i, pbase +j);                                                \
        }                                                                                             \
    }                                                                                                 \
    VectorFn(vtype, swap)(pbase +i, pbase + (len -1));                                                \
    VectorFn(vtype, qsort_generic)(base, i, cmp);                                                     \
    VectorFn(vtype, qsort_generic)(pbase +i +1, len -i -1, cmp);                                      \
}                                                                                                     \
                                                                                                      \
Vector(vtype) VectorFn(vtype, qsort)(Vector(vtype) vc, VectorCmpFnT(vtype) f)                         \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "qsort");                                                                  \
    VectorFn(vtype, qsort_generic)(vc->_.v, vc->_.len, f);                                            \
    return vc;                                                                                        \
}                                                                                                     \
                                                                                                      \
Vector(vtype) VectorFn(vtype, reverse)(Vector(vtype) vc)                                              \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc, "reverse");                                                                \
    vtype *l = vc->begin(vc),                                                                         \
          *u = vc->rbegin(vc);                                                                        \
    while (l && u && l < u) {                                                                         \
        vtype tmp = *l;                                                                               \
        *l = *u;                                                                                      \
        *u = tmp;                                                                                     \
        l = vc->next(vc, l);                                                                          \
        u = vc->rnext(vc, u);                                                                         \
    }                                                                                                 \
    return vc;                                                                                        \
}                                                                                                     \
                                                                                                      \
void VectorFn(vtype, free)(Vector(vtype) *vc_ptr)                                                     \
{                                                                                                     \
    VECTOR_NOT_NULLPTR(vc_ptr, "free");                                                               \
    VECTOR_NOT_NULLPTR(*vc_ptr, "free");                                                              \
    free((*vc_ptr)->_.v);                                                                             \
    free(*vc_ptr);                                                                                    \
    *vc_ptr = NULL;                                                                                   \
}
