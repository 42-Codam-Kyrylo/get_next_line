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
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	src_len = 0;
	dst_len = 0;
	while (src[src_len])
		src_len++;
	while (dst[dst_len])
		dst_len++;
	if (size == 0)
		return (src_len);
	if (dst_len >= size)
		return (size + src_len);
	i = 0;
	while (src[i] && i < size - dst_len - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
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
	size_t	str1_len;
	size_t	str2_len;
	char	*result;

	str1_len = 0;
	str2_len = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[str1_len])
		str1_len++;
	while (s2[str2_len])
		str2_len++;
	result = (char *)malloc((str1_len + str2_len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	ft_strlcpy(result, s1, (str1_len + str2_len + 1));
	ft_strlcat(result, s2, (str1_len + str2_len + 1));
	return (result);
}