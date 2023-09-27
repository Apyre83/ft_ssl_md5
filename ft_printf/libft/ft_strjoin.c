/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <lfresnay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 09:56:16 by lfresnay          #+#    #+#             */
/*   Updated: 2022/12/01 09:15:27 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
