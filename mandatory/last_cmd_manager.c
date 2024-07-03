/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:31:49 by fli               #+#    #+#             */
/*   Updated: 2024/07/03 16:20:36 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	cmd2_child(int cmd_i, t_pids	**pid_list, char **argv, char **envp)
{
	pid_t	pid2;
	t_pids	*new_nod;

	new_nod = ft_lstnew_pipex(cmd_i);
	if (new_nod == NULL)
		return (ft_lstclear_pipex(pid_list), -1);
	ft_lstadd_back_pipex(pid_list, new_nod);
	if (pipe((new_nod)->pipefd) == -1)
		exit(EXIT_FAILURE);
	pid2 = fork();
	if (pid2 == 0)
	{
		if (cmd2_fd_manager(cmd_i, argv, new_nod, pid_list) == -1)
			return (-1);
		if (cmd2_exec(cmd_i, argv, envp, pid_list) == -1)
			return (close_pipe(new_nod->pipefd), free(new_nod), -1);
	}
	close_pipe(new_nod->pipefd);
	new_nod->p_id = pid2;
	return (new_nod->status);
}

static void	exec_cmd2_fail(char **cmd2, char *cmd2_path, t_pids	**pid_list)
{
		free_split(cmd2);
		free(cmd2_path);
		ft_lstclear_pipex(pid_list);
}

int	cmd2_exec(int cmd_i, char **argv, char **envp, t_pids	**pid_list)
{
	char	**cmd2;
	char	*cmd2_path;

	if (argv[cmd_i][0] == '\0')
	{
		ft_lstclear_pipex(pid_list);
		exit(5);
	}
	cmd2 = ft_split((const char *)argv[cmd_i], ' ');
	if (cmd2 == NULL)
		return (-1);
	cmd2_path = get_pathname(envp, cmd2[0]);
	if (cmd2_path == NULL)
	{
		free_split(cmd2);
		ft_lstclear_pipex(pid_list);
		exit(-1);
	}
	if (cmd_exec(cmd2, cmd2_path, envp) == -1)
	{
		exec_cmd2_fail(cmd2, cmd2_path, pid_list);
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	free_split(char	**split)
{
	int	i;

	i = 0;
	while (split[i] != 0)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
