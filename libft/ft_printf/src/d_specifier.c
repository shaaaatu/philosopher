/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 06:26:52 by luebina           #+#    #+#             */
/*   Updated: 2024/02/25 20:24:43 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	put_int_min(t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->hyphen)
	{
		ft_putchar_fd('-', 1);
		count += put_zero(flags, 11);
		ft_putstr_fd("2147483648", 1);
		count += put_space(flags, 11);
	}
	else
	{
		count += put_space(flags, 11);
		ft_putchar_fd('-', 1);
		count += put_zero(flags, 11);
		ft_putstr_fd("2147483648", 1);
	}
	count += 11;
	return (count);
}

void	minus_nb(t_flags *flags, int *is_minus, int *num)
{
	if (*num < 0)
	{
		flags->space = 0;
		flags->plus = 0;
		if (flags->zero || flags->period)
		{
			if (flags->period)
				flags->precision++;
			*is_minus = 1;
			*num *= -1;
		}
		flags->count++;
	}
}

int	d_specifier(int n, t_flags *flags)
{
	int	result;
	int	no_put;
	int	is_minus;

	result = 0;
	no_put = 0;
	is_minus = 0;
	if (n == 0 && flags->period && flags->precision == 0)
		no_put = 1;
	minus_nb(flags, &is_minus, &n);
	if (n == -2147483648 && (flags->period || flags->zero))
		return (put_int_min(flags));
	if (flags->plus)
		result++;
	if (flags->space)
	{
		write(1, " ", 1);
		result++;
		flags->width--;
	}
	if (n == 0 && !no_put)
		flags->count++;
	flags->count += get_digit(n);
	return (result + put_dicimal(flags, n, no_put, is_minus) + flags->count);
}

// if (n < 0)
// 	{
// 		flags->space = 0;
// 		flags->plus = 0;
// 		if (flags->zero || flags->period)
// 		{
// 			if (flags->period)
// 				flags->precision++;
// 			is_minus = 1;
// 			num *= -1;
// 		}
// 		count++;
// 	}