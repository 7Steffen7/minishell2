/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:07:34 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/12 15:19:10 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*dest;
	const unsigned char		*source;
	size_t					i;

	dest = (unsigned char *)dst;
	source = (const unsigned char *)src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dest < source)
	{
		while (i < len)
		{
			dest[i] = source[i];
			i++;
		}
	}
	else
	{
		i = len;
		while (i-- > 0)
			dest[i] = source[i];
	}
	return (dst);
}

// int main(void)
// {
//     char src[] = "helloo";
//     char dst[] = "blabla";
//     // char *src = "blabla";
//     ft_memcpy(dst, src, 6);
//     write(1, dst, 6);
//     return (0);
// }
