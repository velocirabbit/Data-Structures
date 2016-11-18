/**
 * Test file to test the various data structures
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"
#include "stack.h"
#include "queue.h"
#include "hashtable.h"
#include "generictree.h"

#define STRLEN 120

typedef enum {False, True} bool;

// Test functions
bool testList(void);
bool testStack(void);
bool testQueue(void);
bool testHash(void);
bool testTree(void);

// Helper functions
int destroy(void *d);
char *toString(void *d);
int compare(void *d1, void *d2);
char *newObject(char *text);

int main(void) {
    printf("\n\n");
    
    // LinkedList
    if (testList())
        printf("testList successful\n\n");
    else
        printf("testList failed\n\n");

    // Stack
    if (testStack())
        printf("testStack successful\n\n");
    else
        printf("testStack failed\n\n");

    // Queue
    if (testQueue())
        printf("testQueue successful\n\n");
    else
        printf("testQueue failed\n\n");

    // Hash table
    if (testHash())
        printf("testHash successful\n\n");
    else
        printf("testHash failed\n\n");

    // Binary tree
    if (testTree())
        printf("testTree successful\n\n");
    else
        printf("testTree failed\n\n");

    printf("\n\n");
    return 0;
}

/* Test functions */
bool testList(void) {
    printf("\nRunning testList()\n----------\n");

    // initList()
    List *list = initList(destroy, toString, compare);
    if (list->head != NULL) {
        printf("\tlist->head != NULL\n");
        return False;
    }
    else
        printf("\t- initList() successful\n");

    // initListElement()
    ListElement *newLE = initListElement(newObject("Object 1"));
    if (strcmp(newLE->data, "Object 1") != 0) {
        printf("\tstrcmp(newLE->data, \"Object 1\") != 0\n");
        return False;
    }
    else
        printf("\t- initListElement() successful\n");

    // listElementAt(), listAdd()
    listAdd(list, newObject("Object 0"));
    if(strcmp((char*)listElementAt(list, 0), "Object 0") != 0) {
        printf("\tlistAdd(list, \"Object 0\") failed\n");
        return False;
    }
    else
        printf("\t- listAdd() and listElementAt() successful\n");
    
    // Check size
    if (list->size != 1) {
        printf("\tList size error. Test failed\n");
        return False;
    }
    else
        printf("\t- List size check successful\n");

    // listInsert
    listInsert(list, 3, newObject("Object 3"));
    if (listElementAt(list, 1) != NULL || listElementAt(list, 2) != NULL) {
        printf("\tlistInsert(list, 3, \"Object 3\") failed\n");
        return False;
    }
    else if (strcmp((char*)listElementAt(list, 3), "Object 3") != 0) {
        printf("\tlistInsert(list, 3, \"Object 3\") failed\n");
        return False;
    }
    else
        printf("\t- listInsert(list, 3, \"Object 3\") successful\n");

    // listAppend()
    listAppend(list, newObject("Object 4"));
    if (strcmp((char*)(list->tail->data), "Object 4") != 0) {
        printf("\tlistAppend(list, \"Object 4\") failed\n");
        return False;
    }
    else
        printf("\t- listAppend() successful\n");

    listAppend(list, newLE->data);
    if (strcmp((list->toString)(newLE->data), "Object 1") != 0) {
        printf("\tlistAppend() with toString check failed\n");
        return False;
    }
    else
        printf("\t- listAppend() with toString check successful\n");

    // Check size
    if (list->size != 6) {
        printf("\tList size error. Test failed\n");
        return False;
    }
    else
        printf("\t- List size check successful\n");

    // listPrint()
    printf("\t- listPrint() test:\n");
    listPrint(list);

    // freeList()
    freeList(list);
    printf("\t- freeList() successful\n");

    printf("=====================\n");
    return True;
}

bool testStack(void) {
    printf("\nRunning testStack()\n----------\n");

    // initStack
    Stack *stack = initStack(destroy, toString, compare);
    if (stack != NULL && stack->size == 0 && stack->head == NULL)
        printf("\t- initStack() successful\n");
    else {
        printf("\tinitStack() failed\n");
        return False;
    }

    // Push, pop, peek
    push(stack, newObject("Object 1"));
    if(strcmp((char*)(stack->head->data), "Object 1") != 0) {
        printf("\tpush() \"Object 1\" onto stack failed\n");
        return False;
    }
    else
        printf("\t- push() \"Object 1\" onto stack successful\n");

    push(stack, newObject("Object 2"));
    push(stack, newObject("Object 3"));

    if (stackSize(stack) != 3) {
        printf("\tstackSize() check failed\n");
        return False;
    }
    else
        printf("\t- stackSize() check successful\n");

    char *popped = (char*)(pop(stack));
    if (strcmp(popped, "Object 3") != 0) {
        printf("\tpop() \"Object 3\" off stack failed\n");
        printf("%s\n", popped);
        return False;
    }
    else
        printf("\t- pop() \"Object 3\" off stack successful\n");

    char *peeked = (char*)peekStack(stack);
    if (strcmp(peeked, "Object 2") != 0) {
        printf("\tpeekStack() \"Object 2\" at stack top failed\n");
        return False;
    }
    else
        printf("\t- peekStack() \"Object 2\" at stack top successful\n");

    if (stackSize(stack) != 2) {
        printf("\tstackSize() check failed\n");
        return False;
    }
    else
        printf("\t- stackSize() check successful\n");

    // Print test
    stackPrint(stack);
    printf("\t- stackPrint() successful\n");

    // freeStack()
    freeStack(stack);
    printf("\t- freeStack() successful\n");

    printf("=====================\n");
    return True;
}

bool testQueue(void) {
    printf("\nRunning testQueue()\n----------\n");

    // initQueue
    Queue *queue = initQueue(destroy, toString, compare);
    if (queue->size != 0 || queue->head != NULL || queue->tail != NULL) {
        printf("\tinitQueue() failed\n");
        return False;
    }
    else
        printf("\t- initQueue() successful\n");

    // enqueue()
    enqueue(queue, newObject("Object 1"));
    if (queueSize(queue) != 1) {
        printf("\tqueueSize() check failed at 1\n");
        return False;
    }
    else
        printf("\t- queueSize() check at 1 successful\n");
    if (strcmp((char*)(queue->head->data), (char*)(queue->tail->data)) != 0) {
        printf("\tenqueue() an empty queue test failed (head != tail)\n");
        return False;
    }
    else
        printf("\t- enqueue() an empty queue successful (head == tail)\n");
    if (strcmp((char*)(queue->head->data), "Object 1") != 0) {
        printf("\tenqueue() failed\n");
        return False;
    }
    else
        printf("\t- enqueue() successful\n");

    enqueue(queue, newObject("Object 2"));
    if (queueSize(queue) != 2) {
        printf("\tqueueSize() check failed at 2\n");
        return False;
    }
    else
        printf("\t- queueSize() check at 2 successful\n");
    enqueue(queue, newObject("Surprise!"));
    dequeue(queue);

    // queuePrint()
    queuePrint(queue);
    printf("\t- queuePrint() successful\n");

    char *front = (char*)dequeue(queue);
    if (strcmp(front, "Object 2") != 0) {
        printf("\tQueueing somehow failed\n");
        printf("\t%s\n", front);
        return False;
    }
    else
        printf("\t- Queueing generally successful\n");

    // peekQueue()
    char *peeked = (char*)peekQueue(queue);
    if (strcmp(peeked, "Surprise!") != 0) {
        printf("\tQueueing and/or peek somehow failed\n");
        return False;
    }
    else
        printf("\t- Queueing and peek successful\n");

    if (queueSize(queue) != 1) {
        printf("\tqueueSize() check failed at 1\n");
        return False;
    }
    else
        printf("\t- queueSize() check at 1 successful\n");

    // queuePrint()
    queuePrint(queue);
    printf("\t- queuePrint() successful\n");

    // freeQueue()
    freeQueue(queue);
    printf("\t- freeQueue() successful\n");

    printf("=====================\n");
    return True;
}

bool testHash(void) {
    printf("\nRunning testHash()\n----------\n");

    // initHashTable()
    HashTable *ht = initHashTable(destroy, toString, compare);

    // insertHash()
    insertHash(ht, "apple", newObject("A round fruit"));
    HashItem *hItem;
    if ((hItem = lookup(ht, "apple")) == NULL) {
        printf("\tEither insertHash() or lookup() failed\n");
        return False;
    }
    else if (strcmp((char*)(hItem->data), "A round fruit") != 0) {
        printf("\tEither insertHash() or lookup() failed\n");
        return False;
    }
    else
        printf("\t- insertHash() and lookup() successful\n");

    // deleteHash()
    if (deleteHash(ht, "apple") != 0) {
        printf("\tdeletehash() failed\n");
        return False;
    }
    else if (lookup(ht, "apple") != NULL) {
        printf("\tdeletehash() failed when lookup != NULL\n");
        return False;
    }
    else
        printf("\t- deleteHash() successful\n");

    // freeHashTable()
    freeHashTable(ht);
    printf("\t- freeQueue() successful\n");

    printf("=====================\n");
    return True;
}

bool testTree(void) {
    printf("\nRunning testTree()\n----------\n");

    // initTree()
    Tree *bintree = initTree(destroy, toString, compare);
    Tree *gentree = initTree(destroy, toString, compare);

    // add[Bin]Data()
    if (addBinData(bintree, newObject("Apple"), newObject("Apple")) == NULL) {
        printf("\taddBinData() failed\n");
        return False;
    }
    else if (treeSize(bintree) != 1) {
        printf("\ttreeSize(bintree) failed\n");
        return False;
    }
    else
        printf("\t- addBinData() successful\n");

    if (addData(gentree, treeRoot(gentree), 0, newObject("test"),
                newObject("test"), 1) != NULL) {
        printf("\taddData() to empty gentree failed\n");
        return False;
    }
    else
        printf("\t- addData() to empty gentree successful\n");

    treeRoot(gentree) = initTreeNode(newObject("CEO"), newObject("CEO"), 4);
    if (addData(gentree, treeRoot(gentree), 0, newObject("Director"),
                newObject("Director"), 3) == NULL) {
        printf("\taddData() failed\n");
        return False;
    }
    else if (treeSize(gentree) != 1) {
        printf("\ttreeSize(gentree) failed\n");
        return False;
    }
    else
        printf("\t- addData() to nonempty gentree successful\n");

    // freeTree()
    freeTree(bintree);
    freeTree(gentree);

    printf("=====================\n");
    return True;
}

/* Helper functions */
int destroy(void *d) {
    free((char*)d);
    return 0;
}

char *toString(void *d) {
    if (d != NULL)
        return (char*)d;
    else
        return "{NULL}";
}

int compare(void *d1, void *d2) {
    return strcmp((char*)d1, (char*)d2);
}

char *newObject(char *text) {
    char *newStr = malloc(sizeof(char[STRLEN]));
    strcpy(newStr, text);
    return newStr;
}