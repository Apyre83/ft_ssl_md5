/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 11:30:17 by lfresnay          #+#    #+#             */
/*   Updated: 2022/12/03 11:33:17 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Pour le flag 'p':
 * 	La min width
 *	Le flag '-'
 */
int	ft_printf_options_ptr(char *str, t_options *options)
{
	int	result;

	result = 0;
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

char	*ft_printf_ptr(unsigned long long ptr)
{
	char	*result;
	char	*temp;
	char	*temp2;

	if (!ptr)
		result = ft_strdup("0x0");
	else
	{
		temp = ft_strdup("0x");
		temp2 = ft_itoa_ull(ptr);
		result = ft_strjoin(temp, temp2);
		free(temp);
		free(temp2);
	}
	return (result);
}
