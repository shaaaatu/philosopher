/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 04:24:05 by luebina           #+#    #+#             */
/*   Updated: 2023/10/18 16:24:58 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

typedef struct s_flags
{
	int	sharp;
	int	zero;
	int	num;
	int	hyphen;
	int	space;
	int	period;
	int	period_num;
	int	plus;
	int	width;
	int	precision;
	int	count;
}	t_flags;

int		ft_printf(const char *format, ...);
int		x_specifier(unsigned int nb, t_flags *flags, char *lc);
int		c_specifier(char c, int fd, t_flags *flags);
int		d_specifier(int n, t_flags *flags);
int		p_specifier(void *ptr, t_flags *flags);
int		s_specifier(char *s, int fd, t_flags *flags);
int		u_specifier(unsigned int n, t_flags *flags);
int		my_atoi(const char *nptr);
int		get_width(const char *format, t_flags *flags);
int		put_space(t_flags *flags, int count);
int		put_zero(t_flags *flags, int count);
int		return_long(int neg);
int		get_precision(const char *format, t_flags *flags);
void	init_structure(t_flags *flags);
int		put_str_space(t_flags *flags, int count);
int		get_digit_hex(unsigned int nb);
int		get_digit(int nb);
int		get_uintptr_digit(uintptr_t nb);
int		get_u_digit(unsigned int nb);
int		put_dicimal(t_flags *flags, int num, int no_put, int is_minus);
int		put_unbr(t_flags *flags, int no_put, int n);
void	put_ptr(t_flags *flags, uintptr_t nb, int no_put);
void	put_str(t_flags *flags, int fd, char *s, int len);
void	ft_putunsignednbr_fd(unsigned int nb, int fd);
void	print_uintptr_base(uintptr_t nb, t_flags *flags);

#endif
