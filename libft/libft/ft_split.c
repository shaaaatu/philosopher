/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 02:38:19 by luebina           #+#    #+#             */
/*   Updated: 2024/03/26 14:33:00 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

int	word_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i + 1])
	{
		if (!is_sep(s[i], c) && (is_sep(s[i + 1], c) || !s[i + 1]))
			count++;
		i++;
	}
	return (count + 1);
}

char	**asign_word(char **ptr, char const *s, char c, int word)
{
	int	i;
	int	j;
	int	k;
	int	len;

	i = 0;
	k = 0;
	len = 0;
	while (k < word)
	{
		while (is_sep(s[i], c))
			i++;
		j = i;
		while (!is_sep(s[i], c) && s[i++])
			len++;
		ptr[k] = ft_substr(s, j, len);
		if (ptr[k] == NULL)
			return (NULL);
		len = 0;
		k++;
	}
	ptr[word] = NULL;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		word;
	int		k;

	k = 0;
	if (!s)
		return (NULL);
	word = word_count(s, c);
	ptr = (char **)malloc(sizeof(char *) * (word + 1));
	if (ptr == NULL)
		return (NULL);
	ptr = asign_word(ptr, s, c, word);
	if (ptr == NULL)
	{
		while (ptr[k])
			free(ptr[k++]);
		free(ptr);
		return (NULL);
	}
	return (ptr);
}
