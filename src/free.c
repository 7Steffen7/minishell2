/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 12:03:49 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/15 14:56:35 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_token(t_token	*token)
{
	free(token->token_str);
	free(token);
}

void	free_env(t_env *env_node)
{
	free(env_node->var_name);
	free(env_node->var_str);
	free(env_node);
}

void	free_str_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_node(t_node *node)
{
	if (node->node_type == EXEC)
	{
		free_str_array(node->command);
	}
	else if (node->node_type == REDINPT)
		free(node->infile);
	else if (node->node_type == REDOUT
		|| node->node_type == REDAPPND)
		free(node->outfile);
	else if (node->node_type == HEREDOC)
		free(node->limiter);
	free(node);
}
