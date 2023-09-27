/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:01:39 by lfresnay          #+#    #+#             */
/*   Updated: 2022/11/17 16:01:54 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr_wcheck(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	size;

	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (0);
	size = 0;
	while (s[start] && size < len)
	{
		str[size] = s[start];
		size++;
		start++;
	}
	return (str);
}

char	*ft_nb_read_not(char *buffer, char *stock, int nb_read)
{
	free(buffer);
	if (nb_read == -1)
		return (0);
	return (stock);
}

char	*ft_read_buffer(int fd, char *stock)
{
	int		nb_read;
	char	*buffer;
	char	*temp;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (0);
	nb_read = read(fd, buffer, BUFFER_SIZE);
	if (nb_read < 1)
		return (ft_nb_read_not(buffer, stock, nb_read));
	if (!stock)
		stock = ft_calloc(1, sizeof(char));
	if (!stock)
		return (0);
	while (nb_read > 0)
	{
		buffer[nb_read] = '\0';
		temp = stock;
		stock = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_is_in(buffer, '\n'))
			break ;
		nb_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (ft_nb_read_not(buffer, stock, nb_read));
}

/*changer || ft_strlen(line) == 2 car "\n\0" = ? dans if (line[size] == '\0')*/
char	*ft_split_line(char *line)
{
	int		size;
	char	*stock;

	size = 0;
	while (line[size] && line[size] != '\n')
		size++;
	if (line[size] == '\0')
		return (0);
	stock = ft_substr_wcheck(line, size + 1, ft_strlen(line) - size);
	if (!stock || !stock[0])
	{
		if (stock)
			free(stock);
		stock = 0;
	}
	line[size + 1] = '\0';
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = ft_read_buffer(fd, stock);
	if (!line)
		return (0);
	stock = ft_split_line(line);
	return (line);
}
