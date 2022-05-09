/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcesar-d <mcesar-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 02:11:57 by mcesar-d          #+#    #+#             */
/*   Updated: 2022/05/08 15:58:31 by mcesar-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	read_fd(int fd, char *buffer, char **str)
{
	int		b_read;
	char	*tmp;

	if (!*str || !ft_strchr(*str, '\n'))
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		while (b_read > 0)
		{
			buffer[b_read] = 0;
			if (!*str)
				*str = ft_substr(buffer, 0, b_read);
			else
			{
				tmp = *str;
				*str = ft_strjoin(*str, buffer);
				free(tmp);
			}
			if (ft_strchr(buffer, '\n'))
				break ;
			b_read = read(fd, buffer, BUFFER_SIZE);
		}
	}
	free(buffer);
}

static char	*get_line(char **str)
{
	char	*line;
	char	*tmp;
	int		overs;

	if (!*str)
		return (0);
	if (!ft_strchr(*str, '\n'))
	{
		line = ft_substr(*str, 0, ft_strlen(*str));
		free(*str);
		*str = 0;
		if (!*line)
		{
			free(line);
			return (NULL);
		}
		return (line);
	}
	overs = ft_strlen(ft_strchr(*str, '\n'));
	line = ft_substr(*str, 0, ft_strlen(*str) - overs + 1);
	tmp = *str;
	*str = ft_substr(ft_strchr(*str, '\n'), 1, overs - 1);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*line[255];

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	if (BUFFER_SIZE < 1 || fd == -1 || read(fd, buffer, 0) == -1)
	{
		free(buffer);
		return (0);
	}
	read_fd(fd, buffer, &line[fd]);
	return (get_line(&line[fd]));
}
