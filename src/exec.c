/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:52:02 by sparth            #+#    #+#             */
/*   Updated: 2024/04/16 01:05:59 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*free_null(char *del)
{
	free(del);
	return (NULL);
}

void piping(t_node *node, t_data *data)
{
		int		fd[2];
		int		wpidstatus;
		pid_t	pid_left;
		pid_t	pid_right;
		
		if (pipe(fd) == -1)
			exit (1);
		pid_left = fork();
		if (pid_left == -1)
			exit (1);
		if (pid_left == 0)
		{
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				exit (1);
			if (close(fd[0]) == -1 || close(fd[1]) == -1)
				exit(1);
			exec(node->left, data);
		}
		pid_right = fork();
		if (pid_right == -1)
			exit (1);
		if (pid_right == 0)
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
				exit (1);
			if (close(fd[0]) == -1 || close(fd[1]) == -1)
				exit(1);
			exec(node->right, data);
		}
		if (pid_right != 0 && pid_left != 0)
		{
			if (close(fd[0]) == -1 || close(fd[1]) == -1)
				exit (29);
		}
		waitpid(pid_right, &wpidstatus, 0);
		waitpid(pid_left, NULL, 0);
		free_everything(data);
		if (WIFEXITED(wpidstatus))
		{
			exit (WEXITSTATUS(wpidstatus));
		}
}

void	path_error_message(char *error)
{
	// if (access(cmd_cut(error), X_OK) && access(cmd_cut(error), R_OK) == 0)
	// 	fprintf(stderr, "%s%s: %s\n", "minishell: ", cmd_cut(error), strerror(13));
	if (strncmp(error, "/", 1) == 0)
		fprintf(stderr, "%s%s: %s\n", "minishell: ", error, strerror(2));
	else if (strncmp(error, "./", 2) == 0 && access(error, F_OK) == 0)
		fprintf(stderr, "%s%s: %s\n", "minishell: ", error, strerror(13));
	else if (strncmp(error, "./", 2) == 0)
		fprintf(stderr, "%s%s: %s\n", "minishell: ", error, strerror(2));
	else
		fprintf(stderr, "%s%s: %s\n", "minishell: ", error, "command not found");
}

void	check_if_buildin(t_node *node, t_data *data)
{
	if (ft_strncmp (node->command[0], "env", 4) == 0)
	{
		env(data);
		free_everything(data);
		exit (0);
	}
	if ((node->command[0][0] == 'e' || node->command[0][0] == 'E')
		&& (node->command[0][1] == 'c' || node->command[0][1] == 'C')
		&& (node->command[0][2] == 'h' || node->command[0][2] == 'H')
		&& (node->command[0][3] == 'o' || node->command[0][3] == 'O')
		&& node->command[0][4] == '\0')
		echo(node, data);
	if (ft_strncmp (node->command[0], "pwd", 4) == 0)
		pwd(data);
	if (ft_strncmp (node->command[0], "exit", 5) == 0
		|| ft_strncmp (node->command[0], "cd", 3) == 0
		|| ft_strncmp (node->command[0], "unset", 6) == 0
		|| ft_strncmp (node->command[0], "export", 7) == 0)
	{
		free_everything(data);
		exit (0);
	}
}

char	*get_env(t_data *data)
{
	t_env	*env_temp;

	env_temp = data->env_list;
	while (env_temp)
	{
		if (ft_strncmp(env_temp->var_name, "PATH", 4) == 0)
			return (env_temp->var_str);
		env_temp = env_temp->next;
	}
	return (NULL);
}

void	execution(t_node *node, t_data *data)
{
	char		*path;
	struct stat	dir_check;

	check_if_buildin(node, data);
	path = path_check(node->command[0], get_env(data));
	if (!path)
		path_error_message(node->command[0]);
	if (path)
		execve(path, node->command, NULL);
	if (path && access((path), X_OK) && access((path), W_OK) == 0)
	{
		free(path);
		free_everything(data);
		exit (126);
	}
	if (path && stat(path, &dir_check) == 0)
	{
		free(path);
		path = NULL;
		if (S_ISDIR(dir_check.st_mode))
		{
			fprintf(stderr, "%s%s: is a directory\n", "minishell: ", node->command[0]);
			// free_everything(data); // $PWD result in double free !!!!!
			exit(126);
		}
	}
	free(path);
	if (strncmp(node->command[0], "./", 2) == 0 && access((node->command[0]), F_OK) == 0)
	{
		free_everything(data);
		exit (126);
	}
	free_everything(data);
	exit(127);
}

void	string_cut(char *s, int flag)
{
	int		slash_count;
	int		char_count;
	int		i;
	char	cut[PATH_MAX];

	slash_count = 0;
	char_count = 0;
	i = 0;
	while (s[char_count])
	{
		if (s[char_count] == '/')
			slash_count++;
		char_count++;
	}
	char_count = 0;
	if (slash_count <= 1)
		return ;
	while (slash_count)
	{
		if (slash_count - flag == 0)
			break;
		if (s[char_count] == '/')
			slash_count--;
		char_count++;
	}
	while (i < char_count)
	{
		cut[i] = s[i];
		i++;
	}
	cut[i] = '\0';
	if (chdir(cut) == -1)
	{
		printf("chdir failed\n");
		exit (1);
	}
}

void	exec(t_node *node, t_data *data)
{
	if (node->node_type == PIPE)
		piping(node, data);
	else if (node->node_type == REDINPT)
		input_redirect(node, data);
	else if (node->node_type == REDOUT)
		output_redirect(node, data);
	else if (node->node_type == REDAPPND)
		output_redirect_append(node, data);
	else if (node->node_type == HEREDOC)
		heredoc(node, data);
	else if (node->node_type == EXEC)
		execution(node, data);
}

bool	check_exit_syntax(char *cmd)
{
	int	i;
	int	operator_count;

	i = 0;
	operator_count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '-' || cmd[i] == '+')
		{
			operator_count++;
			if (operator_count > 1)
				return (false);
		}
		else if (cmd[i] == '\'' || cmd[i] == '"')
			return (false);
		else if (!ft_isdigit(cmd[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	look_4_exit(t_node *node, t_data *data)
{
	if (node->node_type == EXEC && node->command[0] != NULL &&
		ft_strncmp(node->command[0], "exit", 5) == 0)
	{
		if (node->command[1] == NULL)
		{
			free_everything(data);
			printf("exit\n");
			exit (0);
		}
		else if (node->command[1] && node->command[2] == NULL)
		{
			if (!check_exit_syntax(node->command[1]))
			{
				fprintf(stderr, "minishell: exit: %s: numeric argument required\n", node->command[1]);
				free_everything(data);
				exit (255);
			}
			exit (ft_atoi(node->command[1]));
		}
		else if (node->command[1] && node->command[2])
		{
			if (!check_exit_syntax(node->command[1]))
			{
				fprintf(stderr, "minishell: exit: %s: numeric argument required\n", node->command[1]);
				free_everything(data);
				exit (255);
			}
			else
			{
				printf("exit\n");
				fprintf(stderr, "minishell: exit: too many arguments\n");
			}
			return (1);
		}
	}
	return (0);
}

int	look_4_buildins(t_node *node, t_data *data)
{
	int	cd_value;
	int	ex_value;

	if (look_4_exit(node, data))
		return (-1);
	if (look_4_unset(node, data))
		return (1);
	ex_value = look_4_export(node ,data);
	if (ex_value)
		return (ex_value);
	cd_value = look_4_cd(node, data);
	if (cd_value)
		return (cd_value);
	return (0);
}

int	pre_exec(t_node *node, t_data *data)
{
	pid_t	pid;
	int		wpidstatus;
	int		r_value;
	
	if (node == NULL)
		return (0);
	r_value = look_4_buildins(node, data);
	if (r_value == 1)
		return (0);
	if (r_value == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
	{
		signal(SIGINT, sig_child_int);
		signal(SIGQUIT, sig_child_quit);
		exec(node, data);
	}
	waitpid(pid, &wpidstatus, 0);
	if (WIFEXITED(wpidstatus))
		return (WEXITSTATUS(wpidstatus));
	if (WIFSIGNALED(wpidstatus))
	{
		if (128 + WTERMSIG(wpidstatus) == 131)
			write (2, "Quit: 3", 7);
		write(2, "\n", 1);
		return (128 + WTERMSIG(wpidstatus));
	}
	return (86);
}
