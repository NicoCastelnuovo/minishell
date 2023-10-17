/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fahmadia <fahmadia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:48:11 by fahmadia          #+#    #+#             */
/*   Updated: 2023/05/30 15:06:23 by fahmadia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_current_line(char **remainder, int *i, int fd)
{
	char	*line;
	char	*temp;
	int		j;

	j = 0;
	while (remainder[fd][j])
		j++;
	line = ft_my_substr(remainder[fd], 0, *i + 1);
	temp = remainder[fd];
	if (j - *i - 1 == 0)
		remainder[fd] = NULL;
	else
		remainder[fd] = ft_my_substr(remainder[fd], *i + 1, j - *i - 1);
	free(temp);
	return (line);
}

static char	*get_last_line(char **remainder)
{
	char	*temp;

	temp = NULL;
	temp = ft_my_strjoin(temp, *remainder);
	free(*remainder);
	if (!temp)
		return (NULL);
	*remainder = NULL;
	return (temp);
}

static void	*support_read(char **remainder)
{
	free(*remainder);
	*remainder = NULL;
	return (NULL);
}

static char	*check_end(char *buffer, int *num, int fd, char **remainder)
{	
	int	i;

	while (1)
	{	
		i = 0;
		remainder[fd] = ft_my_strjoin(remainder[fd], buffer);
		if (!(remainder[fd]))
			return (NULL);
		while (remainder[fd][i])
		{
			if (remainder[fd][i] == '\n')
				return (get_current_line(remainder, &i, fd));
			i++;
		}
		if (!*num)
			return (get_last_line(&(remainder[fd])));
		i = 0;
		while (buffer[i])
			buffer[i++] = '\0';
		*num = read(fd, buffer, BUFFER_SIZE);
		if (*num < 0 || BUFFER_SIZE <= 0 || fd < 0)
			support_read(&(remainder[fd]));
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	int			num;
	char		*current_line;
	static char	*remainder[FD_NUM];
	int			i;

	i = 0;
	buffer = calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	num = read(fd, buffer, BUFFER_SIZE);
	if ((num < 0 || BUFFER_SIZE <= 0 || fd < 0) || (!num && !remainder[fd]))
	{
		if (remainder[fd])
		{
			free(remainder[fd]);
			remainder[fd] = NULL;
		}
		free (buffer);
		return (NULL);
	}
	current_line = check_end(buffer, &num, fd, remainder);
	return (free(buffer), current_line);
}
