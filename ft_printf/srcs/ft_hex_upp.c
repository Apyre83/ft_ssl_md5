/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_upp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 11:28:42 by lfresnay          #+#    #+#             */
/*   Updated: 2022/12/03 13:19:39 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*init_temp(char *str)
{
	char	*temp;

	if (str[0] == '0' && str[1] == 'X')
		temp = ft_strdup("0X");
	else
		temp = ft_calloc(1, sizeof(char));
	return (temp);
}

static char	*ft_hex_upp_precision(char *str, t_options *options)
{
	char	*temp;
	char	*temp2;

	temp = init_temp(str);
	if (str[0] == '0' && str[1] == 'X')
		temp2 = ft_strdup(str + 2);
	else
		temp2 = ft_strdup(str);
	free(str);
	if (temp2[0] == '0' && options->precision->value == 0)
	{
		free(temp2);
		temp2 = ft_strdup("");
	}
	else
	{
		while (options->precision->value > ft_strlen(temp2))
			temp2 = add_prefix(temp2, "0");
	}
	str = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	return (str);
}

static char	*ft_hex_upp_min_width(char *str, t_options *options)
{
	char	*temp;
	char	*temp2;
	char	*to_pad;

	temp = ft_init_temp_width(str, options);
	temp2 = ft_init_temp2_width(str, options);
	to_pad = " ";
	if (options->zero_padded && options->precision->is_active == 0
		&& options->left_justify == 0)
		to_pad = "0";
	if (options->left_justify)
	{
		while (options->min_width->value > ft_strlen(temp2))
			temp2 = add_suffix(temp2, to_pad);
	}
	else
	{
		while (options->min_width->value > ft_strlen(temp2) + ft_strlen(temp))
			temp2 = add_prefix(temp2, to_pad);
	}
	free(str);
	str = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	return (str);
}

/*
 * Pour le flag 'x':
 * 	Le flag '#'
 * 	Le flag '0'
 * 	Le flag '-'
 * 	La min width
 * 	La precision
 */
int	ft_printf_options_hexa_upp(char *str, t_options *options)
{
	int	result;

	result = 0;
	if (options->hex_prefix && str[0] != '0')
		str = add_prefix(str, "0X");
	if (options->precision->is_active)
		str = ft_hex_upp_precision(str, options);
	if (options->min_width->is_active)
		str = ft_hex_upp_min_width(str, options);
	ft_putstr_fd(str, 1);
	result = ft_strlen(str);
	free(str);
	return (result);
}

char	*ft_printf_hexa_upp(unsigned int nbr)
{
	char	*result;

	if (!nbr)
	{
		result = ft_calloc(2, sizeof(char));
		result[0] = '0';
	}
	else
		result = ft_itoa_ull((unsigned long long) nbr);
	ft_str_toupper(result);
	return (result);
}
