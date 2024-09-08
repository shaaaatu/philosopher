/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:10:21 by luebina           #+#    #+#             */
/*   Updated: 2023/10/18 16:24:44 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_digit_hex(unsigned int nb)
{
	int	count;

	count = 0;
	while (nb != 0)
	{
		nb /= 16;
		count++;
	}
	return (count);
}

int	get_digit(int nb)
{
	int	count;

	count = 0;
	while (nb != 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

int	get_uintptr_digit(uintptr_t nb)
{
	int	count;

	count = 0;
	while (nb != 0)
	{
		nb /= 16;
		count++;
	}
	return (count);
}

int	get_u_digit(unsigned int nb)
{
	int	count;

	count = 0;
	while (nb != 0)
	{
		nb /= 10;
		count++;
	}
	return (count);
}
