/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:20:26 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/08 14:02:57 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		d;
	size_t				i;

	p = (const unsigned char *)s;
	d = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (p[i] == d)
			return ((void *)&p[i]);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main(void) {
//     char str[] = "Hello, World!";
//     char search_char = 'o';
//     size_t search_size = 5;
//     const void *result = ft_memchr(str, search_char, search_size);
//     size_t index = (size_t)((const char *)result - str);
//     printf("'%c' found at index %zu\n", search_char, index);
//     return 0;
// }
