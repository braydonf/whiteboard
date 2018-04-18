#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

#define GREEN "\x1B[32m"
#define RED "\x1B[31m"
#define RESET "\x1b[0m"

typedef struct item {
    struct item *prev;
    struct item *next;
    uint64_t value;
} item_t;

item_t *new_linked_item(uint64_t value)
{
    item_t *new = calloc(1, sizeof(item_t));
    new->value = value;
    return new;
}

void insert_after(item_t *item, item_t *new)
{
    if (item->next) {
        item->next->prev = new;
        new->next = item->next;
    }

    item->next = new;
    new->prev = item;
}

void insert_before(item_t *item, item_t *new)
{
    if (item->prev) {
        new->prev = item->prev;
    }
    item->prev = new;
    new->next = item;
}


void delete_item(item_t *item)
{
    if (!item->prev) {
        item->next->prev = NULL;
    } else {
        item->prev->next = item->next;
    }

    if (!item->next) {
        item->prev->next = NULL;
    } else {
        item->next->prev = item->prev;
    }
}

int test_linked(item_t *item, item_t *next) {
    if (item->next != next) {
        printf(RED "failed" RESET " next for %"PRIu64" expected: %"PRIu64", actual: %"PRIu64"\n",
               item->value, item->next->value, next->value);
        return 1;
    } else {
        printf(GREEN "passed" RESET " next for %"PRIu64" actual: %"PRIu64"\n",
               item->value, item->next->value);
        return 0;
    }

    if (next->prev != item) {
        printf(RED "failed" RESET " prev for %"PRIu64" expected: %"PRIu64", actual: %"PRIu64"\n",
               next->value, item->value, next->prev->value);
        return 1;
    } else {
        printf(GREEN "passed" RESET " prev for: %"PRIu64", actual: %"PRIu64"\n",
               next->value, next->prev->value);
        return 0;
    }
}

int test_linked_head(item_t *item) {
    if (item->prev != NULL) {
        printf(RED "failed" RESET " head for %"PRIu64" expected: NULL, actual: %"PRIu64"\n",
               item->value, item->prev->value);
        return 1;
    } else {
        printf(GREEN "passed" RESET " head for %"PRIu64" actual: NULL\n", item->value);
        return 0;
    }
}

int test_linked_tail(item_t *item) {
    if (item->next != NULL) {
        printf(RED "failed" RESET " tail for %"PRIu64" expected: NULL, actual: %"PRIu64"\n",
               item->value, item->next->value);
        return 1;
    } else {
        printf(GREEN "passed" RESET " tail for %"PRIu64" actual: NULL\n",
               item->value);
        return 0;
    }
}

int main(int argc, char **argv) {
    int failed = 0;

    item_t *a = new_linked_item(0);
    item_t *b = new_linked_item(1);
    item_t *c = new_linked_item(2);
    item_t *d = new_linked_item(3);
    item_t *e = new_linked_item(4);

    insert_after(a, b);
    insert_after(b, c);
    insert_after(c, e);
    insert_after(c, d);

    failed += test_linked(a, b);
    failed += test_linked(b, c);
    failed += test_linked(c, d);
    failed += test_linked(d, e);

    delete_item(b);
    failed += test_linked(a, c);
    failed += test_linked_head(a);

    delete_item(a);
    failed += test_linked(c, d);
    failed += test_linked_head(c);

    delete_item(e);
    failed += test_linked_tail(d);

    insert_before(d, a);
    failed += test_linked(a, d);
    failed += test_linked_tail(d);

    return (failed > 0) ? 1 : 0;
}
