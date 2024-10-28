#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void  ft_print(char *buf)
{
  int j;
  
  j = 0;
  while(buf[j])
  {
    write(1, &buf[j], 1);
    j++;
  }
}
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
int ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (i + 1);
		i++;
	}
	return (0);
}
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
char  *ft_stoker(char *buf, int len, char *line)
{
  int i;
  int j;
  
  i = 0;
  j = 0;
  while (line[i])
    i++;
  while (j < len && buf[j])
  {
    line[i + j] = buf[j];
    j++;
  }
  line[i + j] = '\0';
  return (line);
}
char  *get_next_line(int fd)
{
  char buf[BUFFER_SIZE];
  char *line;
  static char res[BUFFER_SIZE];
  int  len;
  int         bytesread;
  
  //printf("res = [%s]", res);
  //printf("buf = [%s]", buf);
  line = malloc(sizeof(char) * 1024);
  if (line == 0)
    return (0);
  ft_memset(line, 0, BUFFER_SIZE + 1);
  if (ft_strlen(res) > 0)
  {
    len = ft_strchr(res, '\n');
     //printf("res = [%d]", len);
    if (len > 0)
    {
        line = ft_stoker(res, len, line);
        //ft_stoker(&res[len] + 1, ft_strlen(&res[len] - 1), res);
        bytesread = 0;
        while (res[len + bytesread] != '\n' && res[len + bytesread] != '\0')
        {
          res[bytesread] = res[len + bytesread];
          bytesread++;
        }
        res[bytesread] = '\n';
        //printf("res = [%s]", res);
        ft_print(line);
        return (line);
    } 
    else 
    {
        ft_stoker(res, ft_strlen(res), line);
    }
  }
 while ((bytesread = read(fd, buf, BUFFER_SIZE)) > 0) {
        if (bytesread == -1)
        {
          free(line);
          return (0);
        }
        //buf[bytesread] = '\0'; // Null-terminate le buffer
        len = ft_strchr(buf, '\n');
        if (len > 0) {
            ft_stoker(buf, len, line);
            ft_memset(res, 0, BUFFER_SIZE);
            ft_stoker(&buf[len], bytesread - len, res);
            ft_print(line);
            return (line);
        } else {
            ft_stoker(buf, bytesread, line);
        }
    }

    if (ft_strlen(line) > 0)
    {
        ft_print(line);
        return (line);
    }
    return (NULL);
}
