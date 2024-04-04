/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:52:02 by sparth            #+#    #+#             */
/*   Updated: 2024/04/03 17:41:01 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*free_null(char *del)
{
	free(del);
	return (NULL);
}

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

void	input_redirect(t_node *node)
{
	int	fd_in;

	fd_in = open(node->infile, O_RDONLY);
	if (fd_in == -1)
	{
		printf("error opening infile\n");
		exit(1);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit (1);
	if (close(fd_in) == -1)
		exit (1);
}

void	heredoc(t_node *node)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		exit (2);
	while (1)
	{
		write(1, "here_doc ", 9);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(node->limiter, line, ft_strlen(node->limiter)) == 0
			&& ft_strlen(node->limiter) + 1 == ft_strlen(line))
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
		exit (1);
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
		exit (1);
}

void	output_redirect(t_node *node)
{
	int fd_out;
	
	fd_out = open(node->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		printf("error opening outfile\n");
		exit (1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit(1);
	if (close(fd_out) == -1)
		exit (1);
}

void	output_redirect_append(t_node *node)
{
	int fd_out;
	
	fd_out = open(node->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
	{
		printf("error opening outfile\n");
		exit (1);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit(1);
	if (close(fd_out) == -1)
		exit (1);
}

void piping(t_node *node)
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
			exec(node->left);
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
			exec(node->right);
		}
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
			exit (1);
		waitpid(pid_left, NULL, 0);
		waitpid(pid_right, &wpidstatus, 0);
		// fprintf(stderr, "checkkkk\n");
		if (WIFEXITED(wpidstatus))
		{
			// usleep only 4 printf
			printf("exit status: %d\n", WEXITSTATUS(wpidstatus));
			usleep (20);
		}
}

void	path_error_message(char *error)
{
	if (access(cmd_cut(error), X_OK) && access(cmd_cut(error), R_OK) == 0)
		fprintf(stderr, "%s%s: %s\n", "minishell: ", cmd_cut(error), strerror(13));
	else if (strncmp(error, "./", 2) == 0)
		fprintf(stderr, "%s%s: %s\n", "minishell: ", cmd_cut(error), strerror(2));
	else
		fprintf(stderr, "%s%s: %s\n", "minishell: ", cmd_cut(error), "command not found");
}

void	execution(t_node *node)
{
	char	*path;
	// char	**cmd;

	path = path_check(node->command[0], getenv("PATH="));
	if (!path)
		path_error_message(node->command[0]);
	execve(path, node->command, NULL);
	// fprintf(stderr, "execve failed !\n");
	if (access((path), X_OK) && access((path), W_OK) == 0)
		exit (126);
	exit(127);
	
}

void	exec(t_node *node)
{
	// node->pipe_end = 2;
	if (node->node_type == PIPE)
		piping(node);
	else if (node->node_type == REDINPT)
	{
		input_redirect(node);
		exec(node->next);
	}
	else if (node->node_type == REDOUT)
	{
		output_redirect(node);
		exec(node->next);
	}
	else if (node->node_type == REDAPPND)
	{
		output_redirect_append(node);
		exec(node->next);
	}
	else if (node->node_type == HEREDOC)
	{
		heredoc(node);
		exec(node->next);
	}
	else if (node->node_type == EXEC)
		execution(node);
}

void	pre_exec(t_node *node)
{
	pid_t	pid;
	int		wpidstatus;
	
	if (node->node_type == PIPE)
		exec(node);
	else
	{
		if (node->node_type == EXEC && 
			ft_strncmp(node->command[0], "exit", ft_strlen(node->command[0]) + 1) == 0
			&& node->command[1] == NULL)
		{
			//free everything
			printf("exit\n");
			exit (0);
		}
		pid = fork();
		if (pid == -1)
			exit (1);
		if (pid == 0)
			exec(node);
		else
			waitpid(pid, &wpidstatus, 0);
	}
}