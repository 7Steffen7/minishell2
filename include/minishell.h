/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:44:13 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/16 01:03:51 by sparth           ###   ########.fr       */
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
#include <limits.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>


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


// buildins.c
void	env_buildin(t_data *data);
void	export(char *variable, t_data *data);
void	unset(char *variable, t_data *data);

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
int		strlen_expanded(char *str, t_data *data);
void	create_expanded_str(char *exp_str, char *orig_str, t_data *data);
char	*expand_str(t_token *token, t_data *data);
void	remove_empty_tokens(t_data *data);
void	expander(t_data *data);

// expander_utils.c
int		add_strlen(char *str, int *d_quote_open, int *s_quote_open, t_data *data);
int		add_str(char *str, int *s_quote_open);
void	add_exit_code(char *expanded_str, char *exit_code);
void	copy_over(char **p_expanded_str, char *original_str, t_data *data);

// expander_utils2.c
t_env	*find_var_expander(char *str, t_data *data);
int		var_length(char *str);
int		edit_quote_counters(char *str, int *s_quote_open, int *d_quote_open);
int		count_digits(int n);

// free.c
void	free_token(t_token	*token);
void	free_env(t_env *env_node);
void	free_str_array(char **array);
void	free_node(t_node *node);

// free2.c
void	free_token_list(t_token *token_list);
void	free_parse_tree(t_node *node);
void	free_env_list(t_env *env_list);
void	free_everything(t_data *data);

// init.c
t_node	*init_node(type node_type);
t_data	*init_data(int argc, char **argv, char **env);

// lexer.c
type	tok_type(char *token_str);
type 	classify_char(char c);
int		add_token(t_token **token_list, char *str);
void	lexer(char *input, t_data *data);

// parse_utils.c
void	update_token_list(t_token **token_list);
void	config_redir_node(t_token *redir_token, t_node *redir_node);
t_token	*find_token(t_token	*token_list, type token_type);

// parser.c
t_node	*parse_exec(t_token *token_list);
t_node	*parse_redir(t_token *token_list);
t_node	*parse_pipe(t_token *token_list);

// syntax_check.c
int		check_operators(t_token *token_list);
int		check_quotes(t_token *token_list);
int		syntax_check(t_data *data);

// syntax_check_utils.c
int		pipe_syntax_check(t_token *token_list);
int		redir_syntax_check(t_token *token_list);
int		quotes_wrong(char *str);

// token_list_utils.c
int		toklist_size(t_token *token_list);
void	toklist_clear(t_token **token_list);
t_token	*ft_toknew(char *token_str, type token_type);
t_token	*ft_toklast(t_token *token_list);
void	ft_tokadd_back(t_token **token_list, t_token *new);

// utils.c
int		ft_fork(void);
t_env	*find_var(char *var_name, t_data *data);
void	set_quote_flags(char *str, int *s_quote_open, int *d_quote_open);
int		ft_isspace(char c);

//exec.c
int		pre_exec(t_node *node, t_data *data);
void	exec(t_node *node, t_data *data);
void	set_quote_flags(char *str, int *s_quote_open, int *d_quote_open); //check if still there
void	string_cut(char *s, int flag);

//exec_path.c
void	*free_null(char *del);
void	path_clean(t_path_prep check, int status);
t_path_prep	init_struct(void);
char	*cmd_cut(char *cmd);
char	*path_check2(char *cmd, t_path_prep check);
char	*path_check(char *cmd, char *path);

//exec_redir.c
void	input_redirect(t_node *node, t_data *data);
void	heredoc(t_node *node, t_data *data);
void	output_redirect(t_node *node, t_data *data);
void	output_redirect_append(t_node *node, t_data *data);

//signals.c
void	sig_action(int sig);
void	pre_rl_signals(void);
void	sig_child_int(int sig);
void	sig_child_quit(int sig);

//exec_env_buildins.c
void	env(t_data *data);
int		look_4_unset(t_node *node, t_data *data);
bool	export_check(char *arg);
int		look_4_export(t_node *node, t_data *data);

//exec_print_buildins.c
bool	check_n_option(char *option, char *echo_check);
void	echo(t_node *node, t_data *data);
void	pwd(t_data *data);

//exec_cd_buildin.c
void	change_pwds(t_data *data, bool flag);
void	prep_dir_change(t_data *data, int flag, char *path);
bool	switch_between_dir(t_data *data);
int		path_change(char *cmd, t_data *data);
int		look_4_cd(t_node *node, t_data *data);


#endif