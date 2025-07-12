#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/huffman.h"
#include "../include/stack.h"

Node *mergeNode(Node *left, Node *right) {
    // Create a new internal node
    Node *internalNode = malloc(sizeof(Node));
    if (internalNode == NULL) {
        perror("Error allocating memory for internal node");
        exit(EXIT_FAILURE);
    }

    // Set the character to NULL for internal nodes
    internalNode->character = NULL_CHAR;

    // Set the frequency to the sum of the left and right child frequencies
    internalNode->frequency = left->frequency + right->frequency;

    // Set the left and right pointers
    internalNode->left = left;
    internalNode->right = right;

    return internalNode;
}

Node **buildMinHeap(int *frequencies, int *size) {
    // Allocate memory for the array of Node pointers
    Node **nodes = malloc(*size * sizeof(Node *));
    if (nodes == NULL) {
        perror("Error allocating memory for nodes");
        exit(EXIT_FAILURE);
    }

    int i = 0; // Index for frequencies
    int j = 0; // Index for nodes

    while (i < 256 && j < *size) {

        while (frequencies[i] == 0) {
            // Skip characters with zero frequency
            ++i;
        }

        // Create a new node for each character with non-zero frequency
        nodes[j] = createNode(i, frequencies[i]);
        j++;
        i++;
    }

    for (int i = (*size - 1) / 2; i >= 0; i--) {
        // Build the max heap by calling heapify on each non-leaf node
        heapify(nodes, size, i);
    }

    return nodes;
}

void heapify(Node **nodes, int *size, int i) {
    int largest = i;

    while (1) {
        int left = 2 * largest + 1;
        int right = 2 * largest + 2;
        int maxIdx = largest;

        if (left < *size && nodes[left]->frequency < nodes[maxIdx]->frequency) {
            maxIdx = left;
        }
        if (right < *size && nodes[right]->frequency < nodes[maxIdx]->frequency) {
            maxIdx = right;
        }

        if (maxIdx != largest) {
            Node *temp = nodes[largest];
            nodes[largest] = nodes[maxIdx];
            nodes[maxIdx] = temp;
            largest = maxIdx;
        } else {
            break;
        }
    }
}

Node *createNode(char character, int frequency) {
    // Allocate memory for a new node
    Node *node = malloc(sizeof(Node));
    if (node == NULL) {
        perror("Error allocating memory for node");
        exit(EXIT_FAILURE);
    }

    // Set the character and frequency
    node->character = character;
    node->frequency = frequency;

    // Initialize left and right pointers to NULL
    node->left = NULL;
    node->right = NULL;

    return node;
}

void freeNode(Node *node) {
    if (node != NULL) {
        // Recursively free left and right child nodes
        freeNode(node->left);
        freeNode(node->right);

        // Free the current node
        free(node);
    }
}

Node *popNode(Node **nodes, int *size) {
    if (*size <= 0) {
        fprintf(stderr, "Heap is empty\n");
        return NULL;
    }

    Node *root = nodes[0];

    // Replace the root of the heap with the last element
    nodes[0] = nodes[*size - 1];
    (*size)--;

    // Restore the max heap property
    heapify(nodes, size, 0);

    return root;
}

void pushNode(Node **nodes, int *size, Node *node) {
    // Increase the size of the heap
    (*size)++;

    // Insert the new node at the end of the heap
    nodes[*size - 1] = node;
    
    // Restore the max heap property
    for (int i = (*size - 1) / 2; i >= 0; i--) {
        heapify(nodes, size, i);
    }
}

Node *buildHuffmanTree(Node **nodes, int *size) {
    while (*size > 1) {
        // Pop the two nodes with the smallest frequencies
        Node *left = popNode(nodes, size);
        Node *right = popNode(nodes, size);
        
        if (left == NULL || right == NULL) {
            fprintf(stderr, "Error: Not enough nodes to build the Huffman tree\n");
            exit(EXIT_FAILURE);
        }

        // Merge them into a new internal node
        Node *internalNode = mergeNode(left, right);

        // Push the new internal node back into the heap
        pushNode(nodes, size, internalNode);
    }

    // The last remaining node is the root of the Huffman tree
    return nodes[0];
}

void traverseHuffmanTree(Node *root, char **codes) {
    if (root == NULL) {
        return;
    }

    Stack *stack = createStack();
    pushStackNode(stack, root, "");

    while (!isStackEmpty(stack)) {
        StackNode *stackNode = popStackNode(stack);
        Node *currentNode = stackNode->node;
        char *currentCode = stackNode->code;

        if (currentNode->left == NULL && currentNode->right == NULL) {
            // Leaf node, store the code
            codes[(int)currentNode->character] = strdup(currentCode);
            free(stackNode);
        } else {
            // Internal node, push children onto the stack with updated codes
            if (currentNode->left != NULL) {
                char *leftCode = malloc(strlen(currentCode) + 2);
                sprintf(leftCode, "%s0", currentCode);
                pushStackNode(stack, currentNode->left, leftCode);
            }
            if (currentNode->right != NULL) {
                char *rightCode = malloc(strlen(currentCode) + 2);
                sprintf(rightCode, "%s1", currentCode);
                pushStackNode(stack, currentNode->right, rightCode);
            }
            free(stackNode);
        }
    }
    freeStack(stack);

    return;
}
