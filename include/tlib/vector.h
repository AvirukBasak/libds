#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#undef new
#undef delete

/**
 * new function: returns a pointer to a struct type passed by allocating
 * memory using calloc
 */
#define new(struct_t) ({                                                          \
    struct struct_t *tmp = calloc(1, sizeof(struct struct_t));                    \
    if (!tmp) abort();                                                            \
    tmp;                                                                          \
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
 * format: VectorDeclarePrototypes(vtype)
 */
#define VectorDeclarePrototypes(vtype)                                            \
                                                                                  \
typedef struct Vector(vtype) {                                                    \
    vtype *v;                                                                     \
    size_t length;                                                                \
    void          (*free)    (Vector(vtype) *vc_ptr);                             \
    size_t        (*length)  (Vector(vtype) vc);                                  \
    bool          (*isempty) (Vector(vtype) vc);                                  \
    vtype         (*get)     (Vector(vtype) vc, int index);                       \
    vtype*        (*getref)  (Vector(vtype) vc, int index);                       \
    bool          (*set)     (Vector(vtype) vc, int index, vtype val);            \
    bool          (*push)    (Vector(vtype) vc, vtype val);                       \
    vtype         (*pop)     (Vector(vtype) vc);                                  \
    void          (*print)   (Vector(vtype) vc);                                  \
    Vector(vtype) (*clone)   (Vector(vtype) vc);                                  \
} *Vector(vtype);                                                                 \
                                                                                  \
Vector(vtype) VectorFn(vtype, new)();                                             \
void          VectorFn(vtype, free)    (Vector(vtype) *vc_ptr);                   \
size_t        VectorFn(vtype, length)  (Vector(vtype) vc);                        \
bool          VectorFn(vtype, isempty) (Vector(vtype) vc);                        \
vtype         VectorFn(vtype, get)     (Vector(vtype) vc, int index);             \
vtype*        VectorFn(vtype, getref)  (Vector(vtype) vc, int index);             \
bool          VectorFn(vtype, set)     (Vector(vtype) vc, int index, vtype val);  \
bool          VectorFn(vtype, push)    (Vector(vtype) vc, vtype val);             \
vtype         VectorFn(vtype, pop)     (Vector(vtype) vc);                        \
void          VectorFn(vtype, print)   (Vector(vtype) vc);                        \
Vector(vtype) VectorFn(vtype, clone)   (Vector(vtype) vc);

/**
 * Defines the chosen Vector from template: generates the necessary function definitions
 * vtype should be a primary datatype or typdefed (aliased) pointer
 * format: VectorDefine(vtype, func_print(const value))
 * NOTE: requires VectorDeclarePrototypes(vtype)
 */
#define VectorDefine(vtype, func_print)                                           \
                                                                                  \
Vector(vtype) VectorFn(vtype, new)()                                              \
{                                                                                 \
    Vector(vtype) vc = new(Vector(vtype));                                        \
    vc->v = NULL;                                                                 \
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
    vc->clone   = VectorFn(vtype, clone);                                         \
    return vc;                                                                    \
}                                                                                 \
                                                                                  \
size_t VectorFn(vtype, length)(Vector(vtype) vc)                                  \
{                                                                                 \
    if (!vc) abort();                                                             \
    return vc->length;                                                            \
}                                                                                 \
                                                                                  \
bool VectorFn(vtype, isempty)(Vector(vtype) vc)                                   \
{                                                                                 \
    if (!vc) abort();                                                             \
    return !(vc->length);                                                         \
}                                                                                 \
                                                                                  \
vtype VectorFn(vtype, get)(Vector(vtype) vc, int index)                           \
{                                                                                 \
    if (!vc) abort();                                                             \
    if (index < 0 || index >= vc->length) {                                       \
        fprintf(stderr, "vector: index out of bounds: %d\n", index);              \
        abort();                                                                  \
    }                                                                             \
    return vc->v[index];                                                          \
}                                                                                 \
                                                                                  \
vtype *VectorFn(vtype, getref)(Vector(vtype) vc, int index)                       \
{                                                                                 \
    if (!vc) abort();                                                             \
    if (index < 0 || index >= vc->length) {                                       \
        fprintf(stderr, "vector: index out of bounds: %d\n", index);              \
        abort();                                                                  \
    }                                                                             \
    return &(vc->v[index]);                                                       \
}                                                                                 \
                                                                                \
bool Vector_##vtype##_push(Vector(vtype) vc, vtype val)                         \
{                                                                               \
    if (!st) abort();                                                           \
    Vector_##vtype##_node node = new(Vector_##vtype##_node);                    \
    node->val = val;                                                            \
    node->next = vc->top_ptr;                                                   \
    vc->top_ptr = node;                                                         \
    vc->top = &vc->top_ptr->val;                                                \
    return true;                                                                \
}                                                                               \
                                                                                \
vtype Vector_##vtype##_pop(Vector(vtype) vc)                                     \
{                                                                               \
     if (!st) abort();                                                          \
     if (!vc->top_ptr) return (vtype) 0;                                        \
     Vector_##vtype##_node tmp = vc->top_ptr;                                    \
     vc->top_ptr = tmp->next;                                                   \
     vc->top = &vc->top_ptr->val;                                               \
     vtype retv = tmp->val;                                                     \
     free(tmp);                                                                 \
     return retv;                                                               \
}                                                                               \
                                                                                \
void Vector_##vtype##_print(Vector(vtype) vc)                                    \
{                                                                               \
    if (!st) abort();                                                           \
    Vector_##vtype##_node p = vc->top_ptr;                                       \
    if (!p) { printf("{ }\n"); return; }                                        \
    printf("{\n");                                                              \
    while (p) {                                                                 \
        const vtype value = p->val;                                             \
        printf("    ");                                                         \
        {                                                                       \
            const Vector(vtype) vc = NULL;                                      \
            const Vector_##vtype##_node p = NULL;                                \
            (st, p);                                                            \
            func_print;                                                         \
        }                                                                       \
        printf("\n");                                                           \
        p = p->next;                                                            \
    }                                                                           \
    printf("}\n");                                                              \
}                                                                               \
                                                                                \
void Vector_##vtype##_free(Vector_##vtype *st_ptr)                                \
{                                                                               \
    if (!st_ptr || !*st_ptr) return;                                            \
    Vector_##vtype##_node p = (*st_ptr)->top_ptr;                                \
    while (p) {                                                                 \
        free(p);                                                                \
        p = p->next;                                                            \
    }                                                                           \
    free(*st_ptr);                                                              \
    *st_ptr = NULL;                                                             \
}
