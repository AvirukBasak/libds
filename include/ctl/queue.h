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

#undef Queue
#undef QueueFn

#undef len
/**
 * Return container length
 * @param o Container object
 */
#define len(o) (o->length(o))

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
    void *tmp = ptr;                                                              \
    if (!tmp) {                                                                   \
        fprintf(stderr, "queue: %s(): null pointer\n", fn);                       \
        abort();                                                                  \
    }                                                                             \
    tmp;                                                                          \
})

#undef QUEUE_FOREACH
/**
 * Iterate through the queue
 * @param qu The queue
 * @param action{int i, vtype *value} A code block
 */
#define QUEUE_FOREACH(qu, action) ({                                              \
    QUEUE_NOT_NULLPTR(qu, "FOREACH");                                             \
    for (int _i = qu->_.fnt; _i < qu->_.rer; _i++) {                              \
        typeof(qu->_.v) const value = &(qu->_.v[_i]); value;                      \
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
    for (int _i = qu->_.rer -1; _i >= qu->_.fnt ; _i--) {                         \
        typeof(qu->_.v) const value = &(qu->_.v[_i]); value;                      \
        const int i = _i; i;                                                      \
        const int _i = 0; _i;                                                     \
        action;                                                                   \
    }                                                                             \
})

#undef QUEUE_DECLARE
/**
 * Generates function prototype definitions and typedefs for the Queue.
 * vtype should be a primary datatype or typdefed (aliased) pointer/struct.
 * Format: QUEUE_DECLARE(vtype)
 * @param vtype
 */
#define QUEUE_DECLARE(vtype)                                                      \
                                                                                  \
typedef struct Queue(vtype) *Queue(vtype);                                        \
                                                                                  \
struct Queue(vtype) {                                                             \
    void          (*free)    (Queue(vtype) *qu_ptr);                              \
    size_t        (*length)  (const Queue(vtype) qu);                             \
    bool          (*isempty) (const Queue(vtype) qu);                             \
    vtype*        (*getref)  (const Queue(vtype) qu, int index);                  \
    vtype*        (*begin)   (const Queue(vtype) qu);                             \
    vtype*        (*end)     (const Queue(vtype) qu);                             \
    vtype*        (*rbegin)  (const Queue(vtype) qu);                             \
    vtype*        (*next)    (const Queue(vtype) qu, vtype *curr);                \
    vtype*        (*rnext)   (const Queue(vtype) qu, vtype *curr);                \
    Queue(vtype)  (*push)    (Queue(vtype) qu, vtype val);                        \
    vtype         (*front)   (const Queue(vtype) qu);                             \
    vtype         (*pop)     (Queue(vtype) qu);                                   \
    Queue(vtype)  (*clone)   (const Queue(vtype) qu);                             \
    /** private data members, do not modify */                                    \
    struct {                                                                      \
        vtype *v;                                                                 \
        size_t fnt;                                                               \
        size_t rer;                                                               \
        size_t cap;                                                               \
    } _;                                                                          \
};                                                                                \
                                                                                  \
Queue(vtype)  QueueFn(vtype, new)();                                              \
void          QueueFn(vtype, free)    (Queue(vtype) *qu_ptr);                     \
size_t        QueueFn(vtype, length)  (const Queue(vtype) qu);                    \
bool          QueueFn(vtype, isempty) (const Queue(vtype) qu);                    \
vtype*        QueueFn(vtype, getref)  (const Queue(vtype) qu, int index);         \
vtype*        QueueFn(vtype, begin)   (const Queue(vtype) qu);                    \
vtype*        QueueFn(vtype, end)     (const Queue(vtype) qu);                    \
vtype*        QueueFn(vtype, rbegin)  (const Queue(vtype) qu);                    \
vtype*        QueueFn(vtype, next)    (const Queue(vtype) qu, vtype *curr);       \
vtype*        QueueFn(vtype, rnext)   (const Queue(vtype) qu, vtype *curr);       \
Queue(vtype)  QueueFn(vtype, push)    (Queue(vtype) qu, vtype val);               \
vtype         QueueFn(vtype, front)   (const Queue(vtype) qu);                    \
vtype         QueueFn(vtype, pop)     (Queue(vtype) qu);                          \
Queue(vtype)  QueueFn(vtype, clone)   (const Queue(vtype) qu);

#undef QUEUE_DEFINE
/**
 * Defines the chosen Queue from template: generates the necessary function definitions.
 * vtype should be a primary datatype or typdefed (aliased) pointer/struct.
 * Format: QUEUE_DEFINE(vtype)
 * Note: requires QUEUE_DECLARE(vtype)
 * @param vtype
 */
#define QUEUE_DEFINE(vtype)                                                       \
                                                                                  \
Queue(vtype) QueueFn(vtype, new)()                                                \
{                                                                                 \
    Queue(vtype) qu = QUEUE_NOT_NULLPTR(new(Queue(vtype)), "new");                \
    qu->_.v = NULL;                                                               \
    qu->_.fnt = 0;                                                                \
    qu->_.rer = 0;                                                                \
    qu->_.cap = 0;                                                                \
    qu->free    = QueueFn(vtype, free);                                           \
    qu->length  = QueueFn(vtype, length);                                         \
    qu->isempty = QueueFn(vtype, isempty);                                        \
    qu->getref  = QueueFn(vtype, getref);                                         \
    qu->begin   = QueueFn(vtype, begin);                                          \
    qu->end     = QueueFn(vtype, end);                                            \
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
size_t QueueFn(vtype, length)(const Queue(vtype) qu)                              \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "length");                                              \
    return qu->_.rer - qu->_.fnt;                                                 \
}                                                                                 \
                                                                                  \
bool QueueFn(vtype, isempty)(const Queue(vtype) qu)                               \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "isempty");                                             \
    return qu->_.rer - qu->_.fnt <= 0;                                            \
}                                                                                 \
                                                                                  \
vtype *QueueFn(vtype, getref)(const Queue(vtype) qu, int index)                   \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "getref");                                              \
    if (index < qu->_.fnt || index >= qu->_.rer) {                                \
        fprintf(stderr, "queue: getref(): index out of bounds: %d\n", index);     \
        abort();                                                                  \
    }                                                                             \
    return &(qu->_.v[index]);                                                     \
}                                                                                 \
                                                                                  \
vtype *QueueFn(vtype, begin)(const Queue(vtype) qu)                               \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "begin");                                               \
    if (qu->_.fnt >= qu->_.rer) {                                                 \
        fprintf(stderr, "queue: begin(): queue empty\n");                         \
        abort();                                                                  \
    }                                                                             \
    return &(qu->_.v[qu->_.fnt]);                                                 \
}                                                                                 \
                                                                                  \
vtype *QueueFn(vtype, end)(const Queue(vtype) qu)                                 \
{                                                                                 \
    return qu->begin(qu) + qu->_.rer;                                             \
}                                                                                 \
                                                                                  \
vtype *QueueFn(vtype, rbegin)(const Queue(vtype) qu)                              \
{                                                                                 \
    int index = qu->_.rer -1;                                                     \
    QUEUE_NOT_NULLPTR(qu, "rbegin");                                              \
    if (index < qu->_.fnt) {                                                      \
        fprintf(stderr, "queue: rbegin(): queue empty\n");                        \
        abort();                                                                  \
    }                                                                             \
    return &(qu->_.v[index]);                                                     \
}                                                                                 \
                                                                                  \
vtype *QueueFn(vtype, next)(const Queue(vtype) qu, vtype *curr)                   \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "next");                                                \
    if (!curr) return qu->begin(qu);                                              \
    curr++;                                                                       \
    if (qu->begin(qu) < curr && curr <= qu->rbegin(qu))                           \
        return curr;                                                              \
    return NULL;                                                                  \
}                                                                                 \
vtype *QueueFn(vtype, rnext)(const Queue(vtype) qu, vtype *curr)                  \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "rnext");                                               \
    if (!curr) return qu->rbegin(qu);                                             \
    curr--;                                                                       \
    if (qu->begin(qu) <= curr && curr < qu->rbegin(qu))                           \
        return curr;                                                              \
    return NULL;                                                                  \
}                                                                                 \
                                                                                  \
Queue(vtype) QueueFn(vtype, push)(Queue(vtype) qu, vtype val)                     \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "push");                                                \
    if (qu->_.rer >= qu->_.cap) {                                                 \
        qu->_.cap = (int) (2 * qu->_.cap) +1;                                     \
        qu->_.v = realloc(qu->_.v, sizeof(vtype) * qu->_.cap);                    \
    }                                                                             \
    qu->_.v[qu->_.rer++] = val;                                                   \
    return qu;                                                                    \
}                                                                                 \
                                                                                  \
vtype QueueFn(vtype, front)(const Queue(vtype) qu)                                \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu, "front");                                               \
    return *qu->getref(qu, qu->_.fnt);                                            \
}                                                                                 \
                                                                                  \
vtype QueueFn(vtype, pop)(Queue(vtype) qu)                                        \
{                                                                                 \
     QUEUE_NOT_NULLPTR(qu, "pop");                                                \
     vtype retv = *qu->getref(qu, qu->_.fnt);                                     \
     qu->_.fnt++;                                                                 \
     if (qu->isempty(qu)) qu->_.rer = qu->_.fnt = 0;                              \
     return retv;                                                                 \
}                                                                                 \
                                                                                  \
Queue(vtype) QueueFn(vtype, clone)(const Queue(vtype) qu)                         \
{                                                                                 \
     QUEUE_NOT_NULLPTR(qu, "clone");                                              \
     Queue(vtype) stk = QueueFn(vtype, new)();                                    \
     QUEUE_FOREACH(qu, stk->push(stk, *value));                                   \
     return stk;                                                                  \
}                                                                                 \
                                                                                  \
void QueueFn(vtype, free)(Queue(vtype) *qu_ptr)                                   \
{                                                                                 \
    QUEUE_NOT_NULLPTR(qu_ptr, "free");                                            \
    QUEUE_NOT_NULLPTR(*qu_ptr, "free");                                           \
    free((*qu_ptr)->_.v);                                                         \
    free(*qu_ptr);                                                                \
    *qu_ptr = NULL;                                                               \
}
