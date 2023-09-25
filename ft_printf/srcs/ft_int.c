/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 11:18:47 by lfresnay          #+#    #+#             */
/*   Updated: 2022/12/03 13:21:12 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_int_precision(char *str, t_options *options)
{
	char	*temp;
	char	*temp2;

	temp = ft_init_temp_precision(str);
	temp2 = ft_init_temp2_precision(str);
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

static char	*ft_int_min_width(char *str, t_options *options)
{
	char	*to_pad;
	char	*temp;
	char	*temp2;

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
 * Pour les flags i et d:
 * 	Le flag '+'
 * 	Le flag ' '
 * 	Le flag '0'
 * 	Le min width
 * 	Le flag '-'
 *	La precision
 */
int	ft_printf_options_int(char *str, t_options *options)
{
	int	result;

	result = 0;
	if (options->sign_blank && ft_atoi(str) >= 0)
		str = add_prefix(str, " ");
	if (options->sign_plus && ft_atoi(str) >= 0)
		str = add_prefix(str, "+");
	if (options->precision->is_active)
		str = ft_int_precision(str, options);
	if (options->min_width->is_active)
		str = ft_int_min_width(str, options);
	ft_putstr_fd(str, 1);
	result = ft_strlen(str);
	free(str);
	return (result);
}

char	*ft_printf_nbr(int nbr)
{
	char	*result;

	result = ft_itoa(nbr);
	return (result);
}
