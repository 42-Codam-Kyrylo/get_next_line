#include "get_next_line.h"
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

int	main(int argc, char **argv)
{
	int	fd;
	int	rc;

	if (argc < 2 || (argc >= 2 && strcmp(argv[1], "-") == 0))
	{
		// Read from stdin
		return (print_stream(STDIN_FILENO));
	}
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
