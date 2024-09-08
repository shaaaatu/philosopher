/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 06:19:04 by luebina           #+#    #+#             */
/*   Updated: 2023/10/16 22:45:49 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	c_specifier(char c, int fd, t_flags *flags)
{
	int	count;

	count = 1;
	if (flags->hyphen)
	{
		write(fd, &c, 1);
		count += put_space(flags, count);
	}
	else
	{
		count += put_space(flags, count);
		write(fd, &c, 1);
	}
	return (count);
}
