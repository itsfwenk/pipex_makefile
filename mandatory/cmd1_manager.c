/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd1_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:56:56 by fli               #+#    #+#             */
/*   Updated: 2024/07/02 17:16:19 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	cmd1_child(int *cmd_i, t_pids	**pid_list, char **argv, char **envp)
{
	int		cmd1_fdr;
	pid_t	pid1;
	t_pids	*new_nod;

	// if (argv[*cmd_i][0] == '\0')
	// 	return (write(2, "Command '' not found\n", 22), -1);
	new_nod = ft_lstnew_pipex((*cmd_i)++);
	if (new_nod == NULL)
		return (ft_lstclear_pipex(pid_list), -1);
	ft_lstadd_back_pipex(pid_list, new_nod);
	if (pipe((new_nod)->pipefd) == -1)
		exit(EXIT_FAILURE);
	pid1 = fork();
	if (pid1 == 0)
	{
		cmd1_fdr = cmd1_fd_manager(argv, new_nod);
		if (cmd1_fdr == 2 || cmd1_fdr == 3)
			return (cmd1_fdr);
		if (cmd1_exec(new_nod->cmd_i, argv, envp) == -1)
			return (free(new_nod), -1);
	}
	if (dup2(new_nod->pipefd[0], STDIN_FILENO) == -1)
		return (close_pipe(new_nod->pipefd), -1);
	new_nod->p_id = pid1;
	return (close_pipe(new_nod->pipefd), new_nod->status);
}

int	cmd1_exec(int cmd_i, char **argv, char **envp)
{
	char	**cmd1;
	char	*cmd1_path;

	cmd1 = ft_split((const char *)argv[cmd_i], ' ');
	if (cmd1 == NULL)
		return (-1);
	cmd1_path = get_pathname(envp, cmd1[0]);
	if (cmd1_path == NULL)
	{
		free(cmd1);
		return (-1);
	}
	if (cmd_exec(cmd1, cmd1_path, envp) == -1)
	{
		free(cmd1);
		free(cmd1_path);
		exit(EXIT_FAILURE);
	}
	return (0);
}
