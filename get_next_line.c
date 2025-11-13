/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/10 15:54:20 by kvolynsk      #+#    #+#                 */
/*   Updated: 2025/11/13 17:30:03 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include "stdio.h"
#include <stdbool.h>

char	*get_next_line(int fd)
{
	if(!fd || BUFFER_SIZE < 0)
		return NULL;

	static char *rest_buffer;
	char *buffer;
	char *next_line;
	
	
	bool is_next_line_rb = is_string_contain_character(rest_buffer, '\n');
	if(is_next_line_rb) {
		next_line = line_before_character(rest_buffer, '\n');
		rest_buffer = ft_strchr(rest_buffer, '\n');
		return next_line;
	}

	buffer = malloc(BUFFER_SIZE);
	if (!buffer) 
		return NULL;
	
	int read_result = read(fd, buffer, BUFFER_SIZE);
	
	if(read_result < 0) {
		free(buffer);
		return NULL;
	}

	if(read_result == 0) {
		next_line = ft_strjoin(rest_buffer, "\n");
		free(buffer);
		free(rest_buffer);
		return next_line;
	}

	bool is_next_line_in_buffer = is_string_contain_character(buffer, '\n');
	if (!is_next_line_in_buffer) {
		rest_buffer = ft_strdup(buffer);
		free(buffer);
		return NULL;
	}

	next_line = line_before_character(buffer, '\n');
	
	if(!rest_buffer) {
		rest_buffer = ft_strchr(buffer, '\n');
		return next_line;
	}

	next_line = ft_strjoin(rest_buffer, next_line);
	rest_buffer = ft_strchr(buffer, '\n');
	return next_line;
}
/**
 * @brief returns string before character included character
 * 
 * @param str 
 * @param c 
 * @return char* 
 * @warning dont forget to free
 */
char *line_before_character(char *str, int c) {
	int	i;

	if(!str)
		return NULL;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
		{
			char *result = malloc(i + 2);
			if(!result)
				return NULL;
			ft_strlcpy(result, str, i + 2);
			return result;
		}
		i++;
	}
	if (str[i] == (char)c)
		return (str);
	return (NULL);
}

bool is_string_contain_character(char *str, int c) {
	int i = 0;

	if(!str)
		return NULL;

	while(str[i]) {
		if (str[i] == (char)c)
			return true;
		i++;
	}
	if (str[i] == (char)c)
		return (true);
	return false;
}

