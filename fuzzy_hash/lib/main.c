#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fuzzy.h"


#define SIZE 0x50000


/*
 * int fuzzy_hash_file(FILE *handle, char *result);
 * int fuzzy_hash_filename(const char * filename, char * result);
 * int fuzzy_hash_buf(const unsigned char *buf, uint32_t buf_len, char *result)
 */



int main() {

    unsigned char *buf;
    char *result;
    buf = (unsigned char *) malloc(SIZE);
    result = (char *) malloc(FUZZY_MAX_RESULT);

    char *text = "Also called fuzzy hashes, Ctph can match inputs that have homologies.";
    strcpy(buf, (unsigned char *) text);

    int state = fuzzy_hash_buf(buf, strlen(buf), result);
    printf("%d\n", state);
    printf("%s\n", result);
    return 0;
}
