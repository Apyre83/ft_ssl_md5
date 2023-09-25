/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <lfresnay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:38:40 by lfresnay          #+#    #+#             */
/*   Updated: 2022/11/14 11:27:09 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long int	ft_power(long int n, int pow)
{
	if (pow <= 0)
		return (1);
	return (n * ft_power(n, pow - 1));
}

static long int	ft_abs_size(long int x, int option)
{
	int	i;

	if (option == 1)
	{
		if (x < 0)
			return (x * -1);
		return (x);
	}
	i = 0;
	while (ft_power(10, i) <= x)
		i++;
	return (i);
}

static void	ft_strrev(char *str)
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

static char	*ft_is_zero(void)
{
	char	*result;

	result = malloc(2 * sizeof(char));
	result[0] = '0';
	result[1] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	char			*result;
	int				i;
	long int		number;
	int				sign;

	if (n == 0)
		return (ft_is_zero());
	sign = n < 0;
	number = ft_abs_size((long int) n, 1);
	result = malloc((ft_abs_size(number, 0) + 1 + (sign == 1)) * sizeof(char));
	if (!result)
		return (0);
	if (n < 0)
		result[0] = '-';
	i = n < 0;
	while (number != 0)
	{
		result[i++] = '0' + number % 10;
		number /= 10;
	}
	result[i] = '\0';
	ft_strrev(result + (result[0] == '-'));
	return (result);
}
