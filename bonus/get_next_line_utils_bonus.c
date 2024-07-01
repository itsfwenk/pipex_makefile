/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:56:56 by fli               #+#    #+#             */
/*   Updated: 2024/07/01 16:42:52 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

t_gnl	*ft_lstnew_gnl(int fd, t_gnl **init)
{
	int		read_return;
	t_gnl	*new;

	new = malloc(sizeof(t_gnl));
	if (new == NULL)
		return (NULL);
	read_return = read(fd, new->s, BUFFER_SIZE);
	if (read_return < 0 || (read_return == 0 && !*init))
	{
		free(new);
		return (NULL);
	}
	(new->s)[read_return] = '\0';
	new->min = 0;
	new->max = read_return;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_gnl(t_gnl **lst, t_gnl *new)
{
	t_gnl	*last;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last != NULL)
	{
		if ((last->next) == NULL)
		{
			last->next = new;
			return ;
		}
		last = last->next;
	}
}

char	*ft_strdup_gnl(t_gnl **init, char **gnl)
{
	int		j;
	t_gnl	*pos;

	*gnl = malloc((1 + count_char_gnl(init)) * sizeof(char));
	if (*gnl == NULL)
		return (NULL);
	j = 0;
	pos = *init;
	while (pos && pos->min <= pos->max)
	{
		if ((pos->s)[pos->min] == '\0')
		{
			ft_lstdelone_gnl(init);
			pos = *init;
			continue ;
		}
		if ((pos->s)[pos->min] == '\n')
		{
			(*gnl)[j++] = (pos->s)[(pos->min)++];
			break ;
		}
		(*gnl)[j++] = (pos->s)[(pos->min)++];
	}
	(*gnl)[j] = '\0';
	return (*gnl);
}

void	ft_lstclear_gnl(t_gnl **lst)
{
	t_gnl	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
}

void	ft_lstdelone_gnl(t_gnl **lst)
{
	t_gnl	*temp;

	if (!lst)
		return ;
	temp = (*lst)->next;
	free(*lst);
	*lst = temp;
}
