/**
 * Implementation of stack data structure.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

Stack *initStack(int (*destroy)(void *data), char *(*toString)(void *data),
                 int (*compare)(void *key1, void *key2)) {
    Stack *newStack;
    if ((newStack = malloc(sizeof(Stack))) == NULL) {
        fprintf(stderr, "ERROR: Couldn't malloc for new Stack\n");
        newStack = NULL;
    }
    else {
        newStack->size = 0;
        newStack->destroy = destroy;
        newStack->toString = toString;
        newStack->compare = compare;
        newStack->head = NULL;
    }
    return newStack;
}

StackItem *initStackItem(void *data) {
    StackItem *newItem;
    if ((newItem = malloc(sizeof(StackItem))) == NULL) {
        fprintf(stderr, "ERROR: Couldn't malloc for new StackItem\n");
        newItem = NULL;
    }
    else {
        newItem->data = data;
        newItem->previous = NULL;
    }
    return newItem;
}

void push(Stack *stack, void *data) {
    StackItem *newItem;
    if ((newItem = initStackItem(data)) == NULL) {
        fprintf(stderr, "ERROR: Couldn't push item onto Stack\n");
    }
    else {
        newItem->previous = stack->head;
        stack->head = newItem;
        (stack->size)++;
    }
}

void *pop(Stack *stack) {
    StackItem *off;
    if (stack->size == 0) {
        fprintf(stderr, "ERROR: Stack is empty; can't pop anything off\n");
        off = NULL;
    }
    else {
        off = stack->head;
        stack->head = off->previous;
        (stack->size)--;
    }
    void *offdata = off->data;
    free(off);
    return offdata;
}

void *peekStack(Stack *stack) {
    StackItem *top;
    if (stack->size == 0) {
        fprintf(stderr, "ERROR: Stack is empty; can't peek top item\n");
        top = NULL;
    }
    else {
        top = stack->head;
    }
    void *topdata = top->data;
    return topdata;
}

StackItem *freeStackItem(Stack *stack, StackItem *stackItem) {
    destroyStackItem(stack, stackItem);
    StackItem *previous = stackItem->previous;
    free(stackItem);
    return previous;
}

void freeStack(Stack *stack) {
    StackItem *itemPtr = stack->head;
    while (itemPtr != NULL) {
        itemPtr = freeStackItem(stack, itemPtr);
        (stack->size)--;
    }
    free(stack);
}


void stackItemPrint(Stack *stack, StackItem *stackItem) {
    printf("%s\n", (stack->toString)(stackItem->data));
}

void printStackTop(Stack *stack) {
    stackItemPrint(stack, stack->head);
}

void stackPrint(Stack *stack) {
    StackItem *stackPtr = stack->head;
    for (stackPtr; stackPtr != NULL; stackPtr = stackPtr->previous)
        stackItemPrint(stack, stackPtr);
}