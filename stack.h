/**
 * Header file for implementation of stack data structure.
 *
 */
#ifndef STACK
#define STACK

// Macro functions
#define stackEmpty(stack)           ((stack)->head == NULL)
#define stackSize(stack)            ((stack)->size)
#define isStackTop(stack, item)     ((item) == (stack)->head)

typedef struct stackitem_ {
    void *data;
    struct stackitem_ *previous;
} StackItem;

typedef struct stack_ {
    int size;
    int (*destroy)(void *data);     // specifies how to deallocate
    char *(*toString)(void *data);   // specifies how to print data
    int (*compare)(void *key1, void *key2);
    StackItem *head;
} Stack;

Stack *initStack(int (*destroy)(void *data), char *(*toString)(void *data),
                 int (*compare)(void *key1, void *key2));
StackItem *initStackItem(void *data);
void push(Stack *stack, void *data);
void *pop(Stack *stack);
void *peekStack(Stack *stack);
StackItem *freeStackItem(Stack *stack, StackItem *stackItem);
void freeStack(Stack *stack);
void stackItemPrint(Stack *stack, StackItem *stackItem);
void printStackTop(Stack *stack);
void stackPrint(Stack *stack);

#endif
