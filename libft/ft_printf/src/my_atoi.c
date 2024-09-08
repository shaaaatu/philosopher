/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 07:07:45 by luebina           #+#    #+#             */
/*   Updated: 2023/10/16 18:41:58 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	my_atoi(const char *nptr)
{
	int		i;
	long	nb;
	int		neg;

	i = 0;
	neg = 1;
	nb = 0;
	while (nptr[i] == '#')
		i++;
	while ((nptr[i] >= 48) && (nptr[i] <= 57))
	{
		nb = nb * 10 + (nptr[i] - 48);
		if (nb < 0 || (i > 0 && nb == 0))
			return (return_long(neg));
		i++;
	}
	return ((int)nb);
}
