/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:21:20 by lkramer           #+#    #+#             */
/*   Updated: 2024/12/11 15:36:02 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_get_next_line.h"

char	*ft_strchr(char *s, char c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return (s);
		s++;
	}
	return (NULL);
}

size_t	ft_strsize(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	ft_lststring_len(t_list *lst)
{
	size_t	len;

	len = 0;
	while (lst != NULL)
	{
		len += ft_strsize(lst->buf);
		lst = lst->next;
	}
	return (len);
}

void	*ft_lstclear(t_list *lst)
{
	t_list	*temp;

	while (lst != NULL)
	{
		temp = (lst)->next;
		free(lst);
		lst = temp;
	}
	lst = NULL;
	return (NULL);
}


/* size_t	ft_strsize(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	const char	*str;
	char		cc;

	str = s;
	cc = (char) c;
	while (*str)
	{
		if (*str == cc)
			return ((char *)str);
		str++;
	}
	if (cc == '\0')
		return ((char *)str);
	return (0);
}

t_list	*ft_lstnew(int fd)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->fd = fd;
	new_node->buf = malloc(BUFFER_SIZE + 1);
	if (new_node->buf == NULL)
		return (free(new_node), NULL);
	new_node->buf[0] = '\0';
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstclear(t_list **lst, int fd)
{
	t_list *current = *lst;
	t_list *prev = NULL;
	t_list *temp;

	while (current)
	{
        if (current->fd == fd)
		{
            temp = current->next;
            free(current->buf);
            free(current);
            if (prev)
                prev->next = temp;
			else
                *lst = temp;
            current = temp;
		}
		else
		{
            prev = current;
            current = current->next;
		}
	}
} */