#ifndef FILE_UTILS_H
#define FILE_UTILS_H

/**
 * @brief Reads the content of a file
 * 
 * @param filename The path to the file
 * @return char* The content of the file
 */
char *read_file(const char *filename);

/**
 * @brief Builds the frequency array of characters from the file content
 * 
 * @param content The content of the file
 * @param size Pointer to store the size of the frequency array
 * @return int* The frequency array
 */
int *buildFrequencies(char *content, int *size);

#endif // FILE_UTILS_H
