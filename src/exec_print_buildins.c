/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_print_buildins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:53:11 by sparth            #+#    #+#             */
/*   Updated: 2024/04/16 00:53:49 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_n_option(char *option, char *echo_check)
{
	int	i;
	
	i = 2;
	if (option[0] == '-' && option[1] == 'n')
	{
		if (ft_strncmp(echo_check, "echo", 4) && option[2] != '\0')
			return (0);
		while (option[i])
		{
			if (option[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	else
		return (0);
}

void	echo(t_node *node, t_data *data)
{
	int	i;

	i = 1;
	if (!node->command[i])
		printf("\n");
	else if (check_n_option(node->command[i], node->command[0]))
	{
		while (node->command[++i])
		{
			printf("%s", node->command[i]);
			if (node->command[i + 1])
				printf(" ");
		}
	}
	else
	{
		while (node->command[i])
		{
			printf("%s", node->command[i++]);
			if (node->command[i])
				printf(" ");
		}
		printf("\n");
	}
	free_everything(data);
	exit (0);
}

void	pwd(t_data *data)
{
	char *cwd;
	cwd = getcwd(NULL, PATH_MAX);
	printf("%s\n", cwd);
	free(cwd);
	free_everything(data);
	exit (0);
}
