#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "avl/libavl.h"

#undef new
/**
 * new function: returns a pointer to a struct type passed by allocating
 * memory using calloc
 */
#define new(struct_t) ({                                                                                  \
    struct struct_t *tmp = calloc(1, sizeof(struct struct_t));                                            \
    tmp;                                                                                                  \
})

#undef delete
/**
 * delete function: frees pointer and sets it to null
 */
#define delete(ptr) ({                                                                                    \
    if (ptr) {                                                                                            \
        free(ptr);                                                                                        \
        ptr = NULL;                                                                                       \
    }                                                                                                     \
})

#define Bstmap(ktype, vtype) Bstmap_##ktype##_##vtype
#define BstmapAvl(ktype, vtype) Bstmap_##ktype##_##vtype##_avl
#define BstmapData(ktype, vtype) Bstmap_##ktype##_##vtype##_data
#define BstmapFn(ktype, vtype, func) Bstmap_##ktype##_##vtype##_##func

#undef BSTMAP_NOT_NULLPTR
/**
 * Return ptr if not null else abort
 * @param ptr Pointer to object
 * @param fn Name of caller function
 * @return ptr If not null
 */
#define BSTMAP_NOT_NULLPTR(ptr, fn) ({                                                                    \
    void *tmp = ptr;                                                                                      \
    if (!tmp) {                                                                                           \
        fprintf(stderr, "bstmap: %s(): null pointer\n", fn);                                              \
        abort();                                                                                          \
    }                                                                                                     \
    tmp;                                                                                                  \
})

#undef BSTMAP_FOREACH
/**
 * Iterate inorder through the bstmap
 * @param bm The bstmap
 * @param action{ktype key, vtype *value} A code block
 */
#define BSTMAP_FOREACH(bm, action) ({                                                                     \
    BSTMAP_NOT_NULLPTR(bm, "FOREACH");                                                                    \
})

#undef BSTMAP_RFOREACH
/**
 * Iterate inorder in reverse through the bstmap
 * @param bm The bstmap
 * @param action{ktype key, vtype *value} A code block
 */
#define BSTMAP_RFOREACH(bm, action) ({                                                                    \
    BSTMAP_NOT_NULLPTR(bm, "RFOREACH");                                                                   \
})

/**
 * Generates function prototype definitions and typedefs for the Bstmap.
 * Types should be primary datatypes or typdefed (aliased) pointer/struct.
 * Format: BSTMAP_DECLARE(ktype, vtype)
 * @param ktype Type of the key
 * @param vtype Type of value per key
 */
#define BSTMAP_DECLARE(ktype, vtype)                                                                      \
                                                                                                          \
typedef AVL *BstmapAvl(ktype, vtype);                                                                     \
typedef struct BstmapData(ktype, vtype) *BstmapData(ktype, vtype);                                        \
                                                                                                          \
struct BstmapData(ktype, vtype) {                                                                         \
    ktype key;                                                                                            \
    vtype value;                                                                                          \
    avlnode_t *_;                                                                                         \
};                                                                                                        \
                                                                                                          \
typedef struct Bstmap(ktype, vtype) *Bstmap(ktype, vtype);                                                \
                                                                                                          \
struct Bstmap(ktype, vtype) {                                                                             \
    size_t len;                                                                                           \
    size_t                   (*length) (Bstmap(ktype, vtype) bm);                                         \
    bool                     (*has)    (Bstmap(ktype, vtype) bm, ktype key);                              \
    vtype                    (*get)    (Bstmap(ktype, vtype) bm, ktype key);                              \
    BstmapData(ktype, vtype) (*getref) (Bstmap(ktype, vtype) bm, ktype key);                              \
    bool                     (*set)    (Bstmap(ktype, vtype) bm, ktype key, vtype val);                   \
    bool                     (*del)    (Bstmap(ktype, vtype) bm, ktype key);                              \
    void                     (*free)   (Bstmap(ktype, vtype) *bm_ptr);                                    \
    struct private {                                                                                      \
        BstmapAvl(ktype, vtype) avl;                                                                      \
    } _;                                                                                                  \
};                                                                                                        \
                                                                                                          \
Bstmap(ktype, vtype)     BstmapFn(ktype, vtype, new)();                                                   \
bool                     BstmapFn(ktype, vtype, has)    (Bstmap(ktype, vtype) bm, ktype key);             \
vtype                    BstmapFn(ktype, vtype, get)    (Bstmap(ktype, vtype) bm, ktype key);             \
BstmapData(ktype, vtype) BstmapFn(ktype, vtype, getref) (Bstmap(ktype, vtype) bm, ktype key);             \
bool                     BstmapFn(ktype, vtype, set)    (Bstmap(ktype, vtype) bm, ktype key, vtype val);  \
bool                     BstmapFn(ktype, vtype, del)    (Bstmap(ktype, vtype) bm, ktype key);             \
void                     BstmapFn(ktype, vtype, free)   (Bstmap(ktype, vtype) *bm_ptr);

/**
 * Defines the chosen Bstmap from template: generates the necessary function definitions
 * Types should be primary datatypes or typdefed (aliased) pointer/struct
 * Format: BSTMAP_DEFINE(ktype, vtype)
 * Note: requires BSTMAP_DECLARE(ktype, vtype)
 * @param ktype Type of the key
 * @param vtype Type of value per key
 * @param cmpact{key1, key2} -> (int) An action to compare two ktypes
 * Note: cmpact should return +ve if key1 > key2, -ve if key1 < key2, else 0
 */
#define BSTMAP_DEFINE(ktype, vtype, cmpact)                                                               \
                                                                                                          \
Bstmap(ktype, vtype) BstmapFn(ktype, vtype, new)()                                                        \
{                                                                                                         \
    Bstmap(ktype, vtype) bm = BSTMAP_NOT_NULLPTR(new(Bstmap(ktype, vtype)), "new");                       \
    bm->_.avl = BSTMAP_NOT_NULLPTR(new(AVL), "new avl");                                                  \
    //
}
