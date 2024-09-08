/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:31:19 by luebina           #+#    #+#             */
/*   Updated: 2024/07/13 17:54:09 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	ft_putunsignednbr_fd(unsigned int nb, int fd)
{
	if (nb <= 9)
		ft_putchar_fd(nb + '0', fd);
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putchar_fd((nb % 10) + '0', fd);
	}
}

int	u_specifier(unsigned int n, t_flags *flags)
{
	int	result_count;
	int	no_put;

	result_count = 0;
	no_put = 0;
	if (n == 0 && flags->period && flags->precision == 0)
		no_put = 1;
	if (n == 0 && !no_put)
		flags->count++;
	if (flags->space)
	{
		write(1, " ", 1);
		flags->count++;
	}
	flags->count += get_u_digit(n);
	return (result_count + put_unbr(flags, no_put, n) + flags->count);
}
