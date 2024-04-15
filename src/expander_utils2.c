/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:57:18 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/14 14:23:11 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*find_var_expander(char *str, t_data *data)
{
	t_env	*env_list;
	int		var_len;
	char	*var;

	var_len = var_length(str);
	if (var_len == 0)
		return (NULL);
	var = strndup(str, var_len);
	env_list = data->env_list;
	while (env_list != NULL)
	{
		if (ft_strcmp(var, env_list->var_name) == 0)
		{
			free(var);
			return (env_list);
		}
		env_list = env_list->next;
	}
	free(var);
	return (NULL);
}

int	var_length(char *str)
{
	int	i;

	i = 0;
	while (!(str[i] == ' ' || (str[i] <= 13 && str[i] >= 9))
		&& str[i] != '$' && str[i] != '\0'
		&& str[i] != '\"' && str[i] != '\''
		&& str[i] != '?')
		i++;
	if (str[i] == '?')
		return (i + 1);
	return (i);
}

int	edit_quote_counters(char *str, int *s_quote_open, int *d_quote_open)
{
	if (*str == '\"' && *s_quote_open == 0 && *d_quote_open == 0)
	{
		*d_quote_open = 1;
		return (0);
	}
	else if (*str == '\'' && *s_quote_open == 0 && *d_quote_open == 0)
	{
		*s_quote_open = 1;
		return (0);
	}
	else if (*str == '\"' && *s_quote_open == 0 && *d_quote_open == 1)
	{
		*d_quote_open = 0;
		return (0);
	}
	else if (*str == '\'' && *s_quote_open == 1 && *d_quote_open == 0)
	{
		*s_quote_open = 0;
		return (0);
	}
	return (1);
}

int	count_digits(int n)
{
	unsigned int	counter;

	if (n == 0)
		return (1);
	counter = 0;
	while (n != 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}
