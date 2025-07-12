#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stddef.h>

#define NULL_CHAR '\0' // Define NULL character for internal nodes


/**
 * @brief Node in a Huffman tree.
 * A leaf node stores a character; an internal node 
 * has NULL character and child pointers.
 */
typedef struct Node {
    char character;      // Character for leaf node, NULL for internal node
    int frequency;       // Frequency of character(s) in this subtree
    struct Node *left;   // Left child
    struct Node *right;  // Right child
} Node;

typedef struct Frequency {
    int *frequencies;      // Character
    int size;       // Frequency of the character
} Frequency;

/**
 * @brief Creates an internal Huffman tree node by merging two child nodes.
 * 
 * @param left Pointer to the left child node.
 * @param right Pointer to the right child node.
 * @return Node* Pointer to the newly created internal node.
 */
Node *mergeNode(Node *left, Node *right);

/**
 * @brief Builds a max heap of Huffman tree nodes based on character frequencies.
 * 
 * @param frequencies Array of character frequencies.
 * @param size Number of characters with non-zero frequencies.
 * @return Node** Pointer to an array of pointers to the created nodes.
 */
Node **buildMinHeap(int *frequencies, int *size);

/**
 * @brief Creates a new leaf node for a character with its frequency.
 * 
 * @param character Character of leaf node.
 * @param frequency Frequency of the character.
 * @return Node* Pointer to the newly created node.
 */
Node *createNode(char character, int frequency);

/**
 * @brief Frees the memory allocated for a Huffman tree node.
 * 
 * @param node Pointer to the node to be freed.
 */
void freeNode(Node *node);

/**
 * @brief Maintains the max heap property for a subtree rooted at index i, implemented iteratively.
 * 
 * @param nodes Array of node pointers representing the heap.
 * @param size Number of elements in the heap.
 * @param i Index of the subtree root to heapify.
 */
void heapify(Node **nodes, int *size, int i);

/**
 * @brief Pops the root node from the heap and restores the max heap property.
 * 
 * @param nodes Array of node pointers representing the heap.
 * @param size Pointer to the number of elements in the heap.
 * @return Node* Pointer to the popped node, or NULL if the heap is empty.
 */
Node *popNode(Node **nodes, int *size);

/**
 * @brief Pushes a new node into the heap and restores the max heap property.
 * 
 * @param nodes Array of node pointers representing the heap.
 * @param size Pointer to the number of elements in the heap.
 * @param node Pointer to the node to be pushed into the heap.
 */
void pushNode(Node **nodes, int *size, Node *node);

/**
 * @brief Builds the Huffman tree from the array of nodes.
 * 
 * @param nodes Array of node pointers representing the heap.
 * @param size Pointer to the number of elements in the heap.
 * @return Node* Pointer to the root of the Huffman tree.
 */
Node *buildHuffmanTree(Node **nodes, int *size);

/**
 * @brief Traverses the Huffman tree and generates codes for each character.
 * 
 * @param root the root of the Huffman tree.
 * @param codes a pre-allocated array of strings to store the codes for each character.
 */
void traverseHuffmanTree(Node *root, char **codes);

#endif // HUFFMAN_H
