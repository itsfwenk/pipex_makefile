/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:36:22 by fli               #+#    #+#             */
/*   Updated: 2024/06/28 11:46:23 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

/*#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int	nb_l;
	int	fd;
	char *gnl;

	printf("BUFFER SIZE = %d\n", BUFFER_SIZE);
	gnl = NULL;
	fd = open("testfile", O_RDONLY);
	if (fd == -1)
			printf("Cannot read file.\n");
	nb_l = 0;
	while (nb_l < 3)
	{

		printf("GNL OUTPUT :\n");
		gnl = get_next_line(fd);
		if (gnl == NULL)
			printf("GNL EST NULL\n");
		//gnl ? printf("%s\n", gnl) : printf("gnl est vide\n");
		else
		{
			printf("%s", gnl);
			free(gnl);
		}
		nb_l++;
	}
}*/
