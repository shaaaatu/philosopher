/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:19:12 by luebina           #+#    #+#             */
/*   Updated: 2024/03/26 14:49:02 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

size_t	gnl_strlcpy(char *dest, const char *src, size_t size);
size_t	gnl_strlen(const char *str);
void	gnl_strjoin(char **s1, char const *s2);
char	*gnl_strchr(const char *s, int c);
size_t	gnl_strlcat(char *dest, const char *src, size_t size);
char	*get_next_line(int fd);
void	*gnl_memmove(void *dest, const void *src, size_t n);

#endif