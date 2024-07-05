/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:55:42 by fli               #+#    #+#             */
/*   Updated: 2024/07/05 14:03:45 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	fail_cleaner(t_pids **pid_list)
{
	ft_lstclear_pipex(pid_list);
	exit(EXIT_FAILURE);
}

void	close_and_clear(int pipe[2], t_pids **pid_list)
{
	close_pipe(pipe);
	ft_lstclear_pipex(pid_list);
}
