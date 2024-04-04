/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:58:28 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/09 15:36:09 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;

	total = count * size;
	ptr = malloc(total);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char *ptr1 = ft_calloc(2, 4);
// 	char *ptr2 = calloc(2, 4);
// 	printf("%c\n", ptr1[0]);
// 	printf("%c\n", ptr2[0]);
// }
