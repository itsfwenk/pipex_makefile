/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_manager_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 14:22:36 by fli               #+#    #+#             */
/*   Updated: 2024/07/04 16:14:05 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

t_pids	*ft_lstnew_pipex(int cmd_i)
{
	t_pids	*n;

	n = malloc(sizeof(t_pids));
	if (n == NULL)
		return (NULL);
	n->cmd_i = cmd_i;
	n->here_doc = 0;
	n->status = 0;
	n->next = NULL;
	n->p_id = -1;
	return (n);
}

void	ft_lstadd_back_pipex(t_pids **lst, t_pids *n)
{
	t_pids	*last;

	if (!lst || !n)
		return ;
	if (!(*lst))
	{
		*lst = n;
		return ;
	}
	last = *lst;
	while (last != NULL)
	{
		if ((last->next) == NULL)
		{
			last->next = n;
			return ;
		}
		last = last->next;
	}
}

void	ft_lstclear_pipex(t_pids **lst)
{
	t_pids	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
	return ;
}

void	wait_pids(t_pids **lst, char **argv)
{
	t_pids	*temp;

	if (!lst || !*lst)
		return ;
	temp = *lst;
	while (temp != NULL)
	{
		waitpid(temp->p_id, &(temp->status), 0);
		if (WEXITSTATUS(temp->status) == 255)
		{
			write(2, argv[temp->cmd_i], ft_strlen(argv[temp->cmd_i]));
			write(2, ": command not found\n", ft_strlen(": command not found\n"));
		}
		err_infile(argv, temp->status);
		if (WEXITSTATUS(temp->status) == 4)
		{
			write(2, argv[1 + temp->cmd_i], ft_strlen(argv[1 + temp->cmd_i]));
			write(2, ": Permission denied\n", ft_strlen(": Permission denied\n"));
		}
		cmd_null(temp->status);
		temp = temp->next;
	}
}

void	err_infile(char **argv, int status)
{
	if (WEXITSTATUS(status) == 2)
	{
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": Permission denied\n", ft_strlen(": Permission denied\n"));
	}
	if (WEXITSTATUS(status) == 3 && ft_strncmp_pipex(argv[1], "here_doc", ft_strlen(argv[1])) != 0)
	{
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": No such file or directory\n", ft_strlen(": No such file or directory\n"));
	}
}

void	cmd_null(int status)
{
	if (WEXITSTATUS(status) == 5)
	{
		write(2, "Command '' not found, but can be installed\n",
				ft_strlen("Command '' not found, but can be installed\n"));
	}
}
