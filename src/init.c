/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:33:18 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/14 14:22:20 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*init_node(type node_type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->node_type = node_type;
	node->command = NULL;
	node->infile = NULL;
	node->outfile = NULL;
	node->limiter = NULL;
	node->next = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_data	*init_data(int argc, char **argv, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		ft_error("Memory allocation for data struct failed", errno);
	data->argc = argc;
	data->argv = argv;
	data->env = env;
	data->token_list = NULL;
	data->parse_tree = NULL;
	data->env_list = NULL;
	data->last_exit_code = 0;
	return (data);
}
