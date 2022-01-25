/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddessie <ddessie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:55:31 by Dykk Dessie       #+#    #+#             */
/*   Updated: 2022/01/10 13:57:28 by ddessie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stddef.h>
#include <stdlib.h>

/*
The ft_abs() returns an absolute value of the integer n as an unsigned
integer.
*/
unsigned int	ft_abs(int n)
{
	if (n >= 0)
		return (n);
	return ((n ^ (n >> 31)) + 1);
}

/*
The ft_memset() function fills the first n bytes of the memory area pointed
to by s with the constant byte c.
*/
void	*ft_memset(void *s, int c, size_t n)
{
	const unsigned char	uc = c;
	unsigned char		*su;

	su = s;
	while (n-- > 0)
		*su++ = uc;
	return (s);
}

/*
The ft_strlen() function calculates and  returns  (in bytes)  the 
length  of  the string pointed to by s, excluding the terminating
null byte ('\0').
*/
size_t	ft_strlen(const char *s)
{
	char const	*tmp_ptr;

	tmp_ptr = s;
	while (*tmp_ptr != '\0')
		tmp_ptr ++;
	return (tmp_ptr - s);
}

/*
The ft_memmove() function copies  n  bytes from memory area src to memory area
dst. The memory  areas may overlap: copying takes place as though  the  bytes
in  src  are  first copied into a temporary array that does not overlap src or
dest, and the bytes are then copied from the temporary array to dest.
*/
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*dst_p;
	const char	*src_p;

	if (!dst && !src)
		return (NULL);
	if (src < dst && dst < src + n)
	{
		dst_p = dst + n;
		src_p = src + n;
		while (n-- > 0)
			*--dst_p = *--src_p;
	}
	else
	{
		dst_p = dst;
		src_p = src;
		while (n-- > 0)
			*dst_p++ = *src_p++;
	}
	return (dst);
}

/*
The buf_kill() function receives pointer to buffer, frees memory
which was allocated for it and returns NULL pointer.
*/
void	buf_kill(char	**b)
{
	if (*b)
	{
		free(*b);
		*b = NULL;
	}
}
