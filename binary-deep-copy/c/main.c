// gcc -o main main.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct bnode {
    struct bnode *left;
    struct bnode *right;
    uint64_t value;
} bnode_t;

bnode_t *new_bnode(uint64_t value)
{
    bnode_t *node = calloc(1, sizeof(bnode_t));
    node->value = value;
    return node;
}

bnode_t *deep_copy(bnode_t *original)
{
    bnode_t *new = new_bnode(original->value);
    if (original->left) {
	new->left = deep_copy(original->left);
    }
    if (original->right) {
	new->right = deep_copy(original->right);
    }
    return new;
}

bnode_t *test_new_btree()
{
    bnode_t *node = new_bnode(10);
    node->left = new_bnode(6);
    node->right = new_bnode(18);
    node->left->left = new_bnode(3);
    node->left->right = new_bnode(7);
    node->left->left->left = new_bnode(1);
    return node;
}

int test_check_btree(bnode_t *node)
{
    if (node->value != 10) {
	return false;
    }
    if (node->left->value != 6) {
	return false;
    }
    if (node->right->value != 18) {
	return false;
    }
    if (node->left->left->value != 3) {
	return false;
    }
    if (node->left->right->value != 7) {
	return false;
    }
    if (node->left->left->left->value != 1) {
	return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    bnode_t *node = test_new_btree();
    bnode_t *copy = deep_copy(node);

    if (!test_check_btree(copy)) {
	printf("failed\n");
	return 1;
    } else {
	printf("passed\n");
	return 0;
    }
}
