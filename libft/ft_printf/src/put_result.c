/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_result.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:24:00 by luebina           #+#    #+#             */
/*   Updated: 2023/10/18 16:28:02 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	put_minus_plus(int is_minus, int is_plus)
{
	if (is_minus)
		ft_putchar_fd('-', 1);
	else if (is_plus)
		ft_putchar_fd('+', 1);
}

int	put_dicimal(t_flags *flags, int num, int no_put, int is_minus)
{
	int	result;

	result = 0;
	if (flags->hyphen)
	{
		put_minus_plus(is_minus, flags->plus);
		result += put_zero(flags, flags->count);
		if (!no_put)
			ft_putnbr_fd(num, 1);
		result += put_space(flags, flags->count);
	}
	else
	{
		result += put_space(flags, flags->count);
		put_minus_plus(is_minus, flags->plus);
		result += put_zero(flags, flags->count);
		if (!no_put)
			ft_putnbr_fd(num, 1);
	}
	return (result);
}

int	put_unbr(t_flags *flags, int no_put, int n)
{
	int	result;

	result = 0;
	if (flags->hyphen)
	{
		result += put_zero(flags, flags->count);
		if (!no_put)
			ft_putunsignednbr_fd(n, 1);
		result += put_space(flags, flags->count);
	}
	else
	{
		result += put_space(flags, flags->count);
		result += put_zero(flags, flags->count);
		if (!no_put)
			ft_putunsignednbr_fd(n, 1);
	}
	return (result);
}

void	put_ptr(t_flags *flags, uintptr_t nb, int no_put)
{
	if (flags->hyphen)
	{
		write(1, "0x", 2);
		if (!no_put)
			print_uintptr_base(nb, flags);
		flags->count += get_uintptr_digit(nb);
		flags->count += put_space(flags, flags->count);
	}
	else
	{
		flags->count += get_uintptr_digit(nb);
		flags->count += put_space(flags, flags->count);
		write(1, "0x", 2);
		if (!no_put)
			print_uintptr_base(nb, flags);
	}
}

void	put_str(t_flags *flags, int fd, char *s, int len)
{
	if (flags->hyphen)
	{
		write(fd, s, len);
		flags->count += put_str_space(flags, len);
	}
	else
	{
		flags->count += put_str_space(flags, len);
		write(fd, s, len);
	}
}
