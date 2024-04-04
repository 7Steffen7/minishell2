/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 11:20:54 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/06 18:03:34 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	uc;
	unsigned char	*p;
	size_t			i;

	uc = (unsigned char)c;
	p = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		p[i] = uc;
		i++;
	}
	return (b);
}

// int main(void)
// {
// 	char array[10];
// 	int i;
// 	i = 0;
// 	while (i < 10)
// 	{
// 		write (1, &ft_memset(array, 'a', 10)[i], 1);
// 		i++;
// 	}
// }
// //
/* notes: The function taked void * as the data type of 
the first argument, because it can work with an kind of pointer as input. 
It then transforms the pointer to a unsigned char * pointer. 
The value c is given by an int, but is converted to a unsigned char 
before filling up the bytes, as the manual says.
The reason for converting c from int to unsigned char before filling 
the memory is to ensure that only the lower 8 bits (one byte) of the 
value are used. */