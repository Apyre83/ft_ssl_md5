/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfresnay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:00:57 by lfresnay          #+#    #+#             */
/*   Updated: 2022/11/17 16:01:00 by lfresnay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// Utils

int		ft_strlen(const char *str);

void	*ft_memset(void *s, int c, size_t n);

int		ft_is_in(char *str, char c);

void	*ft_calloc(size_t count, size_t size);

char	*ft_strjoin(const char *s1, const char *s2);

// Main

char	*ft_substr_wcheck(char const *s, unsigned int start, size_t len);

char	*ft_nb_read_not(char *buffer, char *stock, int nb_read);

char	*ft_read_buffer(int fd, char *stock);

char	*ft_split_line(char *line);

char	*get_next_line(int fd);

#endif
