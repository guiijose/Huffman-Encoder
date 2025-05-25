#include <stdio.h>
#include <stdlib.h>

#include "../include/stack.h"

Stack *createStack(void) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));

    if (stack == NULL) {
        perror("Failed to create stack:");
        exit(EXIT_FAILURE);
    }

    stack->top = NULL;
    stack->size = 0;

    return stack;
}

StackNode *popStackNode(Stack *stack) {
    if (stack->top == NULL) {
        return NULL; // Stack is empty
    }

    StackNode *node = stack->top;
    stack->top = node->next;
    stack->size--;

    return node;
}

void pushStackNode(Stack *stack, Node *node) {
    StackNode *newNode = (StackNode*)malloc(sizeof(StackNode));

    if (newNode == NULL) {
        perror("Failed to push node onto stack:");
        exit(EXIT_FAILURE);
    }

    newNode->node = node;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
}

void freeStack(Stack *stack) {
    StackNode *current = stack->top;
    StackNode *nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }

    free(stack);
}

int isStackEmpty(Stack *stack) {
    return stack->size == 0;
}
