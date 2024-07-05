/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:46:04 by fli               #+#    #+#             */
/*   Updated: 2024/07/05 13:41:31 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdarg.h>
#include "libft.h"

typedef struct s_pids
{
	int				cmd_i;
	int				status;
	int				pipefd[2];
	pid_t			p_id;
	struct s_pids	*next;
}	t_pids;

int	main(int argc, char **argv, char **envp);

char	*get_pathname(char **envp, char *cmd);

int	tab_len(char **path_tab);

char	**get_path_tab(char **envp);

void	close_pipe(int pipefd[2]);

t_pids	*ft_lstnew_pipex(int cmd_i);

void	ft_lstadd_back_pipex(t_pids **lst, t_pids *n);

void	ft_lst_new_add_back_pipex(pid_t p_id, t_pids **lst);

void	ft_lstclear_pipex(t_pids **lst);

void	wait_pids(t_pids **lst, char **argv);

int	cmd1_fd_manager(char **argv, t_pids	*new_nod);

int	cmd_fd_manager(t_pids	*new_nod);

int	cmd2_fd_manager(int cmd_i, char **argv, t_pids	*new_nod, t_pids	**pid_list);

int	cmd1_child(int *cmd_i, t_pids	**pid_list, char **argv, char **envp);

int	cmd1_exec(int cmd_i, char **argv, char **envp, t_pids	*new_nod);

int	cmd_exec(char **cmd, char *cmd_path, char **envp);

int	cmd2_child(int cmd_i, t_pids	**pid_list, char **argv, char **envp);

int	cmd2_exec(int cmd_i, char **argv, char **envp, t_pids	**pid_list);

char	*ft_strjoin_pipex(char const *s1, char const *s2);

void	ft_dprintf_s(va_list arg_ptr, int *count, int fd);

int		ft_dprintf(int fd, const char *entry, ...);

int	infile_check(int err);

void	err_infile(char **argv, int status);

void	cmd_null(int status);

void	free_split(char	**split);

void	fail_cleaner(t_pids **pid_list);

void	close_and_clear(int	pipe[2], t_pids	**pid_list);

#endif
