#include <criterion/criterion.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

const char file1[] = "file1.txt";

Test(get_next_line_test, read_first_line)
{
	int fd = open(file1, O_RDONLY);
	cr_assert_neq(fd, -1, "Failed to open file");

	char *got = get_next_line(fd);
	close(fd);
	
	cr_assert_not_null(got, "get_next_line returned NULL");
	cr_assert_str_eq(got, "Hello world! line1\n", "got: %s, want: %s", got, "Hello world! line1\n");
	free(got);
}

Test(get_next_line_test, read_whole_file)
{
	int fd = open(file1, O_RDONLY);
	cr_assert_neq(fd, -1, "Failed to open file");

	char *got1 = get_next_line(fd);
	char *got2 = get_next_line(fd);
	char *got3 = get_next_line(fd);
	char *got4 = get_next_line(fd);
	char *got5 = get_next_line(fd);
	close(fd);

	cr_assert_str_eq(got1, "Hello world! line1\n", "Line 1 mismatch");
	cr_assert_str_eq(got2, "line2\n", "Line 2 mismatch");
	cr_assert_str_eq(got3, "line 3 line 3 line 3\n", "Line 3 mismatch");
	cr_assert_str_eq(got4, "last line!", "Line 4 mismatch (no newline at EOF)");
	cr_assert_null(got5, "Should return NULL after EOF");
	
	free(got1);
	free(got2);
	free(got3);
	free(got4);
}