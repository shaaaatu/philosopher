/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luebina <luebina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:41:45 by luebina           #+#    #+#             */
/*   Updated: 2024/03/26 14:36:32 by luebina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*gnl_memmove(void *dest, const void *src, size_t n)
{
	char	*ptr;
	char	*ptr2;
	size_t	i;

	if (dest == NULL && src == NULL)
		return (dest);
	ptr = (char *)dest;
	ptr2 = (char *)src;
	i = 0;
	if (ptr2 <= ptr)
		while (n--)
			ptr[n] = ptr2[n];
	else
	{
		while (i <= n)
		{
			ptr[i] = ptr2[i];
			i++;
		}
	}
	return (dest);
}

void	*free_memory(char *line, char *buffer, char *read_buffer)
{
	if (line)
		free(line);
	if (buffer)
		free(buffer);
	if (read_buffer)
		free(read_buffer);
	return (NULL);
}

void	read_fd(int fd, char **buffer)
{
	char	*read_buffer;
	int		bytes_read;

	bytes_read = -1;
	read_buffer = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!read_buffer)
		return ;
	while (!gnl_strchr(*buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free_memory(NULL, *buffer, read_buffer);
			*buffer = NULL;
			return ;
		}
		read_buffer[bytes_read] = '\0';
		gnl_strjoin(buffer, read_buffer);
	}
	free(read_buffer);
	if ((bytes_read == 0 && gnl_strlen(*buffer) == 0))
	{
		free(*buffer);
		*buffer = NULL;
	}
}

void	*gnl_memcpy(void *dest, const void *src, size_t n)
{
	char	*ptr;
	char	*ptr2;
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	ptr = (char *)dest;
	ptr2 = (char *)src;
	i = -1;
	while (++i < n)
		ptr[i] = ptr2[i];
	ptr[i] = '\0';
	return (dest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buf[FOPEN_MAX];
	size_t		len;
	size_t		str_len;

	if (fd < 0 || FOPEN_MAX < fd)
		return (NULL);
	len = -1;
	line = NULL;
	read_fd(fd, &buf[fd]);
	if (!buf[fd] || buf[fd][0] == '\0')
		return (free_memory(line, NULL, NULL));
	str_len = gnl_strlen(buf[fd]);
	while (++len < str_len)
	{
		if (buf[fd][len] == '\n' && len++)
			break ;
	}
	line = (char *)malloc(sizeof(char) * len + 1);
	if (!line)
		return (free_memory(line, buf[fd], NULL));
	gnl_memcpy(line, buf[fd], len);
	buf[fd] = gnl_memmove(buf[fd], buf[fd] + len, gnl_strlen(buf[fd] + len));
	return (line);
}
