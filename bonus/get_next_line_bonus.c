/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:36:22 by fli               #+#    #+#             */
/*   Updated: 2024/07/04 10:35:44 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*get_next_line(int fd)
{
	char			*gnl;
	static t_gnl	*init = NULL;
	t_gnl			*new;

	if (fd == -1)
		return (ft_lstclear_gnl(&init), NULL);
	new = NULL;
	while (end_line(&init) != -1)
	{
		new = ft_lstnew_gnl(fd, &init);
		if (new == NULL)
		{
			ft_lstclear_gnl(&init);
			return (NULL);
		}
		ft_lstadd_back_gnl(&init, new);
	}
	gnl = ft_strdup_gnl(&init, &gnl);
	if (gnl == NULL)
	{
		ft_lstclear_gnl(&init);
		return (NULL);
	}
	return (gnl);
}

int	end_line(t_gnl **current)
{
	int		i;
	t_gnl	*pos;

	if (!*current)
		return (0);
	if (((*current)->s)[(*current)->min] == '\0')
		ft_lstdelone_gnl(current);
	pos = *current;
	while (pos != NULL)
	{
		i = pos->min;
		while ((pos->s)[i] != '\0')
		{
			if ((pos->s)[i] == '\n' || pos->max != BUFFER_SIZE
				|| (pos->next && ((pos->next)->s)[0] == '\0'))
				return (-1);
			i++;
		}
		pos = pos->next;
	}
	return (1);
}

int	count_char_gnl(t_gnl **lst)
{
	int		i;
	int		count;
	t_gnl	*pos;

	pos = *lst;
	i = pos->min;
	count = 0;
	while (pos)
	{
		while ((pos->s)[i] != '\0')
		{
			if ((pos->s)[i] == '\n')
				return (count + 1);
			count++;
			i++;
		}
		i = 0;
		pos = pos->next;
	}
	return (count);
}
