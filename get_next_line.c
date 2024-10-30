/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:03:58 by amblanch          #+#    #+#             */
/*   Updated: 2024/10/29 13:04:02 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_memset(char *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		s[i] = c;
		i++;
	}
	return (s);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (dst == 0 || src == 0)
		return (0);
	if (size)
	{
		while (*src && i < size)
		{
			*dst++ = *src++;
			i++;
		}
		*dst = '\0';
	}
	return (ft_strlen(src) + i);
}

char	*ft_res(char *line, char *buf, int bytesread, int i)
{
	static char	res[BUFFER_SIZE];
	int			len;

	while (ft_strlen(res) > 0)
	{
		len = ft_strchr(res, '\n');
		if (len > 0)
		{
			line = ft_strjoin(line, res, len);
			ft_strlcpy(res, &res[len], BUFFER_SIZE - len);
			free(buf);
			return (line);
		}
		else
		{
			line = ft_strjoin(line, res, BUFFER_SIZE);
			ft_memset(res, 0, BUFFER_SIZE);
		}
	}
	if (bytesread > 0)
		ft_strlcpy(res, &buf[i], bytesread);
	return (line);
}

char	*ft_line(char *buf, char *line, int fd)
{
	int	bytesread;
	int	len;

	bytesread = read(fd, buf, BUFFER_SIZE);
	while (bytesread > 0)
	{
		buf[bytesread] = '\0';
		len = ft_strchr(buf, '\n');
		if (len >= 0)
		{
			line = ft_strjoin(line, buf, len);
			ft_res(line, buf, BUFFER_SIZE - len, len);
			free(buf);
			return (line);
		}
		else
			line = ft_strjoin(line, buf, BUFFER_SIZE);
		bytesread = read(fd, buf, BUFFER_SIZE);
	}
	if (bytesread == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;

	if (fd == -1)
		return (0);
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	line = ft_calloc(BUFFER_SIZE, sizeof(char));
	line = ft_memset(line, 0, BUFFER_SIZE);
	if (line == 0)
		return (0);
	line = ft_res(line, buf, 0, 0);
	if (ft_strchr(line, '\n') > 0)
		return (line);
	line = ft_line(buf, line, fd);
	if (ft_strchr(line, '\n') > 0)
		return (line);
	free(buf);
	if (ft_strlen(line) > 0)
		return (line);
	free(line);
	return (NULL);
}
