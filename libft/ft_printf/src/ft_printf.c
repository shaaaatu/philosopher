/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 03:26:19 by luebina           #+#    #+#             */
/*   Updated: 2024/02/25 20:24:45 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_count(char c, va_list args, t_flags *flags)
{
	int	count;

	count = 0;
	if (c == 'd' || c == 'i')
		count += d_specifier(va_arg(args, int), flags);
	else if (c == 'u')
		count += u_specifier(va_arg(args, unsigned int), flags);
	else if (c == 's')
		count += s_specifier(va_arg(args, char *), 1, flags);
	else if (c == 'c')
		count += c_specifier(va_arg(args, int), 1, flags);
	else if (c == 'x')
		count += x_specifier(va_arg(args, int), flags, "lower");
	else if (c == 'X')
		count += x_specifier(va_arg(args, int), flags, "upper");
	else if (c == 'p')
		count += p_specifier(va_arg(args, void *), flags);
	else
	{
		count += write(1, "%", 1);
		if (c != '%')
			count += write(1, &c, 1);
	}
	return (count);
}

int	check_flag(const char *format, t_flags *flags)
{
	int	count;

	count = 1;
	if (*format == '#')
		flags->sharp = 1;
	else if (*format == '0')
	{
		if (!flags->hyphen)
			flags->zero = 1;
	}
	else if (*format >= '1' && *format <= '9')
		count = get_width(format, flags);
	else if (*format == '-')
	{
		flags->hyphen = 1;
		flags->zero = 0;
	}
	else if (*format == ' ')
		flags->space = 1;
	else if (*format == '.')
		count = get_precision(format, flags);
	else if (*format == '+')
		flags->plus = 1;
	return (count);
}

int	is_flag(char c)
{
	if (c == '#' || c == '0' || (c >= '1' && c <= '9')
		|| c == '-' || c == ' ' || c == '.' || c == '+')
		return (1);
	return (0);
}

void	init_structure(t_flags *flags)
{
	flags->num = 0;
	flags->hyphen = 0;
	flags->sharp = 0;
	flags->zero = 0;
	flags->space = 0;
	flags->period = 0;
	flags->period_num = 0;
	flags->plus = 0;
	flags->width = 0;
	flags->precision = 0;
	flags->count = 0;
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	t_flags	flags;
	int		i;

	count = 0;
	i = 0;
	init_structure(&flags);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			while (is_flag(format[i]))
				i += check_flag(&format[i], &flags);
			count += put_count(format[i], args, &flags);
			init_structure(&flags);
		}
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
