#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    const char *path = (argc > 1) ? argv[1] : "tests/no_newline.txt";
    int fd = open(path, O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    printf("Testing no_newline (path=%s) with byte-wise expectations (BUFFER_SIZE=1):\n", path);
    printf("----------------------------------\n");

    const char *expected = "no newline"; // file without trailing \n
    size_t len = strlen(expected);
    int ok = 1;
    char *line;

    // For BUFFER_SIZE=1, until the whole line is accumulated, expect NULL
    for (size_t i = 1; i <= len; ++i)
    {
        line = get_next_line(fd);
        if (line != NULL)
        {
            printf("call %zu: expected NULL, got \"%s\" ✗\n", i, line);
            ok = 0;
            free(line);
        }
        else
        {
            printf("call %zu: NULL ✓\n", i);
        }
    }

    // After reading all bytes, next call should return the full line
    line = get_next_line(fd);
    if (line && strcmp(line, expected) == 0)
    {
        printf("call %zu: \"%s\" ✓\n", len + 1, line);
    }
    else
    {
        printf("call %zu: expected \"%s\", got %s ✗\n", len + 1, expected, line ? line : "NULL");
        ok = 0;
    }
    free(line);

    // And then subsequent call(s) should be NULL
    line = get_next_line(fd);
    if (line == NULL)
        printf("call %zu: NULL ✓\n", len + 2);
    else
    {
        printf("call %zu: expected NULL, got \"%s\" ✗\n", len + 2, line);
        ok = 0;
        free(line);
    }

    close(fd);

    printf("\n----------------------------------\n");
    printf("Expected (BS=1): %zu NULL calls, then one full line, then NULL.\n", len);
    printf("Result: %s\n", ok ? "PASSED ✓" : "FAILED ✗");

    return ok ? 0 : 1;
}