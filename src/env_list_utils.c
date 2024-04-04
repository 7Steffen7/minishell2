/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:50:05 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/26 16:50:22 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*env_list_last(t_env *env_list)
{
	if (env_list == NULL)
		return (NULL);
	while (env_list->next != NULL)
		env_list = env_list->next;
	return (env_list);
}

t_env	*env_list_new(char *var_name, char *var_str)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (node == NULL)
		return (NULL);
	node->var_name = var_name;
	node->var_str = var_str;
	node->next = NULL;
	return (node);
}

void	env_list_add_back(t_env **env_list, t_env *new)
{
	t_env	*last;

	if (env_list && new)
	{
		if (*env_list)
		{
			last = env_list_last(*env_list);
			last->next = new;
		}
		else
			*env_list = new;
	}
}
