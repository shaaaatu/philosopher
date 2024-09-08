/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_specifier.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiebina <luiebina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:42:16 by luebina           #+#    #+#             */
/*   Updated: 2024/02/12 21:27:02 by luiebina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

void	print_uintptr_base(uintptr_t nb, t_flags *flags)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb >= 16)
		print_uintptr_base(nb / 16, flags);
	ft_putchar_fd(base[nb % 16], 1);
}

int	p_specifier(void *ptr, t_flags *flags)
{
	uintptr_t	value;
	int			no_put;

	no_put = 0;
	value = (uintptr_t)ptr;
	if (value == 0 && flags->period && flags->precision == 0)
		no_put = 1;
	if (value == 0 && !no_put)
		flags->count += 3;
	else
		flags->count += 2;
	put_ptr(flags, value, no_put);
	return (flags->count);
}
