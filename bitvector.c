#include <stdio.h>

#include "bitvector.h"

#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))

/* Bit operations. */
#define BIT_SET(b, i, x) b = ((b) & ~(1ULL << (i))) | (((unsigned long long int) (x)) << (i))
#define BIT_GET(b, i) ((b) >> (i)) & 1ULL

/* Out of bounds. */
#define OOB(B, i,  b) (((i) >= (B)->n) || ((b) >= (B)->c))

typedef unsigned long long int ull_t;

bool bitvec_init(bitvec_t *B, size_t n) {
  size_t b = n/64;
  B->n = 0;
  B->c = max(1, b);
  B->d = (ull_t*) malloc(b*sizeof(ull_t));
  if (!B->d) return false;
  return true;
}

bitvec_t* bitvec_create(size_t n) {
  size_t b = n/64;
  bitvec_t *B = (bitvec_t*) malloc(sizeof(bitvec_t));
  if (!B) return NULL;
  B->n = 0;
  B->c = max(1, b);
  B->d = (ull_t*) malloc(b*sizeof(ull_t));
  if (!B->d) { free(B); return NULL; }
  return B;
}

void bitvec_free_contents(bitvec_t *B) { free(B->d); }
void bitvec_free(bitvec_t *B) { bitvec_free_contents(B); free(B); }

bool bitvec_set(bitvec_t *B, size_t i, bool x) {
  size_t b = i/64, j = i%64;
  if (OOB(B, i, b)) return false;
  BIT_SET(B->d[b], j, x);
  return true;
}
bool bitvec_get(bitvec_t *B, size_t i, bool *x) {
  size_t b = i/64, j = i%64;
  if (OOB(B, i, b)) return false;
  *x = BIT_GET(B->d[b], j);
  return true;
}

void bitvec_SET(bitvec_t *B, size_t i, bool x) {
  register size_t b = i/64, j = i%64;
  BIT_SET(B->d[b], j, x);
}
bool bitvec_GET(bitvec_t *B, size_t i) {
  register size_t b = i/64, j = i%64;
  return BIT_GET(B->d[b], j);
}

#define MAGIC_ADD_LEN 2

bool bitvec_grow(bitvec_t *B) {
  ull_t *d;
  d = (ull_t*) realloc(B->d, (B->c+MAGIC_ADD_LEN)*sizeof(ull_t));
  if (!d) return false;
  B->d = d;
  B->c += MAGIC_ADD_LEN;
  return true;
}

bool bitvec_push(bitvec_t *B, bool x) {
  size_t i = B->n;
  size_t b = i/64, j = i%64;
  if (B->n % 64 == 63) if (!bitvec_grow(B)) return false;
  ++B->n;
  BIT_SET(B->d[b], j, x);
  return true;
}
bool bitvec_pop(bitvec_t *B, bool *x) {
  size_t i = --B->n;
  size_t b = i/64, j = i%64;
  if (!x) return true;
  *x = BIT_GET(B->d[b], j);
  return true;
}

void print_ull(unsigned long long int d, size_t k) {
  size_t i;
  for (i = 0; i < k; ++i) putchar('0' + ((d >> i) & 1ULL));
}

void bitvec_print(bitvec_t *B) {
  size_t i;
  printf("<[");
  for (i = 0; i < B->n; i += 64) print_ull(B->d[i], (i+64 > B->n)*(B->n - i) + (i+64 <= B->n)*64);
  printf("],\nn = %lu, c = %lu>\n", B->n, B->c*64);
}
