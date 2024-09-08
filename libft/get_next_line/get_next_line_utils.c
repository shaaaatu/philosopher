/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 01:35:31 by luebina           #+#    #+#             */
/*   Updated: 2024/02/12 15:21:06 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	gnl_strjoin(char **s1, char const *s2)
{
	char	*ptr;

	if (!*s1)
	{
		*s1 = (char *)malloc(sizeof(char) * 1);
		if (!*s1)
			return ;
		*s1[0] = '\0';
	}
	if (!s2)
	{
		free(*s1);
		return ;
	}
	ptr = (char *)malloc(sizeof(char) * (gnl_strlen(*s1) + gnl_strlen(s2) + 1));
	if (ptr == NULL)
	{
		free(*s1);
		*s1 = NULL;
		return ;
	}
	gnl_strlcpy(ptr, *s1, gnl_strlen(*s1) + 1);
	gnl_strlcat(ptr, s2, gnl_strlen(*s1) + gnl_strlen(s2) + 1);
	free(*s1);
	*s1 = ptr;
}

char	*gnl_strchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	if (str[i] == (char)c)
		return (&str[i]);
	return (NULL);
}

size_t	gnl_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size <= 0)
		return (gnl_strlen(src));
	if (size < gnl_strlen(dest))
		return (gnl_strlen(src) + size);
	while (dest[i] && i < size)
		i++;
	while (src[j] && j < (size - i - 1) && size - i != 0)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < size)
		dest[i + j] = 0;
	while (src[j])
		j++;
	return (i + j);
}
