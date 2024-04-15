/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:23:23 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/14 14:20:07 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_operators(t_token *token_list)
{
	if (pipe_syntax_check(token_list) == 1)
		return (1);
	if (redir_syntax_check(token_list) == 1)
		return (1);
	return (0);
}

int	check_quotes(t_token *token_list)
{
	while (token_list != NULL)
	{
		if (quotes_wrong(token_list->token_str) == 1)
			return (1);
		token_list = token_list->next;
	}
	return (0);
}

int	syntax_check(t_data *data)
{
	if (check_quotes(data->token_list) == 1)
	{
		printf("invalid quotes\n");
		return (1);
	}
	else if (check_operators(data->token_list) == 1)
		return (1);
	return (0);
}
