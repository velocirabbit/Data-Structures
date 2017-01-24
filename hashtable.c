/**
 * Implementation of hash table data structure.
 *
 */
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #include "hashtable.h"

 #define nStrlen(str)       (strlen((str)) + 1)

HashTable *initHashTable(int (*destroy)(void *data), char *(*toString)(void *data),
                         int (*compare)(void *key1, void *key2)) {
    HashTable *newHT;
    if ((newHT = malloc(sizeof(HashTable))) == NULL) {
        fprintf(stderr, "ERROR: Couldn't malloc for new HashTable\n");
        newHT = NULL;
    }
    else {
        for (int i = 0; i < HSIZE; i++) {
            if (((newHT->table)[i] = malloc(sizeof(HashList))) == NULL) {
                fprintf(stderr, "ERROR: Couldn't malloc for HashList in new HashTable\n");
                newHT = NULL;
                return newHT;
            }
            (newHT->table)[i]->size = 0;
            (newHT->table)[i]->head = NULL;
            (newHT->table)[i]->tail = NULL;
        }
        newHT->size = 0;
        newHT->destroy = destroy;
        newHT->toString = toString;
        newHT->compare = compare;
    }
    return newHT;
}

void insertHash(HashTable *ht, char *key, void *d) {
    HashItem *newItem;
    if ((newItem = malloc(sizeof(HashItem))) == NULL) {
        fprintf(stderr, "ERROR: Couldn't malloc for new HashItem\n");
        return;
    }
    if ((newItem->key = malloc(sizeof(char) * nStrlen(key))) == NULL) {
        fprintf(stderr, "ERROR: Couldn't malloc for new HashItem name\n");
        return;
    }
    newItem->data = d;
    strcpy(newItem->key, key);
    
    HashList *list = (ht->table)[hash(key)];

    newItem->next = list->head;
    list->head = newItem;
    (list->size)++;
    if (list->size == 1)
        list->tail = newItem;
    (ht->size)++;
}

HashItem *lookup(HashTable *ht, char *key) {
    HashList *list = (ht->table)[hash(key)];
    HashItem *ptr;
    for (ptr = list->head; ptr != NULL; ptr = ptr->next) {
        if (strcmp(key, ptr->key) == 0)
            return ptr;
    }
    return NULL;
}

int deleteHash(HashTable *ht, char *key) {
    HashList *list = (ht->table)[hash(key)];
    HashItem *ptr = list->head, *del = NULL;
    if (strcmp(ptr->key, key) == 0) {
        del = ptr;
        free(del->key);
        (ht->destroy)(del->data);
        list->head = del->next;
        free(del);
        return 0;
    }
    for (ptr; ptr->next != NULL; ) {
        if (strcmp(ptr->next->key, key) == 0) {
            // Delete the next key
            del = ptr->next;
            free(del->key);
            (ht->destroy)(del->data);
            ptr->next = del->next;
            free(del);
            return 0;
        }
    }
    fprintf(stderr, "ERROR: Couldn't delete key %s from HashTable - doesn't exist\n", key);
    return -1;
}

unsigned hash(char *key) {
    unsigned hashval = HINIT;
    for (hashval; *key != '\0'; key++)
        hashval = (*key + HA * hashval) % HSIZE;
    return hashval;
}

void hashItemPrint(HashTable *ht, char *key) {
    HashItem *item = lookup(ht, key);
    if (item == NULL) {
        fprintf(stderr, "ERROR: HashItem doesn't exist\n");
    }
    else {
        printf("%s\n", (ht->toString)(item->data));
    }
}

void freeHashTable(HashTable *ht) {
    HashList *list;
    HashItem *ptr, *temp;
    for (int i = 0; i < HSIZE; i++) {
        list = (ht->table)[i];
        for (ptr = list->head; ptr != NULL; ) {
            free(ptr->key);
            (ht->destroy)(ptr->data);
            temp = ptr->next;
            free(ptr);
            ptr = temp;
        }
        free(list);
    }
    free(ht);
}