#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "ctl/string.h"

void            String_free        (String *str_ptr);
char*           String_cstr        (const String str);
size_t          String_length      (const String str);
bool            String_isempty     (const String str);
char            String_at          (const String str, int index);
char*           String_getref      (const String str, int index);
char            String_front       (const String str);
char            String_back        (const String str);
char*           String_begin       (const String str);
char*           String_end         (const String str);
char*           String_rbegin      (const String str);
char*           String_next        (const String str, char *curr);
char*           String_rnext       (const String str, char *curr);
bool            String_set         (String str, int index, char ch);
char*           String_find        (const String str, cstr_t cs);
char*           String_rfind       (const String str, cstr_t cs);
int             String_index       (const String str, cstr_t cs);
int             String_rindex      (const String str, cstr_t cs);
bool            String_equals      (const String str, cstr_t cs);
int             String_compare     (const String str, cstr_t cs);
String          String_substring   (const String str, int from, int to);
String          String_substr      (const String str, int from, int count);
Vector(String)  String_split       (const String str, cstr_t del);
String          String_replace     (String str, cstr_t needle, cstr_t rep);
String          String_append      (String str, char ch);
String          String_concat      (String str, cstr_t cs);
String          String_nconcat     (String str, cstr_t cs, size_t n);
String          String_insert      (String str, int index, cstr_t cs);
String          String_erase       (String str, int from, int count);
String          String_clone       (const String str);
String          String_reverse     (String str);


String String_new()
{
    String str = STRING_NOT_NULLPTR(new(String), "new");
    str->_.v = NULL;
    str->_.len = 0;
    str->_.cap = 0;
    str->free          = String_free;
    str->cstr          = String_cstr;
    str->length        = String_length;
    str->isempty       = String_isempty;
    str->at            = String_at;
    str->getref        = String_getref;
    str->front         = String_front;
    str->back          = String_back;
    str->begin         = String_begin;
    str->end           = String_end;
    str->rbegin        = String_rbegin;
    str->next          = String_next;
    str->rnext         = String_rnext;
    str->set           = String_set;
    str->find          = String_find;
    str->rfind         = String_rfind;
    str->index         = String_index;
    str->rindex        = String_rindex;
    str->equals        = String_equals;
    str->compare       = String_compare;
    str->substring     = String_substring;
    str->substr        = String_substr;
    str->split         = String_split;
    str->replace       = String_replace;
    str->append        = String_append;
    str->concat        = String_concat;
    str->nconcat       = String_nconcat;
    str->insert        = String_insert;
    str->erase         = String_erase;
    str->clone         = String_clone;
    str->reverse       = String_reverse;
    return str;
}

String String_from(cstr_t cs)
{
    String str = String_new();
    const size_t len = strlen(cs);
    str->_.v = malloc(len * sizeof(char));
    memcpy(str->_.v, cs, len * sizeof(char));
    str->_.len += len;
    str->_.cap += len;
    return str;
}

char *String_cstr(const String str)
{
    return str->_.v;
}

size_t String_length(const String str)
{
    STRING_NOT_NULLPTR(str, "length");
    return str->_.len;
}

bool String_isempty(const String str)
{
    STRING_NOT_NULLPTR(str, "isempty");
    return !(str->_.len);
}

char String_at(const String str, int index)
{
    STRING_NOT_NULLPTR(str, "at");
    if (index < 0 || index >= (int) str->_.len) {
        fprintf(stderr, "string: at(): index out of bounds: %d\n", index);
        abort();
    }
    return str->_.v[index];
}

char *String_getref(const String str, int index)
{
    STRING_NOT_NULLPTR(str, "getref");
    if (index < 0 || index >= (int) str->_.len) {
        fprintf(stderr, "string: getref(): index out of bounds: %d\n", index);
        abort();
    }
    return &(str->_.v[index]);
}

char String_front(const String str)
{
    STRING_NOT_NULLPTR(str, "front");
    return *(str->begin(str));
}

char String_back(const String str)
{
    STRING_NOT_NULLPTR(str, "back");
    return *(str->rbegin(str));
}

char *String_begin(const String str)
{
    STRING_NOT_NULLPTR(str, "begin");
    if (0 >= str->_.len) {
        fprintf(stderr, "string: begin(): string empty\n");
        abort();
    }
    return &(str->_.v[0]);
}

char *String_end(const String str)
{
    return str->begin(str) + str->_.len;
}

char *String_rbegin(const String str)
{
    int index = str->_.len -1;
    STRING_NOT_NULLPTR(str, "rbegin");
    if (index < 0) {
        fprintf(stderr, "string: rbegin(): string empty\n");
        abort();
    }
    return &(str->_.v[index]);
}

char *String_next(const String str, char *curr)
{
    STRING_NOT_NULLPTR(str, "next");
    if (!curr) return str->begin(str);
    curr++;
    if (str->begin(str) <= curr && curr <= str->rbegin(str))
        return curr;
    return NULL;
}
char *String_rnext(const String str, char *curr)
{
    STRING_NOT_NULLPTR(str, "rnext");
    if (!curr) return str->rbegin(str);
    curr--;
    if (str->begin(str) <= curr && curr <= str->rbegin(str))
        return curr;
    return NULL;
}

bool String_set(String str, int index, char ch)
{
    STRING_NOT_NULLPTR(str, "set");
    if (index < 0 || index >= (int) str->_.len) {
        fprintf(stderr, "string: set(): index out of bounds: %d\n", index);
        abort();
    }
    str->_.v[index] = ch;
    return true;
}

char *String_find(const String str, cstr_t cs)
{
    STRING_NOT_NULLPTR(str, "find");
    // TODO: impl find
    return NULL;
}

char *String_rfind(const String str, cstr_t cs)
{
    STRING_NOT_NULLPTR(str, "rfind");
    // TODO: impl rfind
    return NULL;
}

int String_index(const String str, cstr_t cs)
{
    STRING_NOT_NULLPTR(str, "index");
    // TODO: impl index
    return -1;
}

int String_rindex(const String str, cstr_t cs)
{
    STRING_NOT_NULLPTR(str, "rindex");
    // TODO: impl rindex
    return -1;
}

bool String_equals(const String str, cstr_t cs)
{
    STRING_NOT_NULLPTR(str, "equals");
    if (len(str) != strlen(cs))
        return false;
    if (*cstr(str) != *cs)
        return false;
    return !strcmp(cstr(str), cs);
}

int String_compare(const String str, cstr_t cs)
{
    STRING_NOT_NULLPTR(str, "compare");
    if (*cstr(str) != *cs) return *cstr(str) - *cs;
    return strcmp(cstr(str), cs);
}

// TODO: impl remaining functions

String String_substring(const String str, int from, int to)
{}

String String_substr(const String str, int from, int count)
{}

Vector(String) String_split(const String str, cstr_t del)
{}

// TODO: impl remaining functions

String String_replace(String str, cstr_t needle, cstr_t rep)
{
    String res = String_new();
    const char *tmp = cstr(str);
    size_t needle_len = strlen(needle);
    while (true) {
        const char *p = strstr(tmp, needle);
        if (!p) {
            // the remaining string
            res->concat(res, tmp);
            break;
        }
        // the part upto the needle
        res->nconcat(res, tmp, p - tmp);
        // the replacement
        res->concat(res, rep);
        // adjust pointers
        tmp = p + needle_len; 
    }
    // manually free the old string
    free(str->_.v);
    // copy attributes from res to str
    memcpy(&str->_, &res->_, sizeof(res->_));
    return str;
}

String String_append(String str, char ch)
{
    STRING_NOT_NULLPTR(str, "append");
    if (str->_.len >= str->_.cap) {
        str->_.cap = (int) (2 * str->_.cap) +1;
        str->_.v = realloc(str->_.v, sizeof(char) * str->_.cap);
    }
    str->_.v[str->_.len++] = ch;
    return str;
}                             

String String_concat(String str, cstr_t cs)
{
    STRING_NOT_NULLPTR(str, "concat");
    const size_t len = strlen(cs);
    if (str->_.len + len >= str->_.cap) {
        str->_.cap = (int) (2 * str->_.cap) + len;
        str->_.v = realloc(str->_.v, sizeof(char) * str->_.cap);
    }
    memcpy(&str->_.v[str->_.len++], cs, len);
    return str;
}

String String_nconcat(String str, cstr_t cs, size_t n)
{
    STRING_NOT_NULLPTR(str, "nconcat");
    const size_t len = strlen(cs);
    if (str->_.len + len >= str->_.cap) {
        str->_.cap = (int) (2 * str->_.cap) + len;
        str->_.v = realloc(str->_.v, sizeof(char) * str->_.cap);
    }
    memcpy(&str->_.v[str->_.len++], cs, n < len ? n : len);
    return str;
}

String String_insert(String str, int index, cstr_t cs)
{
    STRING_NOT_NULLPTR(str, "insert");
    if (index >= (int) str->_.len) {
        str->concat(str, cs);
        return str;
    }
    const size_t len = strlen(cs);
    char *ptr = str->getref(str, index);
    char *p = str->rbegin(str);
    str->concat(str, cs);
    char *q = str->rbegin(str);
    while (p < q && p >= ptr) {
        *q = *p;
        p = str->rnext(str, p);
        q = str->rnext(str, q);
    }
    memcpy(ptr, cs, len);
    return str;
}

String String_erase(String str, int from, int count)
{
    STRING_NOT_NULLPTR(str, "erase");
    if (from >= (int) str->_.len) {
        fprintf(stderr, "string: erase(): index out of bounds: %d\n", from);
        abort();
    }
    char *p = str->getref(str, from);
    if (p + count >= str->end(str)) {
        fprintf(stderr, "string: erase(): count out of bounds: %d\n", count);
        abort();
    }
    char *q = p + count;
    while (p < q && q < str->end(str)) {
        *p = *q;
        p = str->next(str, p);
        q = str->next(str, q);
    }
    str->_.len -= count;
    return str;
}

String String_clone(const String str)
{
    STRING_NOT_NULLPTR(str, "clone");
    String str2 = String_new();
    str2->concat(str2, cstr(str));
    return str2;
}

String String_reverse(String str)
{
    STRING_NOT_NULLPTR(str, "reverse");
    char *l = str->begin(str),
         *u = str->rbegin(str);
    while (l && u && l < u) {
        char tmp = *l;
        *l = *u;
        *u = tmp;
        l = str->next(str, l);
        u = str->rnext(str, u);
    }
    return str;
}

void String_free(String *str_ptr)
{
    STRING_NOT_NULLPTR(str_ptr, "free");
    STRING_NOT_NULLPTR(*str_ptr, "free");
    free((*str_ptr)->_.v);
    free(*str_ptr);
    *str_ptr = NULL;
}
