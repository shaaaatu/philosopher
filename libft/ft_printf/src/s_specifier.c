/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 06:22:15 by luebina           #+#    #+#             */
/*   Updated: 2024/02/25 20:24:48 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	str_null(t_flags *flags)
{
	int	len;
	int	count;

	len = 6;
	count = 0;
	if (len > flags->precision && flags->period == 1)
		len = flags->precision;
	if (flags->hyphen)
	{
		write(1, "(null)", len);
		count += put_space(flags, len);
	}
	else
	{
		count += put_space(flags, len);
		write(1, "(null)", len);
	}
	count += len;
	return (count);
}

int	s_specifier(char *s, int fd, t_flags *flags)
{
	int	len;

	len = 0;
	if (!s)
		return (str_null(flags));
	len = (int)ft_strlen(s);
	if (len > flags->precision && flags->period == 1)
		len = flags->precision;
	put_str(flags, fd, s, len);
	return (flags->count + len);
}
