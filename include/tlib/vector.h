#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#undef new
/**
 * new function: returns a pointer to a struct type passed by allocating
 * memory using calloc
 */
#define new(struct_t) ({                                                          \
    struct struct_t *tmp = calloc(1, sizeof(struct struct_t));                    \
    tmp;                                                                          \
})

#undef delete
/**
 * delete function: frees pointer and sets it to null
 */
#define delete(ptr) ({                                                            \
    if (ptr) {                                                                    \
        free(ptr);                                                                \
        ptr = NULL;                                                               \
    }                                                                             \
})

#define Vector(vtype) Vector_##vtype
#define VectorFn(vtype, func) Vector_##vtype##_##func
#define VectorCmpFnT(vtype) Vector_##vtype##_##cmpfunc_t

#undef VECTOR_NOT_NULLPTR
/**
 * Return ptr if not null else abort
 * @param ptr Pointer to object
 * @param fn Name of caller function
 * @return ptr If not null
 */
#define VECTOR_NOT_NULLPTR(ptr, fn) ({                                            \
    void *tmp = ptr;                                                              \
    if (!tmp) {                                                                   \
        fprintf(stderr, "vector: %s(): null pointer\n", fn);                      \
        abort();                                                                  \
    }                                                                             \
    tmp;                                                                          \
})

#undef VECTOR_FOREACH
/**
 * Iterate through the vector
 * @param vc The vector
 * @param action{int i, vtype *value} A code block
 */
#define VECTOR_FOREACH(vc, action) ({                                             \
    VECTOR_NOT_NULLPTR(vc, "FOREACH");                                            \
    for (int _i = 0; _i < vc->_.len; _i++) {                                      \
        typeof(vc->_.v) const value = &(vc->_.v[_i]); value;                      \
        const int i = _i; i;                                                      \
        const int _i = 0; _i;                                                     \
        action;                                                                   \
    }                                                                             \
})

#undef VECTOR_RFOREACH
/**
 * Iterate in reverse through the vector
 * @param vc The vector
 * @param action{int i, vtype *value} A code block
 */
#define VECTOR_RFOREACH(vc, action) ({                                            \
    VECTOR_NOT_NULLPTR(vc, "RFOREACH");                                           \
    for (int _i = vc->_.len -1; _i >= 0 ; _i--) {                                 \
        typeof(vc->_.v) const value = &(vc->_.v[_i]); value;                      \
        const int i = _i; i;                                                      \
        const int _i = 0; _i;                                                     \
        action;                                                                   \
    }                                                                             \
})

/**
 * Generates function prototype definitions and typedefs for the Vector.
 * vtype should be a primary datatype or typdefed (aliased) pointer/struct.
 * Format: VECTOR_DECLARE(vtype)
 * @param vtype
 */
#define VECTOR_DECLARE(vtype)                                                     \
                                                                                  \
typedef struct Vector(vtype) *Vector(vtype);                                      \
typedef int (*VectorCmpFnT(vtype))(vtype a, vtype b);                             \
                                                                                  \
struct Vector(vtype) {                                                            \
    void          (*free)    (Vector(vtype) *vc_ptr);                             \
    size_t        (*length)  (const Vector(vtype) vc);                            \
    bool          (*isempty) (const Vector(vtype) vc);                            \
    vtype         (*get)     (const Vector(vtype) vc, int index);                 \
    vtype*        (*getref)  (const Vector(vtype) vc, int index);                 \
    vtype         (*front)   (const Vector(vtype) vc);                            \
    vtype         (*back)    (const Vector(vtype) vc);                            \
    vtype*        (*begin)   (const Vector(vtype) vc);                            \
    vtype*        (*end)     (const Vector(vtype) vc);                            \
    vtype*        (*rbegin)  (const Vector(vtype) vc);                            \
    vtype*        (*next)    (const Vector(vtype) vc, vtype *curr);               \
    vtype*        (*rnext)   (const Vector(vtype) vc, vtype *curr);               \
    bool          (*set)     (Vector(vtype) vc, int index, vtype val);            \
    bool          (*push)    (Vector(vtype) vc, vtype val);                       \
    vtype         (*pop)     (Vector(vtype) vc);                                  \
    bool          (*insert)  (Vector(vtype) vc, int index, vtype val);            \
    vtype         (*erase)   (Vector(vtype) vc, int index);                       \
    Vector(vtype) (*clone)   (const Vector(vtype) vc);                            \
    Vector(vtype) (*qsort)   (Vector(vtype) vc, VectorCmpFnT(vtype) f);           \
    Vector(vtype) (*reverse) (Vector(vtype) vc);                                  \
    /** private data members, do not modify */                                    \
    struct {                                                                      \
        vtype *v;                                                                 \
        size_t len;                                                               \
        size_t cap;                                                               \
    } _;                                                                          \
};                                                                                \
                                                                                  \
Vector(vtype) VectorFn(vtype, new)();                                             \
void          VectorFn(vtype, free)    (Vector(vtype) *vc_ptr);                   \
size_t        VectorFn(vtype, length)  (const Vector(vtype) vc);                  \
bool          VectorFn(vtype, isempty) (const Vector(vtype) vc);                  \
vtype         VectorFn(vtype, get)     (const Vector(vtype) vc, int index);       \
vtype*        VectorFn(vtype, getref)  (const Vector(vtype) vc, int index);       \
vtype         VectorFn(vtype, front)   (const Vector(vtype) vc);                  \
vtype         VectorFn(vtype, back)    (const Vector(vtype) vc);                  \
vtype*        VectorFn(vtype, begin)   (const Vector(vtype) vc);                  \
vtype*        VectorFn(vtype, end)     (const Vector(vtype) vc);                  \
vtype*        VectorFn(vtype, rbegin)  (const Vector(vtype) vc);                  \
vtype*        VectorFn(vtype, next)    (const Vector(vtype) vc, vtype *curr);     \
vtype*        VectorFn(vtype, rnext)   (const Vector(vtype) vc, vtype *curr);     \
bool          VectorFn(vtype, set)     (Vector(vtype) vc, int index, vtype val);  \
bool          VectorFn(vtype, push)    (Vector(vtype) vc, vtype val);             \
vtype         VectorFn(vtype, pop)     (Vector(vtype) vc);                        \
bool          VectorFn(vtype, insert)  (Vector(vtype) vc, int index, vtype val);  \
vtype         VectorFn(vtype, erase)   (Vector(vtype) vc, int index);             \
Vector(vtype) VectorFn(vtype, clone)   (const Vector(vtype) vc);                  \
Vector(vtype) VectorFn(vtype, qsort)   (Vector(vtype) vc, VectorCmpFnT(vtype) f); \
Vector(vtype) VectorFn(vtype, reverse) (Vector(vtype) vc);

/**
 * Defines the chosen Vector from template: generates the necessary function definitions
 * vtype should be a primary datatype or typdefed (aliased) pointer/struct
 * Format: VECTOR_DEFINE(vtype)
 * Note: requires VECTOR_DECLARE(vtype)
 * @param vtype
 */
#define VECTOR_DEFINE(vtype)                                                      \
                                                                                  \
Vector(vtype) VectorFn(vtype, new)()                                              \
{                                                                                 \
    Vector(vtype) vc = VECTOR_NOT_NULLPTR(new(Vector(vtype)), "new");             \
    vc->_.v = NULL;                                                               \
    vc->_.len = 0;                                                                \
    vc->_.cap = 0;                                                                \
    vc->free    = VectorFn(vtype, free);                                          \
    vc->length  = VectorFn(vtype, length);                                        \
    vc->isempty = VectorFn(vtype, isempty);                                       \
    vc->get     = VectorFn(vtype, get);                                           \
    vc->getref  = VectorFn(vtype, getref);                                        \
    vc->front   = VectorFn(vtype, front);                                         \
    vc->back    = VectorFn(vtype, back);                                          \
    vc->begin   = VectorFn(vtype, begin);                                         \
    vc->end     = VectorFn(vtype, end);                                           \
    vc->rbegin  = VectorFn(vtype, rbegin);                                        \
    vc->next    = VectorFn(vtype, next);                                          \
    vc->rnext   = VectorFn(vtype, rnext);                                         \
    vc->set     = VectorFn(vtype, set);                                           \
    vc->push    = VectorFn(vtype, push);                                          \
    vc->pop     = VectorFn(vtype, pop);                                           \
    vc->insert  = VectorFn(vtype, insert);                                        \
    vc->erase   = VectorFn(vtype, erase);                                         \
    vc->clone   = VectorFn(vtype, clone);                                         \
    vc->qsort   = VectorFn(vtype, qsort);                                         \
    vc->reverse = VectorFn(vtype, reverse);                                       \
    return vc;                                                                    \
}                                                                                 \
                                                                                  \
size_t VectorFn(vtype, length)(const Vector(vtype) vc)                            \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "length");                                             \
    return vc->_.len;                                                             \
}                                                                                 \
                                                                                  \
bool VectorFn(vtype, isempty)(const Vector(vtype) vc)                             \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "isempty");                                            \
    return !(vc->_.len);                                                          \
}                                                                                 \
                                                                                  \
vtype VectorFn(vtype, get)(const Vector(vtype) vc, int index)                     \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "get");                                                \
    if (index < 0 || index >= (int) vc->_.len) {                                  \
        fprintf(stderr, "vector: get(): index out of bounds: %d\n", index);       \
        abort();                                                                  \
    }                                                                             \
    return vc->_.v[index];                                                        \
}                                                                                 \
                                                                                  \
vtype *VectorFn(vtype, getref)(const Vector(vtype) vc, int index)                 \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "getref");                                             \
    if (index < 0 || index >= (int) vc->_.len) {                                  \
        fprintf(stderr, "vector: getref(): index out of bounds: %d\n", index);    \
        abort();                                                                  \
    }                                                                             \
    return &(vc->_.v[index]);                                                     \
}                                                                                 \
                                                                                  \
vtype VectorFn(vtype, front)(const Vector(vtype) vc)                              \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "front");                                              \
    return *(vc->begin(vc));                                                      \
}                                                                                 \
                                                                                  \
vtype VectorFn(vtype, back)(const Vector(vtype) vc)                               \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "back");                                               \
    return *(vc->rbegin(vc));                                                     \
}                                                                                 \
                                                                                  \
vtype *VectorFn(vtype, begin)(const Vector(vtype) vc)                             \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "begin");                                              \
    if (0 >= vc->_.len) {                                                         \
        fprintf(stderr, "vector: begin(): vector empty\n");                       \
        abort();                                                                  \
    }                                                                             \
    return &(vc->_.v[0]);                                                         \
}                                                                                 \
                                                                                  \
vtype *VectorFn(vtype, end)(const Vector(vtype) vc)                               \
{                                                                                 \
    return vc->begin(vc) + vc->length(vc);                                        \
}                                                                                 \
                                                                                  \
vtype *VectorFn(vtype, rbegin)(const Vector(vtype) vc)                            \
{                                                                                 \
    int index = vc->_.len -1;                                                     \
    VECTOR_NOT_NULLPTR(vc, "rbegin");                                             \
    if (index < 0) {                                                              \
        fprintf(stderr, "vector: rbegin(): vector empty\n");                      \
        abort();                                                                  \
    }                                                                             \
    return &(vc->_.v[index]);                                                     \
}                                                                                 \
                                                                                  \
vtype *VectorFn(vtype, next)(const Vector(vtype) vc, vtype *curr)                 \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "next");                                               \
    if (!curr) return vc->begin(vc);                                              \
    curr++;                                                                       \
    if (vc->begin(vc) <= curr && curr <= vc->rbegin(vc))                          \
        return curr;                                                              \
    return NULL;                                                                  \
}                                                                                 \
vtype *VectorFn(vtype, rnext)(const Vector(vtype) vc, vtype *curr)                \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "rnext");                                              \
    if (!curr) return vc->rbegin(vc);                                             \
    curr--;                                                                       \
    if (vc->begin(vc) <= curr && curr <= vc->rbegin(vc))                          \
        return curr;                                                              \
    return NULL;                                                                  \
}                                                                                 \
                                                                                  \
bool VectorFn(vtype, set)(Vector(vtype) vc, int index, vtype val)                 \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "set");                                                \
    if (index < 0 || index >= (int) vc->_.len) {                                  \
        fprintf(stderr, "vector: set(): index out of bounds: %d\n", index);       \
        abort();                                                                  \
    }                                                                             \
    return vc->_.v[index];                                                        \
}                                                                                 \
                                                                                  \
bool VectorFn(vtype, push)(Vector(vtype) vc, vtype val)                           \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "push");                                               \
    if (vc->_.len >= vc->_.cap) {                                                 \
        vc->_.cap = (int) (2 * vc->_.cap) +1;                                     \
        vc->_.v = realloc(vc->_.v, sizeof(vtype) * vc->_.cap);                    \
    }                                                                             \
    vc->_.v[vc->_.len++] = val;                                                   \
    return true;                                                                  \
}                                                                                 \
                                                                                  \
vtype VectorFn(vtype, pop)(Vector(vtype) vc)                                      \
{                                                                                 \
     VECTOR_NOT_NULLPTR(vc, "pop");                                               \
     vtype retv = *vc->rbegin(vc);                                                \
     vc->_.len--;                                                                 \
     return retv;                                                                 \
}                                                                                 \
                                                                                  \
bool VectorFn(vtype, insert)(Vector(vtype) vc, int index, vtype val)              \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "insert");                                             \
    if (index >= (int) vc->_.len) {                                               \
        vc->push(vc, val);                                                        \
        return true;                                                              \
    }                                                                             \
    vc->push(vc, vc->back(vc));                                                   \
    vtype *p = vc->begin(vc) + index;                                             \
    vtype *r = vc->rbegin(vc);                                                    \
    while (r > p) {                                                               \
        vtype *tmp = vc->rnext(vc, r);                                            \
        *r = *tmp;                                                                \
        r = tmp;                                                                  \
    }                                                                             \
    *p = val;                                                                     \
    return true;                                                                  \
}                                                                                 \
                                                                                  \
vtype VectorFn(vtype, erase)(Vector(vtype) vc, int index)                         \
{                                                                                 \
     VECTOR_NOT_NULLPTR(vc, "erase");                                             \
     if (index >= (int) vc->_.len)                                                \
         return vc->pop(vc);                                                      \
     vtype *p = vc->getref(vc, index);                                            \
     vtype retv = *p;                                                             \
     while (p < vc->rbegin(vc)) {                                                 \
         vtype *tmp = vc->next(vc, p);                                            \
         *p = *tmp;                                                               \
         p = tmp;                                                                 \
     }                                                                            \
     vc->_.len--;                                                                 \
     return retv;                                                                 \
}                                                                                 \
                                                                                  \
Vector(vtype) VectorFn(vtype, clone)(const Vector(vtype) vc)                      \
{                                                                                 \
     VECTOR_NOT_NULLPTR(vc, "clone");                                             \
     Vector(vtype) vec = VectorFn(vtype, new)();                                  \
     VECTOR_FOREACH(vc, vec->push(vec, *value));                                  \
     return vec;                                                                  \
}                                                                                 \
                                                                                  \
Vector(vtype) VectorFn(vtype, qsort)(Vector(vtype) vc, VectorCmpFnT(vtype) f)     \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "qsort");                                              \
     return vc;                                                                   \
}                                                                                 \
                                                                                  \
Vector(vtype) VectorFn(vtype, reverse)(Vector(vtype) vc)                          \
{                                                                                 \
     VECTOR_NOT_NULLPTR(vc, "reverse");                                           \
     vtype *l = vc->begin(vc),                                                    \
           *u = vc->rbegin(vc);                                                   \
     while (l && u && l < u) {                                                    \
         vtype tmp = *l;                                                          \
         *l = *u;                                                                 \
         *u = tmp;                                                                \
         l = vc->next(vc, l);                                                     \
         u = vc->rnext(vc, u);                                                    \
     }                                                                            \
     return vc;                                                                   \
}                                                                                 \
                                                                                  \
void VectorFn(vtype, free)(Vector(vtype) *vc_ptr)                                 \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc_ptr, "free");                                           \
    VECTOR_NOT_NULLPTR(*vc_ptr, "free");                                          \
    free((*vc_ptr)->_.v);                                                         \
    free(*vc_ptr);                                                                \
    *vc_ptr = NULL;                                                               \
}
