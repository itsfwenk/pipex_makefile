/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:02:34 by fli               #+#    #+#             */
/*   Updated: 2024/07/05 14:08:59 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	cmd_exec(char **cmd, char *cmd_path, char **envp)
{
	if (execve(cmd_path, (char *const *)cmd, (char *const *)envp) == -1)
		return (-1);
	return (0);
}

void	del_heredoc(t_pids	*pid_list)
{
	char	*heredoc_name;
	char	*i_to_a;

	i_to_a = ft_itoa(pid_list->here_doc);
	heredoc_name = ft_strjoin("here_doc", i_to_a);
	if (heredoc_name == NULL)
		return ;
	unlink(heredoc_name);
	free(heredoc_name);
	free(i_to_a);
}

int	main(int argc, char **argv, char **envp)
{
	int		cmd_i;
	int		cmd1;
	t_pids	*pid_list;

	if (argc < 5)
		return (0);
	pid_list = NULL;
	cmd_i = 2;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		cmd_i++;
	cmd1 = cmd1_child(&cmd_i, &pid_list, argv, envp);
	if (cmd1 == 2 || cmd1 == 3)
		exit(cmd1);
	while (cmd_i < (argc - 2))
	{
		if (cmd_middle_child(&cmd_i, &pid_list, argv, envp) == -1)
			exit(EXIT_FAILURE);
	}
	if (cmd2_child(cmd_i, &pid_list, argv, envp) == -1)
		exit(EXIT_FAILURE);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		del_heredoc(pid_list);
	wait_pids(&pid_list, argv);
	ft_lstclear_pipex(&pid_list);
}
