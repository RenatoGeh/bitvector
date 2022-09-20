#ifndef _BITVECTOR_H
#define _BITVECTOR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdbool.h>

typedef struct bitvec {
  size_t n;
  size_t c;
  unsigned long long int *d;
} bitvec_t;

/* Initializes a bitvec_t containing at least n elements, discarding all and any values B may
 * contain. Returns success. */
bool bitvec_init(bitvec_t *B, size_t n);
/* Creates and returns a new (dynamically allocated) bitvec_t containing at least n elements. */
bitvec_t* bitvec_create(size_t n);

/* Frees the contents of a bitvec_t. */
void bitvec_free_contents(bitvec_t *B);
/* Frees bitvec_t and its contents. */
void bitvec_free(bitvec_t *B);

/* Sets the i-th position of bitvec_t B to x. Returns true if successful, false otherwise. */
bool bitvec_set(bitvec_t *B, size_t i, bool x);
/* Retrieves the value of the i-th position of bitvec_t B. Returns true if successful, false
 * otherwise. */
bool bitvec_get(bitvec_t *B, size_t i, bool *x);

/* Sets the i-th position of bitvec_t B to x without checking for out-of-bounds. Use with care. */
void bitvec_SET(bitvec_t *B, size_t i, bool x);
/* Retrieves the value of the i-th position of bitvec_t B without checking for out-of-bounds. Use
 * with care. */
bool bitvec_GET(bitvec_t *B, size_t i);

/* Appends value x to bitvec_t B's tail. */
bool bitvec_push(bitvec_t *B, bool x);
/* Removes and retrieves the last element of bitvec_t B. */
bool bitvec_pop(bitvec_t *B, bool *x);

/* Prints a representation of bitvec_t B. */
void bitvec_print(bitvec_t *B);

#ifdef __cplusplus
}
#endif

#endif
