#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stddef.h>

/**
 * @brief Node in a Huffman tree.
 * A leaf node stores a character; an internal node 
 * has NULL character and child pointers.
 */
typedef struct Node {
    char *character;     // Character for leaf node, NULL for internal node
    int frequency;       // Frequency of character(s) in this subtree
    struct Node *left;   // Left child
    struct Node *right;  // Right child
} Node;

/**
 * @brief Creates an internal Huffman tree node by merging two child nodes.
 * 
 * @param left Pointer to the left child node.
 * @param right Pointer to the right child node.
 * @return Node* Pointer to the newly created internal node.
 */
Node *mergeNode(Node *left, Node *right);

#endif // HUFFMAN_H