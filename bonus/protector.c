/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:55:42 by fli               #+#    #+#             */
/*   Updated: 2024/07/04 18:11:18 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	pipe_fail(char **argv, t_pids **pid_list)
{
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)

	ft_lstclear_pipex(pid_list);
	exit(EXIT_FAILURE);
}
