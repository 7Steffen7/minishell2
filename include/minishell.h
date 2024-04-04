/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:44:13 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/04 16:02:28 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../libft/libft.h"
#include <string.h>
#include "../libft/get_next_line.h"

typedef enum
{
	WORD,
	EXEC,
	BUILDIN,
	REDIR,
	REDINPT,
	REDOUT,
	REDAPPND,
	HEREDOC,
	PIPE,
	TOKEN_SPACE,
}	type;

typedef struct s_token	t_token;
typedef struct s_node	t_node;
typedef struct s_env	t_env;

typedef struct s_node
{
	// all types
	type	node_type;
	// exec type
	char	**command;
	// redir types
	char	*infile;
	char	*outfile;
	char	*limiter;
	t_node	*next;
	// pipe type
	t_node	*left;
	t_node	*right;
}	t_node;

typedef struct s_token
{
	type		token_type;
	char		*token_str;
	t_token		*next;
	t_token		*previous;
}	t_token;

typedef struct s_env
{
	char	*var_name;
	char	*var_str;
	t_env	*next;
}	t_env;

typedef struct s_data
{
	int		argc;
	char	**argv;
	char 	**env;
	t_token	*token_list;
	t_node	*parse_tree;
	t_env	*env_list;
	int		last_exit_code;
}	t_data;

typedef struct s_path_prep
{
	char	**directory;
	char	*cmd_prep;
	char	*pathcheck;
	char	*first_cmd;
	char	*paths;
}			t_path_prep;


// env_list_utils.c
t_env	*env_list_last(t_env *env_list);
t_env	*env_list_new(char *var_name, char *var_str);
void	env_list_add_back(t_env **env_list, t_env *new);

// env.c
char	*get_var_str(char *env_line);
char	*get_var_name(char *env_line);
void	create_env_list(t_data *data);

// error.c
void	ft_error(char *message, int code);

// expander.c
t_env	*find_var(char *str, int var_length, t_data *data);
int		var_length(char *str);
int		edit_quote_counters(char *str, int *s_quote_open, int *d_quote_open);
int		add_strlen(char *str, int *d_quote_open, int *s_quote_open, t_data *data);
int		add_str(char *str, int *s_quote_open);
int		strlen_expanded(char *str, t_data *data);
void	create_expanded_str(char *expanded_str, char *original_str, t_data *data);
char	*expand_str(t_token *token, t_data *data);
void	expander(t_data *data);

// free.c
void	free_token(t_token	*token);

// handle_quotes.c
int		quotes_left(char *start, char *position, char c);
int		quotes_right(char *start, char *position, char c);
int		in_quotes(char *start, char *position);

// init.c
t_node	*init_node(type node_type);
t_data	*init_data(int argc, char **argv, char **env);

// lexer.c
type	tok_type(char *token_str);
// char	*ft_strtok_mod(char *str, const char *sep);
void	lexer(char *input, t_data *data);

// parse_utils.c
void	update_token_list(t_token **token_list, t_token *redir_token);
void	config_redir_node(t_token *redir_token, t_node *redir_node);
t_token	*find_token(t_token	*token_list, type token_type);

// parser.c
t_node	*parse_exec(t_token *token_list);
t_node	*parse_redir(t_token *token_list);
t_node	*parse_pipe(t_token *token_list);

// token_list_utils.c
int		toklist_size(t_token *token_list);
void	toklist_clear(t_token **token_list);
t_token	*ft_toknew(char *token_str, type token_type);
t_token	*ft_toklast(t_token *token_list);
void	ft_tokadd_back(t_token **token_list, t_token *new);

// utils.c
int		ft_fork(void);

//exec.c
void	pre_exec(t_node *node);
void	exec(t_node *node);

#endif