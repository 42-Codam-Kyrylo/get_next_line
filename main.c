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

    printf("Testing no_newline (path=%s):\n", path);
    printf("----------------------------------\n");

    char *line1 = get_next_line(fd);
    char *line2 = get_next_line(fd);
    char *line3 = get_next_line(fd);
    char *line4 = get_next_line(fd);
    char *line5 = get_next_line(fd);
    close(fd);

    printf("line1: %s", line1 ? (strcmp(line1, "\n") == 0 ? "\"\\n\" ✓\n" : line1) : "NULL ✗\n");
    printf("line2: %s", line2 ? (strcmp(line2, "\n") == 0 ? "\"\\n\" ✓\n" : line2) : "NULL ✗\n");
    printf("line3: %s", line3 ? (strcmp(line3, "\n") == 0 ? "\"\\n\" ✓\n" : line3) : "NULL ✗\n");
    printf("line4: %s", line4 ? (strcmp(line4, "\n") == 0 ? "\"\\n\" ✓\n" : line4) : "NULL ✗\n");
    printf("line5: %s", line5 ? "NOT NULL ✗\n" : "NULL ✓\n");

    printf("\n----------------------------------\n");
    printf("Expected: 4 newlines, then NULL\n");
    printf("Result: %s\n", 
           (line1 && strcmp(line1, "\n") == 0 &&
            line2 && strcmp(line2, "\n") == 0 &&
            line3 && strcmp(line3, "\n") == 0 &&
            line4 && strcmp(line4, "\n") == 0 &&
            line5 == NULL) ? "PASSED ✓" : "FAILED ✗");

    free(line1);
    free(line2);
    free(line3);
    free(line4);

    return 0;
}