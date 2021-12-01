/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moseddik <moseddik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:19:53 by moseddik          #+#    #+#             */
/*   Updated: 2021/12/01 05:02:08 by moseddik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*save(char *str)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free (str);
		return (NULL);
	}
	ptr = malloc(sizeof(char) * ft_strlen(str) - i);
	i++;
	j = 0;
	while (str[i])
		ptr[j++] = str[i++];
	ptr[j] = '\0';
	free (str);
	return (ptr);
}

int	ft_error(ssize_t byt_to_read, char *buff, char *ptr)
{
	if (byt_to_read < 0)
	{
		free(buff);
		if (ptr != NULL)
			free(ptr);
		return (1);
	}
	else if (byt_to_read == 0 && !ptr)
	{
		free(buff);
		return (1);
	}
	else if (ptr[0] == '\0')
	{
		free(ptr);
		free(buff);
		return (1);
	}
	free (buff);
	return (0);
}

char	*read_caracters(int fd, char *str)
{
	char	*buff;
	char	*temp;
	ssize_t	byt_to_read;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	byt_to_read = read(fd, buff, BUFFER_SIZE);
	while (byt_to_read > 0)
	{
		buff[byt_to_read] = '\0';
		if (!str)
			str = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(str, buff);
			free (str);
			str = temp;
		}
		if (ft_strchr(str, '\n'))
			break ;
		byt_to_read = read(fd, buff, BUFFER_SIZE);
	}
	if (ft_error(byt_to_read, buff, str))
		return (0);
	return (str);
}

char	*remplis_line(char *str)
{
	int		len;
	char	*line;

	len = 0;
	while (str[len] != '\n' && str[len])
		len++;
	if (str[len] == '\n')
		line = ft_substr(str, 0, len + 1);
	else
		line = ft_substr(str, 0, len);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*ptr;
	char		*line;

	ptr = read_caracters(fd, ptr);
	if (!ptr)
		return (NULL);
	line = remplis_line(ptr);
	ptr = save(ptr);
	return (line);
}
