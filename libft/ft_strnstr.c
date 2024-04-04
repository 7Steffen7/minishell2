/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:21:22 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/13 12:45:14 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i] != '\0')
	{
		j = i;
		k = 0;
		while (haystack[j] == needle[k] && haystack[j] != '\0'
			&& needle[k] != '\0' && j < len)
		{
			j++;
			k++;
		}
		if (needle[k] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char haystack[] = "etyhhellonveiosvyrbhv";
// 	char needle[] = "hello";
// 	printf("%p\n", ft_strnstr(haystack, needle, 15));
// 	printf("%p\n", strnstr(haystack, needle, 15));
// }
