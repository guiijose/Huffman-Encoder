#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/file_utils.h"
#include "../include/huffman.h"


int main(int argc, char *argv[]) {

    // Check if the user provided a file path
    if (argc < 2) {
        fprintf(stderr, "Usage: ./encode <path_to_file>\n");
        return 1;
    }

    char *content = read_file(argv[1]);

    if (content == NULL) {
        return 1;
    }

    printf("File content:\n\"%s\"\n", content);

    int size = 0;

    // Build the frequency array
    int *frequencies = buildFrequencies(content, &size);

    // Build the max heap of nodes
    Node **nodes = buildMinHeap(frequencies, &size);

    printf("Size of heap: %d\n", size);

    for (int i = 0; i < size; i++) {
        printf("\tCharacter index: '%d', Frequency: %d\n", nodes[i]->character, nodes[i]->frequency);
    }

    Node *root = buildHuffmanTree(nodes, &size);

    if (root == NULL) {
        fprintf(stderr, "Error building Huffman tree.\n");
        return 1;
    }

    printf("\033[0;32mHuffman tree built successfully.\033[0m\n");

    return 0;
}
