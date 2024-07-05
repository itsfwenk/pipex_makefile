/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:40:12 by fli               #+#    #+#             */
/*   Updated: 2024/07/05 14:07:58 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*get_pathname(char **envp, char *cmd)
{
	int		i;
	char	**path_tab;
	char	*pathname_cmd;

	if (cmd == NULL)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	path_tab = get_path_tab(envp);
	if (path_tab == NULL)
		return (NULL);
	i = 0;
	while (path_tab[i] != NULL)
	{
		pathname_cmd = ft_strjoin_pipex(path_tab[i], cmd);
		if (pathname_cmd == NULL)
			return (free_split(path_tab), NULL);
		if (access(pathname_cmd, X_OK) == 0)
			return (free_split(path_tab), pathname_cmd);
		i++;
		free(pathname_cmd);
	}
	free_split(path_tab);
	return (NULL);
}

int	tab_len(char **path_tab)
{
	int	tab_len;

	tab_len = 0;
	while (path_tab[tab_len] != NULL)
		tab_len++;
	return (tab_len);
}

char	*get_env(char **envp)
{
	int		i;
	char	*path_s;

	i = 0;
	while (envp[i] != NULL)
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'
			&& envp[i][2] == 'T' && envp[i][3] == 'H')
		{
			path_s = envp[i];
			return (path_s);
		}
		i++;
	}
	return (NULL);
}

char	**get_path_tab(char **envp)
{
	int			first_len;
	char		*path_s;
	char		**path_tab;

	path_s = get_env(envp);
	if (path_s == NULL)
		return (NULL);
	path_tab = ft_split(path_s, ':');
	if (path_tab == NULL)
		return (NULL);
	first_len = ft_strlen(path_tab[0] + 5);
	ft_memmove(path_tab[0], path_tab[0] + 5, ft_strlen(path_tab[0] + 5));
	ft_bzero(path_tab[0] + first_len, ft_strlen(path_tab[0]) - first_len);
	return (path_tab);
}

void	close_pipe(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}
