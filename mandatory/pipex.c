/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 10:12:51 by fli               #+#    #+#             */
/*   Updated: 2024/07/05 14:02:24 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	cmd_exec(char **cmd, char *cmd_path, char **envp)
{
	if (execve(cmd_path, cmd, envp) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		cmd_i;
	int		cmd1;
	t_pids	*pid_list;

	if (argc != 5)
		return (0);
	pid_list = NULL;
	cmd_i = 2;
	cmd1 = cmd1_child(&cmd_i, &pid_list, argv, envp);
	if (cmd1 == 2 || cmd1 == 3)
		exit(cmd1);
	if (cmd2_child(cmd_i, &pid_list, argv, envp) == -1)
		exit(EXIT_FAILURE);
	wait_pids(&pid_list, argv);
	ft_lstclear_pipex(&pid_list);
}
