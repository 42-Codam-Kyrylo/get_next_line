// main.c — ручной тест для функции get_next_line.
// Запускает несколько последовательных чтений, имитируя тест read_whole_file.
// Советы по отладке:
// 1. Поставь breakpoint внутри get_next_line (например, на первую строку функции).
// 2. F5 (конфигурация "Debug get_next_line").
// 3. Смотри переменные: buffer, rest_buffer, read_result.
// 4. Используй Step Over (F10) / Step Into (F11).

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    const char *path = (argc > 1) ? argv[1] : "tests/file1.txt"; // файл лежит в папке tests
    int fd = open(path, O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    printf("Reading whole file test (path=%s):\n", path);
    printf("----------------------------------\n");

    char *got1 = get_next_line(fd);
    printf("Line 1: %s", got1 ? got1 : "NULL\n");
    if (got1 && got1[strlen(got1) - 1] != '\n')
        printf("\n");

    char *got2 = get_next_line(fd);
    printf("Line 2: %s", got2 ? got2 : "NULL\n");
    if (got2 && got2[strlen(got2) - 1] != '\n')
        printf("\n");

    char *got3 = get_next_line(fd);
    printf("Line 3: %s", got3 ? got3 : "NULL\n");
    if (got3 && got3[strlen(got3) - 1] != '\n')
        printf("\n");

    char *got4 = get_next_line(fd);
    printf("Line 4: %s", got4 ? got4 : "NULL\n");
    if (got4 && got4[strlen(got4) - 1] != '\n')
        printf("\n");

    char *got5 = get_next_line(fd);
    printf("Line 5: %s", got5 ? got5 : "NULL\n");
    if (got5 && got5[strlen(got5) - 1] != '\n')
        printf("\n");

    close(fd);

    free(got1);
    free(got2);
    free(got3);
    free(got4);
    free(got5);

    return 0;
}