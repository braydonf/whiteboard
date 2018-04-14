// gccgo -o main main.go

package main

import "fmt"

const GREEN = "\x1B[32m"
const RED = "\x1B[31m"
const RESET = "\x1b[0m"

func fib(n int) uint64 {
	if (n == 0) {
		return 0;
	}
	var prev uint64 = 0;
	var next uint64 = 1;

	for i := 1; i < n; i++ {
		var _prev uint64 = prev;
		prev = next;
		next = _prev + next;
	}

	return next;
}

func main() {
	expected := [51]uint64{0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269,2178309,3524578,5702887,9227465,14930352,24157817,39088169,63245986,102334155,165580141,267914296,433494437,701408733,1134903170,1836311903,2971215073,4807526976,7778742049,12586269025}

	for i := 0; i < 51; i++ {
		result := fib(i)
		if (result != expected[i]) {
			fmt.Printf(RED + "failed" + RESET + " for %v, actual: %v, expected: %v\n", i, result, expected[i])
		} else {
			fmt.Printf(GREEN + "passed" + RESET + " for %v, actual: %v\n", i, result)
		}
	}
}
