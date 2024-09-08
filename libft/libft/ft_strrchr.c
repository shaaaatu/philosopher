/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 06:07:28 by luebina           #+#    #+#             */
/*   Updated: 2023/09/27 08:30:19 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;
	int		j;

	str = (char *)s;
	i = 0;
	j = -1;
	while (str[i])
	{
		if (str[i] == (char)c)
			j = i;
		i++;
	}
	if (str[i] == (char)c)
		return (&str[i]);
	if (j != -1)
		return (&str[j]);
	return (NULL);
}
