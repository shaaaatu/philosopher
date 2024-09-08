/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 06:33:12 by luebina           #+#    #+#             */
/*   Updated: 2023/09/29 22:02:03 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void	*ptr;
	size_t	i;

	i = 0;
	if (number == 0 || size == 0)
		return (malloc(0));
	if ((size_t)SIZE_MAX / number < size)
		return (NULL);
	ptr = malloc(number * size);
	if (ptr == NULL)
		return (NULL);
	while (i < number * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
