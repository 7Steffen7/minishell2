/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:34:46 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/12 15:46:17 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_buildin(t_data *data)
{
	t_env	*env_list;

	env_list = data->env_list;
	while (env_list != NULL)
	{
		printf("%s=%s\n", env_list->var_name, env_list->var_str);
		env_list = env_list->next;
	}
}

void	export(char *variable, t_data *data)
{
	t_env	*var;
	char	*var_name;
	char	*var_str;

	var_name = get_var_name(variable);
	var_str = get_var_str(variable);
	if ((ft_strlen(var_str) == 0 && ft_strchr(variable, '=') == NULL)
		|| ft_strlen(var_name) == 0)
		{
			free(var_name);
			free(var_str);
			return ;
		}
	var = find_var(var_name, data);
	if (var != NULL)
	{
		free(var->var_str);
		var->var_str = var_str;
		free(var_name);
	}
	else
		env_list_add_back(&data->env_list, env_list_new(var_name, var_str));
}

void	unset(char *variable, t_data *data)
{
	t_env	*env_list;
	t_env	*tmp;

	if (data->env_list != NULL)
	{
		env_list = data->env_list;
		if (ft_strcmp(env_list->var_name, variable) == 0)
		{
			data->env_list = env_list->next;
			free_env(env_list);
		}
		else
		{
			while (env_list->next != NULL)
			{
				if (ft_strcmp(env_list->next->var_name, variable) == 0)
				{
					tmp = env_list->next;
					env_list->next = tmp->next;
					return (free_env(tmp));
				}
				env_list = env_list->next;
			}
		}
	}
}
