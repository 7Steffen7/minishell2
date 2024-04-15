/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:54:47 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/14 14:25:16 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	add_strlen(char *str, int *d_quote_open, int *s_quote_open, t_data *data)
{
	t_env	*var;

	if (*str == '$' && *s_quote_open != 1)
	{
		str++;
		var = find_var_expander(str, data);
		if (var != NULL)
			return (ft_strlen(var->var_str));
		else if ((*str == ' ' || (*str <= 13 && *str >= 9))
			|| *str == '\0')
			return (1);
		else if (*str == '?')
			return (count_digits(data->last_exit_code));
		else
			return (0);
	}
	else
		return (edit_quote_counters(str, s_quote_open, d_quote_open));
}

int	add_str(char *str, int *s_quote_open)
{
	if (*str == '$' && *s_quote_open != 1)
	{
		str++;
		return (var_length(str) + 1);
	}
	else
		return (1);
}

void	add_exit_code(char *expanded_str, char *exit_code)
{
	while (*exit_code != '\0')
	{
		*expanded_str = *exit_code;
		expanded_str++;
		exit_code++;
	}
}

void	copy_over(char **p_expanded_str, char *original_str, t_data *data)
{
	t_env	*var;
	char	*exit_code;

	exit_code = NULL;
	var = find_var_expander(original_str + 1, data);
	if (var != NULL)
	{
		ft_strncpy(*p_expanded_str, var->var_str, ft_strlen(var->var_str));
		*p_expanded_str += ft_strlen(var->var_str);
	}
	else if (ft_isspace(*(original_str + 1))
		|| *(original_str + 1) == '\0' || *(original_str + 1) == '\"')
	{
		**p_expanded_str = '$';
		(*p_expanded_str)++;
	}
	else if (*(original_str + 1) == '?')
	{
		exit_code = ft_itoa(data->last_exit_code);
		add_exit_code(*p_expanded_str, exit_code);
		(*p_expanded_str) += ft_strlen(exit_code);
		free(exit_code);
	}
	else
		return ;
}
