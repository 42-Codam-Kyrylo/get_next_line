#include <criterion/criterion.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

Test(edge_cases, empty_file)
{
	int fd = open("empty.txt", O_RDONLY);
	cr_assert_neq(fd, -1, "Failed to open file");

	char *line = get_next_line(fd);
	close(fd);

	cr_assert_null(line, "Empty file should return NULL");
}

Test(edge_cases, no_newline_at_end)
{
	int fd = open("no_newline.txt", O_RDONLY);
	cr_assert_neq(fd, -1, "Failed to open file");

	char *line = get_next_line(fd);
	close(fd);

	cr_assert_not_null(line, "Should read line without newline");
	cr_assert_str_eq(line, "no newline", "Content mismatch");
	free(line);
}

Test(edge_cases, only_newlines)
{
	int fd = open("only_newlines.txt", O_RDONLY);
	cr_assert_neq(fd, -1, "Failed to open file");

	char *line1 = get_next_line(fd);
	char *line2 = get_next_line(fd);
	char *line3 = get_next_line(fd);
	char *line4 = get_next_line(fd);
	char *line5 = get_next_line(fd);
	close(fd);

	cr_assert_str_eq(line1, "\n", "First empty line");
	cr_assert_str_eq(line2, "\n", "Second empty line");
	cr_assert_str_eq(line3, "\n", "Third empty line");
	cr_assert_str_eq(line4, "\n", "Fourth empty line");
	cr_assert_null(line5, "Should return NULL after all lines, got: %s", line5 ? line5 : "NULL");
	
	free(line1);
	free(line2);
	free(line3);
	free(line4);
}

Test(edge_cases, invalid_fd)
{
	char *line = get_next_line(-1);
	cr_assert_null(line, "Invalid fd should return NULL");

	line = get_next_line(9999);
	cr_assert_null(line, "Non-existent fd should return NULL");
}

Test(edge_cases, single_line_with_newline)
{
	int fd = open("single_line.txt", O_RDONLY);
	cr_assert_neq(fd, -1, "Failed to open file");

	char *line1 = get_next_line(fd);
	char *line2 = get_next_line(fd);
	close(fd);

	cr_assert_str_eq(line1, "single line\n", "Single line mismatch");
	cr_assert_null(line2, "Should return NULL after single line");
	
	free(line1);
}
