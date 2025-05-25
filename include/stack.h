#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include "huffman.h"

typedef struct StackNode {
    Node *node;
    struct StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
    int size;
} Stack;

/**
 * @brief Create a Stack object
 * 
 * @return Stack* Pointer to the newly created stack
 */
Stack *createStack(void);

/**
 * @brief Pops a node from the stack
 * 
 * @param stack Pointer to the stack from which to pop the node
 * @return StackNode* Pointer to the popped node, or NULL if the stack is empty
 */
StackNode *popStackNode(Stack *stack);

/**
 * @brief Push a node onto the stack
 * 
 * @param stack Pointer to the stack where the node will be pushed
 * @param node Pointer to the node to be pushed onto the stack
 */
void pushStackNode(Stack *stack, Node *node);


/**
 * @brief Free the memory allocated for the stack
 * 
 * @param stack Pointer to the stack to be freed
 */
void freeStack(Stack *stack);

/**
 * @brief Check if the stack is empty
 * 
 * @param stack Pointer to the stack to check
 * @return int 1 if the stack is empty, 0 otherwise
 */
int isStackEmpty(Stack *stack);

#endif // STACK_H
