/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 11:17:57 by lfresnay          #+#    #+#             */
/*   Updated: 2022/12/03 11:18:28 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Pour le flag s:
 * 	Le min width
 * 	le flag -
 * 	La precision
 */
int	ft_printf_options_str(char *str, t_options *options)
{
	int	result;

	if (options->precision->is_active)
	{
		if (options->precision->value < ft_strlen(str))
			str[options->precision->value] = '\0';
	}
	if (options->min_width->is_active)
	{
		if (options->left_justify)
		{
			while (options->min_width->value > ft_strlen(str))
				str = add_suffix(str, " ");
		}
		else
		{
			while (options->min_width->value > ft_strlen(str))
				str = add_prefix(str, " ");
		}
	}
	ft_putstr_fd(str, 1);
	result = ft_strlen(str);
	free(str);
	return (result);
}

char	*ft_printf_charptr(char *word)
{
	char	*result;

	if (!word)
		result = ft_strdup("(null)");
	else
		result = ft_strdup(word);
	return (result);
}
