/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_manager_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:16:14 by fli               #+#    #+#             */
/*   Updated: 2024/07/01 16:45:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	cmd1_fd_manager(char **argv, t_pids	*new_nod)
{
	int	fd_in;

	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) != 0)
		fd_in = open(argv[1], O_RDONLY);
	else
		fd_in = open("here_doc", O_RDONLY);
	if (fd_in == -1)
		infile_check(errno);
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (-1);
	close(fd_in);
	if (dup2((new_nod)->pipefd[1], STDOUT_FILENO) == -1)
		return (-1);
	close_pipe((new_nod)->pipefd);
	return (0);
}

int	cmd_fd_manager(t_pids	*new_nod)
{

	if (dup2((new_nod)->pipefd[1], STDOUT_FILENO) == -1)
		return (-1);
	close_pipe(new_nod->pipefd);
	return (0);
}

int	cmd2_fd_manager(int cmd_i, char **argv, t_pids	*new_nod)
{
	int	fd_out;

	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) != 0)
		fd_out = open(argv[cmd_i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(argv[cmd_i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out == -1)
		exit(4);
	if (dup2(fd_out, 1) == -1)
		return (-1);
	close(fd_out);
	close_pipe((new_nod)->pipefd);
	return (0);
}
