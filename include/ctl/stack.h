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

#undef Stack
#undef StackFn

#define Stack(vtype) Stack_##vtype
#define StackFn(vtype, func) Stack_##vtype##_##func

#undef len
/**
 * Return container length
 * @param o Container object
 */
#define len(o) (o->length(o))

#undef STACK_NOT_NULLPTR
/**
 * Return ptr if not null else abort
 * @param ptr Pointer to object
 * @param fn Name of caller function
 * @return ptr If not null
 */
#define STACK_NOT_NULLPTR(ptr, fn) ({                                             \
    void *tmp = ptr;                                                              \
    if (!tmp) {                                                                   \
        fprintf(stderr, "stack: %s(): null pointer\n", fn);                       \
        abort();                                                                  \
    }                                                                             \
    tmp;                                                                          \
})

#undef STACK_FOREACH
/**
 * Iterate through the stack
 * @param st The stack
 * @param action{int i, vtype *value} A code block
 */
#define STACK_FOREACH(st, action) ({                                              \
    STACK_NOT_NULLPTR(st, "FOREACH");                                             \
    for (int _i = 0; _i < st->_.len; _i++) {                                      \
        typeof(st->_.v) const value = &(st->_.v[_i]); value;                      \
        const int i = _i; i;                                                      \
        const int _i = 0; _i;                                                     \
        action;                                                                   \
    }                                                                             \
})

#undef STACK_RFOREACH
/**
 * Iterate in reverse through the stack
 * @param st The stack
 * @param action{int i, vtype *value} A code block
 */
#define STACK_RFOREACH(st, action) ({                                             \
    STACK_NOT_NULLPTR(st, "RFOREACH");                                            \
    for (int _i = st->_.len -1; _i >= 0 ; _i--) {                                 \
        typeof(st->_.v) const value = &(st->_.v[_i]); value;                      \
        const int i = _i; i;                                                      \
        const int _i = 0; _i;                                                     \
        action;                                                                   \
    }                                                                             \
})

#undef STACK_DECLARE
/**
 * Generates function prototype definitions and typedefs for the Stack.
 * vtype should be a primary datatype or typdefed (aliased) pointer/struct.
 * Format: STACK_DECLARE(vtype)
 * @param vtype
 */
#define STACK_DECLARE(vtype)                                                      \
                                                                                  \
typedef struct Stack(vtype) *Stack(vtype);                                        \
                                                                                  \
struct Stack(vtype) {                                                             \
    void          (*free)    (Stack(vtype) *st_ptr);                              \
    size_t        (*length)  (const Stack(vtype) st);                             \
    bool          (*isempty) (const Stack(vtype) st);                             \
    vtype*        (*begin)   (const Stack(vtype) st);                             \
    vtype*        (*end)     (const Stack(vtype) st);                             \
    vtype*        (*rbegin)  (const Stack(vtype) st);                             \
    vtype*        (*next)    (const Stack(vtype) st, vtype *curr);                \
    vtype*        (*rnext)   (const Stack(vtype) st, vtype *curr);                \
    Stack(vtype)  (*push)    (Stack(vtype) st, vtype val);                        \
    vtype         (*top)     (const Stack(vtype) st);                             \
    vtype         (*pop)     (Stack(vtype) st);                                   \
    Stack(vtype)  (*clone)   (const Stack(vtype) st);                             \
    /** private data members, do not modify */                                    \
    struct {                                                                      \
        vtype *v;                                                                 \
        size_t len;                                                               \
        size_t cap;                                                               \
    } _;                                                                          \
};                                                                                \
                                                                                  \
Stack(vtype)  StackFn(vtype, new)();                                              \
void          StackFn(vtype, free)    (Stack(vtype) *st_ptr);                     \
size_t        StackFn(vtype, length)  (const Stack(vtype) st);                    \
bool          StackFn(vtype, isempty) (const Stack(vtype) st);                    \
vtype*        StackFn(vtype, begin)   (const Stack(vtype) st);                    \
vtype*        StackFn(vtype, end)     (const Stack(vtype) st);                    \
vtype*        StackFn(vtype, rbegin)  (const Stack(vtype) st);                    \
vtype*        StackFn(vtype, next)    (const Stack(vtype) st, vtype *curr);       \
vtype*        StackFn(vtype, rnext)   (const Stack(vtype) st, vtype *curr);       \
Stack(vtype)  StackFn(vtype, push)    (Stack(vtype) st, vtype val);               \
vtype         StackFn(vtype, top)     (const Stack(vtype) st);                    \
vtype         StackFn(vtype, pop)     (Stack(vtype) st);                          \
Stack(vtype)  StackFn(vtype, clone)   (const Stack(vtype) st);

#undef STACK_DEFINE
/**
 * Defines the chosen Stack from template: generates the necessary function definitions
 * vtype should be a primary datatype or typdefed (aliased) pointer/struct
 * Format: STACK_DEFINE(vtype)
 * Note: requires STACK_DECLARE(vtype)
 * @param vtype
 */
#define STACK_DEFINE(vtype)                                                       \
                                                                                  \
Stack(vtype) StackFn(vtype, new)()                                                \
{                                                                                 \
    Stack(vtype) st = STACK_NOT_NULLPTR(new(Stack(vtype)), "new");                \
    st->_.v = NULL;                                                               \
    st->_.len = 0;                                                                \
    st->_.cap = 0;                                                                \
    st->free    = StackFn(vtype, free);                                           \
    st->length  = StackFn(vtype, length);                                         \
    st->isempty = StackFn(vtype, isempty);                                        \
    st->begin   = StackFn(vtype, begin);                                          \
    st->end     = StackFn(vtype, end);                                            \
    st->rbegin  = StackFn(vtype, rbegin);                                         \
    st->next    = StackFn(vtype, next);                                           \
    st->rnext   = StackFn(vtype, rnext);                                          \
    st->push    = StackFn(vtype, push);                                           \
    st->top     = StackFn(vtype, top);                                            \
    st->pop     = StackFn(vtype, pop);                                            \
    st->clone   = StackFn(vtype, clone);                                          \
    return st;                                                                    \
}                                                                                 \
                                                                                  \
size_t StackFn(vtype, length)(const Stack(vtype) st)                              \
{                                                                                 \
    STACK_NOT_NULLPTR(st, "length");                                              \
    return st->_.len;                                                             \
}                                                                                 \
                                                                                  \
bool StackFn(vtype, isempty)(const Stack(vtype) st)                               \
{                                                                                 \
    STACK_NOT_NULLPTR(st, "isempty");                                             \
    return !(st->_.len);                                                          \
}                                                                                 \
                                                                                  \
vtype *StackFn(vtype, begin)(const Stack(vtype) st)                               \
{                                                                                 \
    STACK_NOT_NULLPTR(st, "begin");                                               \
    if (0 >= st->_.len) {                                                         \
        fprintf(stderr, "stack: begin(): stack empty\n");                         \
        abort();                                                                  \
    }                                                                             \
    return &(st->_.v[0]);                                                         \
}                                                                                 \
                                                                                  \
vtype *StackFn(vtype, end)(const Stack(vtype) st)                                 \
{                                                                                 \
    return st->begin(st) + st->_.len;                                             \
}                                                                                 \
                                                                                  \
vtype *StackFn(vtype, rbegin)(const Stack(vtype) st)                              \
{                                                                                 \
    int index = st->_.len -1;                                                     \
    STACK_NOT_NULLPTR(st, "rbegin");                                              \
    if (index < 0) {                                                              \
        fprintf(stderr, "stack: rbegin(): stack empty\n");                        \
        abort();                                                                  \
    }                                                                             \
    return &(st->_.v[index]);                                                     \
}                                                                                 \
                                                                                  \
vtype *StackFn(vtype, next)(const Stack(vtype) st, vtype *curr)                   \
{                                                                                 \
    STACK_NOT_NULLPTR(st, "next");                                                \
    if (!curr) return st->begin(st);                                              \
    curr++;                                                                       \
    if (st->begin(st) < curr && curr <= st->rbegin(st))                           \
        return curr;                                                              \
    return NULL;                                                                  \
}                                                                                 \
vtype *StackFn(vtype, rnext)(const Stack(vtype) st, vtype *curr)                  \
{                                                                                 \
    STACK_NOT_NULLPTR(st, "rnext");                                               \
    if (!curr) return st->rbegin(st);                                             \
    curr--;                                                                       \
    if (st->begin(st) <= curr && curr < st->rbegin(st))                           \
        return curr;                                                              \
    return NULL;                                                                  \
}                                                                                 \
                                                                                  \
Stack(vtype) StackFn(vtype, push)(Stack(vtype) st, vtype val)                     \
{                                                                                 \
    STACK_NOT_NULLPTR(st, "push");                                                \
    if (st->_.len >= st->_.cap) {                                                 \
        st->_.cap = (int) (2 * st->_.cap) +1;                                     \
        st->_.v = realloc(st->_.v, sizeof(vtype) * st->_.cap);                    \
    }                                                                             \
    st->_.v[st->_.len++] = val;                                                   \
    return st;                                                                    \
}                                                                                 \
                                                                                  \
vtype StackFn(vtype, top)(const Stack(vtype) st)                                  \
{                                                                                 \
    STACK_NOT_NULLPTR(st, "top");                                                 \
    return *st->rbegin(st);                                                       \
}                                                                                 \
                                                                                  \
vtype StackFn(vtype, pop)(Stack(vtype) st)                                        \
{                                                                                 \
     STACK_NOT_NULLPTR(st, "pop");                                                \
     vtype retv = *st->rbegin(st);                                                \
     st->_.len--;                                                                 \
     return retv;                                                                 \
}                                                                                 \
                                                                                  \
Stack(vtype) StackFn(vtype, clone)(const Stack(vtype) st)                         \
{                                                                                 \
     STACK_NOT_NULLPTR(st, "clone");                                              \
     Stack(vtype) stk = StackFn(vtype, new)();                                    \
     STACK_FOREACH(st, stk->push(stk, *value));                                   \
     return stk;                                                                  \
}                                                                                 \
                                                                                  \
void StackFn(vtype, free)(Stack(vtype) *st_ptr)                                   \
{                                                                                 \
    STACK_NOT_NULLPTR(st_ptr, "free");                                            \
    STACK_NOT_NULLPTR(*st_ptr, "free");                                           \
    free((*st_ptr)->_.v);                                                         \
    free(*st_ptr);                                                                \
    *st_ptr = NULL;                                                               \
}
