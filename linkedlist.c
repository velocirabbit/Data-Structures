/**
 * Implementation of linked list data structure.
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

/**
 * Initializes a new List object. Allocates memory for the structure, so the
 * memory must be freed later.
 */
List *initList(int (*destroy)(void *data), char *(*toString)(void *data),
               int (*compare)(void *key1, void *key2)) {
    List *newList;
    if ((newList = malloc(sizeof(List))) == NULL) {
        fprintf(stderr, "ERROR: Couldn't malloc for new List\n");
        newList = NULL;
    }
    else {
        newList->size = 0;
        newList->destroy = destroy;
        newList->toString = toString;
        newList->compare = compare;
        newList->head = NULL;
        newList->tail = NULL;
    }
    return newList;
}

/**
 * Initializes a new ListElement uding the passed in data.
 */
ListElement *initListElement(void *data) {
    ListElement *newListElem;
    if ((newListElem = malloc(sizeof(ListElement))) == NULL) {
        fprintf(stderr, "ERROR: Couldn't malloc for new ListElement\n");
        newListElem = NULL;
    }
    else {
        newListElem->data = data;
        newListElem->next = NULL;
    }
    return newListElem;
}

/**
 * Adds a new ListElement next in the List after the passed in ListElement.
 * Uses the passed in data to initialize the new ListElement.
 */
void insertAfter(List *list, ListElement *listElem, void *data) {
    ListElement *newElem;
    if ((newElem = initListElement(data)) != NULL) {
        newElem->next = listElem->next;
        listElem->next = newElem;
        if (newElem->next == NULL)
            list->tail = newElem;
        (list->size)++;
    }
    else {
        fprintf(stderr, "ERROR: Couldn't insert new ListElement after listElem\n");
    }
}

/**
 * Deletes the next ListElement after the one passed in.
 */
void deleteNext(List *list, ListElement *listElem) {
    if (listElem->next != NULL) {
        listElem->next = freeListElement(list, listElem->next);
        if (listElem->next == NULL)
            list->tail = listElem;
        (list->size)--;
    }
    else {
        fprintf(stderr, "ERROR: Next LinkedList item is NULL; can't delete\n");
    }
}

/**
 * Free the passed in List object from memory.
 */
void freeList(List *list) {
    // Free each ListElement in the list (including the data stored in them)
    ListElement *listPtr = list->head;
    while (listPtr != NULL) {
        listPtr = freeListElement(list, listPtr);
        (list->size)--;
    }

    // Free the list
    free(list);
}

/**
 * Free the passed in ListElement from memory (including the data stored in it).
 * Returns a pointer to listElem->next (which could be NULL).
 */
ListElement *freeListElement(List *list, ListElement *listElem) {
    destroyListElement(list, listElem);
    ListElement *next = listElem->next;
    free(listElem);
    return next;
}

/**
 * Inserts the data into a new ListElement at the specified index.
 */
void listInsert(List *list, int index, void *data) {
    if (index == 0) {
        listAdd(list, data);
    }
    else {
        int i;
        ListElement *listPtr;
        for (i = 0, listPtr = list->head; i < index - 1;
                                i++, listPtr = listPtr->next) {
            if (listPtr->next == NULL) {
                listPtr->next = initListElement(NULL);
                (list->size)++;
            }
        }
        insertAfter(list, listPtr, data);
    }
}

/**
 * Appends the data to the end of List.
 */
void listAppend(List *list, void *data) {
    ListElement *oldTail = list->tail;
    list->tail = initListElement(data);
    oldTail->next = list->tail;
    (list->size)++;
}

/**
 * Returns the data stored in the ListElement at the specified index of List.
 * Indexing is 0-based.
 */
void *listElementAt(List *list, int index) {
    if (index >= list->size) {
        fprintf(stderr, "ERROR: index %d past List size (size: %d)\n",
                index, list->size);
        return NULL;
    }
    else {
        ListElement *listPtr = list->head;
        for (int i = 0; i < index; i++, listPtr = listPtr->next);
            return listPtr->data;
    }
}

/**
 * Prints List to the output.
 */
void listPrint(List *list) {
    ListElement *listPtr = list->head;
    for (listPtr; listPtr != NULL; listPtr = listPtr->next)
        listElementPrint(list, listPtr);
}

/**
 * Adds the data to a new ListElement at the front of the List.
 */
void listAdd(List *list, void *data) {
    ListElement *oldHead = list->head;
    list->head = initListElement(data);
    (list->head)->next = oldHead;
    (list->size)++;
}

/**
 * Prints ListElement to the output.
 */
void listElementPrint(List *list, ListElement *listElem) {
    printf("%s\n", (list->toString)(listElem->data));
}