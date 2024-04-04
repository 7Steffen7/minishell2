/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:52:11 by sparth            #+#    #+#             */
/*   Updated: 2024/01/16 17:46:10 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 30
# endif

typedef struct s_listg
{
	char			*buffstack;
	struct s_listg	*next;
}t_listg;

char	*get_next_line(int fd);
void	remainings(t_listg **lst);
void	ft_lstclean(t_listg **lst, t_listg *replace, char *leftovers);
char	*create_line(t_listg *lst);
int		linecount(t_listg *lst);
void	lst_to_line(t_listg *lst, char *line);
void	file_read(t_listg **header, int fd);
bool	lstchr(t_listg *lst, char c);
void	create_buffer_list(t_listg **lst, char *buffer);
t_listg	*ft_lstlast_clean(t_listg *lst, int check);

#endif