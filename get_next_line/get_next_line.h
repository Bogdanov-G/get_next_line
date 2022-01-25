/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddessie <ddessie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 18:54:01 by ddessie           #+#    #+#             */
/*   Updated: 2022/01/10 13:57:02 by ddessie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <unistd.h>

char			*get_next_line(int fd);
void			buf_fill(char **b, int fd, ssize_t *r, char **eol);
void			ret_get(char **b, ssize_t r, char *eol, char **ret);
char			*eol_find(char *b, int offset);
char			*buf_resizer(char *b, size_t len_o, int diff);
unsigned int	ft_abs(int n);
void			*ft_memset(void *s, int c, size_t n);
size_t			ft_strlen(const char *s);
void			*ft_memmove(void *dst, const void *src, size_t n);
void			buf_kill(char	**b);
#endif
