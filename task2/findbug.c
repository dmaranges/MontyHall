/*
 * String splitter
 *
 * Example:
 *
 * $ make
 * $ ./splitter "This is a test"
 *
 * Get help:
 *
 * $ ./splitter --help
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Type definitions ------------------------------------------------------------

typedef char * string_t;        // A string is an array of bytes
typedef string_t * matrix_t;    // A matrix is an array of strings

// Constant definitions --------------------------------------------------------

static const char DELIM = ' ';  // String delimiter: space

// Functions declaration -------------------------------------------------------

// Split a string into a string array. Return NULL on error.
static matrix_t strsplit(const string_t string, char delim);

// Clone a string array. Return NULL on error.
static matrix_t matrixdup(const matrix_t matrix);

// Free a string array. Nothing happens if it's null.
static void matrixfree(matrix_t matrix);

// -----------------------------------------------------------------------------
// Main function

int main(int argc, char ** argv) {
    matrix_t parts;
    matrix_t copy;

    size_t i;

    // Check parameters

    switch (argc) {
    case 1:
        fprintf(stderr, "ERROR: No string given.\n");
        return EXIT_FAILURE;

    case 2:
        if (strcmp(argv[1], "--help") == 0) {
            printf("Syntax:\n  %s \"A few strings\"\n", argv[0]);
            return EXIT_SUCCESS;
        }

        break;

    default:
        fprintf(stderr, "ERROR: Too much arguments given. Did you surround your string with quotes (\") ?\n");
        return EXIT_FAILURE;
    }

    // Split the first argument by spaces

    if (parts = strsplit(argv[1], DELIM), !parts) {
        fprintf(stderr, "ERROR: String was not splitted.\n");
        return EXIT_FAILURE;
    }

    // Copy the matrix and delete the original
    for (int it = 0; parts[it]; it++) {
        printf("parts = %s\n", parts[it]);
    }
    copy = matrixdup(parts);
    
    for (int it = 0; copy[it]; it++) {
        printf("copy = %s\n", copy[it]);
    }
    matrixfree(parts);

    // Print the matrix

    for (i = 0; copy[i]; i++) {
        printf("%s\n", copy[i]);
    }

    // Delete the copy and exit

    matrixfree(copy);
    return EXIT_SUCCESS;
}

// -----------------------------------------------------------------------------
// Split a string into a string array. Return NULL on error.

char ** strsplit(const string_t string, char delim) {
    char sdelim[] = { delim, '\0' };    // strtok() wants a string
    matrix_t matrix;
    matrix_t _matrix;
    string_t part;
    size_t i = 0;

    /*
     * A byte matrix is a null-terminated string array.
     * For instance: { "This", "is", "a", "demo", NULL }
     */

    // Create the pointer array

    if (matrix = (matrix_t)calloc(1, sizeof(string_t)), !matrix) {
        fprintf(stderr, "ERROR: Insufficient memory for matrix.\n");
        return NULL;
    }

    for (part = strtok(string, sdelim); part; part = strtok(NULL, sdelim)) {

        // Allocate also space for the terminating null pointer

        if (_matrix = (matrix_t)realloc(matrix, (i + 2) * sizeof(string_t)), _matrix) {
            matrix = _matrix;

            // Copy each string

            if (matrix[i] = strdup(part), !matrix[i]) {
                fprintf(stderr, "ERROR: Insufficient memory for string.\n");
                matrixfree(matrix);
				return NULL;
            }

            // Terminate array with NULL
            matrix[++i] = NULL;
        } else {
            fprintf(stderr, "ERROR: Insufficient memory for matrix.\n");
            matrixfree(matrix);
            return NULL;
        }
    };

    return matrix;
}

// -----------------------------------------------------------------------------
// Clone a string array. Return NULL on error.

matrix_t matrixdup(const matrix_t matrix) {
    matrix_t copy = NULL;
    matrix_t _copy;
    size_t i;
    
    for (i = 0; matrix[i]; i++) {
        // realloc() works as malloc() when the first argument is NULL

        if (_copy = (matrix_t)realloc(copy, (i + 2) * sizeof(string_t)), _copy) {
            copy = _copy;
            // Copy each string

            if (copy[i] = strdup(matrix[i]), !copy[i]) {
                fprintf(stderr, "ERROR: Insufficient memory for string copy.\n");
                matrixfree(copy);
				return NULL;
            }
            //copy[i + 1] = NULL; //error 1

        } else {
            fprintf(stderr, "ERROR: Insufficient memory for matrix copy.\n");
            matrixfree(copy);
            return NULL;
        }
    }

    // Terminate array with NULL
    copy[i] = NULL;
    return copy;
}

// -----------------------------------------------------------------------------
// Free a string array. Nothing happens if it's null.

void matrixfree(matrix_t matrix) {

    // Do nothing if the matrix is null

    if (matrix) {
        for (int i = 0; matrix[i]; i++) {
            free(matrix[i]);
        }

        free(matrix);
    }
}