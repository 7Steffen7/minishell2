/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:42:48 by aweissha          #+#    #+#             */
/*   Updated: 2024/03/28 14:46:42 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// function should return the top of the parse tree
void	parse_input(char *input, t_data *data)
{
	// check_syntax(input);
	lexer(input, data);
	// expander(data);
	data->parse_tree = parse_pipe(data->token_list);
}

/** function should execute all commands, by starting at the top of the parse tree 
 * and calling itself whenever following a fork to another node **/
void	run_commands(t_node *node)
{
	// add the correct conditions for each type of node	
	// call itself, whenever its not the bottom of the parse tree (which is an EXEC type node)
	// how to implement these function: video shell program explained
	if (node->node_type == EXEC)
		run_exec(node);
	else if (node->node_type == PIPE)
		run_pipe(node);
	else if (node->node_type == BUILDIN)
		run_buildin(node);
	else if (node->node_type == REDIR)
		run_redir(node);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_data	*data;

	data = init_data(argc, argv, env);
	while (1)
	{
		input = readline("Minishell $> ");
		// If input is NULL, user entered EOF (Ctrl+D)
		if (input == NULL)
		{
			printf("\n");
			break ;
		}
		// else if (ft_strcmp(input, "exit") == 0)
		// {
		// 	free(input);
		// 	exit(0);
		// }
		
		// Check for cd command and chdir in the parent process if needed
	
		// If input is empty, prompt again
		else if (ft_strlen(input) == 0)
			free(input);
		else
		{
			if (ft_fork() == 0)
			{
				parse_input(input, data);
				run_commands(data->parse_tree);
			}
			wait(NULL);
			free_parse_tree(data); // free nodes and command of exec nodes, infile, outfile ... from top to bottom of parse tree
			free(input);
		}
	}
	free(data);
}


// Plan:
/*

- checker for checking if every opened quote is closed again. Only then does my expander make sense.
- implement the configuration of the env_list at the beginning of the parent process. Also add the vriable ? for the last exit code.
- replace isspace funtion in lexer
- replace strndup with ft_strndup in lexer
- syntax checker: check right amount of quotes, every opened quote is closed.
- implement quotes '' and ""
- cd -



*/