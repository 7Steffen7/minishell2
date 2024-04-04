/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:24:02 by aweissha          #+#    #+#             */
/*   Updated: 2024/04/04 14:48:37 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static int	search_path(char **env)
// {
// 	int	i;

// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		if (ft_strnstr(env[i], "PATH", ft_strlen(env[i])) != NULL)
// 			break ;
// 		i++;
// 	}
// 	return (i);
// }

// char	*get_path(char *str, char **env)
// {
// 	char	**path_array;
// 	char	*path1;
// 	char	*path2;
// 	int		i;

// 	path_array = ft_split(&env[search_path(env)][5], ':');
// 	i = 0;
// 	while (path_array[i] != NULL && str != NULL)
// 	{
// 		path1 = ft_strjoin(path_array[i], "/");
// 		path2 = ft_strjoin(path1, str);
// 		free(path1);
// 		if (access(path2, X_OK) == 0)
// 		{
// 			ft_free_array(path_array);
// 			return (path2);
// 		}
// 		else
// 		{
// 			free(path2);
// 			i++;
// 		}
// 	}
// 	ft_free_array(path_array);
// 	return (NULL);
// }

// int	is_comm(char *str, t_data *data)
// {
// 	if (get_path(str, data->env) == NULL)
// 		return (0);
// 	return (1);
// }

type	tok_type(char *token_str)
{
	if (ft_strcmp(token_str, "<") == 0
		|| ft_strcmp(token_str, ">") == 0
		|| ft_strcmp(token_str, ">>") == 0
		|| ft_strcmp(token_str, "<<") == 0)
		return (REDIR);
	else if (ft_strcmp(token_str, "|") == 0)
		return (PIPE);
	else
		return (WORD);
}

// char	*ft_strtok_mod(char *str, const char *sep)
// {
// 	static char	*position;
// 	char		*token_start;

// 	if (str == NULL && position == NULL)
// 		return (NULL);
// 	if (str != NULL)
// 		position = str;
// 	while (ft_strchr(sep, *position) != NULL && *position != '\0')
// 		position++;
// 	if (*position == '\0')
// 	{
// 		position = NULL;
// 		return (NULL);
// 	}
// 	token_start = position;
// 	while ((ft_strchr(sep, *position) == NULL && *position != '\0')
// 		|| (in_quotes(token_start, position) == 1 && *position != '\0'))
// 		position++;
// 	if (*position != '\0')
// 		*(position)++ = '\0';
// 	else
// 		position = NULL;
// 	return (token_start);
// }

// void	lexer(char *input, t_data *data)
// {
// 	char	*token_str;

// 	token_str = ft_strtok_mod(input);
// 	while (token_str != NULL)
// 	{
// 		ft_tokadd_back(&data->token_list, ft_toknew(token_str, tok_type(token_str)));
// 		token_str = ft_strtok_mod(NULL);
// 	}
// }

type classify_char(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (REDIR);
	else if (c == '>')
		return (REDIR);
	else if (isspace(c))
		return (TOKEN_SPACE);
	return (WORD);
}

void	add_token(t_token **token_list, char *str, char *str_start)
{
	type	token_type;
	int		i;

	i = 0;
	token_type = classify_char(*str);
	while ((classify_char(str[i]) == token_type && str[i] != '\0')
		|| (in_quotes(str_start, &str[i]) == 1 && str[i] != '\0'))
		i++;
	// printf("number counted\n");
	ft_tokadd_back(token_list, ft_toknew(strndup(str, i), token_type));
	// printf("token added\n");
}

void	lexer(char *input, t_data *data)
{
	type	token_type;
	char	*input_start;

	input_start = input;
	while (*input != '\0')
	{
		while (classify_char(*input) == TOKEN_SPACE && *input != '\0')
			input++;
		if (*input != '\0')
			add_token(&data->token_list, input, input_start);
		token_type = classify_char(*input);
		while ((classify_char(*input) == token_type && *input != '\0')
			|| (in_quotes(input_start, input) == 1 && *input != '\0'))
			input++;
	}
}
