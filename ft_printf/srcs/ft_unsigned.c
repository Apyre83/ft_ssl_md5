/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 11:45:25 by lfresnay          #+#    #+#             */
/*   Updated: 2022/12/03 13:13:01 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_get_precision(char *str, t_options *options)
{
	if (str[0] == '0' && options->precision->value == 0)
	{
		free(str);
		str = ft_strdup("");
	}
	else
	{
		while (options->precision->value > ft_strlen(str))
			str = add_prefix(str, "0");
	}
	return (str);
}

static char	*ft_get_width(char *str, t_options *options, char *to_pad)
{
	if (options->zero_padded && options->precision->is_active == 0
		&& options->left_justify == 0)
		to_pad = "0";
	if (options->left_justify)
	{
		while (options->min_width->value > ft_strlen(str))
			str = add_suffix(str, to_pad);
	}
	else
	{
		while (options->min_width->value > ft_strlen(str))
			str = add_prefix(str, to_pad);
	}
	return (str);
}

/*
 * Pour le flag 'u':
 * 	La precision
 * 	Le flag '0'
 * 	Le flag '-'
 * 	La min width
 */
int	ft_printf_options_unsigned(char *str, t_options *options)
{
	int		result;

	result = 0;
	if (options->precision->is_active)
		str = ft_get_precision(str, options);
	if (options->min_width->is_active)
		str = ft_get_width(str, options, " ");
	ft_putstr_fd(str, 1);
	result = ft_strlen(str);
	free(str);
	return (result);
}

char	*ft_printf_unsigned(unsigned int nbr)
{
	char	*result;

	result = ft_itoa_u(nbr);
	return (result);
}
