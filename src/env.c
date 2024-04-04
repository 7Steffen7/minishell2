/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:29:47 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/26 18:14:12 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_var_str(char *env_line)
{
	int		i;
	int		j;
	char	*str_name;

	i = 0;
	while (env_line[i] != '=' && env_line[i] != '\0')
		i++;
	if (env_line[i] == '=')
		i++;
	j = 0;
	while (env_line[i + j] != '\0')
		j++;
	str_name = strndup(&env_line[i], j);
	return (str_name);
}

char	*get_var_name(char *env_line)
{
	int		i;
	char	*var_name;

	i = 0;
	while (env_line[i] != '=' && env_line[i] != '\0')
		i++;
	// eigene ft_strndup verwenden
	var_name = strndup(env_line, i);
	return (var_name);	
}

void	create_env_list(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		env_list_add_back(&data->env_list, env_list_new(get_var_name(data->env[i]), get_var_str(data->env[i])));
		i++;
	}
}
