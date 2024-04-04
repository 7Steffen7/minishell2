/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:04:22 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/13 15:48:57 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	unsigned int	counter;
	unsigned int	i;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		i++;
		if (((s[i] == c || s[i] == '\0') && s[i - 1] != c))
			counter++;
	}
	return (counter);
}

static int	strlength(char const *s, unsigned int index, char c)
{
	unsigned int	counter;

	counter = 1;
	while (index > 0 && s[index - 1] != c)
	{
		counter++;
		index--;
	}
	return (counter);
}

static char	**ft_free(char **array, int index)
{
	while (index >= 0)
	{
		free(array[index]);
		index--;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char			**array;
	unsigned int	i;
	unsigned int	j;
	unsigned int	wordlen;

	array = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!(array))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		i++;
		if (((s[i] == c || s[i] == '\0') && s[i - 1] != c))
		{
			wordlen = strlength(s, i - 1, c);
			array[j] = malloc(wordlen + 1);
			if (!(array[j]))
				return (ft_free(array, j));
			ft_strlcpy(array[j++], &s[i - wordlen], (wordlen + 1));
		}
	}
	array[j] = NULL;
	return (array);
}

// #include <stdio.h>
// int main(void)
// {
// 	char str[] = "zzzhellozzmyznamezziszzalexzz";
// 	char **array = ft_split(str, 'z');
// 	printf("%s", array[4]);
// }
