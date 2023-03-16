
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
    BstmapData(ktype, vtype) data = avl_search(m, &key, Bstmap(ktype, vtype)##__map_nkcomp);   \
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
    BstmapData(ktype, vtype) data = avl_search(m, &key, Bstmap(ktype, vtype)##__map_nkcomp);   \
    if (data) {                                                                       \
        data->value = val;                                                            \
        return true;                                                                  \
    }                                                                                 \
    data = malloc(sizeof(struct BstmapData(ktype, vtype)));                               \
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
    BstmapData(ktype, vtype) data = node->data;                                           \
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
    return ((BstmapData(ktype, vtype)) d1)->key - ((BstmapData(ktype, vtype)) d2)->key;       \
}                                                                                     \
                                                                                      \
int BstmapFn(ktype, vtype, _map_nkcomp)(void *key, void *d) {                               \
    /* if id < data, -ve or decrease data, i.e. go to left subtree                    \
     * if id > data, +ve or increase data, i.e. go to right subtree                   \
     * if equal 0, match found                                                        \
     */                                                                               \
    return *(unsigned long int*) key - ((BstmapData(ktype, vtype)) d)->key;               \
}                                                                                     \
