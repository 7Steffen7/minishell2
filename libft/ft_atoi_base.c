/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:39:27 by aweissha          #+#    #+#             */
/*   Updated: 2024/01/09 13:40:08 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_base(int base, char c)
{
	int		i;

	i = 0;
	while (i < base)
	{
		if (c == "0123456789abcdef"[i] || c == "0123456789ABCDEF"[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	i;
	int	minus_counter;
	int	number;

	i = 0;
	minus_counter = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus_counter = minus_counter * (-1);
		i++;
	}
	while (is_in_base(str_base, str[i]) == 1
		&& str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			number = number * str_base + str[i] - 48;
		else if (str[i] >= 'A' && str[i] <= 'F')
			number = number * str_base + str[i] - 65 + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			number = number * str_base + str[i] - 97 + 10;
		i++;
	}
	return (number * minus_counter);
}
