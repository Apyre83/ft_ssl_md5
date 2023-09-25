/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_upp_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:19:04 by lfresnay          #+#    #+#             */
/*   Updated: 2022/12/03 13:19:18 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_init_temp_width(char *str, t_options *options)
{
	char	*temp;

	if (options->zero_padded && options->precision->is_active == 0
		&& options->left_justify == 0)
	{
		if (str[0] == '0' && str[1] == 'X')
			temp = ft_strdup("0X");
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
		if (str[0] == '0' && str[1] == 'X')
			temp2 = ft_strdup(str + 2);
		else
			temp2 = ft_strdup(str);
	}
	else
		temp2 = ft_strdup(str);
	return (temp2);
}
