/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 11:26:08 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/14 13:38:06 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	toklist_size(t_token *token_list)
{
	t_token	*tmp;
	int		i;

	if (token_list == NULL)
		return (0);
	tmp = token_list;
	i = 1;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	toklist_clear(t_token **token_list)
{
	t_token	*tmp;

	tmp = *token_list;
	while (tmp != NULL)
	{
		tmp = (*token_list)->next;
		if ((*token_list)->token_str)
			free((*token_list)->token_str);
		if (*token_list)
			free((*token_list));
		*token_list = tmp;
	}
}

t_token	*ft_toknew(char *token_str, type token_type)
{
	t_token	*token_node;

	token_node = malloc(sizeof(t_token));
	if (token_node == NULL)
		ft_error("Memory allocation for token list failed", errno);
	token_node->token_str = token_str;
	token_node->token_type = token_type;
	token_node->next = NULL;
	token_node->previous = NULL;
	return (token_node);
}

t_token	*ft_toklast(t_token *token_list)
{
	if (token_list == NULL)
		return (NULL);
	while (token_list->next != NULL)
		token_list = token_list->next;
	return (token_list);
}

void	ft_tokadd_back(t_token **token_list, t_token *new)
{
	t_token	*last;

	if (token_list && new)
	{
		if (*token_list)
		{
			last = ft_toklast(*token_list);
			last->next = new;
			last->next->previous = last;
		}
		else
			*token_list = new;
	}
}
