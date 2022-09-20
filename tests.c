#include <stdio.h>

#include "bitvector.h"

#define TEST_LEN 1000
#define assert(x) if (!x) return false

bool test_bitvec(void) {
  bitvec_t A = {0}, *B = NULL;
  bool A_t[TEST_LEN] = {0}, B_t[TEST_LEN] = {0};
  size_t i, j;

  for (i = 0; i < 100; ++i) {
    assert(bitvec_init(&A, 10));
    B = bitvec_create(11);
    assert(B);

    for (j = 0; j < TEST_LEN; ++j) {
      bool a, b;

      A_t[j] = rand() % 2;
      B_t[j] = rand() % 2;

      assert(bitvec_push(&A, A_t[j]));
      assert(bitvec_push(B, B_t[j]));

      assert(bitvec_get(&A, j, &a));
      assert(bitvec_get(B, j, &b));

      assert(a == A_t[j]);
      assert(b == B_t[j]);
    }
    putchar('.');

    for (j = 0; j < 1000; ++j) {
      bool a, b;
      size_t p = rand() % A.n, q = rand() % B->n;
      bool x = rand() % 2, y = rand() % 2;
      assert(bitvec_get(&A, p, &a));
      assert(bitvec_get(B, q, &b));

      assert(a == A_t[p]);
      assert(b == B_t[q]);

      assert(bitvec_set(&A, p, x));
      assert(bitvec_set(B, q, y));

      assert(bitvec_get(&A, p, &a));
      assert(bitvec_get(B, q, &b));

      assert(a == x);
      assert(b == y);

      A_t[p] = x;
      B_t[q] = y;
    }
    putchar('.');

    for (j = 0; j < 1000; ++j) {
      size_t p = rand() % A.n, q = rand() % B->n;
      bool x = rand() % 2, y = rand() % 2;

      assert(bitvec_GET(&A, p) == A_t[p]);
      assert(bitvec_GET(B, q) == B_t[q]);

      bitvec_SET(&A, p, x);
      bitvec_SET(B, q, y);

      assert(bitvec_GET(&A, p) == x);
      assert(bitvec_GET(B, q) == y);

      A_t[p] = x;
      B_t[q] = y;
    }
    putchar('.');

    for (j = 0; j < TEST_LEN; ++j) {
      bool a, b;

      assert(bitvec_pop(&A, &a));
      assert(bitvec_pop(B, &b));

      assert(a == A_t[TEST_LEN-j-1]);
      assert(b == B_t[TEST_LEN-j-1]);
    }
    putchar('.');

    bitvec_free_contents(&A);
    bitvec_free(B);
    B = NULL;
  }

  return true;
}

int main(void) {
  bool r;
  srand(101);
  puts("Running tests:");
  r = test_bitvec();
  if (r) puts("\nOK");
  else puts("\nFAIL");
  return !r;
}
