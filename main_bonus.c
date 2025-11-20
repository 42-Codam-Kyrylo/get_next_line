#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	print_stream(int fd)
{
	char	*line;
	size_t	len;

	while ((line = get_next_line(fd)) != NULL)
	{
		len = strlen(line);
		if (len > 0)
			(void)!write(STDOUT_FILENO, line, len);
		free(line);
	}
	return (0);
}

static int	print_streams_interleaved(int fd1, int fd2)
{
	char	*l1;
	char	*l2;
	int		done1;
	int		done2;
	size_t	len;

	l1 = NULL;
	l2 = NULL;
	done1 = 0;
	done2 = 0;
	while (!done1 || !done2)
	{
		if (!done1)
		{
			l1 = get_next_line(fd1);
			if (l1)
			{
				len = strlen(l1);
				if (len > 0)
					(void)!write(STDOUT_FILENO, l1, len);
				free(l1);
			}
			else
				done1 = 1;
		}
		if (!done2)
		{
			l2 = get_next_line(fd2);
			if (l2)
			{
				len = strlen(l2);
				if (len > 0)
					(void)!write(STDOUT_FILENO, l2, len);
				free(l2);
			}
			else
				done2 = 1;
		}
	}
	return (0);
}

static int	open_arg_as_fd(const char *arg)
{
	if (arg && strcmp(arg, "-") == 0)
		return (STDIN_FILENO);
	return (open(arg, O_RDONLY));
}

int	main(int argc, char **argv)
{
	int	fd1;
	int	fd2;
	int	rc;
	int	fd;

	if (argc >= 3)
	{
		fd1 = open_arg_as_fd(argv[1]);
		fd2 = open_arg_as_fd(argv[2]);
		rc = 0;
		if (fd1 == -1)
		{
			perror("open fd1");
			return (1);
		}
		if (fd2 == -1)
		{
			if (fd1 != STDIN_FILENO)
				close(fd1);
			perror("open fd2");
			return (1);
		}
		rc = print_streams_interleaved(fd1, fd2);
		if (fd1 != STDIN_FILENO)
			close(fd1);
		if (fd2 != STDIN_FILENO)
			close(fd2);
		return (rc);
	}
	// Fallback: single input behavior (stdin if no arg or '-')
	if (argc < 2 || (argc >= 2 && strcmp(argv[1], "-") == 0))
		return (print_stream(STDIN_FILENO));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	rc = print_stream(fd);
	close(fd);
	return (rc);
}
