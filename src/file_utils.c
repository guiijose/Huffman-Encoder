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

    int bytes_read = fread(buffer, 1, file_size, file);

    while (bytes_read < file_size) {
        // If the read was not successful, try again
        bytes_read += fread(buffer + bytes_read, 1, file_size - bytes_read, file);
    }

    fclose(file); // Close the file

    return buffer;
}


int *buildFrequencies(char *content, int *size) {
    // Initialize the frequencies array
    int *frequencies = malloc(256 * sizeof(int));
    if (frequencies == NULL) {
        perror("Error allocating memory for frequencies");
        return NULL;
    }

    // Initialize all frequencies to 0
    for (int i = 0; i < 256; i++) {
        frequencies[i] = 0;
    }

    // Count the frequency of each character in the content
    for (int i = 0; content[i] != '\0'; i++) {
        int ch = content[i];

        // Increment size if new character is found
        if (frequencies[ch] == 0) {
            (*size)++;
        }

        // Increment the frequency of the character
        ++frequencies[ch];
    }

    return frequencies;
}
