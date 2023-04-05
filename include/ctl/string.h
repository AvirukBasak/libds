#ifndef STRING_H
#define STRING_H

#include <string.h>

#include "vector.h"

typedef struct String *String;
typedef const char *cstr_t;

VECTOR_DECLARE(String);

struct String {
    void            (*free)      (String *str_ptr);
    char*           (*cstr)      (const String str);
    size_t          (*length)    (const String str);
    bool            (*isempty)   (const String str);
    char            (*at)        (const String str, int index);
    char*           (*getref)    (const String str, int index);
    char            (*front)     (const String str);
    char            (*back)      (const String str);
    char*           (*begin)     (const String str);
    char*           (*end)       (const String str);
    char*           (*rbegin)    (const String str);
    char*           (*next)      (const String str, char *curr);
    char*           (*rnext)     (const String str, char *curr);
    bool            (*set)       (String str, int index, char ch);
    char*           (*find)      (const String str, cstr_t cs);
    char*           (*rfind)     (const String str, cstr_t cs);
    int             (*index)     (const String str, cstr_t cs);
    int             (*rindex)    (const String str, cstr_t cs);
    bool            (*equals)    (const String str, cstr_t cs);
    int             (*compare)   (const String str, cstr_t cs);
    String          (*substring) (const String str, int from, int to);
    String          (*substr)    (const String str, int from, int count);
    Vector(String)  (*split)     (const String str, cstr_t del);
    String          (*trim)      (String str);
    String          (*ltrim)     (String str);
    String          (*rtrim)     (String str);
    String          (*lowercase) (String str);
    String          (*uppercase) (String str);
    String          (*replace)   (String str, cstr_t needle, cstr_t rep);
    String          (*append)    (String str, char ch);
    String          (*concat)    (String str, cstr_t cs);
    String          (*nconcat)   (String str, cstr_t cs, size_t n);
    String          (*insert)    (String str, int index, cstr_t cs);
    String          (*erase)     (String str, int from, int count);
    String          (*clone)     (const String str);
    String          (*reverse)   (String str);
    /** private data members, do not modify */
    struct {
        char *_;
        char *v;
        int len;
        int cap;
    } _;
};

#undef StringFn
#define StringFn(func) String_##func

String String_new();
String String_from(cstr_t cs);

#undef len
/**
 * Return container length
 * @param o Container object
 */
#define len(o) (o->length(o))

#undef cstr
/**
 * Return a c string i.e. char*
 * @param str String object
 */
#define cstr(str) (str->cstr(str))

#undef STRING_NOT_NULLPTR
/**
 * Return ptr if not null else abort
 * @param ptr Pointer to object
 * @param fn Name of caller function
 * @return ptr If not null
 */
#define STRING_NOT_NULLPTR(ptr, fn) ({                                \
    void *tmp = ptr;                                                  \
    if (!tmp) {                                                       \
        fprintf(stderr, "string: %s(): null pointer\n", fn);          \
        abort();                                                      \
    }                                                                 \
    tmp;                                                              \
})

#undef STRING_FOREACH
/**
 * Iterate through the string
 * @param str The string
 * @param action{int i, vtype *value} A code block
 */
#define STRING_FOREACH(str, action) ({                                \
    STRING_NOT_NULLPTR(str, "FOREACH");                               \
    for (int _i = 0; _i < str->_.len; _i++) {                         \
        typeof(str->_.v) const value = &(str->_.v[_i]); value;        \
        const int i = _i; i;                                          \
        const int _i = 0; _i;                                         \
        action;                                                       \
    }                                                                 \
})

#undef STRING_RFOREACH
/**
 * Iterate in reverse through the string
 * @param str The string
 * @param action{int i, vtype *value} A code block
 */
#define STRING_RFOREACH(str, action) ({                               \
    STRING_NOT_NULLPTR(str, "RFOREACH");                              \
    for (int _i = str->_.len -1; _i >= 0 ; _i--) {                    \
        typeof(str->_.v) const value = &(str->_.v[_i]); value;        \
        const int i = _i; i;                                          \
        const int _i = 0; _i;                                         \
        action;                                                       \
    }                                                                 \
})

#endif
