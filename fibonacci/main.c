#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define GREEN "\x1B[32m"
#define RED "\x1B[31m"
#define RESET "\x1b[0m"

uint64_t fib(int n) {
  if (n == 0) {
    return 0;
  }
  uint64_t prev = 0;
  uint64_t next = 1;

  for (int i = 1; i < n; i++) {
    uint64_t _prev = prev;
    prev = next;
    next = _prev + next;
  }

  return next;
}

uint64_t expected[] = {0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269,2178309,3524578,5702887,9227465,14930352,24157817,39088169,63245986,102334155,165580141,267914296,433494437,701408733,1134903170,1836311903,2971215073,4807526976,7778742049,12586269025};
int expected_length = 51;

int main(int argc, char **argv) {

  for (int i = 0; i < expected_length; i++) {
    uint64_t result = fib(i);
    if (result != expected[i]) {
      printf(RED "failed" RESET " for %i: actual: %"PRIu64", expected: %"PRIu64"\n", i, result, expected[i]);
    } else {
      printf(GREEN "passed" RESET " for %i, actual: %"PRIu64"\n", i, result);
    }
  }

  return 0;
}
