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
		fprintf(stderr, "Failed to open file: %s\n", path);
		return 1;
	}

	char *line = get_next_line(fd);
	close(fd);

	if (line == NULL)
	{
		fprintf(stderr, "get_next_line returned NULL (expected a line)\n");
		return 1;
	}

	// Debug info: show returned string and metadata
	size_t len = strlen(line);
	printf("Returned line (len=%zu): '%s'\n", len, line);
	if (len > 0)
		printf("Last char code: %d\n", (unsigned char)line[len - 1]);

	// Expectation from the test: content should equal "no newline"
	const char *expected = "no newline";
	if (strcmp(line, expected) != 0)
	{
		fprintf(stderr, "Content mismatch. Expected: '%s', Got: '%s'\n", expected, line);
		free(line);
		return 1;
	}

	printf("OK: line matches expected without trailing newline.\n");
	free(line);
	return 0;
}