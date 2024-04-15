/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env_buildins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:47:56 by sparth            #+#    #+#             */
/*   Updated: 2024/04/16 00:49:19 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env(t_data *data)
{
	t_env	*env_temp;

	env_temp = data->env_list;
	while (env_temp)
	{
		printf("%s=%s\n", env_temp->var_name, env_temp->var_str);
		env_temp = env_temp->next;
	}
}

int	look_4_unset(t_node *node, t_data *data)
{
	int	i;
	
	i = 1;
	if (node->node_type == EXEC && node->command[0] != NULL &&
		ft_strncmp(node->command[0], "unset", 6) == 0)
	{
		while (node->command[i])
		{
			unset(node->command[i], data);
			i++;
		}
		return (1);
	}
	return (0);
}

bool	export_check(char *arg)
{
	int	i;

	i = 1;
	if ((!ft_isalpha(arg[0]) && !(arg[0] == '_')))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalpha(arg[i]) && !(arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	look_4_export(t_node *node, t_data *data)
{
	int	i;
	
	i = 1;
	if (node->node_type == EXEC && node->command[0] != NULL &&
		ft_strncmp(node->command[0], "export", 7) == 0)
	{
		if (node->command[1] == NULL)
			return (1);
		if (!export_check(node->command[1]))
		{
			fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", node->command[1]);
			return (-1);
		}
		while (node->command[i])
		{
			export(node->command[i], data);
			i++;
		}
		return (1);
	}
	return (0);
}
