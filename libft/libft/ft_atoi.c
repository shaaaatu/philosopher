/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 07:07:45 by luebina           #+#    #+#             */
/*   Updated: 2024/07/10 19:16:08 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	return_long(int neg)
{
	if (neg == 1)
		return (LLONG_MAX);
	else
		return (LLONG_MIN);
}

long long	ft_atoi(const char *nptr)
{
	int			i;
	int			neg;
	long long	nb;
	long long	tmp;

	i = 0;
	neg = 1;
	nb = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while ((nptr[i] >= 48) && (nptr[i] <= 57))
	{
		tmp = nb;
		nb = nb * 10 + (nptr[i] - 48);
		if (tmp > nb)
			return (return_long(neg));
		i++;
	}
	return (nb * neg);
}
