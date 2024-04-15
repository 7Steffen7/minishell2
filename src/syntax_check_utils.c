/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:48:49 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/14 14:19:43 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	pipe_syntax_check(t_token *token_list)
{
	while (token_list != NULL)
	{
		if (token_list->token_type == PIPE)
		{
			if (token_list->next == NULL
				|| token_list->previous == NULL
				|| token_list->previous->token_type != WORD)
			{
				printf("minishell: syntax error near '|'\n");
				return (1);
			}
		}
		token_list = token_list->next;
	}
	return (0);
}

int	redir_syntax_check(t_token *token_list)
{
	while (token_list != NULL)
	{
		if (token_list->token_type == REDIR)
		{
			if (token_list->next == NULL
				|| token_list->next->token_type != WORD)
			{
				printf("minishell: syntax error near '\\n'\n");
				return (1);
			}
		}
		token_list = token_list->next;
	}
	return (0);
}

int	quotes_wrong(char *str)
{
	int		s_quote_open;
	int		d_quote_open;

	s_quote_open = 0;
	d_quote_open = 0;
	while (*str != '\0')
	{
		set_quote_flags(str, &s_quote_open, &d_quote_open);
		str++;
	}
	if (s_quote_open != 0 || d_quote_open != 0)
		return (1);
	return (0);
}
