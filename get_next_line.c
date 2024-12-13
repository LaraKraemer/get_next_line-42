/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:21:17 by lkramer           #+#    #+#             */
/*   Updated: 2024/12/13 11:44:05 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_nodes_to_string(t_list *lst)
{
	size_t	string_len;
	size_t	i;
	size_t	k;
	t_list	*temp_lst;
	char	*string;

	temp_lst = lst;
	string_len = ft_lststring_len(lst);
	if (string_len <= 0)
		return (ft_lstclear(temp_lst), NULL);
	string = malloc(sizeof(*string) * (string_len + 1));
	if (!string)
		return (NULL);
	lst = temp_lst;
	i = 0;
	while (lst != NULL && i < string_len)
	{
		k = 0;
		while ((lst->buf)[k] != '\0')
			string[i++] = (lst->buf)[k++];
		lst = lst->next;
	}
	string[i] = '\0';
	ft_lstclear(temp_lst);
	return (string);
}

static t_list	*ft_node_after_nl(t_list *lst, char *nl)
{
	t_list			*new_node;
	unsigned int	i;

	if (!lst || !nl)
		return (NULL);
	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	i = 0;
	nl++;
	while (nl[i] != '\0')
	{
		(new_node->buf)[i] = nl[i];
		if (i == 0)
			nl[i] = '\0';
		i++;
	}
	(new_node->buf)[i] = '\0';
	return (new_node);
}

static int	ft_first_node_in_lst(t_list **lst, t_list **head)
{
	t_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
	{
		ft_lstclear(*head);
		return (0);
	}
	new_node->next = NULL;
	if (!*lst)
		*head = new_node;
	else
		(*lst)->next = new_node;
	*lst = new_node;
	return (1);
}

static void	ft_initializer_and_checker(char **nl, t_list **head,
								ssize_t *red, t_list *lst)
{
	*nl = NULL;
	*head = NULL;
	*red = 1;
	if (lst != NULL)
	{
		*head = lst;
		*nl = ft_strchr(lst->buf, '\n');
	}
}

char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	t_list			*head;
	char			*nl;
	ssize_t			red;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_initializer_and_checker(&nl, &head, &red, lst);
	while (nl == NULL && red > 0)
	{
		if (!ft_first_node_in_lst(&lst, &head))
			return (NULL);
		red = read(fd, lst->buf, BUFFER_SIZE);
		if (red < 0)
		{
			lst = NULL;
			return (ft_lstclear(head), NULL);
		}
		(lst->buf)[red] = '\0';
		nl = ft_strchr(lst->buf, '\n');
	}
	lst = ft_node_after_nl(lst, nl);
	return (ft_nodes_to_string(head));
}

/* 
t_list	*ft_nl_new_nodenode(t_list *lst, char *nl)
{
	t_list			*new_node;
	unsigned int	i;

	if (lst == NULL || nl == NULL)
		return (NULL);
	new_node = malloc(sizeof(*new_node));
	if (new_node == NULL)
		return (NULL);
	new_node->buf = malloc(BUFFER_SIZE + 1);
	if (new_node->buf == NULL)
		return (free(new_node), NULL);
	new_node->next = NULL;
	i = 0;
	nl++;
	while (nl[i] != '\0')
	{
		(new_node->buf)[i] = nl[i];
		if (i == 0)
			nl[i] = '\0';
		i++;
	}
	new_node->buf[i] = '\0';
	return (new_node);
}

int	ft_create_new_nodenode_move_tonext(t_list **lst, t_list **head, int fd)
{
	t_list	*current;

	if (*head == NULL)
	{
		*lst = ft_lstnew_node(fd);
		if (!*lst)
			return (0);
		*head = *lst;
		return (1);
	}
	current = *head;
	while (current->next)
		current = current->next;
	*lst = ft_lstnew_node(fd);
	if (!*lst)
		return (0);
	current->next = *lst;
	return (1);
}


char	*get_line_from_buf(t_list *head, char *nl, ssize_t red_lines)
{
	char	*line;
	size_t	string_len;
	size_t	i;

	if (!head || !head->buf)
		return (NULL);
	if (nl)
		string_len = nl - head->buf;
	else
		string_len = red_lines;
	line = (char *)malloc(string_len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < string_len)
	{
		line[i] = head->buf[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}


void	ft_check(int fd, char **nl, t_list **head, ssize_t *red_lines)
{
	t_list	*current;

	*nl = NULL;
	*red_lines = 1;

	current = *head;
	while (current)
	{
		if (current->fd == fd)
		{
			*head = current;
			*nl = ft_strchr(current->buf, '\n');
			return ;
		}
		current = current->next;
	}
	current = ft_lstnew_node(fd);
	if (!current)
		return ;
	current->next = *head;
	*head = current;
}


char	*get_next_line(int fd)
{
	static t_list	*lst = NULL;
	t_list			*head;
	ssize_t			red_lines;
	char			*nl;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_check(fd, &nl, &head, &red_lines);
	while (!nl && red_lines > 0)
	{
		red_lines = read(fd, head->buf,   BUFFER_SIZE);
		if (red_lines <= 0)
			return (ft_lstclear(&lst, fd), NULL);
		head->buf[red_lines] = '\0';
		nl = ft_strchr(head->buf, '\n');
	}
	line = get_line_from_buf(head, nl, red_lines);
	if (!line)
	{
		return (ft_lstclear(&lst, fd), NULL);
	}
	if (nl)
		lst = ft_nl_new_nodenode(head, nl);
	return (line);
} 
 */