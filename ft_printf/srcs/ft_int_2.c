/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:20:04 by lfresnay          #+#    #+#             */
/*   Updated: 2022/12/03 13:20:50 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_init_temp_precision(char *str)
{
	char	*temp;

	if (str[0] == '+' || str[0] == '-' || str[0] == ' ')
	{
		temp = ft_calloc(2, sizeof(char));
		temp[0] = str[0];
	}
	else
		temp = ft_calloc(1, sizeof(char));
	return (temp);
}

char	*ft_init_temp2_precision(char *str)
{
	char	*temp2;

	if (str[0] == '+' || str[0] == '-' || str[0] == ' ')
		temp2 = ft_strdup(str + 1);
	else
		temp2 = ft_strdup(str);
	return (temp2);
}

char	*ft_init_temp_width(char *str, t_options *options)
{
	char	*temp;

	if (options->zero_padded && options->precision->is_active == 0
		&& options->left_justify == 0)
	{
		if (str[0] == '+' || str[0] == '-' || str[0] == ' ')
		{
			temp = ft_calloc(2, sizeof(char));
			temp[0] = str[0];
		}
		else
			temp = ft_calloc(1, sizeof(char));
	}
	else
		temp = ft_calloc(1, sizeof(char));
	return (temp);
}

char	*ft_init_temp2_width(char *str, t_options *options)
{
	char	*temp2;

	if (options->zero_padded && options->precision->is_active == 0
		&& options->left_justify == 0)
	{
		if (str[0] == '+' || str[0] == '-' || str[0] == ' ')
			temp2 = ft_strdup(str + 1);
		else
			temp2 = ft_strdup(str);
	}
	else
		temp2 = ft_strdup(str);
	return (temp2);
}
