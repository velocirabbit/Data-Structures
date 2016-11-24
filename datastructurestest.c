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
    if (addBinData(bintree, newObject("Earth"), newObject("Earth")) == NULL) {
        printf("\taddBinData() failed\n");
        return False;
    }
    else if (treeSize(bintree) != 1) {
        printf("\ttreeSize(bintree) failed\n");
        return False;
    }
    else
        printf("\t- addBinData() successful\n");

    if (addData(gentree, treeRoot(gentree), 1, newObject("test"),
                newObject("test"), 1) != NULL) {
        printf("\tfailed addData() to empty gentree failed\n");
        return False;
    }
    else
        printf("\t- failed addData() to empty gentree successful\n");

    if (addData(gentree, treeRoot(gentree), 0, newObject("CEO"),
                newObject("CEO"), 4) == NULL) {
        printf("\taddData() failed\n");
        return False;
    }
    else if (treeSize(gentree) != 1) {
        printf("\ttreeSize(gentree) failed\n");
        return False;
    }
    else
        printf("\t- addData() to empty gentree successful\n");
        
    if (addData(gentree, treeRoot(gentree), 0, newObject("Director"),
                newObject("Director"), 3) == NULL) {
        printf("\taddData() failed\n");
        return False;
    }
    else if (treeSize(gentree) != 2) {
        printf("\ttreeSize(gentree) failed\n");
        return False;
    }
    else
        printf("\t- addData() to nonempty gentree successful\n");

    // printTree()
    printf("\t- Print 1:\n");
    printf("\n*** bintree: ***\n");
    printTree(bintree, treeRoot(bintree), 1, 0);
    printf("\n\n*** gentree: **\n");
    printTree(gentree, treeRoot(gentree), 0, 0);

    // add more to both
    addBinData(bintree, newObject("Cat"), newObject("Cat"));
    addBinData(bintree, newObject("Dog"), newObject("Dog"));
    addBinData(bintree, newObject("xylophone"), newObject("xylophone"));
    addBinData(bintree, newObject("Mouse"), newObject("Mouse"));
    addBinData(bintree, newObject("Zebra"), newObject("Zebra"));
    addBinData(bintree, newObject("Tarantula"), newObject("Tarantula"));

    int gensize = 2;
    char *tmp = malloc(sizeof(char[80]));
    int chiefC = 1;
    for (int i = 0; i < numChildren(treeRoot(gentree)); i++) {
        if (i != 0) {
            addData(gentree, treeRoot(gentree), i, newObject("Director+"),
                    newObject("Director+"), (i % 2) + 2);
            gensize++;
        }
        for (int j = 0; j < numChildren(nodeChild(treeRoot(gentree), i)); j++) {
            sprintf(tmp, "Chief %d", chiefC++);
            int numEmp = (i % 2) + (j % 3) + 2;
            addData(gentree, nodeChild(treeRoot(gentree), i), j,
                                    newObject(tmp), newObject(tmp), numEmp);
            gensize++;
            if (i == 1 && j == 2) {
                TreeNode *tmp = nodeChild(treeRoot(gentree), i);
                tmp = nodeChild(tmp, j);
                addData(gentree, tmp, 1, newObject("FINDME1"), newObject("FINDME1"), 0);
                gensize++;
            }
            if (i == 0 && j == 1) {
                TreeNode *tmp = nodeChild(treeRoot(gentree), i);
                tmp = nodeChild(tmp, j);
                addData(gentree, tmp, 1, newObject("FINDME2"), newObject("FINDME2"), 0);
                gensize++;
            }
        }
    }

    // printTree()
    printf("\n\n\n\t- Print 2:\n");
    printf("\n*** bintree: ***\n");
    printTree(bintree, treeRoot(bintree), 1, 0);
    printf("\ntreeSize(bintree): %d\n", treeSize(bintree));
    printf("\n\n*** gentree: ***\n");
    printTree(gentree, treeRoot(gentree), 0, 0);
    printf("\ntreeSize(gentree): %d\n\n", treeSize(gentree));

    // Test additions
    if (treeSize(bintree) != 7) {
        printf("\ttreeSize(bintree) failed at 7 members\n");
        return False;
    }
    else
        printf("\t- Adding more nodes to bintree successful\n");

    if (treeSize(gentree) != gensize) {
        printf("\ttreeSize(gentree) failed at %d members\n", gensize);
        return False;
    }
    else
        printf("\t- Adding more nodes to gentree successful\n");

    // findNode() - bin
    TreeNode *findBin = findNode(bintree, 1, "xylophone", NULL);
    if (findBin == NULL) {
        printf("\tfindNode(bintree, 1, \"xylophone\", NULL) failed\n");
        return False;
    }
    else
        printf("\t- \"xylophone\" in bintree found: %s\n", nodeKey(findBin));
    findBin = findNode(bintree, 1, NULL, newObject("Tarantula"));
    if (findBin == NULL) {
        printf("\tfindNode(bintree, 1, NULL, newObject()) failed\n");
        return False;
    }
    else
        printf("\t- findNode(bintree, 1, NULL, newObject()) found: %s\n", nodeKey(findBin));
    findBin = findNode(bintree, 1, "octopus", NULL);
    if (findBin != NULL) {
        printf("\tfindNode in bintree of nonexistant key failed\n");
        return False;
    }
    else
        printf("\t- findNode in bintree of nonexistant key successful (returned NULL)\n");
    findBin = findNode(bintree, 1, NULL, newObject("jackalope"));
    if (findBin != NULL) {
        printf("\tfindNode in bintree of nonexistant object failed\n");
        return False;
    }
    else
        printf("\t- findNode in bintree of nonexistant object successful (returned NULL)\n");

    // findNode() - gen
    findBin = findNode(gentree, 0, "FINDME1", NULL);
    if (findBin == NULL) {
        printf("\tfindNode(gentree, 1, \"FINDME1\", NULL) failed\n");
        return False;
    }
    else
        printf("\t- \"FINDME1\" in gentree found: %s\n", nodeKey(findBin));
    findBin = findNode(gentree, 0, NULL, newObject("FINDME2"));
    if (findBin == NULL) {
        printf("\tfindNode(gentree, 1, NULL, newObject()) failed\n");
        return False;
    }
    else
        printf("\t- findNode(gentree, 1, NULL, newObject()) found: %s\n", nodeKey(findBin));
    findBin = findNode(gentree, 0, "octopus", NULL);
    if (findBin != NULL) {
        printf("\tfindNode in gentree of nonexistant key failed\n");
        return False;
    }
    else
        printf("\t- findNode in gentree of nonexistant key successful (returned NULL)\n");
    findBin = findNode(gentree, 0, NULL, newObject("jackalope"));
    if (findBin != NULL) {
        printf("\tfindNode in gentree of nonexistant object failed\n");
        return False;
    }
    else
        printf("\t- findNode in gentree of nonexistant object successful (returned NULL)\n");

    addBinData(bintree, newObject("Panda"), newObject("Panda"));
    addBinData(bintree, newObject("Rhino"), newObject("Rhino"));
    addBinData(bintree, newObject("megazord"), newObject("megazord"));
    addBinData(bintree, newObject("Thundurous"), newObject("Thundurous"));
    addBinData(bintree, newObject("Pokemon"), newObject("Pokemon"));
    addBinData(bintree, newObject("Koala"), newObject("Koala"));
    addBinData(bintree, newObject("Dandelion"), newObject("Dandelion"));
    addBinData(bintree, newObject("Camera"), newObject("Camera"));
    addBinData(bintree, newObject("Angielski"), newObject("Angielski"));
    addBinData(bintree, newObject("Dutch"), newObject("Dutch"));
    addBinData(bintree, newObject("Doduo"), newObject("Doduo"));
    addBinData(bintree, newObject("Eames"), newObject("Eames"));

    int empc = 1;
    for (int i = 0; i < numChildren(treeRoot(gentree)); i++) {
        TreeNode *dir = nodeChild(treeRoot(gentree), i);
        for (int j = 0; j < numChildren(dir); j++) {
            TreeNode *pm = nodeChild(dir, j);
            for (int k = 0; k < numChildren(pm); k++) {
                sprintf(tmp, "Employee %d", empc++);
                addData(gentree, pm, k, newObject(tmp), newObject(tmp), 0);
            }
        }
    }
    free(tmp);

    // printTree()
    printf("\n\n\n\t- Print 3:\n");
    printf("\n*** bintree: ***\n");
    printTree(bintree, treeRoot(bintree), 1, 0);
    printf("\ntreeSize(bintree): %d\n", treeSize(bintree));

    // deleteNode() test - bin
    deleteNode(bintree, 1, "Mouse", NULL);
    deleteNode(bintree, 1, NULL, newObject("Cat"));
    printf("\tDeleted nodes from bintree\n");

    // printTree()
    printf("\n\n\n\t- Print 4:\n");
    printf("\n*** bintree: ***\n");
    printTree(bintree, treeRoot(bintree), 1, 0);
    printf("\ntreeSize(bintree): %d\n", treeSize(bintree));

    printf("\n\n*** gentree: ***\n");
    printTree(gentree, treeRoot(gentree), 0, 0);
    printf("\ntreeSize(gentree): %d\n\n", treeSize(gentree));

    // deleteNode() test - gen
    deleteNode(gentree, 0, "Chief 4", NULL);
    deleteNode(gentree, 0, NULL, newObject("Chief 6"));
    printf("\tDeleted nodes from gentree\n");

    // printTree()
    printf("\n\n*** gentree: ***\n");
    printTree(gentree, treeRoot(gentree), 0, 0);
    printf("\ntreeSize(gentree): %d\n\n", treeSize(gentree));

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

