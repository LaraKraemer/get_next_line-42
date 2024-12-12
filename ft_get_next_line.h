/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkramer <lkramer@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:10:03 by lkramer           #+#    #+#             */
/*   Updated: 2024/12/11 15:43:52 by lkramer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			buf[BUFFER_SIZE + 1];
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
char	*ft_strchr(char *s, char c);
size_t	ft_strsize(const char *str);
size_t	ft_lststring_len(t_list *lst);
void	*ft_lstclear(t_list *lst);

#endif

/* typedef struct s_list
{
	int				fd;
	char			*buf;
	struct s_list	*next;
}	t_list;
char	*get_next_line(int fd);
size_t	ft_strsize(const char *s);
t_list	*ft_lstnew(int fd);
void	ft_lstclear(t_list **lst, int fd);
char	*ft_strchr(const char *s, int c);
int		ft_create_newnode_move_tonext(t_list **lst, t_list **head, int fd);
t_list	*ft_nl_newnode(t_list *lst, char *nl);
char	*get_line_from_buf(t_list *head, char *nl, ssize_t red_lines);
void	ft_check(int fd, char **nl, t_list **head, ssize_t *red_lines);
 */