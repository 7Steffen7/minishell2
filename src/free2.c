/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:43:28 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/14 14:22:35 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_token_list(t_token *token_list)
{
	t_token	*tmp;

	while (token_list != NULL)
	{
		tmp = token_list->next;
		free_token(token_list);
		token_list = tmp;
	}
}

void	free_parse_tree(t_node *node)
{
	if (node == NULL)
		return ;
	if (node->node_type == PIPE)
	{
		free_parse_tree(node->left);
		free_parse_tree(node->right);
	}
	else if (node->node_type == REDINPT
		|| node->node_type == REDOUT
		|| node->node_type == REDAPPND
		|| node->node_type == HEREDOC)
		free_parse_tree(node->next);
	free_node(node);
}

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list != NULL)
	{
		tmp = env_list->next;
		free_env(env_list);
		env_list = tmp;
	}
}

void	free_everything(t_data *data)
{
	free_parse_tree(data->parse_tree);
	data->parse_tree = NULL;
	free_env_list(data->env_list);
	data->env_list = NULL;
	free(data);
}
