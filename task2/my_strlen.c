/* Custom strlen implementation
 * May 16, 2019
 * This code is intended to run on x86-64 little-endian architecture.
 * my_strlen() should work as the libc's strlen() function, assuming that:
 *   1. str points to a valid string.
 *   2. That string is zero-terminated.
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/* https://jameshfisher.com/2017/01/24/bitwise-check-for-zero-byte */
#define zero(v) ((v - 0x0101010101010101) & ~v & 0x8080808080808080)

size_t my_strlen(const char * str) {
    uint64_t ans = zero(*(uint64_t *)str);
    size_t z = 0;

    /* ans = 0 means that the argument does not contain any zero byte */
    while (ans == 0) {
        printf("%s \n", str);
        /* Shift the string and find any zero in the next chunk */
        str += 8;
        z += 8;
        ans = zero(*(uint64_t *)str);
    }

    /* Find the first non-null byte, starting by the least significant one */
    while ((ans & 0xFF) == 0) {
        ans >>= 8;
        ++z;
    }

    return z;
}

/******************************************************************************/

#define strlen my_strlen

int main(int argc, char ** argv) {
    if (argc > 1) {
        printf("%lu\n", strlen(argv[1]));
    } else {
        fprintf(stderr, "Syntax: %s <string>\n", argv[0]);
    }
}
