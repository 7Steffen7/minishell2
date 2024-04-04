/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:22:25 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/04 14:49:37 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_token_list(t_token **token_list, t_token *redir_token)
{
	t_token	*tmp;
	t_token	*tmp2;

	redir_token = NULL;
	if ((*token_list)->token_type == REDIR)
	{
		tmp = *token_list;
		*token_list = (*token_list)->next->next;
		(*token_list)->previous = NULL;
		free_token(tmp->next);
		free_token(tmp);
	}
	else
	{
		tmp = *token_list;
		while (tmp->next->token_type != REDIR)
			tmp = tmp->next;
		tmp2 = tmp;
		tmp = tmp->next->next->next;
		free_token(tmp2->next->next);
		free_token(tmp2->next);
		tmp2->next = tmp;
		if (tmp != NULL)
			tmp->previous = tmp2;
	}
}

void	config_redir_node(t_token *redir_token, t_node *redir_node)
{
	char	*token_str;
	
	token_str = redir_token->token_str;
	if (ft_strcmp(token_str, "<") == 0)
	{
		redir_node->node_type = REDINPT;
		redir_node->infile = ft_strdup(redir_token->next->token_str);
	}
	else if (ft_strcmp(token_str, ">") == 0)
	{
		redir_node->node_type = REDOUT;
		redir_node->outfile = ft_strdup(redir_token->next->token_str);
	}
	else if (ft_strcmp(token_str, ">>") == 0)
	{
		redir_node->node_type = REDAPPND;
		redir_node->outfile = ft_strdup(redir_token->next->token_str);
	}
	else if (ft_strcmp(token_str, "<<") == 0)
	{
		redir_node->node_type = HEREDOC;
		redir_node->limiter = ft_strdup(redir_token->next->token_str);
	}
}

t_token	*find_token(t_token	*token_list, type token_type)
{
	while (token_list != NULL)
	{
		if (token_list->token_type == token_type)
			return (token_list);
		token_list = token_list->next;
	}
	return (NULL);
}
