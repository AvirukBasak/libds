#ifndef STRING_H
#define STRING_H

#include "tlib/vector.h"

typedef struct String String;

struct String {
    char* arr;
    size_t length;
    int *refcount;
    String (*clone)    (String this);
    String (*concat)   (String this, String str);
    String (*append)   (String this, char c);
    String (*equals)   (String this, String str);
    String (*compare)  (String this, String str);
    String (*replace)  (String this, String mat, String rep);
    String (*substing) (String this, int start, int end);
    String (*substr)   (String this, int start, int count);
    Vector(String) (*split) (String this, String del);
};

String String_new(const char *str);
void String_free(String *str);

String String_clone(String this);
String String_concat(String this, String str);
String String_append(String this, char c);
String String_equals(String this, String str);
String String_compare(String this, String str);
String String_replace(String this, String mat, String rep);
String String_substing(String this, int start, int end);
String String_substr(String this, int start, int count);
Vector(String) String_split(String this, String del);

#endif
