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

#define Bstmap(ktype, vtype) Bstmap_##ktype##_##vtype
#define BstmapFn(ktype, vtype, func) Bstmap_##ktype##_##vtype##_##func

#undef BSTMAP_NOT_NULLPTR
/**
 * Return ptr if not null else abort
 * @param ptr Pointer to object
 * @param fn Name of caller function
 * @return ptr If not null
 */
#define BSTMAP_NOT_NULLPTR(ptr, fn) ({                                            \
    if (!ptr) {                                                                   \
        fprintf(stderr, "bstmap: %s(): null pointer\n", fn);                      \
        abort();                                                                  \
    }                                                                             \
    ptr;                                                                          \
})

#undef BSTMAP_FOREACH
/**
 * Iterate inorder through the bstmap
 * @param bm The bstmap
 * @param action{ktype key, vtype *value} A code block
 */
#define BSTMAP_FOREACH(bm, action) ({                                              \
    BSTMAP_NOT_NULLPTR(bm, "FOREACH");                                             \
})

#undef BSTMAP_RFOREACH
/**
 * Iterate inorder in reverse through the bstmap
 * @param bm The bstmap
 * @param action{ktype key, vtype *value} A code block
 */
#define BSTMAP_RFOREACH(bm, action) ({                                            \
    BSTMAP_NOT_NULLPTR(bm, "RFOREACH");                                           \
})

/**
 * Generates function prototype definitions and typedefs for the Bstmap.
 * Types should be primary datatypes or typdefed (aliased) pointer/struct.
 * Format: BSTMAP_DECLARE(ktype, vtype)
 * @param ktype Type of the key
 * @param vtype Type of value per key
 */
#define BSTMAP_DECLARE(ktype, vtype)                                               \


/**
 * Defines the chosen Bstmap from template: generates the necessary function definitions
 * Types should be primary datatypes or typdefed (aliased) pointer/struct
 * Format: BSTMAP_DEFINE(ktype, vtype)
 * Note: requires BSTMAP_DECLARE(ktype, vtype)
 * @param ktype Type of the key
 * @param vtype Type of value per key
 * @param hashact{key} -> (int hash) An action to hash a non-primitive ktype
 */
#define BSTMAP_DEFINE(ktype, vtype, hashact)                                       \

