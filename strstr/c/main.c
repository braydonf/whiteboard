#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define GREEN "\x1B[32m"
#define RED "\x1B[31m"
#define RESET "\x1b[0m"

const char *strstr_(const char *haystack, const char *needle)
{
    int hlen = strlen(haystack);
    int nlen = strlen(needle);
    if (!hlen || !nlen || nlen > hlen) {
        return NULL;
    }

    for (int i = 0; i < hlen; i++) {
        if (haystack[i] == needle[0]) {
            bool match = true;
            for (int j = 0; j < nlen; j++) {
                if (i + j >= hlen || haystack[i + j] != needle[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return &haystack[i];
            }
        }
    }

    return NULL;
}

int test_strstr_(const char *haystack, const char *needle, const char *expected, int num)
{
    const char *found = strstr_(haystack, needle);
    if ((expected == NULL && found == NULL) || strcmp(found, expected) == 0) {
        printf(GREEN "passed" RESET " for %i: result: %s\n", num, found);
        return 1;
    }
    printf(RED "failed" RESET " for %i: result: %s, expected: %s\n", num, found, expected);
    return 0;
}

int main(int argc, char **argv)
{
    int failed = 0;

    if (test_strstr_("some of the words that are random", "that", "that are random", 0)) {
        failed++;
    }

    if (test_strstr_("some more words ending with a t", "that", NULL, 1)) {
        failed++;
    }

    if (test_strstr_("therefore than this thanks that", "that", "that", 2)) {
        failed++;
    }

    if (test_strstr_("haystack", "h", "haystack", 3)) {
        failed++;
    }

    if (test_strstr_("n", "needle", NULL, 4)) {
        failed++;
    }

    if (test_strstr_("", "overflow", NULL, 5)) {
        failed++;
    }

    if (test_strstr_("overflow", "", NULL, 6)) {
        failed++;
    }

    return failed > 0 ? 1 : 0;
}
