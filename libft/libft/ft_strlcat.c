/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 05:18:58 by luebina           #+#    #+#             */
/*   Updated: 2023/09/29 20:36:34 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size <= 0)
		return (ft_strlen(src));
	if (size < ft_strlen(dest))
		return (ft_strlen(src) + size);
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
