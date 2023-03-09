/**
 * Implementation of an ordered map using a self balancing BST.
 * Implemented using libavl.
 * @author Aviruk Basak
 * @date 10.12.2022
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "libavl.h"

#undef new
#undef delete

/**
 * new function: returns a pointer to a struct type passed by allocating
 * memory using calloc
 */
#define new(struct_t) ({                                                              \
    struct struct_t *tmp = calloc(1, sizeof(struct struct_t));                        \
    if (!tmp) abort();                                                                \
    tmp;                                                                              \
})

/**
 * delete function: frees pointer and sets it to null
 */
#define delete(ptr) ({                                                                \
    if (ptr) {                                                                        \
        free(ptr);                                                                    \
        ptr = NULL;                                                                   \
    }                                                                                 \
})

#define BstMap(vtype, vtype) Bstmap(ktype, vtype)
#define BstMapFunc(ktype, vtype, func) bstmap_##ktype##_##vtype##_##func

/**
 * Generates function prototype definitions and typedefs for the map
 * vtype should be a primary datatype or typdefed (aliased) pointer
 * format: BstMapDeclarePrototypes(vtype)
 */
#define BstMapDeclarePrototypes(vtype)                                                \
                                                                                      \
typedef AVL *Bstmap(ktype, vtype);                                                         \
                                                                                      \
typedef struct bstmap_data_##vtype {                                                 \
    unsigned long int key;                                                            \
    vtype value;                                                                      \
} *bstmap_data_##vtype;                                                              \
                                                                                      \
Bstmap(ktype, vtype) BstmapFn(ktype, vtype, newmap)();                                           \
unsigned long int BstmapFn(ktype, vtype, hashString)(const char *strkey);                   \
vtype BstmapFn(ktype, vtype, get)(Bstmap(ktype, vtype) m, unsigned long int key, bool *found);   \
bool BstmapFn(ktype, vtype, set)(Bstmap(ktype, vtype) m, unsigned long int key, vtype val);      \
bool BstmapFn(ktype, vtype, del)(Bstmap(ktype, vtype) m, unsigned long int key);                 \
void BstmapFn(ktype, vtype, print)(Bstmap(ktype, vtype) m);                                      \
void BstmapFn(ktype, vtype, free)(Bstmap(ktype, vtype) *m);

/**
 * Defines the chosen map from template: generates the necessary function definitions
 * vtype should be a primary datatype or typdefed (aliased) pointer
 * Format: BstMapDefine(vtype, func_print(const value))
 * Note: requires BstMapDeclarePrototypes(vtype)
 */
#define BstMapDefine(vtype, func_print)                                               \
                                                                                      \
/* helper functions */                                                                \
void BstmapFn(ktype, vtype, _map_print)(avlnode_t *node);                                   \
void BstmapFn(ktype, vtype, _map_free)(avlnode_t *node);                                    \
int BstmapFn(ktype, vtype, _map_ncomp)(void *d1, void *d2);                                 \
int BstmapFn(ktype, vtype, _map_nkcomp)(void *id, void *d);                                 \
                                                                                      \
Bstmap(ktype, vtype) BstmapFn(ktype, vtype, newmap)()                                            \
{                                                                                     \
    return calloc(1, sizeof(AVL));                                                    \
}                                                                                     \
                                                                                      \
unsigned long int BstmapFn(ktype, vtype, hashString)(const char *strkey)                    \
{                                                                                     \
    unsigned long int hash = 0;                                                       \
    size_t i, len = strlen(strkey);                                                   \
    for (i = 0; i < len; i++) {                                                       \
        hash = hash * 2 + (strkey[i] ^ hash);                                         \
    }                                                                                 \
    return hash;                                                                      \
}                                                                                     \
                                                                                      \
vtype BstmapFn(ktype, vtype, get)(Bstmap(ktype, vtype) m, unsigned long int key, bool *found)    \
{                                                                                     \
    if (!m) abort();                                                                  \
    bstmap_data_##vtype data = avl_search(m, &key, Bstmap(ktype, vtype)##__map_nkcomp);   \
    if (data) {                                                                       \
        if (found) *found = true;                                                     \
        return data->value;                                                           \
    }                                                                                 \
    if (found) *found = false;                                                        \
    return (vtype) 0;                                                                 \
}                                                                                     \
                                                                                      \
bool BstmapFn(ktype, vtype, set)(Bstmap(ktype, vtype) m, unsigned long int key, vtype val)       \
{                                                                                     \
    if (!m) abort();                                                                  \
    bstmap_data_##vtype data = avl_search(m, &key, Bstmap(ktype, vtype)##__map_nkcomp);   \
    if (data) {                                                                       \
        data->value = val;                                                            \
        return true;                                                                  \
    }                                                                                 \
    data = malloc(sizeof(struct bstmap_data_##vtype));                               \
    avlnode_t *node = malloc(sizeof(avlnode_t));                                      \
    node->data = data;                                                                \
    data->key = key;                                                                  \
    data->value = val;                                                                \
    return avl_attach(m, node, Bstmap(ktype, vtype)##__map_ncomp);                         \
}                                                                                     \
                                                                                      \
bool BstmapFn(ktype, vtype, del)(Bstmap(ktype, vtype) m, unsigned long int key)                  \
{                                                                                     \
    if (!m) abort();                                                                  \
    avlnode_t *node = avl_detach(m, &key, Bstmap(ktype, vtype)##__map_nkcomp);             \
    if (!node) return false;                                                          \
    free(node);                                                                       \
    if (node->data) free(node->data);                                                 \
    return true;                                                                      \
}                                                                                     \
                                                                                      \
void BstmapFn(ktype, vtype, print)(Bstmap(ktype, vtype) m)                                       \
{                                                                                     \
    if (!m) return;                                                                   \
    printf("{\n");                                                                    \
    avl_traverse(m, Bstmap(ktype, vtype)##__map_print);                                    \
    printf("}\n");                                                                    \
}                                                                                     \
                                                                                      \
void BstmapFn(ktype, vtype, free)(Bstmap(ktype, vtype) *m)                                       \
{                                                                                     \
    if (!m || !(*m)) return;                                                          \
    avl_traverse(*m, Bstmap(ktype, vtype)##__map_free);                                    \
    delete(*m);                                                                       \
}                                                                                     \
                                                                                      \
/* helper function definitions */                                                     \
void BstmapFn(ktype, vtype, _map_free)(avlnode_t *node) {                                   \
    free(node->data);                                                                 \
    free(node);                                                                       \
}                                                                                     \
                                                                                      \
void BstmapFn(ktype, vtype, _map_print)(avlnode_t *node) {                                  \
    bstmap_data_##vtype data = node->data;                                           \
    if (!data) return;                                                                \
    printf("    %lu -> ", data->key);                                                 \
    const vtype value = data->value;                                                  \
    {                                                                                 \
        const Bstmap(ktype, vtype) m = NULL;                                               \
        const Bstmap(ktype, vtype) data = NULL;                                            \
        (m, data);                                                                    \
        func_print;                                                                   \
    }                                                                                 \
    printf("\n");                                                                     \
}                                                                                     \
                                                                                      \
int BstmapFn(ktype, vtype, _map_ncomp)(void *d1, void *d2) {                                \
    return ((bstmap_data_##vtype) d1)->key - ((bstmap_data_##vtype) d2)->key;       \
}                                                                                     \
                                                                                      \
int BstmapFn(ktype, vtype, _map_nkcomp)(void *key, void *d) {                               \
    /* if id < data, -ve or decrease data, i.e. go to left subtree                    \
     * if id > data, +ve or increase data, i.e. go to right subtree                   \
     * if equal 0, match found                                                        \
     */                                                                               \
    return *(unsigned long int*) key - ((bstmap_data_##vtype) d)->key;               \
}                                                                                     \
