/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:17:13 by luebina           #+#    #+#             */
/*   Updated: 2023/10/16 18:18:26 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	get_width(const char *format, t_flags *flags)
{
	int	num;
	int	count;

	count = 0;
	num = my_atoi(format);
	flags->width = num;
	while (num > 0)
	{
		num /= 10;
		count++;
	}
	return (count);
}

int	put_str_space(t_flags *flags, int count)
{
	int	space_count;
	int	i;

	i = 0;
	space_count = flags->width - count;
	while (space_count > i)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (space_count < 0)
		space_count = 0;
	return (space_count);
}

int	put_space(t_flags *flags, int count)
{
	int	space_count;
	int	precision;
	int	i;

	i = 0;
	precision = flags->precision;
	if (precision < count)
		precision = count;
	if (flags->sharp)
		precision += 2;
	if (flags->plus)
		precision += 1;
	space_count = flags->width - precision;
	while (space_count > i && !(flags->zero && !flags->period))
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (space_count < 0 || (flags->zero && !flags->period))
		space_count = 0;
	return (space_count);
}

int	put_zero(t_flags *flags, int count)
{
	int	zero_count;
	int	i;

	zero_count = 0;
	i = 0;
	if (flags->period)
		zero_count = flags->precision - count;
	else if (flags->zero)
		zero_count = flags->width - count;
	while (zero_count > i && (flags->zero || flags->precision))
	{
		ft_putchar_fd('0', 1);
		i++;
	}
	if (zero_count < 0)
		zero_count = 0;
	return (zero_count);
}

int	get_precision(const char *format, t_flags *flags)
{
	int	num;
	int	count;

	count = 0;
	num = my_atoi(&format[1]);
	flags->period = 1;
	flags->precision = num;
	if (format[1] < '0' || format[1] > '9')
		return (1);
	if (num == 0)
		count++;
	while (format[count + 1] >= '0' && format[count + 1] <= '9')
		count++;
	count++;
	return (count);
}
