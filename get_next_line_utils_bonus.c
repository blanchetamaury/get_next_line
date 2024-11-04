/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amblanch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:05:53 by amblanch          #+#    #+#             */
/*   Updated: 2024/10/29 13:05:54 by amblanch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (s == 0)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_invalid(char *line, int bytesread)
{
	if (bytesread == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

void	free_buffer(char **buf, int fd)
{
	if (buf[fd])
	{
		free(buf[fd]);
		buf[fd] = NULL;
	}
}

int	ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (s == 0)
		return (-1);
	while (s[i] != '\0' && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return (i + 1);
	return (-1);
}

char	*ft_strjoin(char *str, char *src, int len)
{
	int		i;
	int		j;
	char	*new;

	if (!src)
		return (str);
	new = malloc(sizeof(char) * (ft_strlen(str) + len + 1));
	if (new == 0)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	while (src[j] && j < len)
	{
		new[i + j] = src[j];
		j++;
	}
	new[i + j] = '\0';
	free(str);
	return (new);
}
