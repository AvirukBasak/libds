#include <assert.h>

#include "ctl/string.h"

void test_replace() {
    String str = String_from("The quick brown dog jumps over the lazy cat.");
    str->replace(str, "dog", "fox")
       ->replace(str, "cat", "dog");
    assert( str->equals(str, "The quick brown fox jumps over the lazy dog.") );
    str->free(&str);
    str = String_from("The quick brown dog jumps over the lazy cat.");
    str->replace(str, " ", "_")
       ->replace(str, "o", "O");
    assert( str->equals(str, "The_quick_brOwn_dOg_jumps_Over_the_lazy_cat.") );
    str->free(&str);
}

void test_insert() {
    String str = String_from("Hello world!");
    str->insert(str, 5, ", oh accursed");
    assert( str->equals(str, "Hello, oh accursed world!") );
    str->free(&str);
}

void test_erase() {
    String str = String_from("Hello, oh accursed world!");
    str->erase(str, 5, strlen(", oh accursed"));
    assert( str->equals(str, "Hello world!") );
    str->free(&str);
}

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
    VECTOR_FOREACH(vec, (*value)->free(value));
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

void test_clone() {
    String str = String_from("  hello world   ");
    str->trim(str);
    String str2 = str->clone(str);
    assert( str2->equals(str2, cstr(str)) );
    str->free(&str);
    str2->free(&str2);
}

void test_reverse() {
    String str = String_from("hello world");
    str->reverse(str);
    assert( str->equals(str, "dlrow olleh") );
    str->free(&str);
}

void teststr() {
    /* split internally uses: isempty, substring, begin, end, substr
     * substring internally uses: getref, nconcat
     * substr internally uses: getref, nconcat
     */
    test_split();
    test_uppercase();
    test_lowercase();
    test_ltrim();
    test_rtrim();
    test_trim();
    test_replace();
    /* insert internally uses: concat, getref, rbegin, rnext */
    test_insert();
    /* erase internally uses: end, getref */
    test_erase();
    /* clone internally uses: concat, next, end */
    test_clone();
    /* reverse internally uses: begin, rbegin, next, rnext */
    test_reverse();
    printf("string: passed testcases\n");
}
