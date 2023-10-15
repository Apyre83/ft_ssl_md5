/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <lfresnay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:41:04 by lfresnay          #+#    #+#             */
/*   Updated: 2022/11/16 10:57:23 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

void	*ft_memset(void *s, int c, size_t n)
{
	int	i;

	i = 0;
	while ((size_t)i < n)
		((char *) s)[i++] = c;
	return (s);
}

int	ft_is_in(char *buffer, char c)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;
	size_t	size_t_max;

	size_t_max = 4294967295;
	if (size > size_t_max || count > size_t_max || count * size > size_t_max)
		return (0);
	result = (void *) malloc(size * count);
	if (!result)
		return (0);
	ft_memset(result, 0, count * size);
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		size;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	size = ft_strlen((char *) s1) + ft_strlen((char *) s2);
	result = malloc((size + 1) * sizeof(char));
	if (!result)
		return (0);
	i = -1;
	while (s1[++i])
		result[i] = s1[i];
	j = -1;
	while (s2[++j])
		result[i + j] = s2[j];
	result[i + j] = '\0';
	return (result);
}
