/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 11:16:14 by lfresnay          #+#    #+#             */
/*   Updated: 2022/12/03 13:15:03 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Les fonctions ft_printf_space() et ft_printf_unique_char(char c) sont
 * 	inutiles, question de nornme
 */
int	ft_printf_space(void)
{
	ft_putchar_fd(' ', 1);
	return (1);
}

int	ft_printf_unique_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

/*
 * Pour le flag c:
 * 	Le min_width
 * 	le flag '-'
 */
int	ft_printf_options_char(char *str, t_options *options)
{
	int	result;

	result = 1;
	if (options->min_width->is_active)
	{
		if (options->left_justify)
		{
			ft_putchar_fd(str[0], 1);
			while (options->min_width->value > result)
				result += ft_printf_space();
		}
		else
		{
			while (options->min_width->value > result)
				result += ft_printf_space();
			ft_putchar_fd(str[0], 1);
		}
	}
	else
		ft_putchar_fd(str[0], 1);
	free(str);
	return (result);
}

char	*ft_printf_char(char c)
{
	char	*result;

	result = ft_calloc(2, sizeof(char));
	result[0] = c;
	return (result);
}
