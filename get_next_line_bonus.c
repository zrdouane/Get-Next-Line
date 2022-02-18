/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zrdouane <zrdouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 17:12:06 by zrdouane          #+#    #+#             */
/*   Updated: 2022/01/09 01:34:32 by zrdouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *buffers)
{
	char	calcul[BUFFER_SIZE + 1];
	int		byte;

	byte = 1;
	while (!ft_strchr(buffers, '\n') && byte)
	{
		byte = read(fd, calcul, BUFFER_SIZE);
		if (byte == -1)
			return (0);
		calcul[byte] = '\0';
		buffers = ft_strjoin(buffers, calcul);
	}
	return (buffers);
}

char	*ft_readline(char *buffers)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!buffers[i])
		return (0);
	while (buffers[i] != '\n' && buffers[i] != '\0')
		i++;
	if (buffers[i] == '\n')
		i++;
	tmp = (char *)malloc(sizeof(char) * i + 1);
	if (!tmp)
		return (0);
	i = 0;
	while (buffers[i] != '\n' && buffers[i] != '\0')
	{
		tmp[i] = buffers[i];
		i++;
	}
	if (buffers[i] == '\n')
		tmp[i++] = '\n';
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_rest(char *buffers)
{
	int		i;
	char	*rmn;
	int		len;
	int		j;

	i = 0;
	j = 0;
	while (buffers[i] != '\n' && buffers[i])
		i++;
	if (!buffers[i])
	{
		free(buffers);
		return (0);
	}
	len = ft_strlen(buffers) - i;
	rmn = (char *)malloc(sizeof(char) * len + 1);
	if (!rmn)
		return (0);
	i++;
	while (buffers[i])
		rmn[j++] = buffers[i++];
	rmn[j] = '\0';
	free(buffers);
	return (rmn);
}

char	*get_next_line(int fd)
{
	static char	*buffers[10240];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	buffers[fd] = ft_read(fd, buffers[fd]);
	if (!buffers[fd])
		return (0);
	line = ft_readline(buffers[fd]);
	buffers[fd] = ft_rest(buffers[fd]);
	return (line);
}
