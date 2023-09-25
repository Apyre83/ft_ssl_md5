/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:35:00 by lfresnay          #+#    #+#             */
/*   Updated: 2022/12/03 14:05:49 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_param
{
	int	is_active;
	int	value;
}	t_param;

typedef struct s_options
{
	int		sign_blank;
	int		sign_plus;
	int		left_justify;
	int		hex_prefix;
	int		zero_padded;
	t_param	*precision;
	t_param	*min_width;
}	t_options;

int			ft_isdigit(int c);
int			ft_strlen(char *str);
int			ft_atoi(const char *s);
char		*ft_itoa(int n);
char		*ft_strdup(char const *str);
char		*ft_strjoin(char const *s1, char const *s2);
void		*ft_calloc(size_t count, size_t size);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_itoa_ull(unsigned long long nbr);
char		*ft_itoa_u(unsigned int nbr);
void		ft_bzero(void	*s, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_str_toupper(char *str);

// Printf

char		*ft_printf_char(char c);
char		*ft_printf_charptr(char *word);
char		*ft_printf_ptr(unsigned long long ptr);
char		*ft_printf_nbr(int nbr);
char		*ft_printf_unsigned(unsigned int nbr);
char		*ft_printf_hexa_low(unsigned int nbr);
char		*ft_printf_hexa_upp(unsigned int nbr);
char		*ft_printf_percent(void);

int			ft_printf(const char *str, ...);

int			ft_printf_options_char(char *str, t_options *options);
int			ft_printf_options_str(char *str, t_options *options);
int			ft_printf_options_hexa_low(char *str, t_options *options);
int			ft_printf_options_hexa_upp(char *str, t_options *options);
int			ft_printf_options_ptr(char *str, t_options *options);
int			ft_printf_options_unsigned(char *str, t_options *options);
int			ft_printf_options_int(char *str, t_options *options);
int			ft_printf_options_percent(char *str, t_options *options);

int			ft_printf_unique_char(char c);

int			ft_u_size(unsigned int nbr);

char		*ft_init_temp_width(char *str, t_options *options);
char		*ft_init_temp2_width(char *str, t_options *options);
char		*ft_init_temp_precision(char *str);
char		*ft_init_temp2_precision(char *str);

// Options

void		ft_free_options(t_options *options);

int			get_min_width(const char *str, t_options *options);
int			get_precision(const char *str, t_options *options);

t_options	*init_options(void);
t_param		*init_param(void);
t_options	*reset_options(t_options *old);

char		*add_suffix(char *str, char *suffix);
char		*add_prefix(char *str, char *prefix);

#endif
