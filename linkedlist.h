/**
 * Header file for implementation of linked list data structure.
 *
 */
#ifndef LINKEDLIST
#define LINKEDLIST

// Macro functions
#define listSize(list)          ((list)->size)
#define listHead(list)          ((list)->head)
#define listTail(list)          ((list)->tail)
#define isListHead(list, elem)  ((elem) == (list)->head)
#define isListTail(list, elem)  ((elem) == (list)->tail)
#define listData(elem)          ((elem)->data)
#define listNext(elem)          ((elem)->next)
#define destroyListElement(list, elem)  (((list)->destroy)((elem)->data))

typedef struct listelement_ {
    void *data;
    struct listelement_ *next;
} ListElement;

typedef struct list_ {
    int size;
    int (*destroy)(void *data);     // specifies how to deallocate
    char *(*toString)(void *data);   // specifies how to print data
    int (*compare)(void *key1, void *key2);
    ListElement *head;
    ListElement *tail;
} List;

List *initList(int (*destroy)(void *data), char *(*toString)(void *data),
               int (*compare)(void *key1, void *key2));
ListElement *initListElement(void *data);
ListElement *freeListElement(List *list, ListElement *listElem);
void insertAfter(List *list, ListElement *listElem, void *data);
void deleteNext(List *list, ListElement *listElem);
void freeList(List *list);
void listInsert(List *list, int index, void *data);
void listAppend(List *list, void *data);
void *listElementAt(List *list, int index);
void listPrint(List *list);
void listAdd(List *list, void *data);
void listElementPrint(List *list, ListElement *listElem);

#endif
