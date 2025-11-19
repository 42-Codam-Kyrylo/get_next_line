#include "get_next_line_bonus.h"
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	sfree(char **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
	}
}

Test(gnl_bonus, interleaved_two_fds_simple)
{
	int	fd1;
	int	fd2;

	fd1 = open("file1.txt", O_RDONLY);
	fd2 = open("single_line.txt", O_RDONLY);
	cr_assert_neq(fd1, -1, "Failed to open file1.txt");
	cr_assert_neq(fd2, -1, "Failed to open single_line.txt");
	char *a1 = get_next_line(fd1); // file1: line1\n
	char *b1 = get_next_line(fd2); // single_line: line\n
	char *a2 = get_next_line(fd1); // file1: line2\n
	char *b2 = get_next_line(fd2); // single_line: EOF -> NULL
	char *a3 = get_next_line(fd1); // file1: line3\n
	char *a4 = get_next_line(fd1); // file1: last line! (no trailing \n)
	cr_expect_str_eq(a1, "Hello world! line1\n");
	cr_expect_str_eq(a2, "line2\n");
	cr_expect_str_eq(a3, "line 3 line 3 line 3\n");
	cr_expect_str_eq(a4, "last line!");
	cr_expect_str_eq(b1, "single line\n");
	cr_expect_null(b2);
	sfree(&a1);
	sfree(&a2);
	sfree(&a3);
	sfree(&a4);
	sfree(&b1); // b2 is NULL
	close(fd1);
	close(fd2);
}

Test(gnl_bonus, interleaved_three_fds_round_robin)
{
	int	f1;
	int	f2;
	int	f3;

	f1 = open("file1.txt", O_RDONLY);
	f2 = open("only_newlines.txt", O_RDONLY);
	f3 = open("no_newline.txt", O_RDONLY);
	cr_assert_neq(f1, -1, "open file1.txt failed");
	cr_assert_neq(f2, -1, "open only_newlines.txt failed");
	cr_assert_neq(f3, -1, "open no_newline.txt failed");
	char *t1 = get_next_line(f1); // file1 line1\n
	char *u1 = get_next_line(f2); // "\n"
	char *v1 = get_next_line(f3); // "no newline" (no trailing \n)
	char *u2 = get_next_line(f2); // "\n"
	char *t2 = get_next_line(f1); // file1 line2\n
	char *v2 = get_next_line(f3); // EOF -> NULL
	char *u3 = get_next_line(f2); // "\n"
	char *t3 = get_next_line(f1); // file1 line3\n
	char *u4 = get_next_line(f2); // "\n"
	char *t4 = get_next_line(f1); // file1 last line!
	char *u5 = get_next_line(f2); // EOF -> NULL
	cr_expect_str_eq(t1, "Hello world! line1\n");
	cr_expect_str_eq(t2, "line2\n");
	cr_expect_str_eq(t3, "line 3 line 3 line 3\n");
	cr_expect_str_eq(t4, "last line!");
	cr_expect_str_eq(u1, "\n");
	cr_expect_str_eq(u2, "\n");
	cr_expect_str_eq(u3, "\n");
	cr_expect_str_eq(u4, "\n");
	cr_expect_null(u5);
	cr_expect_str_eq(v1, "no newline");
	cr_expect_null(v2);
	sfree(&t1);
	sfree(&t2);
	sfree(&t3);
	sfree(&t4);
	sfree(&u1);
	sfree(&u2);
	sfree(&u3);
	sfree(&u4);
	sfree(&v1);
	close(f1);
	close(f2);
	close(f3);
}

Test(gnl_bonus, invalid_fd_does_not_affect_valid)
{
	char	*bad;
	int		fd;
	char	*ok1;
	char	*ok2;

	// invalid first
	bad = get_next_line(-1);
	cr_expect_null(bad);
	fd = open("single_line.txt", O_RDONLY);
	cr_assert_neq(fd, -1, "Failed to open single_line.txt");
	ok1 = get_next_line(fd);
	ok2 = get_next_line(fd);
	cr_expect_str_eq(ok1, "single line\n");
	cr_expect_null(ok2);
	sfree(&ok1);
	close(fd);
}

Test(gnl_bonus, separate_state_for_two_fds_same_file)
{
	int	a;
	int	b;

	a = open("file1.txt", O_RDONLY);
	b = open("file1.txt", O_RDONLY);
	cr_assert_neq(a, -1);
	cr_assert_neq(b, -1);
	// Read alternatingly; each fd should keep its own position
	char *a1 = get_next_line(a); // line1\n
	char *b1 = get_next_line(b); // line1\n
	char *a2 = get_next_line(a); // line2\n
	char *b2 = get_next_line(b); // line2\n
	cr_expect_str_eq(a1, "Hello world! line1\n");
	cr_expect_str_eq(b1, "Hello world! line1\n");
	cr_expect_str_eq(a2, "line2\n");
	cr_expect_str_eq(b2, "line2\n");
	sfree(&a1);
	sfree(&a2);
	sfree(&b1);
	sfree(&b2);
	close(a);
	close(b);
}
