#include <assert.h>
#include <string.h>

#include "ctl/string.h"

void test_split() {
    // initialize a string to split
    String str = String_from("apple, banana, orange");

    // call the split method with the delimiter ", "
    Vector(String) vec = str->split(str, ", ");

    // check that the resulting vector has three elements
    assert(len(vec) == 3);

    // check that the elements of the vector match the expected values
    assert( vec->at(vec, 0)->equals(vec->at(vec, 0), "apple") );
    assert( vec->at(vec, 1)->equals(vec->at(vec, 1), "banana") );
    assert( vec->at(vec, 2)->equals(vec->at(vec, 2), "orange") );

    // free the vector and string
    vec->free(&vec);
    str->free(&str);
}

void test_uppercase() {
    String str = String_from("hello wOrld");
    str->uppercase(str);
    assert(str->equals(str, "HELLO WORLD"));
    str->free(&str);
}

void test_lowercase() {
    String str = String_from("HELLO WOrLD");
    str->lowercase(str);
    assert(str->equals(str, "hello world"));
    str->free(&str);
}

void test_trim() {
    String str = String_from("   hello world   ");
    str->trim(str);
    assert(str->equals(str, "hello world"));
    str->free(&str);
}

void test_ltrim() {
    String str = String_from("   hello world  ");
    str->ltrim(str);
    assert(str->equals(str, "hello world  "));
    str->free(&str);
}

void test_rtrim() {
    String str = String_from("  hello world   ");
    str->rtrim(str);
    assert(str->equals(str, "  hello world"));
    str->free(&str);
}

void teststr() {
    test_split();
    test_uppercase();
    test_lowercase();
    test_trim();
    test_ltrim();
    test_rtrim();
    printf("string: passed testcases\n");
}
