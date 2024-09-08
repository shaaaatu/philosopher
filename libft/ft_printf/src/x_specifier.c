/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 00:46:38 by luebina           #+#    #+#             */
/*   Updated: 2023/10/17 10:54:35 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	print_number_base(int no_put, unsigned int nb, char *lc, t_flags *flags)
{
	char		*base;

	if (no_put)
		return ;
	if (ft_strncmp(lc, "lower", 5) == 0)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nb >= 16)
		print_number_base(no_put, nb / 16, lc, flags);
	ft_putchar_fd(base[nb % 16], 1);
}

int	put_zero_x(t_flags *flags, int nb, char *lc)
{
	if (flags->sharp == 1 && nb)
	{
		if (ft_strncmp(lc, "lower", 5) == 0)
			ft_putstr_fd("0x", 1);
		else if (ft_strncmp(lc, "upper", 5) == 0)
			ft_putstr_fd("0X", 1);
		return (2);
	}
	return (0);
}

int	num_0_count(int n, int no_put, t_flags *flags)
{
	if (n == 0 && !no_put)
	{
		flags->sharp = 0;
		return (1);
	}
	return (0);
}

int	x_specifier(unsigned int nb, t_flags *flags, char *lc)
{
	int	result_count;
	int	no_put;

	result_count = 0;
	no_put = 0;
	if (nb == 0 && flags->period && flags->precision == 0)
		no_put = 1;
	flags->count += num_0_count(nb, no_put, flags);
	flags->count += get_digit_hex(nb);
	if (flags->hyphen)
	{
		result_count += put_zero_x(flags, nb, lc)
			+ put_zero(flags, flags->count);
		print_number_base(no_put, nb, lc, flags);
		result_count += put_space(flags, flags->count);
	}
	else
	{
		result_count += put_space(flags, flags->count)
			+ put_zero_x(flags, nb, lc) + put_zero(flags, flags->count);
		print_number_base(no_put, nb, lc, flags);
	}
	return (result_count + flags->count);
}
