/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddessie <ddessie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 21:04:54 by Dykk Dessie       #+#    #+#             */
/*   Updated: 2022/01/10 14:09:01 by ddessie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*b;
	char		*eol;
	char		*ret;
	ssize_t		r;

	if (fd < 0)
		return (NULL);
	eol = NULL;
	ret = NULL;
	r = 1;
	buf_fill(&b, fd, &r, &eol);
	ret_get(&b, r, eol, &ret);
	return (ret);
}

/*
The buff_file() function reads BUFFER_SIZE bytes from the specified file
descriptor fd into the buffer and increments the read byte counter r
by the value that was returned from the read system call.
The reading is repeated until the first character of the end of the line
is received from fd or the end of fd.
*/
void	buf_fill(char **b, int fd, ssize_t *r, char **eol)
{
	size_t			len_o;

	*eol = eol_find(*b, 0);
	while (!(*eol) && *r > 0)
	{
		if (*b)
			len_o = ft_strlen(*b);
		else
			len_o = 0;
		*b = buf_resizer(*b, len_o, BUFFER_SIZE);
		if (!(*b))
			return ;
		*r = read(fd, *b + len_o, BUFFER_SIZE);
		if (*r < 0)
		{
			buf_kill(b);
			return ;
		}
		*b = buf_resizer(*b, len_o + BUFFER_SIZE, *r - BUFFER_SIZE);
		if (!(*b))
			return ;
		*eol = eol_find(*b, len_o);
	}
}

/*
The ret_get() function extracts the part of buffer till EOL or
all buffer if no EOL was found into the ret string which will be
returned by the get_next_line() function.
The ret_get() resizes the buffer according to the extracted part.
*/
void	ret_get(char **b, ssize_t r, char *eol, char **ret)
{
	size_t	len_b;

	if (!(*b))
		return ;
	len_b = ft_strlen(*b);
	if (r == 0)
	{
		if (!(*b))
			return ;
		*ret = malloc(sizeof(char) * (len_b + 1));
		if (!(*ret))
			return ;
		(*ret)[len_b] = '\0';
		*ret = (char *)ft_memmove(*ret, *b, len_b);
		buf_kill(b);
		return ;
	}
	*ret = malloc(sizeof(char) * (eol - *b + 2));
	if (!(*ret))
		return ;
	(*ret)[eol - *b + 1] = '\0';
	(*ret) = (char *)ft_memmove(*ret, *b, eol - *b + 1);
	*b = ft_memmove(*b, eol + 1, len_b - (eol - *b + 1));
	*b = buf_resizer(*b, len_b, -(eol - *b + 1));
}

/*
The eol_find() function scans given null terminated string str and returns
pointer to the first entrance of EOL if it exists or NULL pointer otherwise.
*/
char	*eol_find(char *b, int offset)
{
	char	*str;

	if (!b || offset < 0)
		return (NULL);
	str = b + offset;
	while (*str != '\0')
	{
		if (*str == '\n' || *str == '\r')
			return (str);
		str++;
	}
	return (NULL);
}

/*
The buf_resizer() function creates a new buffer and returns a pointer to it.
The size of the new buffer is smaller or larger than the given one by diff
bytes. If diff is negative and its absolute value more or equal buffer length,
or if the given buffer is empty then the empty buffer will be returned.
*/
char	*buf_resizer(char *b, size_t len_o, int diff)
{
	char	*b_new;

	if (diff == 0)
		return (b);
	if (diff < 0 && ft_abs(diff) >= len_o)
	{
		free(b);
		b = NULL;
		return (b);
	}
	b_new = (char *)malloc(sizeof(char) * (len_o + diff + 1));
	if (!b_new)
		return (b);
	b_new = ft_memset(b_new, '_', len_o + diff);
	b_new[len_o + diff] = '\0';
	if (b)
	{
		if (diff < 0)
			b_new = (char *)ft_memmove(b_new, b, len_o + diff);
		else
			b_new = (char *)ft_memmove(b_new, b, len_o);
		free(b);
	}
	b = b_new;
	return (b);
}
