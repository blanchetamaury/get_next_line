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

#include "get_next_line_bonus.h"
#include <stdio.h>

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

char	*ft_res(char *line, char **buf, int fd)
{
	int			len;

	while (ft_strlen(buf[fd]) > 0)
	{
		len = ft_strchr(buf[fd], '\n');
		if (len > 0)
		{
			line = ft_strjoin(line, buf[fd], len);
			ft_strlcpy(buf[fd], &buf[fd][len], BUFFER_SIZE - len + 1);
			return (line);
		}
		else
		{
			line = ft_strjoin(line, buf[fd], BUFFER_SIZE);
			ft_memset(buf[fd], 0, BUFFER_SIZE);
		}
	}
	return (line);
}

char	*ft_line(char **buf, char *line, int fd)
{
	int	bytesread;
	int	len;

	bytesread = read(fd, buf[fd], BUFFER_SIZE);
	while (bytesread > 0)
	{
		buf[fd][bytesread] = '\0';
		len = ft_strchr(buf[fd], '\n');
		if (len >= 0)
		{
			line = ft_strjoin(line, buf[fd], len);
			ft_strlcpy(buf[fd], &buf[fd][len], BUFFER_SIZE - len + 1);
			return (line);
		}
		else
			line = ft_strjoin(line, buf[fd], BUFFER_SIZE);
		bytesread = read(fd, buf[fd], BUFFER_SIZE);
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
	static char		*buf[1024];
	char		*line;

    if (fd < 0 || fd >= 1024)
	    return (NULL);
    if (!buf[fd])
    {
	    buf[fd] = malloc( sizeof(char) * (BUFFER_SIZE + 1));
	    if (!buf[fd])
                return (NULL);
	    buf[fd] = ft_memset(buf[fd], 0, BUFFER_SIZE + 1);
    }
    line = ft_calloc(1, sizeof(char));
     if (line == 0)
	return (NULL);
    line = ft_res(line, buf, fd);
    //printf("[%s]", buf[fd]);
    if (ft_strchr(line, '\n') >= 0)
    {
	return (line);
    }
    line = ft_line(buf, line, fd);
    //printf("[%s]", buf[fd]);
    if (ft_strchr(line, '\n') >= 0 || ft_strlen(line) > 0)
    {
	return (line);
    }
    free(line);
    return (NULL);
}
/*int	main(void)
{
  	int	fd;
    //int	fd1;
    char *str;
    //char *str1;

    fd = open("test", O_RDONLY);
    //fd1 = open("test1", O_RDONLY);
    str = get_next_line(fd);
    printf("[%s]", str);
    free(str);
    str = get_next_line(fd);
    printf("[%s]", str);
    free(str);
    str = get_next_line(fd);
    printf("[%s]", str);
    free(str);
    close(fd);
   // close(fd1);
    return (0);
}*/
