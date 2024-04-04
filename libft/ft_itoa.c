/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:48:00 by aweissha          #+#    #+#             */
/*   Updated: 2023/10/12 16:40:37 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits(int n)
{
	unsigned int	counter;

	if (n == 0)
		return (1);
	counter = 0;
	while (n != 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

static void	fill_number(char *number, unsigned int nbrlen, int n)
{
	number[nbrlen] = '\0';
	if (n == -2147483648)
	{
		number[0] = '-';
		number[1] = '2';
		n = 147483648;
	}
	else if (n < 0)
	{
		number[0] = '-';
		n = n * (-1);
	}
	else if (n == 0)
		number[0] = 48;
	nbrlen--;
	while (n != 0)
	{
		number[nbrlen] = (n % 10) + 48;
		n = n / 10;
		nbrlen--;
	}
}

char	*ft_itoa(int n)
{
	char			*number;
	unsigned int	nbrlen;

	nbrlen = digits(n);
	if (n < 0)
		nbrlen++;
	number = malloc(nbrlen + 1);
	if (number == NULL)
		return (NULL);
	fill_number(number, nbrlen, n);
	return (number);
}

// #include <printf.h>
// int main(void)
// {
// 	int n = 0;
// 	printf("%s\n", ft_itoa(n));
// }
