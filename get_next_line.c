/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/10 15:54:20 by kvolynsk      #+#    #+#                 */
/*   Updated: 2025/11/12 21:04:05 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include "stdio.h"

char	*get_next_line(int fd)
{
	static char *rest_buffer = NULL;
	int i = 0;

	while(rest_buffer && rest_buffer[i] != '\n') {
		i++;
	}
	if(rest_buffer && rest_buffer[i] == '\n') {
		++i;
		char *next_line = malloc(i + 1);
		ft_strlcpy(next_line, rest_buffer, i + 1);
		rest_buffer = ft_strdup(rest_buffer + i);
		return next_line;
	}
	 else if(rest_buffer) {
		char *buffer = malloc(BUFFER_SIZE);
		int result = read(fd, buffer, BUFFER_SIZE);
		if (result == -1)
			return (NULL);
		i = 0;
		while(i < BUFFER_SIZE && buffer[i] != '\n') {
			i++;
		}	
		if (buffer[i] == '\n') 
			i++;

		ft_strlcat(rest_buffer, buffer, ft_strlen(rest_buffer + i));
		i = 0;
		while(rest_buffer[i] != '\n') {
			i++;
		}
		char *next_line = malloc(i + 1);
		ft_strlcpy(next_line, rest_buffer, i + 1);
		rest_buffer = ft_strdup(rest_buffer + i);
		return next_line;
	}
	

	char *buffer = malloc(BUFFER_SIZE);
	int result = read(fd, buffer, BUFFER_SIZE);
	if (result == -1)
		return (NULL);

	i = 0;
	while(i < BUFFER_SIZE && buffer[i] != '\n') {
		i++;
	}
	if (buffer[i] == '\n') 
		i++;

	rest_buffer = ft_strdup(buffer + i);

	char *next_line = malloc(i + 1);
	ft_strlcpy(next_line, buffer, i + 1);
	
	return (next_line);
}
