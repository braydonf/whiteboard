// gccgo -o main main.go

package main

import "fmt"
import "os"

const GREEN = "\x1B[32m"
const RED = "\x1B[31m"
const RESET = "\x1b[0m"

// Note: Does not use pointers yet
func StrStr(haystack string, needle string) string {
	hlen := len(haystack)
	nlen := len(needle)
	if hlen == 0 || nlen == 0 || nlen > hlen {
		return ""
	}

	for i := 0; i < hlen; i++ {
		if haystack[i] == needle[0] {
			match := true
			for j := 0; j < nlen; j++ {
				if (i + j >= hlen || haystack[i + j] != needle[j]) {
					match = false
					break
				}
			}
			if match {
				return haystack[i:]
			}
		}
	}

	return ""
}

func TestStrStr(haystack string, needle string, expected string, index uint) bool {
	found := StrStr(haystack, needle);
	if (found == expected) {
		fmt.Printf(GREEN + "passed" + RESET + " for %d: result: %s\n", index, found)
		return true
	}
	fmt.Printf(RED + "failed" + RESET + " for %d: result: %s, expected: %s\n", index, found, expected)
	return false
}


func main() {

	failed := 0
	status := 0

	if (!TestStrStr("some of the words that are random", "that", "that are random", 0)) {
		failed++
	}

	if (!TestStrStr("some more words ending with a t", "that", "", 1)) {
		failed++
	}

	if (!TestStrStr("therefore than this thanks that", "that", "that", 2)) {
		failed++
	}

	if (!TestStrStr("haystack", "h", "haystack", 3)) {
		failed++
	}

	if (!TestStrStr("n", "needle", "", 4)) {
		failed++
	}

	if (!TestStrStr("", "overflow", "", 5)) {
		failed++
	}

	if (!TestStrStr("overflow", "", "", 6)) {
		failed++
	}

	if (failed > 0) {
		status = 1
	}

	os.Exit(status)
}
