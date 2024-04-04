/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:02:04 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/20 17:09:32 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

// #include <string.h>
// #include <stdio.h>
// int main(void)
// {
// 	char str1[] = "";
// 	char str2[] = "";
// 	printf("%d\n", strcmp(str1, str2));
// 	printf("%d\n", ft_strcmp(str1, str2));
// }
