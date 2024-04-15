/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:41:51 by sparth            #+#    #+#             */
/*   Updated: 2024/04/15 23:46:38 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// void	*free_null(char *del)
// {
// 	free(del);
// 	return (NULL);
// }

void	path_clean(t_path_prep check, int status)
{
	int	i;

	i = 0;
	if (check.directory)
	{
		while (check.directory[i])
			free(check.directory[i++]);
		free(check.directory);
	}
	if (check.cmd_prep)
		free(check.cmd_prep);
	if (check.first_cmd)
		free(check.first_cmd);
	if (check.paths)
		free(check.paths);
	if (check.pathcheck && status == 0)
		free(check.pathcheck);
}

t_path_prep	init_struct(void)
{
	t_path_prep	check;

	check.directory = NULL;
	check.cmd_prep = NULL;
	check.pathcheck = NULL;
	check.first_cmd = NULL;
	check.paths = NULL;
	return (check);
}
char	*cmd_cut(char *cmd)
{
	int		i;
	int		k;
	char	*cutted;

	i = 0;
	while (cmd[i] != ' ' && cmd[i])
		i++;
	cutted = (char *)malloc(sizeof(char) * i + 1);
	if (!cutted)
		return (NULL);
	k = 0;
	while (k < i)
	{
		cutted[k] = cmd[k];
		k++;
	}
	cutted[k] = '\0';
	return (cutted);
}

char	*path_check2(char *cmd, t_path_prep check)
{
	int	i;

	i = 0;
	while (check.directory[i])
	{
		check.pathcheck = ft_strjoin(check.directory[i], check.cmd_prep);
		if (!check.pathcheck)
			return (path_clean(check, 0), NULL);
		if (access(check.pathcheck, X_OK) == 0)
			return (path_clean(check, 1), check.pathcheck);
		check.pathcheck = free_null(check.pathcheck);
		i++;
	}
	path_clean(check, 0);
	if (access(cmd, X_OK) == 0 && ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (cmd);
	return (NULL);
}

char	*path_check(char *cmd, char *path)
{
	t_path_prep	check;

	check = init_struct();
	check.first_cmd = cmd_cut(cmd);
	if (!check.first_cmd)
		return (NULL);
	if (strncmp(check.first_cmd, "./", 2) == 0
		&& access(check.first_cmd, X_OK) == 0)
		return (check.first_cmd);
	if (!path)
		return (path_clean(check, 0), NULL);
	if (strncmp(check.first_cmd, "./", 2) == 0
		&& (ft_strlen(check.first_cmd) != ft_strlen(cmd) || access(cmd, X_OK)))
		return (path_clean(check, 0), NULL);
	check.cmd_prep = ft_strjoin("/", check.first_cmd);
	check.first_cmd = free_null(check.first_cmd);
	check.paths = ft_strtrim(path, "PATH=");
	check.directory = ft_split(check.paths, ':');
	if (!check.directory || !check.paths || !check.cmd_prep)
		return (path_clean(check, 0), NULL);
	check.paths = free_null(check.paths);
	return (path_check2(cmd, check));
}