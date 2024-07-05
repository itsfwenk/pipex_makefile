/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd1_manager_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:56:56 by fli               #+#    #+#             */
/*   Updated: 2024/07/05 13:16:29 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	cmd1_child(int *cmd_i, t_pids	**pid_list, char **argv, char **envp)
{
	int		cmd1_fdr;
	pid_t	pid1;
	t_pids	*new_nod;

	new_nod = ft_lstnew_pipex((*cmd_i)++);
	if (new_nod == NULL)
		return (-1);
	ft_lstadd_back_pipex(pid_list, new_nod);
	check_heredoc(argv, new_nod);
	if (pipe((new_nod)->pipefd) == -1)
		fail_cleaner(argv, pid_list);
	pid1 = fork();
	if (pid1 == -1)
		fail_cleaner(argv, pid_list);
	if (pid1 == 0)
	{
		cmd1_fdr = cmd1_fd_manager(argv, new_nod);
		if (cmd1_fdr == 2 || cmd1_fdr == 3)
			return (cmd1_fdr);
		cmd1_exec(new_nod->cmd_i, argv, envp, new_nod);
	}
	if (dup2(new_nod->pipefd[0], STDIN_FILENO) == -1)
		return (close_pipe(new_nod->pipefd), -1);
	new_nod->p_id = pid1;
	return (close_pipe(new_nod->pipefd), new_nod->status);
}

static void	cmd1_exec_part2(char **cmd1, char **envp, t_pids	*new_nod)
{
	char	*cmd1_path;

	cmd1_path = get_pathname(envp, cmd1[0]);
	if (cmd1_path == NULL)
	{
		free_split(cmd1);
		free(new_nod);
		exit(-1);
	}
	if (cmd_exec(cmd1, cmd1_path, envp) == -1)
	{
		free_split(cmd1);
		free(cmd1_path);
		free(new_nod);
		exit(EXIT_FAILURE);
	}
}

int	cmd1_exec(int cmd_i, char **argv, char **envp, t_pids	*new_nod)
{
	char	**cmd1;

	if (argv[cmd_i][0] == '\0')
	{
		free(new_nod);
		exit(5);
	}
	cmd1 = ft_split(argv[cmd_i], ' ');
	if (cmd1 == NULL)
	{
		free(new_nod);
		exit(EXIT_FAILURE);
	}
	cmd1_exec_part2(cmd1, envp, new_nod);
	return (0);
}
