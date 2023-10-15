/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <lfresnay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 14:01:48 by lfresnay          #+#    #+#             */
/*   Updated: 2022/12/03 14:19:23 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * Affiche tout ce qu'il y a a afficher de la variable et renvoie le nombre de
 * characteres qu'elle a affiche
 *
 * Petit rappel des options:
 * 	'+' Affiche un '+' si le nombre est positif
 * 	' ' Affiche un ' ' si le nombre est positif
 * 	'-' Fais un decalage vers la gauche avec des espaces
 * 	'0' Le decalage se fait avec des '0' et non des espaces
 * 	'#' Rajoute le prefixe 0x devant un hexa minuscule ou 0X devant maj
 */
int	ft_printf_options(char *str, char c, t_options *options)
{
	int	result;

	result = 0;
	if (c == 'c')
		result = ft_printf_options_char(str, options);
	else if (c == 's')
		result = ft_printf_options_str(str, options);
	else if (c == 'd' || c == 'i')
		result = ft_printf_options_int(str, options);
	else if (c == 'x')
		result = ft_printf_options_hexa_low(str, options);
	else if (c == 'X')
		result = ft_printf_options_hexa_upp(str, options);
	else if (c == 'p')
		result = ft_printf_options_ptr(str, options);
	else if (c == 'u')
		result = ft_printf_options_unsigned(str, options);
	else if (c == '%')
		result = ft_printf_options_percent(str, options);
	return (result);
}

int	ft_printf_item(char c, va_list args, t_options *options)
{
	char	*result;
	int		size;

	result = 0;
	if (c == 'c')
		result = ft_printf_char(va_arg(args, int));
	else if (c == 's')
		result = ft_printf_charptr(va_arg(args, char *));
	else if (c == 'p')
		result = ft_printf_ptr(va_arg(args, unsigned long long));
	else if (c == 'd')
		result = ft_printf_nbr(va_arg(args, int));
	else if (c == 'i')
		result = ft_printf_nbr(va_arg(args, int));
	else if (c == 'u')
		result = ft_printf_unsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		result = ft_printf_hexa_low(va_arg(args, unsigned int));
	else if (c == 'X')
		result = ft_printf_hexa_upp(va_arg(args, unsigned int));
	else if (c == '%')
		result = ft_printf_percent();
	size = ft_printf_options(result, c, options);
	return (size);
}

int	ft_is_flag(char c)
{
	char	*flags;
	int		i;

	flags = "-0+ #";
	i = 0;
	while (i < 5)
	{
		if (c == flags[i])
			return (1);
		i++;
	}
	return (0);
}

/*
 * Il faut d'abord recuperer les flags, cad "-0+ #"
 */
int	get_flags(const char *str, t_options *options)
{
	int	i;

	i = 1;
	while (str[i] && ft_is_flag(str[i]))
	{
		if (str[i] == '0')
			options->zero_padded = 1;
		else if (str[i] == ' ')
		{
			if (options->sign_plus == 0)
				options->sign_blank = 1;
		}
		else if (str[i] == '+')
		{
			if (options->sign_blank == 1)
				options->sign_blank = 0;
			options->sign_plus = 1;
		}
		else if (str[i] == '#')
			options->hex_prefix = 1;
		else if (str[i] == '-')
			options->left_justify = 1;
		i++;
	}
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			i;
	int			result;
	t_options	*options;

	options = 0;
	va_start(args, str);
	result = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '%')
		{
			options = reset_options(options);
			i += get_flags(str + i, options);
			i += get_min_width(str + i, options);
			i += get_precision(str + i, options);
			result += ft_printf_item(str[i], args, options);
		}
		else
			result += ft_printf_unique_char(str[i]);
	}
	ft_free_options(options);
	return (result);
}
