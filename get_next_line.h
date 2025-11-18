/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/10 15:23:21 by kvolynsk      #+#    #+#                 */
/*   Updated: 2025/11/15 15:03:47 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdbool.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*process_read(int fd, char **rest_buffer);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*line_before_character(char *str, int c);
char	*handle_no_line_buffer(char **rest_buffer, char **buffer,
			int read_result, int fd);
char	*handle_read_result0(char **rest_buffer, char **next_line,
			char **buffer);
char	*handle_buffer_new_line(char **next_line, char **buffer,
			char **rest_buffer);
void	ft_free(char **str);

#endif