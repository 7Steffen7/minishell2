/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:24:02 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/14 14:21:55 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

type	tok_type(char *token_str)
{
	if (ft_strcmp(token_str, "<") == 0
		|| ft_strcmp(token_str, ">") == 0
		|| ft_strcmp(token_str, ">>") == 0
		|| ft_strcmp(token_str, "<<") == 0)
		return (REDIR);
	else if (ft_strcmp(token_str, "|") == 0)
		return (PIPE);
	else
		return (WORD);
}

type	classify_char(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (REDINPT);
	else if (c == '>')
		return (REDOUT);
	else if (ft_isspace(c))
		return (TOKEN_SPACE);
	return (WORD);
}

int	add_token(t_token **token_list, char *str)
{
	type	token_type;
	int		i;
	int		s_quote_open;
	int		d_quote_open;

	s_quote_open = 0;
	d_quote_open = 0;
	token_type = classify_char(*str);
	i = 0;
	while ((classify_char(str[i]) == token_type && str[i] != '\0')
		|| ((s_quote_open == 1 || d_quote_open == 1) && str[i] != '\0'))
	{
		set_quote_flags(&str[i], &s_quote_open, &d_quote_open);
		i++;
		if ((i > 1 && token_type == REDINPT)
			|| (i > 1 && token_type == REDOUT)
			|| (i > 0 && token_type == PIPE))
			break ;
	}
	if (token_type == REDINPT || token_type == REDOUT)
		ft_tokadd_back(token_list, ft_toknew(strndup(str, i), REDIR));
	else
		ft_tokadd_back(token_list, ft_toknew(strndup(str, i), token_type));
	return (i);
}

void	lexer(char *input, t_data *data)
{
	while (input && *input != '\0')
	{
		while (classify_char(*input) == TOKEN_SPACE && *input != '\0')
			input++;
		if (*input != '\0')
			input += add_token(&data->token_list, input);
	}
}
