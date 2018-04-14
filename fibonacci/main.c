#include <stdint.h>
#include <stdio.h>

#define GREEN "\x1B[32m"
#define RED "\x1B[31m"
#define RESET "\x1b[0m"

int fib(int n) {
  return n;
}

uint8_t expected[] = {1,1,2,3,5,8,13,21,34};
int expected_length = 8;

int main(int argc, char **argv) {

  for (int i = 0; i < expected_length; i++) {
    int result = fib(i);
    if (result != expected[i]) {
      printf(RED "failed" RESET " for %i: actual: %i, expected: %i\n", i, result, expected[i]);
    } else {
      printf(GREEN "passed" RESET " for %i, actual: %i\n", i, result);
    }
  }

  return 0;
}
