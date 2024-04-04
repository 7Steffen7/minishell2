/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:15:11 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/09 19:17:05 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	total_len;
	char			*str_joined;
	unsigned int	i;
	unsigned int	j;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	str_joined = malloc(total_len + 1);
	if (str_joined == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str_joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str_joined[i] = s2[j];
		i++;
		j++;
	}
	str_joined[i] = '\0';
	return (str_joined);
}

// #include <stdio.h>
// int main(void)
// {
// 	char const s1[] = "hello";
// 	char const s2[] = "world";
// 	printf("%s\n", ft_strjoin(s1, s2));
// }
