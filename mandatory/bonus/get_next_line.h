/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 16:41:56 by fli               #+#    #+#             */
/*   Updated: 2024/06/27 14:56:22 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

typedef struct s_gnl
{
	int				min;
	int				max;
	char			s[BUFFER_SIZE + 1];
	struct s_gnl	*next;
}	t_gnl;

char	*get_next_line(int fd);

int		end_line(t_gnl **current);

int		count_char_gnl(t_gnl **lst);

t_gnl	*ft_lstnew_gnl(int fd, t_gnl **init);

void	ft_lstadd_back_gnl(t_gnl **lst, t_gnl *new);

char	*ft_strdup_gnl(t_gnl **init, char **gnl);

void	ft_lstclear_gnl(t_gnl **lst);

void	ft_lstdelone_gnl(t_gnl **lst);

#endif
