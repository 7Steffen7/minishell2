/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:13:50 by sparth            #+#    #+#             */
/*   Updated: 2023/11/23 21:02:10 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_listg	*ft_lstlast_clean(t_listg *lst, int check)
{
	t_listg	*temp;

	if (check == 1)
	{
		if (!lst)
			return (NULL);
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	if (check == 2)
	{
		temp = lst;
		while (lst)
		{
			temp = (lst)->next;
			free((lst)->buffstack);
			free(lst);
			lst = temp;
		}
		lst = NULL;
	}
	return (NULL);
}

void	ft_lstclean(t_listg **lst, t_listg *replace, char *leftovers)
{
	t_listg	*temp;

	temp = *lst;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->buffstack);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	if (replace->buffstack[0])
		*lst = replace;
	else
	{
		free(leftovers);
		free(replace);
	}
}

bool	lstchr(t_listg *lst, char c)
{
	int	i;

	while (lst)
	{
		i = 0;
		while (lst->buffstack[i] && i < BUFFER_SIZE)
		{
			if (lst->buffstack[i] == c)
				return (true);
			i++;
		}
		lst = lst->next;
	}
	return (false);
}

int	linecount(t_listg *lst)
{
	int	i;
	int	count;

	count = 0;
	while (lst)
	{
		i = 0;
		while (lst->buffstack[i])
		{
			if (lst->buffstack[i++] == '\n')
				return (++count);
			count++;
		}
		lst = lst->next;
	}
	return (count);
}

void	remainings(t_listg **lst)
{
	t_listg	*replace;
	t_listg	*last_node;
	char	*leftovers;
	int		i;
	int		j;

	i = 0;
	j = 0;
	last_node = ft_lstlast_clean(*lst, 1);
	leftovers = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	replace = (t_listg *)malloc(sizeof(t_listg));
	if (!replace || !leftovers)
	{
		ft_lstlast_clean(*lst, 2);
		free(leftovers);
		return ;
	}
	while (last_node->buffstack[i] != '\n' && last_node->buffstack[i] != '\0')
		i++;
	while (last_node->buffstack[i] && last_node->buffstack[++i])
		leftovers[j++] = last_node->buffstack[i];
	leftovers[j] = '\0';
	replace->buffstack = leftovers;
	replace->next = NULL;
	ft_lstclean(lst, replace, leftovers);
}
