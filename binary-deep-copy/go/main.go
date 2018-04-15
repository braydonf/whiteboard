// gccgo -o main main.go

package main

import "fmt"
import "os"

const GREEN = "\x1B[32m"
const RED = "\x1B[31m"
const RESET = "\x1b[0m"

type Bnode struct {
	value uint64
	left  *Bnode
	right *Bnode
}

func DeepCopy(node *Bnode) *Bnode {
	new := Bnode{node.value, nil, nil}
	if (node.left != nil) {
		new.left = DeepCopy(node.left)
	}
	if (node.right != nil) {
		new.right = DeepCopy(node.right)
	}
	return &new
}

func DeepCompare(a *Bnode, b *Bnode) bool {
	if (a != nil && b != nil) {
		if (a.value != b.value) {
			return false
		}
		if (!DeepCompare(a.left, b.left) || !DeepCompare(a.right, b.right)) {
			return false
		}
		return true

	} else if (a != nil && b == nil) {
		return false
	} else if (a == nil && b != nil) {
		return false
	} else if (a == nil && b == nil) {
		return true
	}
	return false;
}

func main() {
	status := 0
	node := &Bnode{
		10,
		&Bnode{
			6,
			&Bnode{
				3,
				&Bnode{
					1,
					nil,
					nil,
				},
				nil,
			},
			&Bnode{
				7,
				nil,
				nil,
			},
		},
		&Bnode{
			18,
			nil,
			nil,
		},
	};

	copy := DeepCopy(node);
	same := DeepCompare(node, copy);

	if (!same) {
		fmt.Printf(RED + "failed" + RESET + "\n")
		status =1
	} else {
		fmt.Printf(GREEN + "passed" + RESET + "\n")
	}

	os.Exit(status)
}
