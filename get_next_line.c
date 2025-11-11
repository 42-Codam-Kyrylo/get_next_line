/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/10 15:54:20 by kvolynsk      #+#    #+#                 */
/*   Updated: 2025/11/11 17:10:39 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	char *buffer = malloc(BUFFER_SIZE + 1);
	int result = read(fd, buffer, BUFFER_SIZE);
	if (result == -1)
	{
		return (NULL);
	}

	buffer[BUFFER_SIZE + 1] = '\0';

	return (buffer);
}
