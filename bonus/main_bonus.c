/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:02:34 by fli               #+#    #+#             */
/*   Updated: 2024/07/01 16:43:32 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	cmd_exec(char **cmd, char *cmd_path, char **envp)
{
	if (execve(cmd_path, (char *const*)cmd, (char *const *)envp) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		cmd_i;
	t_pids	*pid_list;

	if (argc < 5)
		return (0);
	pid_list = NULL;
	cmd_i = 2;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		if_here_doc(argv);
		cmd_i = 3;
	}
	if (cmd1_child(&cmd_i, &pid_list, argv, envp) == -1)
		exit(EXIT_FAILURE);
	while (cmd_i < (argc - 2))
	{
		if (cmd_middle_child(&cmd_i, &pid_list, argv, envp))
			exit(EXIT_FAILURE);
	}
	if (cmd2_child(cmd_i, &pid_list, argv, envp) == -1)
		exit(EXIT_FAILURE);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
		unlink("here_doc");
	wait_pids(&pid_list, argv);
	ft_lstclear_pipex(&pid_list);
}
