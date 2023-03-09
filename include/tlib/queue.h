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

#define Queue(vtype) Queue_##vtype
#define QueueFn(vtype, func) Queue_##vtype##_##func

#undef QUEUE_NOT_NULLPTR
/**
 * Return ptr if not null else abort
 * @param ptr Pointer to object
 * @param fn Name of caller function
 * @return ptr If not null
 */
#define QUEUE_NOT_NULLPTR(ptr, fn) ({                                             \
    if (!ptr) {                                                                   \
        fprintf(stderr, "queue: %s(): null pointer\n", fn);                       \
        abort();                                                                  \
    }                                                                             \
    ptr;                                                                          \
})

#undef QUEUE_FOREACH
/**
 * Iterate through the queue
 * @param qu The queue
 * @param action{int i, vtype *value} A code block
 */
#define QUEUE_FOREACH(qu, action) ({                                              \
    QUEUE_NOT_NULLPTR(qu, "FOREACH");                                             \
    for (int _i = qu->fnt; _i < qu->rer; _i++) {                                  \
        typeof(qu->v) const value = &(qu->v[_i]); value;                          \
        const int i = _i; i;                                                      \
        const int _i = 0; _i;                                                     \
        action;                                                                   \
    }                                                                             \
})

#undef QUEUE_RFOREACH
/**
 * Iterate in reverse through the queue
 * @param qu The queue
 * @param action{int i, vtype *value} A code block
 */
#define QUEUE_RFOREACH(qu, action) ({                                             \
    QUEUE_NOT_NULLPTR(qu, "RFOREACH");                                            \
    for (int _i = qu->rer -1; _i >= qu->fnt ; _i--) {                             \
        typeof(qu->v) const value = &(qu->v[_i]); value;                          \
        const int i = _i; i;                                                      \
        const int _i = 0; _i;                                                     \
        action;                                                                   \
    }                                                                             \
})

/**
 * Generates function prototype definitions and typedefs for the Queue
 * vtype should be a primary datatype or typdefed (aliased) pointer/struct
 * format: QUEUE_DECLARE(vtype)
 * @param vtype
 */
#define QUEUE_DECLARE(vtype)                                                      \
                                                                                  \
typedef struct Queue(vtype) *Queue(vtype);                                        \
                                                                                  \
struct Queue(vtype) {                                                             \
    vtype *v;                                                                     \
    size_t fnt;                                                                   \
    size_t rer;                                                                   \
    size_t cap;                                                                   \
    void          (*free)    (Queue(vtype) *qu_ptr);                              \
    size_t        (*length)  (Queue(vtype) qu);                                   \
    bool          (*isempty) (Queue(vtype) qu);                                   \
    vtype*        (*getref)  (Queue(vtype) qu, int index);                        \
    vtype*        (*begin)   (Queue(vtype) qu);                                   \
    vtype*        (*rbegin)  (Queue(vtype) qu);                                   \
    vtype*        (*next)    (Queue(vtype) qu, vtype *curr);                      \
    vtype*        (*rnext)   (Queue(vtype) qu, vtype *curr);                      \
    bool          (*push)    (Queue(vtype) qu, vtype val);                        \
    vtype         (*front)   (Queue(vtype) qu);                                   \
    vtype         (*pop)     (Queue(vtype) qu);                                   \
    Queue(vtype)  (*clone)   (Queue(vtype) qu);                                   \
};                                                                                \
                                                                                  \
Queue(vtype)  QueueFn(vtype, new)();                                              \
void          QueueFn(vtype, free)    (Queue(vtype) *qu_ptr);                     \
size_t        QueueFn(vtype, length)  (Queue(vtype) qu);                          \
bool          QueueFn(vtype, isempty) (Queue(vtype) qu);                          \
vtype*        QueueFn(vtype, getref)  (Queue(vtype) qu, int index);               \
vtype*        QueueFn(vtype, begin)   (Queue(vtype) qu);                          \
vtype*        QueueFn(vtype, rbegin)  (Queue(vtype) qu);                          \
vtype*        QueueFn(vtype, next)    (Queue(vtype) qu, vtype *curr);             \
vtype*        QueueFn(vtype, rnext)   (Queue(vtype) qu, vtype *curr);             \
bool          QueueFn(vtype, push)    (Queue(vtype) qu, vtype val);               \
vtype         QueueFn(vtype, front)   (Queue(vtype) qu);                          \
vtype         QueueFn(vtype, pop)     (Queue(vtype) qu);                          \
Queue(vtype)  QueueFn(vtype, clone)   (Queue(vtype) qu);

/**
 * Defines the chosen Queue from template: generates the necessary function definitions
 * vtype should be a primary datatype or typdefed (aliased) pointer/struct
 * Format: QUEUE_DEFINE(vtype)
 * Note: requires QUEUE_DECLARE(vtype)
 * @param vtype
 */
#define QUEUE_DEFINE(vtype)                                                       \
                                                                                  \
Queue(vtype) QueueFn(vtype, new)()                                                \
{                                                                                 \
    Queue(vtype) qu = QUEUE_NOT_NULLPTR(new(Queue(vtype)), "new");                \
    qu->v = NULL;                                                                 \
    qu->fnt = 0;                                                                  \
    qu->rer = 0;                                                                  \
    qu->cap = 0;                                                                  \
    qu->free    = QueueFn(vtype, free);                                           \
    qu->length  = QueueFn(vtype, length);                                         \
    qu->isempty = QueueFn(vtype, isempty);                                        \
    qu->getref  = QueueFn(vtype, getref);                                         \
    qu->begin   = QueueFn(vtype, begin);                                          \
    qu->rbegin  = QueueFn(vtype, rbegin);                                         \
    qu->next    = QueueFn(vtype, next);                                           \
    qu->rnext   = QueueFn(vtype, rnext);                                          \
    qu->push    = QueueFn(vtype, push);                                           \
    qu->front   = QueueFn(vtype, front);                                          \
    qu->pop     = QueueFn(vtype, pop);                                            \
    qu->clone   = QueueFn(vtype, clone);                                          \
    return qu;                                                                    \
}                                                                                 \
                                                                                  \
size_t QueueFn(vtype, length)(Queue(vtype) qu)                                    \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "length");                                              \
    return qu->rer - qu->fnt;                                                     \
}                                                                                 \
                                                                                  \
bool QueueFn(vtype, isempty)(Queue(vtype) qu)                                     \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "isempty");                                             \
    return qu->rer - qu->fnt <= 0;                                                \
}                                                                                 \
                                                                                  \
vtype *QueueFn(vtype, getref)(Queue(vtype) qu, int index)                         \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "getref");                                              \
    if (index < qu->fnt || index >= qu->rer) {                                    \
        fprintf(stderr, "queue: getref(): index out of bounds: %d\n", index);     \
        abort();                                                                  \
    }                                                                             \
    return &(qu->v[index]);                                                       \
}                                                                                 \
                                                                                  \
vtype *QueueFn(vtype, begin)(Queue(vtype) qu)                                     \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "begin");                                               \
    if (qu->fnt >= qu->rer) {                                                     \
        fprintf(stderr, "queue: begin(): queue empty\n");                         \
        abort();                                                                  \
    }                                                                             \
    return &(qu->v[qu->fnt]);                                                     \
}                                                                                 \
                                                                                  \
vtype *QueueFn(vtype, rbegin)(Queue(vtype) qu)                                    \
{                                                                                 \
    int index = qu->rer -1;                                                       \
    QUEUE_NOT_NULLPTR(qu, "rbegin");                                              \
    if (index < qu->fnt) {                                                        \
        fprintf(stderr, "queue: rbegin(): queue empty\n");                        \
        abort();                                                                  \
    }                                                                             \
    return &(qu->v[index]);                                                       \
}                                                                                 \
                                                                                  \
vtype *QueueFn(vtype, next)(Queue(vtype) qu, vtype *curr)                         \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "next");                                                \
    if (!curr) return qu->begin(qu);                                              \
    curr++;                                                                       \
    if (qu->begin(qu) < curr && curr <= qu->rbegin(qu))                           \
        return curr;                                                              \
    return NULL;                                                                  \
}                                                                                 \
vtype *QueueFn(vtype, rnext)(Queue(vtype) qu, vtype *curr)                        \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "rnext");                                               \
    if (!curr) return qu->rbegin(qu);                                             \
    curr--;                                                                       \
    if (qu->begin(qu) <= curr && curr < qu->rbegin(qu))                           \
        return curr;                                                              \
    return NULL;                                                                  \
}                                                                                 \
                                                                                  \
bool QueueFn(vtype, push)(Queue(vtype) qu, vtype val)                             \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "push");                                                \
    if (qu->rer >= qu->cap) {                                                     \
        qu->cap = (int) (2 * qu->cap) +1;                                         \
        qu->v = realloc(qu->v, sizeof(vtype) * qu->cap);                          \
    }                                                                             \
    qu->v[qu->rer++] = val;                                                       \
    return true;                                                                  \
}                                                                                 \
                                                                                  \
vtype QueueFn(vtype, front)(Queue(vtype) qu)                                      \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "front");                                               \
    return *qu->getref(qu, qu->fnt);                                              \
}                                                                                 \
                                                                                  \
vtype QueueFn(vtype, pop)(Queue(vtype) qu)                                        \
{                                                                                 \
     QUEUE_NOT_NULLPTR(qu, "pop");                                                \
     vtype retv = *qu->getref(qu, qu->fnt);                                       \
     qu->fnt++;                                                                   \
     if (qu->isempty(qu)) qu->rer = qu->fnt = 0;                                  \
     return retv;                                                                 \
}                                                                                 \
                                                                                  \
Queue(vtype) QueueFn(vtype, clone)(Queue(vtype) qu)                               \
{                                                                                 \
     QUEUE_NOT_NULLPTR(qu, "clone");                                              \
     Queue(vtype) stk = QueueFn(vtype, new)();                                    \
     QUEUE_FOREACH(qu, stk->push(stk, *value));                                   \
     return stk;                                                                  \
}                                                                                 \
                                                                                  \
void QueueFn(vtype, free)(Queue(vtype) *qu_ptr)                                   \
{                                                                                 \
    if (!qu_ptr || !*qu_ptr) return;                                              \
    free(*qu_ptr);                                                                \
    *qu_ptr = NULL;                                                               \
}
