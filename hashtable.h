/**
 * Header file for implementation of hash table data structure.
 *
 */

#ifndef HASHTABLE
#define HASHTABLE

#define HSIZE 101
#define HINIT 0
#define HA 31

// Macro functions
#define isVariableDefined(ht, x)    (lookup((ht), (x)) != NULL)
#define numVariables(ht)            ((ht)->size)

typedef struct hashitem_ {
    struct hashitem_ *next;
    char *key;
    void *data;
} HashItem;

typedef struct hashlist_ {
    int size;
    HashItem *head;
    HashItem *tail;
} HashList;

typedef struct hashtable_ {
    int size;
    HashList *table[HSIZE];
    int (*destroy)(void *data);
    char *(*toString)(void *data);
    int (*compare)(void *key1, void *key2);
} HashTable;

HashTable *initHashTable(int (*destroy)(void *data), char *(*toString)(void *data),
                         int (*compare)(void *key1, void *key2));
void insertHash(HashTable *ht, char *key, void *d);
HashItem *lookup(HashTable *ht, char *key);
int deleteHash(HashTable *ht, char *key);
unsigned hash(char *key);
void hashItemPrint(HashTable *ht, char *key);
void freeHashTable(HashTable *ht);

#endif