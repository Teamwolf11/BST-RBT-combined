#include <stdio.h> /* for fprintf */
#include <stdlib.h> /* for size_t, malloc, realloc, exit */
#include "mylib.h"
#include <assert.h>
#include <ctype.h>

/**
 * Memory allocation function.
 * @param s - takes the size given to allocate.
 * @return result - returns memory allocated.
 **/
void *emalloc(size_t s) {
    void* result =malloc(s);
    if(result==NULL){
        fprintf(stderr, "memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

/**
 * Memory reallocation function.
 * @param myArray - takes the array we want to reallocate memory to.
 * @param s - takes the size given to allocate.
 * @return result - returns memory allocated.
 **/
void *erealloc(void *myArray, size_t s) {
    void* changedArray = realloc(myArray, s);
    if (NULL == changedArray) {
        fprintf(stderr, "memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return changedArray;
}

/**
 * Function to get words from file. 
 * @param s - word to be read in.
 * @param limit - max size of word.
 * @param stream - where the word  will come from.
 * @return int - based off whether reached end of file or not.
 **/
int getword(char *s, int limit, FILE *stream) {
    int c;
    char *w = s;
    assert(limit > 0 && s != NULL && stream != NULL);
    /* skip to the start of the word */
    while (!isalnum(c = getc(stream)) && EOF != c)
        ;
    if (EOF == c) {
        return EOF;
    } else if (--limit > 0) { /* reduce limit by 1 to allow for the \0 */
        *w++ = tolower(c);
    }
    while (--limit > 0) {
        if (isalnum(c = getc(stream))) {
            *w++ = tolower(c);
        } else if ('\'' == c) {
            limit++;
        } else {
            break;
        }
    }
    *w = '\0';
    return w - s;
}
