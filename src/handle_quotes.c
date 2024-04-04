/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:34:01 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/04 14:47:49 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	quotes_left(char *start, char *position, char c)
{
	int	quote_count;

	quote_count = 0;
	position--;
	while (position >= start)
	{
		if (*position == c)
			quote_count++;
		position--;
	}
	return (quote_count);
}

int	quotes_right(char *start, char *position, char c)
{
	int	quote_count;

	start = NULL;
	quote_count = 0;
	position++;
	while (*position !='\0')
	{
		if (*position == c)
			quote_count++;
		position++;
	}
	return (quote_count);
}

int	in_quotes(char *start, char *position)
{
	// printf("hello from in_quotes\n");
	if ((quotes_left(start, position, 34) % 2) == 1 
		&& quotes_right(start, position, 34) > 0 
		&& *position != 34)
		return (1);
	else if ((quotes_left(start, position, 39) % 2) == 1 
		&& quotes_right(start, position, 39) > 0 
		&& *position != 39)
		return (1);	
	// else if (*position == 34 && (quotes_left(start, position, 34) % 2) == 1)
	// 	return (1);
	// else if (*position == 39 && (quotes_left(start, position, 39) % 2) == 1)
	// 	return (1);
	// else if (*position == 34 && (quotes_right(start, position, 34) > 0))
	// 	return (1);
	// else if (*position == 39 && (quotes_right(start, position, 39) > 0))
	// 	return (1);
	return (0);
}
