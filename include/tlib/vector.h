#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#undef new
/**
 * new function: returns a pointer to a struct type passed by allocating
 * memory using calloc
 */
#define new(struct_t) ({                                                          \
    calloc(1, sizeof(struct struct_t));                                           \
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

#undef VECTOR_NOT_NULLPTR
/**
 * Return ptr if not null else abort
 * @param ptr Pointer to object
 * @param fn Name of caller function
 * @return ptr If not null
 */
#define VECTOR_NOT_NULLPTR(ptr, fn) ({                                            \
    if (!ptr) {                                                                   \
        fprintf("vector: %s(): null pointer\n", fn);                              \
        abort();                                                                  \
    }                                                                             \
    ptr;                                                                          \
})

#undef VECTOR_FOREACH
/**
 * Iterate through the vector
 * @param vc The vector
 * @param action{Vector(vtype) vc, int i, vtype *value} A code block
 */
#define VECTOR_FOREACH(vc, action) ({                                             \
    VECTOR_NOT_NULLPTR(ptr, "FOREACH");                                           \
    for (int _i = 0; _i < vc->length; _i++) {                                     \
        typeof(vc->v) const value = &(vc->v[_i]);                                 \
        const int i = _i;                                                         \
        const int _i = 0;                                                         \
        action;                                                                   \
    }                                                                             \
})

#undef VECTOR_RFOREACH
/**
 * Iterate in reverse through the vector
 * @param vc The vector
 * @param action{Vector(vtype) vc, int i, vtype *value} A code block
 */
#define VECTOR_RFOREACH(vc, action) ({                                            \
    VECTOR_NOT_NULLPTR(ptr, "RFOREACH");                                          \
    for (int _i = vc->length -1; _i >= 0 ; _i--) {                                \
        typeof(vc->v) const value = &(vc->v[_i]);                                 \
        const int i = _i;                                                         \
        const int _i = 0;                                                         \
        action;                                                                   \
    }                                                                             \
})

/**
 * Generates function prototype definitions and typedefs for the Vector
 * vtype should be a primary datatype or typdefed (aliased) pointer/struct
 * format: VECTOR_DECLARE(vtype)
 * @param vtype
 */
#define VECTOR_DECLARE(vtype)                                                     \
                                                                                  \
typedef struct Vector(vtype) {                                                    \
    vtype *v;                                                                     \
    int refcount;                                                                 \
    size_t length;                                                                \
    size_t capacity;                                                              \
    void          (*free)    (Vector(vtype) *vc_ptr);                             \
    size_t        (*length)  (Vector(vtype) vc);                                  \
    bool          (*isempty) (Vector(vtype) vc);                                  \
    vtype         (*get)     (Vector(vtype) vc, int index);                       \
    vtype*        (*getref)  (Vector(vtype) vc, int index);                       \
    vtype*        (*begin)   (Vector(vtype) vc);                                  \
    vtype*        (*rbegin)  (Vector(vtype) vc);                                  \
    bool          (*set)     (Vector(vtype) vc, int index, vtype val);            \
    bool          (*push)    (Vector(vtype) vc, vtype val);                       \
    vtype         (*pop)     (Vector(vtype) vc);                                  \
    Vector(vtype) (*copy)    (Vector(vtype) vc);                                  \
    Vector(vtype) (*clone)   (Vector(vtype) vc);                                  \
} *Vector(vtype);                                                                 \
                                                                                  \
Vector(vtype) VectorFn(vtype, new)();                                             \
void          VectorFn(vtype, free)    (Vector(vtype) *vc_ptr);                   \
size_t        VectorFn(vtype, length)  (Vector(vtype) vc);                        \
bool          VectorFn(vtype, isempty) (Vector(vtype) vc);                        \
vtype         VectorFn(vtype, get)     (Vector(vtype) vc, int index);             \
vtype*        VectorFn(vtype, getref)  (Vector(vtype) vc, int index);             \
vtype*        VectorFn(vtype, begin)   (Vector(vtype) vc);                        \
vtype*        VectorFn(vtype, rbegin)  (Vector(vtype) vc);                        \
bool          VectorFn(vtype, set)     (Vector(vtype) vc, int index, vtype val);  \
bool          VectorFn(vtype, push)    (Vector(vtype) vc, vtype val);             \
vtype         VectorFn(vtype, pop)     (Vector(vtype) vc);                        \
Vector(vtype) VectorFn(vtype, copy)    (Vector(vtype) vc);                        \
Vector(vtype) VectorFn(vtype, clone)   (Vector(vtype) vc);

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
    vc->v = NULL;                                                                 \
    vc->refcount = 1;                                                             \
    vc->length = 0;                                                               \
    vc->capacity = 0;                                                             \
    vc->free    = VectorFn(vtype, free);                                          \
    vc->length  = VectorFn(vtype, length);                                        \
    vc->isempty = VectorFn(vtype, isempty);                                       \
    vc->get     = VectorFn(vtype, get);                                           \
    vc->getref  = VectorFn(vtype, getref);                                        \
    vc->begin   = VectorFn(vtype, begin);                                         \
    vc->rbegin  = VectorFn(vtype, rbegin);                                        \
    vc->set     = VectorFn(vtype, set);                                           \
    vc->push    = VectorFn(vtype, push);                                          \
    vc->pop     = VectorFn(vtype, pop);                                           \
    vc->copy    = VectorFn(vtype, copy);                                          \
    vc->clone   = VectorFn(vtype, clone);                                         \
    return vc;                                                                    \
}                                                                                 \
                                                                                  \
size_t VectorFn(vtype, length)(Vector(vtype) vc)                                  \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "length");                                             \
    return vc->length;                                                            \
}                                                                                 \
                                                                                  \
bool VectorFn(vtype, isempty)(Vector(vtype) vc)                                   \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "isempty");                                            \
    return !(vc->length);                                                         \
}                                                                                 \
                                                                                  \
vtype VectorFn(vtype, get)(Vector(vtype) vc, int index)                           \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "get");                                                \
    if (index < 0 || index >= vc->length) {                                       \
        fprintf(stderr, "vector: get(): index out of bounds: %d\n", index);       \
        abort();                                                                  \
    }                                                                             \
    return vc->v[index];                                                          \
}                                                                                 \
                                                                                  \
vtype *VectorFn(vtype, getref)(Vector(vtype) vc, int index)                       \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "getref");                                             \
    if (index < 0 || index >= vc->length) {                                       \
        fprintf(stderr, "vector: getref(): index out of bounds: %d\n", index);    \
        abort();                                                                  \
    }                                                                             \
    return &(vc->v[index]);                                                       \
}                                                                                 \
                                                                                  \
vtype *VectorFn(vtype, begin)(Vector(vtype) vc)                                   \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "begin");                                              \
    if (0 >= vc->length) {                                                        \
        fprintf(stderr, "vector: begin(): index out of bounds: %d\n", 0);         \
        abort();                                                                  \
    }                                                                             \
    return &(vc->v[0]);                                                           \
}                                                                                 \
                                                                                  \
vtype *VectorFn(vtype, rbegin)(Vector(vtype) vc)                                  \
{                                                                                 \
    int index = vc->length -1;                                                    \
    VECTOR_NOT_NULLPTR(vc, "rbegin");                                             \
    if (index < 0) {                                                              \
        fprintf(stderr, "vector: rbegin(): index out of bounds: %d\n", index);    \
        abort();                                                                  \
    }                                                                             \
    return &(vc->v[index]);                                                       \
}                                                                                 \
                                                                                  \
bool VectorFn(vtype, set)(Vector(vtype) vc, int index, vtype val)                 \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "set");                                                \
    if (index < 0 || index >= vc->length) {                                       \
        fprintf(stderr, "vector: set(): index out of bounds: %d\n", index);       \
        abort();                                                                  \
    }                                                                             \
    return vc->v[index];                                                          \
}                                                                                 \
                                                                                  \
bool VectorFn(vtype, push)(Vector(vtype) vc, vtype val)                           \
{                                                                                 \
    VECTOR_NOT_NULLPTR(vc, "push");                                               \
    
    return true;                                                                  \
}                                                                                 \
                                                                                  \
vtype VectorFn(vtype, pop)(Vector(vtype) vc)                                      \
{                                                                                 \
     VECTOR_NOT_NULLPTR(vc, "pop");                                               \
     
     return retv;                                                                 \
}                                                                                 \
                                                                                  \
void VectorFn(vtype, free)(Vector(vtype) *vc_ptr)                                 \
{                                                                                 \
    if (!vc_ptr || !*vc_ptr) return;                                              \
    free(*vc_ptr);                                                                \
    *vc_ptr = NULL;                                                               \
}
