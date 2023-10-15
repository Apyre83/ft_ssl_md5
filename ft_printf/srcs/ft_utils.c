/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <lfresnay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 08:24:16 by lfresnay          #+#    #+#             */
/*   Updated: 2022/12/03 13:17:03 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_strrev(char *str)
{
	int		size;
	int		i;
	char	temp;

	size = ft_strlen(str);
	i = 0;
	while (i < size / 2)
	{
		temp = str[i];
		str[i] = str[size - 1 - i];
		str[size - 1 - i] = temp;
		i++;
	}
}

unsigned long long	ft_power_ull(unsigned long long x, int pow)
{
	if (pow <= 0)
		return (1);
	return (x * ft_power_ull(x, pow - 1));
}

static int	ft_ull_size(unsigned long long nbr)
{
	int	i;

	i = 0;
	while (nbr)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}

char	*ft_itoa_ull(unsigned long long nbr)
{
	int		size;
	char	*result;
	int		i;
	char	*base;

	base = "0123456789abcdef";
	size = ft_ull_size(nbr);
	result = ft_calloc(size + 1, sizeof(char));
	if (!result)
		return (0);
	i = 0;
	while (nbr != 0)
	{
		result[i++] = base[nbr % 16];
		nbr /= 16;
	}
	ft_strrev(result);
	return (result);
}

char	*ft_itoa_u(unsigned int nbr)
{
	int		size;
	char	*result;
	int		i;

	if (!nbr)
	{
		result = ft_calloc(2, sizeof(char));
		result[0] = '0';
		return (result);
	}
	size = ft_u_size(nbr);
	result = ft_calloc(size + 1, sizeof(char));
	if (!result)
		return (0);
	i = 0;
	while (nbr != 0)
	{
		result[i++] = '0' + nbr % 10;
		nbr /= 10;
	}
	ft_strrev(result);
	return (result);
}
