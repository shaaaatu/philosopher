/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 02:56:52 by luebina           #+#    #+#             */
/*   Updated: 2023/09/29 20:45:41 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*ptr;
	char	*ptr2;
	size_t	i;

	if (dest == NULL && src == NULL)
		return (dest);
	ptr = (char *)dest;
	ptr2 = (char *)src;
	i = 0;
	if (ptr2 < ptr)
		while (n--)
			ptr[n] = ptr2[n];
	else
	{
		while (i < n)
		{
			ptr[i] = ptr2[i];
			i++;
		}
	}
	return (dest);
}
