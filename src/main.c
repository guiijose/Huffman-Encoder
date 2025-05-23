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
    Node **nodes = buildMaxHeap(frequencies, size);

    return 0;
}
