#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/file_utils.h"


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

    return 0;
}