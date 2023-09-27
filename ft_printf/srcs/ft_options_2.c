/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_options_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 13:15:31 by lfresnay          #+#    #+#             */
/*   Updated: 2022/12/03 13:15:53 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_free_options(t_options *options)
{
	if (options)
	{
		free(options->precision);
		free(options->min_width);
		free(options);
	}
}
