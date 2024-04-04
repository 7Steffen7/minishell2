/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:13:29 by sparth            #+#    #+#             */
/*   Updated: 2023/12/09 16:31:20 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	create_buffer_list(t_listg **lst, char *buffer)
{
	t_listg	*new_node;

	new_node = (t_listg *)malloc(sizeof(t_listg));
	if (!new_node)
	{
		free(buffer);
		buffer = NULL;
		return ;
	}
	if (*lst)
		ft_lstlast_clean(*lst, 1)->next = new_node;
	else
		*lst = new_node;
	new_node->buffstack = buffer;
	new_node->next = NULL;
}

void	file_read(t_listg **header, int fd)
{
	int		byte_read;
	char	*buffer;

	while (!(lstchr(*header, '\n')))
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return ;
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (!byte_read)
		{
			free(buffer);
			return ;
		}
		buffer[byte_read] = '\0';
		create_buffer_list(header, buffer);
	}
}

void	lst_to_line(t_listg *lst, char *line)
{
	int		i;
	int		k;

	k = 0;
	while (lst)
	{
		i = 0;
		while (lst->buffstack[i])
		{
			if (lst->buffstack[i] == '\n')
			{
				line[k++] = '\n';
				line[k] = '\0';
				return ;
			}
			line[k++] = lst->buffstack[i++];
		}
		lst = lst->next;
	}
	line[k] = '\0';
}

char	*create_line(t_listg *lst)
{
	int		line_len;
	char	*line;

	line_len = linecount(lst);
	line = (char *)malloc((line_len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	lst_to_line(lst, line);
	return (line);
}

char	*get_next_line(int fd)
{
	static t_listg	*header;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
		ft_lstlast_clean(header, 2);
		header = NULL;
		return (NULL);
	}
	file_read(&header, fd);
	if (!header)
	{
		ft_lstlast_clean(header, 2);
		header = NULL;
		return (NULL);
	}
	line = create_line(header);
	remainings(&header);
	return (line);
}

// int main() 
// {
// int fd = open("file.txt", O_RDONLY);
// if (fd == -1) {
//     write(1,"Failed to open the file",23);
//     return 1;
// }
// char *line;
// while (1)
// {
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	if (line == NULL)
// 		break;
// 	free(line);
//}
//     return 0;
// }
