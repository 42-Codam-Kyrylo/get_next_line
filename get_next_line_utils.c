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

void	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

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
	size_t	duplicate_len;

	duplicate_len = 0;
	if (!s)
		return (NULL);
	while (s[duplicate_len])
		duplicate_len++;
	duplicate_len += 1;
	duplicate = (char *)malloc(duplicate_len * sizeof(char));
	if (duplicate == NULL)
		return (NULL);
	ft_strlcpy(duplicate, s, duplicate_len);
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
