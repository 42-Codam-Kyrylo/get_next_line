/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: kvolynsk <kvolynsk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/11/10 15:54:12 by kvolynsk      #+#    #+#                 */
/*   Updated: 2025/11/13 17:50:51 by kvolynsk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

/**
 * @brief
 *
 * @param s
 * @return char*
 * @warning FREE
 */
char	*ft_strdup(const char *s)
{
	char	*duplicate;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	duplicate = (char *)malloc((i + 1) * sizeof(char));
	if (!duplicate)
		return (NULL);
	i = 0;
	while (s[i])
	{
		duplicate[i] = s[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

/**
 * @brief returns string after c NOT INCLUDED C
 *
 * @param s
 * @param c
 * @return char*
 */
char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			return ((char *)(s + i + 1));
		}
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

/**
 * @brief
 *
 * @param s1
 * @param s2
 * @return char*
 * @warning FREE
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	result = (char *)malloc((i + j + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = -1;
	while (s2[++j])
		result[i + j] = s2[j];
	result[i + j] = '\0';
	return (result);
}

/**
 * @brief returns string before character included character
 *
 * @param str
 * @param c
 * @return char*
 * @warning dont forget to free
 */
char	*line_before_character(char *str, int c)
{
	int		i;
	int		j;
	char	*result;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != (char)c)
		i++;
	if (str[i] != (char)c)
		return (NULL);
	result = malloc(i + 2);
	if (!result)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		result[j] = str[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

void	ft_free(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}
