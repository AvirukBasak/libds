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

#define Stack(vtype) Stack_##vtype
#define StackFn(vtype, func) Stack_##vtype##_##func

#undef STACK_NOT_NULLPTR
/**
 * Return ptr if not null else abort
 * @param ptr Pointer to object
 * @param fn Name of caller function
 * @return ptr If not null
 */
#define STACK_NOT_NULLPTR(ptr, fn) ({                                             \
    if (!ptr) {                                                                   \
        fprintf(stderr, "stack: %s(): null pointer\n", fn);                       \
        abort();                                                                  \
    }                                                                             \
    ptr;                                                                          \
})

#undef STACK_FOREACH
/**
 * Iterate through the stack
 * @param st The stack
 * @param action{int i, vtype *value} A code block
 */
#define STACK_FOREACH(st, action) ({                                              \
    STACK_NOT_NULLPTR(st, "FOREACH");                                             \
    for (int _i = 0; _i < st->len; _i++) {                                        \
        typeof(st->v) const value = &(st->v[_i]); value;                          \
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
    for (int _i = st->len -1; _i >= 0 ; _i--) {                                   \
        typeof(st->v) const value = &(st->v[_i]); value;                          \
        const int i = _i; i;                                                      \
        const int _i = 0; _i;                                                     \
        action;                                                                   \
    }                                                                             \
})

/**
 * Generates function prototype definitions and typedefs for the Stack
 * vtype should be a primary datatype or typdefed (aliased) pointer/struct
 * format: STACK_DECLARE(vtype)
 * @param vtype
 */
#define STACK_DECLARE(vtype)                                                      \
                                                                                  \
typedef struct Stack(vtype) *Stack(vtype);                                        \
                                                                                  \
struct Stack(vtype) {                                                             \
    vtype *v;                                                                     \
    size_t len;                                                                   \
    size_t cap;                                                                   \
    void          (*free)    (Stack(vtype) *st_ptr);                              \
    size_t        (*length)  (Stack(vtype) st);                                   \
    bool          (*isempty) (Stack(vtype) st);                                   \
    vtype*        (*begin)   (Stack(vtype) st);                                   \
    vtype*        (*rbegin)  (Stack(vtype) st);                                   \
    vtype*        (*next)    (Stack(vtype) st, vtype *curr);                      \
    vtype*        (*rnext)   (Stack(vtype) st, vtype *curr);                      \
    bool          (*push)    (Stack(vtype) st, vtype val);                        \
    vtype         (*top)     (Stack(vtype) st);                                   \
    vtype         (*pop)     (Stack(vtype) st);                                   \
    Stack(vtype)  (*clone)   (Stack(vtype) st);                                   \
};                                                                                \
                                                                                  \
Stack(vtype)  StackFn(vtype, new)();                                              \
void          StackFn(vtype, free)    (Stack(vtype) *st_ptr);                     \
size_t        StackFn(vtype, length)  (Stack(vtype) st);                          \
bool          StackFn(vtype, isempty) (Stack(vtype) st);                          \
vtype*        StackFn(vtype, begin)   (Stack(vtype) st);                          \
vtype*        StackFn(vtype, rbegin)  (Stack(vtype) st);                          \
vtype*        StackFn(vtype, next)    (Stack(vtype) st, vtype *curr);             \
vtype*        StackFn(vtype, rnext)   (Stack(vtype) st, vtype *curr);             \
bool          StackFn(vtype, push)    (Stack(vtype) st, vtype val);               \
vtype         StackFn(vtype, top)     (Stack(vtype) st);                          \
vtype         StackFn(vtype, pop)     (Stack(vtype) st);                          \
Stack(vtype)  StackFn(vtype, clone)   (Stack(vtype) st);

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
    st->v = NULL;                                                                 \
    st->len = 0;                                                                  \
    st->cap = 0;                                                                  \
    st->free    = StackFn(vtype, free);                                           \
    st->length  = StackFn(vtype, length);                                         \
    st->isempty = StackFn(vtype, isempty);                                        \
    st->begin   = StackFn(vtype, begin);                                          \
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
size_t StackFn(vtype, length)(Stack(vtype) st)                                    \
{                                                                                 \
    STACK_NOT_NULLPTR(st, "length");                                              \
    return st->len;                                                               \
}                                                                                 \
                                                                                  \
bool StackFn(vtype, isempty)(Stack(vtype) st)                                     \
{                                                                                 \
    STACK_NOT_NULLPTR(st, "isempty");                                             \
    return !(st->len);                                                            \
}                                                                                 \
                                                                                  \
vtype *StackFn(vtype, begin)(Stack(vtype) st)                                     \
{                                                                                 \
    STACK_NOT_NULLPTR(st, "begin");                                               \
    if (0 >= st->len) {                                                           \
        fprintf(stderr, "stack: begin(): stack empty\n");                         \
        abort();                                                                  \
    }                                                                             \
    return &(st->v[0]);                                                           \
}                                                                                 \
                                                                                  \
vtype *StackFn(vtype, rbegin)(Stack(vtype) st)                                    \
{                                                                                 \
    int index = st->len -1;                                                       \
    STACK_NOT_NULLPTR(st, "rbegin");                                              \
    if (index < 0) {                                                              \
        fprintf(stderr, "stack: rbegin(): index out of bounds: %d\n", index);     \
        abort();                                                                  \
    }                                                                             \
    return &(st->v[index]);                                                       \
}                                                                                 \
                                                                                  \
vtype *StackFn(vtype, next)(Stack(vtype) st, vtype *curr)                         \
{                                                                                 \
    STACK_NOT_NULLPTR(st, "next");                                                \
    if (!curr) return st->begin(st);                                              \
    curr++;                                                                       \
    if (st->begin(st) < curr && curr <= st->rbegin(st))                           \
        return curr;                                                              \
    return NULL;                                                                  \
}                                                                                 \
vtype *StackFn(vtype, rnext)(Stack(vtype) st, vtype *curr)                        \
{                                                                                 \
    STACK_NOT_NULLPTR(st, "rnext");                                               \
    if (!curr) return st->rbegin(st);                                             \
    curr--;                                                                       \
    if (st->begin(st) <= curr && curr < st->rbegin(st))                           \
        return curr;                                                              \
    return NULL;                                                                  \
}                                                                                 \
                                                                                  \
bool StackFn(vtype, push)(Stack(vtype) st, vtype val)                             \
{                                                                                 \
    STACK_NOT_NULLPTR(st, "push");                                                \
    if (st->len >= st->cap) {                                                     \
        st->cap = (int) (2 * st->cap) +1;                                         \
        st->v = realloc(st->v, sizeof(vtype) * st->cap);                          \
    }                                                                             \
    st->v[st->len++] = val;                                                       \
    return true;                                                                  \
}                                                                                 \
                                                                                  \
vtype StackFn(vtype, top)(Stack(vtype) st)                                        \
{                                                                                 \
    STACK_NOT_NULLPTR(st, "top");                                                 \
    return *st->rbegin(st);                                                       \
}                                                                                 \
                                                                                  \
vtype StackFn(vtype, pop)(Stack(vtype) st)                                        \
{                                                                                 \
     STACK_NOT_NULLPTR(st, "pop");                                                \
     vtype retv = *st->rbegin(st);                                                \
     st->len--;                                                                   \
     return retv;                                                                 \
}                                                                                 \
                                                                                  \
Stack(vtype) StackFn(vtype, clone)(Stack(vtype) st)                               \
{                                                                                 \
     STACK_NOT_NULLPTR(st, "clone");                                              \
     Stack(vtype) stk = StackFn(vtype, new)();                                    \
     STACK_FOREACH(st, stk->push(stk, *value));                                   \
     return stk;                                                                  \
}                                                                                 \
                                                                                  \
void StackFn(vtype, free)(Stack(vtype) *st_ptr)                                   \
{                                                                                 \
    if (!st_ptr || !*st_ptr) return;                                              \
    free(*st_ptr);                                                                \
    *st_ptr = NULL;                                                               \
}
