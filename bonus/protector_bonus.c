/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protector_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:55:42 by fli               #+#    #+#             */
/*   Updated: 2024/07/05 14:09:14 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	fail_cleaner(char **argv, t_pids **pid_list)
{
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		del_heredoc(*pid_list);
	ft_lstclear_pipex(pid_list);
	exit(EXIT_FAILURE);
}

void	close_and_clear(int pipe[2], t_pids **pid_list)
{
	close_pipe(pipe);
	ft_lstclear_pipex(pid_list);
}
