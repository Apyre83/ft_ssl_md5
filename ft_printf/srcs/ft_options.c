/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_options.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 12:23:05 by lfresnay          #+#    #+#             */
/*   Updated: 2022/12/03 13:03:05 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_param	*init_param(void)
{
	t_param	*param;

	param = malloc(1 * sizeof(t_param));
	param->is_active = 0;
	param->value = 0;
	return (param);
}

t_options	*init_options(void)
{
	t_options	*options;

	options = malloc(1 * sizeof(t_options));
	options->sign_blank = 0;
	options->sign_plus = 0;
	options->left_justify = 0;
	options->hex_prefix = 0;
	options->zero_padded = 0;
	options->precision = init_param();
	options->min_width = init_param();
	return (options);
}

t_options	*reset_options(t_options *old)
{
	t_options	*options;

	if (old)
	{
		free(old->precision);
		free(old->min_width);
		free(old);
	}
	options = init_options();
	return (options);
}

int	get_precision(const char *str, t_options *options)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	if (str[i] != '.')
		return (0);
	i++;
	while (ft_isdigit(str[i]))
	{
		value *= 10;
		value += str[i] - '0';
		i++;
	}
	options->precision->is_active = 1;
	options->precision->value = value;
	return (i);
}

int	get_min_width(const char *str, t_options *options)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		value *= 10;
		value += str[i] - '0';
		i++;
	}
	options->min_width->is_active = 1;
	options->min_width->value = value;
	return (i);
}
