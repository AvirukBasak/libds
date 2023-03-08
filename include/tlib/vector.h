#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#undef new
#undef delete

/**
 * Return ptr if not null else abort
 */
#define Vector_notnullptr(ptr, fn) ({                                             \
    if (!ptr) {                                                                   \
        fprintf("vector: %s(): null pointer\n", fn);                              \
        abort();                                                                  \
    }                                                                             \
    ptr;                                                                          \
})

/**
 * new function: returns a pointer to a struct type passed by allocating
 * memory using calloc
 */
#define new(struct_t) ({                                                          \
    Vector_notnullptr(calloc(1, sizeof(struct struct_t)), "new");                 \
})

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

/**
 * Generates function prototype definitions and typedefs for the Vector
 * vtype should be a primary datatype or typdefed (aliased) pointer
 * format: VectorDeclare(vtype)
 */
#define VectorDeclare(vtype)                                                      \
                                                                                  \
typedef struct Vector(vtype) {                                                    \
    vtype *v;                                                                     \
    int refcount;                                                                 \
    size_t length;                                                                \
    void          (*free)    (Vector(vtype) *vc_ptr);                             \
    void          (*clear)   (Vector(vtype) *vc_ptr);                             \
    size_t        (*length)  (Vector(vtype) vc);                                  \
    bool          (*isempty) (Vector(vtype) vc);                                  \
    vtype         (*get)     (Vector(vtype) vc, int index);                       \
    vtype*        (*getref)  (Vector(vtype) vc, int index);                       \
    bool          (*set)     (Vector(vtype) vc, int index, vtype val);            \
    bool          (*push)    (Vector(vtype) vc, vtype val);                       \
    vtype         (*pop)     (Vector(vtype) vc);                                  \
    void          (*print)   (Vector(vtype) vc);                                  \
    Vector(vtype) (*copy)    (Vector(vtype) vc);                                  \
    Vector(vtype) (*clone)   (Vector(vtype) vc);                                  \
} *Vector(vtype);                                                                 \
                                                                                  \
Vector(vtype) VectorFn(vtype, new)();                                             \
void          VectorFn(vtype, free)    (Vector(vtype) *vc_ptr);                   \
void          VectorFn(vtype, clear)   (Vector(vtype) *vc_ptr);                   \
size_t        VectorFn(vtype, length)  (Vector(vtype) vc);                        \
bool          VectorFn(vtype, isempty) (Vector(vtype) vc);                        \
vtype         VectorFn(vtype, get)     (Vector(vtype) vc, int index);             \
vtype*        VectorFn(vtype, getref)  (Vector(vtype) vc, int index);             \
bool          VectorFn(vtype, set)     (Vector(vtype) vc, int index, vtype val);  \
bool          VectorFn(vtype, push)    (Vector(vtype) vc, vtype val);             \
vtype         VectorFn(vtype, pop)     (Vector(vtype) vc);                        \
void          VectorFn(vtype, print)   (Vector(vtype) vc);                        \
Vector(vtype) VectorFn(vtype, copy)    (Vector(vtype) vc);                        \
Vector(vtype) VectorFn(vtype, clone)   (Vector(vtype) vc);

/**
 * Defines the chosen Vector from template: generates the necessary function definitions
 * vtype should be a primary datatype or typdefed (aliased) pointer
 * format: VectorDefine(vtype, func_print(const value))
 * NOTE: requires VectorDeclare(vtype)
 */
#define VectorDefine(vtype, func_print)                                           \
                                                                                  \
Vector(vtype) VectorFn(vtype, new)()                                              \
{                                                                                 \
    Vector(vtype) vc = new(Vector(vtype));                                        \
    vc->v = NULL;                                                                 \
    vc->refcount = 1;                                                             \
    vc->length = 0;                                                               \
    vc->free    = VectorFn(vtype, free);                                          \
    vc->length  = VectorFn(vtype, length);                                        \
    vc->isempty = VectorFn(vtype, isempty);                                       \
    vc->get     = VectorFn(vtype, get);                                           \
    vc->getref  = VectorFn(vtype, getref);                                        \
    vc->set     = VectorFn(vtype, set);                                           \
    vc->push    = VectorFn(vtype, push);                                          \
    vc->pop     = VectorFn(vtype, pop);                                           \
    vc->print   = VectorFn(vtype, print);                                         \
    vc->copy    = VectorFn(vtype, copy);                                          \
    vc->clone   = VectorFn(vtype, clone);                                         \
    return vc;                                                                    \
}                                                                                 \
                                                                                  \
size_t VectorFn(vtype, length)(Vector(vtype) vc)                                  \
{                                                                                 \
    Vector_notnullptr(vc, "length");                                              \
    return vc->length;                                                            \
}                                                                                 \
                                                                                  \
bool VectorFn(vtype, isempty)(Vector(vtype) vc)                                   \
{                                                                                 \
    Vector_notnullptr(vc, "isempty");                                             \
    return !(vc->length);                                                         \
}                                                                                 \
                                                                                  \
vtype VectorFn(vtype, get)(Vector(vtype) vc, int index)                           \
{                                                                                 \
    Vector_notnullptr(vc, "get");                                                 \
    if (index < 0 || index >= vc->length) {                                       \
        fprintf(stderr, "vector: get(): index out of bounds: %d\n", index);       \
        abort();                                                                  \
    }                                                                             \
    return vc->v[index];                                                          \
}                                                                                 \
                                                                                  \
vtype *VectorFn(vtype, getref)(Vector(vtype) vc, int index)                       \
{                                                                                 \
    Vector_notnullptr(vc, "getref");                                              \
    if (index < 0 || index >= vc->length) {                                       \
        fprintf(stderr, "vector: getref(): index out of bounds: %d\n", index);    \
        abort();                                                                  \
    }                                                                             \
    return &(vc->v[index]);                                                       \
}                                                                                 \
                                                                                  \
bool VectorFn(vtype, set)(Vector(vtype) vc, int index, vtype val)                 \
{                                                                                 \
    Vector_notnullptr(vc, "set");                                                 \
    if (index < 0 || index >= vc->length) {                                       \
        fprintf(stderr, "vector: set(): index out of bounds: %d\n", index);       \
        abort();                                                                  \
    }                                                                             \
    return vc->v[index];                                                          \
}                                                                                 \
                                                                                  \
bool VectorFn(vtype, push)(Vector(vtype) vc, vtype val)                           \
{                                                                                 \
    Vector_notnullptr(vc, "push");                                                \
    
    return true;                                                                  \
}                                                                                 \
                                                                                  \
vtype VectorFn(vtype, pop)(Vector(vtype) vc)                                      \
{                                                                                 \
     Vector_notnullptr(vc, "push");                                               \
     
     return retv;                                                                 \
}                                                                                 \
                                                                                  \
void VectorFn(vtype, print)(Vector(vtype) vc)                                     \
{                                                                                 \
    Vector_notnullptr(vc, "push");                                                \
    if (!vc->v) { printf("{ }\n"); return; }                                      \
    printf("{\n");                                                                \
    for (int i = 0; i < vc->length; i++) {                                        \
        const vtype value = vc->v[i];                                             \
        printf("    ");                                                           \
        {                                                                         \
            const Vector(vtype) vc = NULL; vc;                                    \
            func_print;                                                           \
        }                                                                         \
        printf("\n");                                                             \
    }                                                                             \
    printf("}\n");                                                                \
}                                                                                 \
                                                                                  \
void VectorFn(vtype, free)(Vector(vtype) *vc_ptr)                                 \
{                                                                                 \
    if (!vc_ptr || !*vc_ptr) return;                                              \
    free(*vc_ptr);                                                                \
    *vc_ptr = NULL;                                                               \
}                                                                                 \
                                                                                  \
void VectorFn(vtype, clear)(Vector(vtype) *vc_ptr)                                \
{                                                                                 \
    if (!vc_ptr || !*vc_ptr) return;                                              \
    for (int i = 0; i < vc->length; i++) {                                        \
        free(vc->v[i]);                                                           \
    }                                                                             \
    free(*vc_ptr);                                                                \
    *vc_ptr = NULL;                                                               \
}
