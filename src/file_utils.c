#include <stdio.h>
#include <stdlib.h>

char *read_file(const char *filename) {
    // Open the file in read mode and check for error
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Place the cursor at the end and then get the size of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);

    // Place the cursor back to the beginning of the file

    fseek(file, 0, SEEK_SET);

    // Initialize the buffer and check for error
    char *buffer = malloc(file_size + 1);
    
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0'; // Null-terminate the buffer

    // Read the whole file into the buffer

    size_t bytes_read = fread(buffer, 1, file_size, file);

    while (bytes_read < file_size) {
        // If the read was not successful, try again
        bytes_read += fread(buffer + bytes_read, 1, file_size - bytes_read, file);
    }

    fclose(file); // Close the file

    return buffer;
}